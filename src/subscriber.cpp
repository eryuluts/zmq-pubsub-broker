#include "subscriber.hpp"
#include <fmt/format.h>

namespace pubsubservice
{
Subscriber::Subscriber(std::string addr) : m_addr(addr)
{
    sock = zmq::socket_t(ctx, zmq::socket_type::sub);
    sock.set(zmq::sockopt::rcvtimeo, 100);
    sock.connect(m_addr);

    subscriber_thread = std::jthread(&Subscriber::subscriber_task, this);
}

void Subscriber::subscribe(std::string topic, topic_handler handler)
{
    std::lock_guard lock(m_lock);
    sock.set(zmq::sockopt::subscribe, topic);
    topic_handlers.emplace(topic, handler);
}

/**
 * Publication Frames:
 *  [topic]
 *  [data]
 */
void Subscriber::subscriber_task()
{
    using namespace std::literals::chrono_literals;
    auto st = subscriber_thread.get_stop_token();

    while (!st.stop_requested())
    {
        zmq::multipart_t msg;
        auto rs = msg.recv(sock);
        if (!rs)
        {
            continue;
        }
        fmt::println("I: message received: {}", msg.str());
        dispatch(std::move(msg));
    }
}

void Subscriber::dispatch(zmq::multipart_t msg)
{
    std::lock_guard lock(m_lock);
    // TODO: call related topic handler
    std::string topic = msg.popstr();
    std::string data = msg.popstr();
}
} // namespace pubsubservice
