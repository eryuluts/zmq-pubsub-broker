/* SPDX-License-Identifier: MPL-2.0 */

#include <gtest/gtest.h>
#include <iostream>
#include "pubsubservice.pb.h"
#include "test_models.pb.h"

#include "subscriber.hpp"
#include "publisher.hpp"

TEST(TestPublicationMessage, test_conversion_to_any)
{
    test_models::ExamplePayload ex_payload;
    test_models::ExamplePayload recv_payload;
    pubsubservice::Publication pub;

    ex_payload.set_name("test message");
    pub.mutable_payload()->PackFrom(ex_payload);
    pub.payload().UnpackTo(&recv_payload);
    EXPECT_EQ(recv_payload.name(), ex_payload.name());
}

TEST(TestSubscriber, test_publication)
{
    std::string test_topic{"test-topic"};
    pubsubservice::Subscriber sub("tcp://localhost:5555");
    pubsubservice::Publisher pub("tcp://lo:5555");

    using namespace std::literals::chrono_literals;
    auto handler = [](auto publication)
    {
        pubsubservice::Publication msg;
        publication.payload().UnpackTo(&msg);
        std::cout << msg.DebugString();
    };

    sub.subscribe(test_topic, handler);
    std::this_thread::sleep_for(1s);

    test_models::ExamplePayload ex_payload;
    ex_payload.set_name("test message");
    pubsubservice::Publication msg;
    msg.mutable_payload()->PackFrom(ex_payload);
    pub.publish(test_topic, msg);
    std::this_thread::sleep_for(1s);
}