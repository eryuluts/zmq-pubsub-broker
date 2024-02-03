#pragma once
#include <zmq.hpp>
#include "pubsubservice.pb.h"

namespace pubsubservice
{
class Publisher
{
  public:
    Publisher(std::string addr);
    void publish(std::string topic, Publication msg);

  private:
    zmq::context_t ctx;
    zmq::socket_t sock;
};

} // namespace pubsubservice
