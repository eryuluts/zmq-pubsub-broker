#include <gtest/gtest.h>
#include <iostream>
#include "pubsubservice.pb.h"
#include "test_models.pb.h"

#include "subscriber.hpp"

TEST(TestPublicationMessage, test_any_conversion)
{
    test_models::ExamplePayload ex_payload;
    test_models::ExamplePayload recv_payload;
    pubsubservice::Publication pub;

    ex_payload.set_name("Eray");
    pub.mutable_payload()->PackFrom(ex_payload);
    pub.payload().UnpackTo(&recv_payload);
    EXPECT_EQ(recv_payload.name(), ex_payload.name());
}