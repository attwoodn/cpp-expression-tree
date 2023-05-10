#pragma once

#include <attwoodn/expression_tree.hpp>
#include <memory>
#include <string>

namespace et = attwoodn::expression_tree;

struct test_fixture {
    std::string some_string;
    const std::string some_const_string = "this IS 4 T3s7 $tRing    ";
    char* some_char_ptr;
    uint16_t some_uint;

    bool is_some_uint_greater_than_zero() const {
        return some_uint;
    }
};

struct packet_payload {
    const uint16_t error_code; 
    std::string data;

    uint64_t payload_size() const {
        return data.size();
    }
};

class data_packet {
    const uint32_t sender_id;
    packet_payload payload;
};