#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include <limits>
#include <iostream>
#include <cassert>

using namespace attwoodn::expression_tree;

void test_one_layer_op_node_evaluation();

int main(int argc, char** argv) {
    test_one_layer_op_node_evaluation();

    return EXIT_SUCCESS;
}

void test_one_layer_op_node_evaluation() {
    auto child_expr1 = make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"));
    auto child_expr2 = make_expr(&test_fixture::some_uint, op::less_than, (uint16_t) 500);

    auto expr = make_op_node<test_fixture>(child_expr1, boolean_op::AND, child_expr2);
    
    test_fixture fixture;
    fixture.some_string = "hello, world!";
    fixture.some_uint = 499;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 0;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 1;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 250;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 435;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 500;
    assert(!expr->evaluate(fixture));
    
    fixture.some_uint = 501;
    assert(!expr->evaluate(fixture));

    fixture.some_uint = 9999;
    assert(!expr->evaluate(fixture));

    fixture.some_uint = std::numeric_limits<uint16_t>::max();
    assert(!expr->evaluate(fixture));

    fixture.some_uint = 499;
    assert(expr->evaluate(fixture));

    fixture.some_string = "hello!";
    assert(!expr->evaluate(fixture));

    fixture.some_string = "hello          world!";
    assert(!expr->evaluate(fixture));

    fixture.some_string = "hello,world!";
    assert(!expr->evaluate(fixture));

    fixture.some_string = "hello, world!";
    assert(expr->evaluate(fixture));
}