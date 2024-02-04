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

TEST(TestSubscriber, test_publication_multi_handler)
{
    using namespace std::literals::chrono_literals;
    std::string addr{"tcp://localhost:5555"};

    std::string test_topic1{"test-topic-1"};
    test_models::ExamplePayload msg1;
    msg1.set_name("test message-1");
    std::atomic<int> counter1{0};
    auto handler1 = [&counter1, msg1](const pubsubservice::Publication &pub)
    {
        counter1++;
        test_models::ExamplePayload recv_msg;
        pub.payload().UnpackTo(&recv_msg);
        EXPECT_TRUE(google::protobuf::util::MessageDifferencer().Equals(msg1, recv_msg));
    };

    std::string test_topic2{"test-topic-2"};
    test_models::ExamplePayload msg2;
    msg2.set_name("test message-2");
    std::atomic<int> counter2{0};
    auto handler2 = [&counter2, msg2](const pubsubservice::Publication &pub)
    {
        counter2++;
        test_models::ExamplePayload recv_msg;
        pub.payload().UnpackTo(&recv_msg);
        EXPECT_TRUE(google::protobuf::util::MessageDifferencer().Equals(msg2, recv_msg));
    };

    std::string test_topic3{"test-topic-3"};
    std::atomic<int> counter3{0};
    auto handler3 = [&counter3](const pubsubservice::Publication &pub) { counter3++; };

    std::string general_topic{"test-topic"};
    std::atomic<int> counter4{0};
    auto general_handler = [&counter4](const pubsubservice::Publication &pub) { counter4++; };

    pubsubservice::Subscriber sub(addr);
    pubsubservice::Publisher pub(addr);
    sub.subscribe(test_topic1, handler1);
    sub.subscribe(test_topic2, handler2);
    sub.subscribe(test_topic3, handler3);
    sub.subscribe(general_topic, general_handler);
    std::this_thread::sleep_for(200ms); // wait for zeromq subscription to happen.

    pub.publish(test_topic1, msg1);
    pub.publish(test_topic2, msg2);
    std::this_thread::sleep_for(200ms); // wait message to be transmitted.
    ASSERT_EQ(counter1, 1);
    ASSERT_EQ(counter2, 1);
    ASSERT_EQ(counter3, 0);
    ASSERT_EQ(counter4, 2);
}