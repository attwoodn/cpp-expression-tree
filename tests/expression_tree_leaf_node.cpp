#include <attwoodn/expression_tree.hpp>
#include <iostream>
#include <cassert>

using namespace attwoodn::expression_tree;

struct test_fixture {
    std::string some_string;
};

template<class T> struct type_id{typedef T type;}; 

// template<typename Obj, typename CompValue, typename Op = typename type_id<bool (*)(CompValue*, CompValue*)>::type>
// node::expression_tree_leaf_node<Obj, Op, CompValue>* make_leaf_node( CompValue Obj::* member_var, Op op, CompValue comp_value ) {
//     return new node::expression_tree_leaf_node<Obj, Op, CompValue>( member_var, op, comp_value );
// }

template<typename Obj, typename CompValue, typename Op = typename type_id<bool (*)(CompValue, CompValue)>::type>
node::expression_tree_leaf_node<Obj, Op, CompValue>* make_leaf_node( CompValue Obj::* member_var, Op op, CompValue comp_value ) {
    return new node::expression_tree_leaf_node<Obj, Op, CompValue>( member_var, op, comp_value );
}

int main(int argc, char** argv) {
    test_fixture fixture;
    fixture.some_string = "hello world!";

    auto node = make_leaf_node(&test_fixture::some_string, &op::equals, std::string("hello world!"));
    assert(node->evaluate(fixture));

    fixture.some_string = "hey, world!";
    assert(!node->evaluate(fixture));

    return EXIT_SUCCESS;
}