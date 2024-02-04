/* SPDX-License-Identifier: MPL-2.0 */

#pragma once
#include <functional>
#include <map>
#include <thread>
#include <zmq_addon.hpp>
#include <mutex>
#include "pubsubservice.pb.h"

namespace pubsubservice
{
using topic_handler = std::function<void(pubsubservice::Publication)>;

class Subscriber
{
  public:
    Subscriber(std::string addr);
    void subscribe(std::string topic, topic_handler handler);

  private:
    std::unordered_multimap<std::string, topic_handler> topic_handlers;
    std::string m_addr;

    zmq::context_t ctx;
    zmq::socket_t sock;
    std::jthread subscriber_thread;
    std::mutex m_lock;
    void subscriber_task();
    void dispatch(zmq::multipart_t msg);
};

} // namespace pubsubservice
