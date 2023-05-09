#include <attwoodn/expression_tree.hpp>
#include <iostream>
#include <cassert>

using namespace attwoodn::expression_tree;

struct test_fixture {
    std::string some_string;
    char* some_char_ptr;
};

void test_string_evaluation();
void test_char_ptr_evaluation();

int main(int argc, char** argv) {
    test_string_evaluation();
    test_char_ptr_evaluation();

    return EXIT_SUCCESS;
}

void test_string_evaluation() {
    test_fixture fixture;
    fixture.some_string = "hello world!";

    auto node = make_expr(&test_fixture::some_string, &op::equals, std::string("hello world!"));
    assert(node->evaluate(fixture));

    fixture.some_string = "hey, world!";
    assert(!node->evaluate(fixture));
}

void test_char_ptr_evaluation() {
    char a = 'a';
    char a_too = 'a';
    char b = 'b';
    char b_too = 'b';
    char c = 'c';
    char c_too = 'c';

    test_fixture fixture;

    // test equals
    {
        // make an expression : given char* == 'a'
        auto expr = make_expr(&test_fixture::some_char_ptr, &op::equals, &a);

        fixture.some_char_ptr = &a;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &a_too;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &b;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &b_too;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &c;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &c_too;
        assert(!expr->evaluate(fixture));
    }

    // test not_equals
    {
        // make an expression : given char* != 'a'
        auto expr = make_expr(&test_fixture::some_char_ptr, &op::not_equals, &a);

        fixture.some_char_ptr = &a;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &a_too;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &b;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &b_too;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &c;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &c_too;
        assert(expr->evaluate(fixture));
    }

    // test less_than
    {
        // make an expression : given char* < 'b'
        auto expr = make_expr(&test_fixture::some_char_ptr, &op::less_than, &b);

        fixture.some_char_ptr = &a;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &a_too;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &b;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &b_too;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &c;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &c_too;
        assert(!expr->evaluate(fixture));
    }

    // test greater_than
    {
        // make an expression : given char* > 'b'
        auto expr = make_expr(&test_fixture::some_char_ptr, &op::greater_than, &b);

        fixture.some_char_ptr = &a;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &a_too;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &b;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &b_too;
        assert(!expr->evaluate(fixture));

        fixture.some_char_ptr = &c;
        assert(expr->evaluate(fixture));

        fixture.some_char_ptr = &c_too;
        assert(expr->evaluate(fixture));
    }
}