/* SPDX-License-Identifier: MPL-2.0 */

#include <gtest/gtest.h>
#include <iostream>
#include <google/protobuf/util/message_differencer.h>

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
    using namespace std::literals::chrono_literals;
    std::string test_topic{"test-topic"};
    std::string addr{"tcp://localhost:5555"};

    test_models::ExamplePayload msg;
    msg.set_name("test message");

    std::atomic<int> counter{0};
    auto handler = [&counter, msg](const pubsubservice::Publication &pub)
    {
        counter++;
        test_models::ExamplePayload recv_msg;
        pub.payload().UnpackTo(&recv_msg);
        EXPECT_TRUE(google::protobuf::util::MessageDifferencer().Equals(msg, recv_msg));
    };

    pubsubservice::Subscriber sub(addr);
    pubsubservice::Publisher pub(addr);
    sub.subscribe(test_topic, handler);
    std::this_thread::sleep_for(200ms); // wait for zeromq subscription to happen.

    pub.publish(test_topic, msg);
    std::this_thread::sleep_for(200ms); // wait message to be transmitted.
    ASSERT_TRUE(counter == 1);
}