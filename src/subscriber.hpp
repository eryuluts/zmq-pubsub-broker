#pragma once
#include <string>
#include <functional>

namespace pubsubservice
{
using topic_handler = std::function<void(std::string)>;

class Subscriber
{
  public:
    void subscribe(std::string topic, topic_handler handler);
};

} // namespace pubsubservice
