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
    uint16_t error_code; 
    std::string data;
    bool checksum_ok;

    uint64_t payload_size() const {
        return data.size();
    }
};

class data_packet {
    public:
        std::string sender_name;
        packet_payload payload;
};

struct my_type {
    int my_int;
    bool my_bool;

    int get_my_int() const {
        return my_int;      
    }
};