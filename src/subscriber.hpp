#pragma once
#include <string>
#include <functional>
#include "pubsubservice.pb.h"

namespace pubsubservice
{
using topic_handler = std::function<void(pubsubservice::Publication)>;

class Subscriber
{
  public:
    void subscribe(std::string topic, topic_handler handler);
};

} // namespace pubsubservice
