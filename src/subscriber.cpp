/* SPDX-License-Identifier: MPL-2.0 */

#include "subscriber.hpp"
#include <fmt/format.h>

namespace pubsubservice
{
Subscriber::Subscriber(std::string addr) : m_addr(addr)
{
    m_sock = zmq::socket_t(m_ctx, zmq::socket_type::sub);
    m_sock.set(zmq::sockopt::rcvtimeo, 100);
    m_sock.connect(m_addr);

    m_subscriber_thread = std::jthread(&Subscriber::subscriber_task, this);
}

void Subscriber::subscribe(std::string topic, topic_handler handler)
{
    std::lock_guard lock(m_lock);
    m_sock.set(zmq::sockopt::subscribe, topic);
    m_topic_handlers.emplace(topic, handler);
}

/**
 * Publication Frames:
 *  [topic]
 *  [data]
 */
void Subscriber::subscriber_task()
{
    using namespace std::literals::chrono_literals;
    auto st = m_subscriber_thread.get_stop_token();

    while (!st.stop_requested())
    {
        zmq::multipart_t msg;
        auto rs = msg.recv(m_sock);
        if (!rs)
        {
            continue;
        }
        fmt::println("I: message received: {}", msg.str());

        try
        {
            dispatch(std::move(msg));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Subscriber::dispatch(zmq::multipart_t msg)
{
    std::lock_guard lock(m_lock);
    std::string topic = msg.popstr();
    std::string data = msg.popstr();

    pubsubservice::Publication pub;
    if (!pub.ParseFromString(data))
    {
        throw std::runtime_error(fmt::format("topic: {}: can't parse received publication", topic));
    }

    for (auto [k, handler] : m_topic_handlers)
    {
        if (k == topic)
        {
            try
            {
                handler(pub);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}
} // namespace pubsubservice
