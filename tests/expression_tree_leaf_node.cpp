#include <attwoodn/expression_tree.hpp>
#include <iostream>
#include <cassert>

using namespace attwoodn::expression_tree;

struct test_fixture {
    std::string some_string;
    const std::string some_const_string = "this IS 4 T3s7 $tRing    ";
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

    // test const string
    {
        // test equals
        {
            auto expr1 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("hello world!"));
            assert(!expr1->evaluate(fixture));

            auto expr2 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("h"));
            assert(!expr2->evaluate(fixture));

            auto expr3 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("t"));
            assert(!expr3->evaluate(fixture));

            auto expr4 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("this "));
            assert(!expr4->evaluate(fixture));

            auto expr5 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing   "));
            assert(!expr5->evaluate(fixture));

            auto expr6 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing"));
            assert(!expr6->evaluate(fixture));

            auto expr7 = make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing    "));
            assert(expr7->evaluate(fixture));

            auto expr8 = make_expr(&test_fixture::some_const_string, &op::equals, fixture.some_const_string);
            assert(expr8->evaluate(fixture));
        }

        // test not_equals
        {
            auto expr1 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("hello world!"));
            assert(expr1->evaluate(fixture));

            auto expr2 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("h"));
            assert(expr2->evaluate(fixture));

            auto expr3 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("t"));
            assert(expr3->evaluate(fixture));

            auto expr4 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this "));
            assert(expr4->evaluate(fixture));

            auto expr5 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing   "));
            assert(expr5->evaluate(fixture));

            auto expr6 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing"));
            assert(expr6->evaluate(fixture));

            auto expr7 = make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing    "));
            assert(!expr7->evaluate(fixture));

            auto expr8 = make_expr(&test_fixture::some_const_string, &op::not_equals, fixture.some_const_string);
            assert(!expr8->evaluate(fixture));
        }

        // test less_than
        {
            auto expr1 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("u"));
            assert(expr1->evaluate(fixture));

            auto expr2 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("z"));
            assert(expr2->evaluate(fixture));

            auto expr3 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this IS 4 T3s7 $tRing          "));
            assert(expr3->evaluate(fixture));

            auto expr4 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("1234567890"));
            assert(!expr4->evaluate(fixture));

            auto expr5 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("A"));
            assert(!expr5->evaluate(fixture));

            auto expr6 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this "));
            assert(!expr6->evaluate(fixture));

            auto expr7 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("stuff"));
            assert(!expr7->evaluate(fixture));

            auto expr8 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("abcdefghijklmnopqrstuvwxyz"));
            assert(!expr8->evaluate(fixture));

            auto expr9 = make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this IS 4 T3s7 $tRing    "));
            assert(!expr9->evaluate(fixture));

            auto expr10 = make_expr(&test_fixture::some_const_string, &op::less_than, fixture.some_const_string);
            assert(!expr10->evaluate(fixture));
        }

        // test greater_than
        {
            auto expr1 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("u"));
            assert(!expr1->evaluate(fixture));

            auto expr2 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("z"));
            assert(!expr2->evaluate(fixture));

            auto expr3 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this IS 4 T3s7 $tRing          "));
            assert(!expr3->evaluate(fixture));

            auto expr4 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("1234567890"));
            assert(expr4->evaluate(fixture));

            auto expr5 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("A"));
            assert(expr5->evaluate(fixture));

            auto expr6 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this "));
            assert(expr6->evaluate(fixture));

            auto expr7 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("stuff"));
            assert(expr7->evaluate(fixture));

            auto expr8 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("abcdefghijklmnopqrstuvwxyz"));
            assert(expr8->evaluate(fixture));

            auto expr9 = make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this IS 4 T3s7 $tRing    "));
            assert(!expr9->evaluate(fixture));

            auto expr10 = make_expr(&test_fixture::some_const_string, &op::greater_than, fixture.some_const_string);
            assert(!expr10->evaluate(fixture));
        }
    }

    // test non-const string
    {
        fixture.some_string = "hello world!";

        auto node = make_expr(&test_fixture::some_string, &op::equals, std::string("hello world!"));
        assert(node->evaluate(fixture));

        fixture.some_string = "hey, world!";
        assert(!node->evaluate(fixture));
    }
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