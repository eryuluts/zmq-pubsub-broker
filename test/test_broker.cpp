#include <gtest/gtest.h>
#include <iostream>
#include "pubsubservice.pb.h"
#include "test_models.pb.h"

#include "subscriber.hpp"

TEST(TestPublicationMessage, test_any_conversion)
{
    test_models::ExamplePayload ex_payload;
    ex_payload.set_name("Eray");

    pubsubservice::Publication pub;
    pub.mutable_payload()->PackFrom(ex_payload);

    test_models::ExamplePayload recv_payload;
    pub.payload().UnpackTo(&recv_payload);
    std::cout << recv_payload.name() << std::endl;
}