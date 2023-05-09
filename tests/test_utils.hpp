#pragma once

#include <attwoodn/expression_tree.hpp>
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

/**
 * Helper function for creating inner expression tree nodes. I'm undecided if this should be included in the public API
*/
template<typename Obj, typename LeftChild, typename RightChild>
et::node::expression_tree_op_node<Obj, LeftChild, RightChild>* make_op_node(LeftChild* left, et::boolean_op op, RightChild* right) {
    auto node = new et::node::expression_tree_op_node<Obj, LeftChild, RightChild>(op);
    node->set_left(left);
    node->set_right(right);
    return node;
}