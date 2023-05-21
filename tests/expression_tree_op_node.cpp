#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include "release_asserts.hpp"
#include <limits>

using namespace attwoodn::expression_tree;

void test_AND_op_node_evaluation();
void test_OR_op_node_evaluation();

int main(int argc, char** argv) {
    test_AND_op_node_evaluation();
    test_OR_op_node_evaluation();

    return EXIT_SUCCESS;
}

void test_AND_op_node_evaluation() {
    auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
        make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
        ->AND(make_expr(&test_fixture::some_uint, op::less_than, (uint16_t) 500))
    );
    
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

void test_OR_op_node_evaluation() {
    auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
        make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
        ->OR(make_expr(&test_fixture::some_uint, op::less_than, (uint16_t) 500))
    );
    
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
    assert(expr->evaluate(fixture));
    
    fixture.some_uint = 501;
    assert(expr->evaluate(fixture));

    fixture.some_uint = 9999;
    assert(expr->evaluate(fixture));

    fixture.some_uint = std::numeric_limits<uint16_t>::max();
    assert(expr->evaluate(fixture));

    fixture.some_uint = 499;
    assert(expr->evaluate(fixture));

    fixture.some_string = "hello!";
    assert(expr->evaluate(fixture));

    fixture.some_string = "hello          world!";
    assert(expr->evaluate(fixture));

    fixture.some_string = "hello,world!";
    assert(expr->evaluate(fixture));

    fixture.some_string = "some test string";
    fixture.some_uint = 501;
    assert(!expr->evaluate(fixture));

    fixture.some_string = "hello!";
    fixture.some_uint = 5876;
    assert(!expr->evaluate(fixture));

    fixture.some_string = "hello hello HELLO";
    fixture.some_uint = 12345;
    assert(!expr->evaluate(fixture));

    fixture.some_string = "";
    fixture.some_uint = -1;
    assert(!expr->evaluate(fixture));

    fixture.some_string = "";
    fixture.some_uint = 0;
    assert(expr->evaluate(fixture));

    fixture.some_string = "hello, world!";
    fixture.some_uint = 350;
    assert(expr->evaluate(fixture));
}

