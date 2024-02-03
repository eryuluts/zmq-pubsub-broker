#include "subscriber.hpp"

namespace pubsubservice
{
void Subscriber::subscribe(std::string topic, topic_handler handler) { handler("test"); }
} // namespace pubsubservice
