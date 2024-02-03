#include "publisher.hpp"
#include <zmq_addon.hpp>

namespace pubsubservice
{
Publisher::Publisher(std::string addr)
{
    sock = zmq::socket_t(ctx, zmq::socket_type::pub);
    sock.bind(addr);
}
void Publisher::publish(std::string topic, Publication msg)
{
    zmq::multipart_t mp;
    mp.addstr(topic);
    mp.addstr(msg.SerializeAsString());
    zmq::send_multipart(sock, mp);
}
} // namespace pubsubservice