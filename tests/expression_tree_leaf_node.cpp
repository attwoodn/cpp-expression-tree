#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include <limits>
#include <iostream>
#include <cassert>

using namespace attwoodn::expression_tree;

void test_string_evaluation();
void test_char_ptr_evaluation();
void test_uint_evaluation();
void test_const_func_evaluation();

int main(int argc, char** argv) {
    test_string_evaluation();
    test_char_ptr_evaluation();
    test_uint_evaluation();
    test_const_func_evaluation();

    return EXIT_SUCCESS;
}

void test_string_evaluation() {
    test_fixture fixture;

    // test const string
    {
        // test equals
        {
            auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("hello world!"))
            );
            assert(!expr1->evaluate(fixture));

            auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("h"))
            );
            assert(!expr2->evaluate(fixture));

            auto expr3 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("t"))
            );
            assert(!expr3->evaluate(fixture));

            auto expr4 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("this "))
            );
            assert(!expr4->evaluate(fixture));

            auto expr5 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing   "))
            );
            assert(!expr5->evaluate(fixture));

            auto expr6 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing"))
            );
            assert(!expr6->evaluate(fixture));

            auto expr7 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, std::string("this IS 4 T3s7 $tRing    "))
            );
            assert(expr7->evaluate(fixture));

            auto expr8 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::equals, fixture.some_const_string)
            );
            assert(expr8->evaluate(fixture));
        }

        // test not_equals
        {
            auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("hello world!"))
            );
            assert(expr1->evaluate(fixture));

            auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("h"))
            );
            assert(expr2->evaluate(fixture));

            auto expr3 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("t"))
            );
            assert(expr3->evaluate(fixture));

            auto expr4 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this "))
            );
            assert(expr4->evaluate(fixture));

            auto expr5 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing   "))
            );
            assert(expr5->evaluate(fixture));

            auto expr6 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing"))
            );
            assert(expr6->evaluate(fixture));

            auto expr7 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, std::string("this IS 4 T3s7 $tRing    "))
            );
            assert(!expr7->evaluate(fixture));

            auto expr8 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::not_equals, fixture.some_const_string)
            );
            assert(!expr8->evaluate(fixture));
        }

        // test less_than
        {
            auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("u"))
            );
            assert(expr1->evaluate(fixture));

            auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("z"))
            );
            assert(expr2->evaluate(fixture));

            auto expr3 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this IS 4 T3s7 $tRing          "))
            );
            assert(expr3->evaluate(fixture));

            auto expr4 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("1234567890"))
            );
            assert(!expr4->evaluate(fixture));

            auto expr5 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("A"))
            );
            assert(!expr5->evaluate(fixture));

            auto expr6 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this "))
            );
            assert(!expr6->evaluate(fixture));

            auto expr7 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("stuff"))
            );
            assert(!expr7->evaluate(fixture));

            auto expr8 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("abcdefghijklmnopqrstuvwxyz"))
            );
            assert(!expr8->evaluate(fixture));

            auto expr9 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, std::string("this IS 4 T3s7 $tRing    "))
            );
            assert(!expr9->evaluate(fixture));

            auto expr10 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::less_than, fixture.some_const_string)
            );
            assert(!expr10->evaluate(fixture));
        }

        // test greater_than
        {
            auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("u"))
            );
            assert(!expr1->evaluate(fixture));

            auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("z"))
            );
            assert(!expr2->evaluate(fixture));

            auto expr3 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this IS 4 T3s7 $tRing          "))
            );
            assert(!expr3->evaluate(fixture));

            auto expr4 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("1234567890"))
            );
            assert(expr4->evaluate(fixture));

            auto expr5 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("A"))
            );
            assert(expr5->evaluate(fixture));

            auto expr6 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this "))
            );
            assert(expr6->evaluate(fixture));

            auto expr7 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("stuff"))
            );
            assert(expr7->evaluate(fixture));

            auto expr8 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("abcdefghijklmnopqrstuvwxyz"))
            );
            assert(expr8->evaluate(fixture));

            auto expr9 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, std::string("this IS 4 T3s7 $tRing    "))
            );
            assert(!expr9->evaluate(fixture));

            auto expr10 = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_const_string, &op::greater_than, fixture.some_const_string)
            );
            assert(!expr10->evaluate(fixture));
        }
    }

    // test non-const string
    {
        // test equals
        {
            auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, &op::equals, std::string("hello world!"))
            );

            fixture.some_string = "hello world!";
            assert(expr->evaluate(fixture));

            fixture.some_string = "hey, world!";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "1234";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "-----";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "";
            assert(!expr->evaluate(fixture));

            fixture.some_string = " ";
            assert(!expr->evaluate(fixture));
        }

        // test not_equals
        {
            auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, &op::not_equals, std::string("hello world!"))
            );

            fixture.some_string = "hello world!";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "hey, world!";
            assert(expr->evaluate(fixture));

            fixture.some_string = "1234";
            assert(expr->evaluate(fixture));

            fixture.some_string = "-----";
            assert(expr->evaluate(fixture));

            fixture.some_string = "";
            assert(expr->evaluate(fixture));

            fixture.some_string = " ";
            assert(expr->evaluate(fixture));
        }

        // test less_than
        {
            auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, &op::less_than, std::string("this IS 4 T3s7 $tRing    "))
            );

            fixture.some_string = "u";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "z";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "this IS 4 T3s7 $tRing          ";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "";
            assert(expr->evaluate(fixture));

            fixture.some_string = "1234567890";
            assert(expr->evaluate(fixture));

            fixture.some_string = "A";
            assert(expr->evaluate(fixture));

            fixture.some_string = "this ";
            assert(expr->evaluate(fixture));

            fixture.some_string = "stuff";
            assert(expr->evaluate(fixture));

            fixture.some_string = "abcdefghijklmnopqrstuvwxyz";
            assert(expr->evaluate(fixture));

            fixture.some_string = "this IS 4 T3s7 $tRing    ";
            assert(!expr->evaluate(fixture));
        }

        // test greater_than
        {
            auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, &op::greater_than, std::string("this IS 4 T3s7 $tRing    "))
            );

            fixture.some_string = "u";
            assert(expr->evaluate(fixture));

            fixture.some_string = "z";
            assert(expr->evaluate(fixture));

            fixture.some_string = "this IS 4 T3s7 $tRing          ";
            assert(expr->evaluate(fixture));

            fixture.some_string = "";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "1234567890";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "A";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "this ";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "stuff";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "abcdefghijklmnopqrstuvwxyz";
            assert(!expr->evaluate(fixture));

            fixture.some_string = "this IS 4 T3s7 $tRing    ";
            assert(!expr->evaluate(fixture));
        }
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
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_char_ptr, &op::equals, &a)
        );

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
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_char_ptr, &op::not_equals, &a)
        );

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
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_char_ptr, &op::less_than, &b)
        );

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
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_char_ptr, &op::greater_than, &b)
        );

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

void test_uint_evaluation() {
    test_fixture fixture;

    // test equals
    {
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_uint, op::equals, (uint16_t) 9001)
        );

        fixture.some_uint = 0;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 1;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9000;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9002;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9001;
        assert(expr->evaluate(fixture));
    }

    // test not_equals
    {
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_uint, op::not_equals, (uint16_t) 9001)
        );

        fixture.some_uint = 0;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 1;
        assert(expr->evaluate(fixture));

        fixture.some_uint = -1;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9000;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9002;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9001;
        assert(!expr->evaluate(fixture));
    }

    // test less_than
    {
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_uint, op::less_than, (uint16_t) 9001)
        );

        fixture.some_uint = 0;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 1;
        assert(expr->evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9000;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9002;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9001;
        assert(!expr->evaluate(fixture));
    }

    // test greater_than
    {
        auto expr = std::unique_ptr<node::expression_tree_node<test_fixture>>(
            make_expr(&test_fixture::some_uint, op::greater_than, (uint16_t) 9001)
        );

        fixture.some_uint = 0;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 1;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = -1;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9000;
        assert(!expr->evaluate(fixture));

        fixture.some_uint = 9002;
        assert(expr->evaluate(fixture));

        fixture.some_uint = 9001;
        assert(!expr->evaluate(fixture));
    }
}

void test_const_func_evaluation() {
    test_fixture fixture;

    // test equals
    {
        auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::equals, true));
        auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::equals, false));

        fixture.some_uint = 0;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::min();
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = 1;
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = 500;
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::max();
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = -1;
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));
    }

    // test not_equals
    {
        auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::not_equals, true));
        auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::not_equals, false));

        fixture.some_uint = 0;
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::min();
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = 1;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = 500;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::max();
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));
    }

    // test less_than
    {
        auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::less_than, true));
        auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::less_than, false));

        fixture.some_uint = 0;
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::min();
        assert(expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = 1;
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = 500;
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::max();
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));
    }

    // test greater_than
    {
        auto expr1 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::greater_than, true));
        auto expr2 = std::unique_ptr<node::expression_tree_node<test_fixture>>(make_expr(&test_fixture::is_some_uint_greater_than_zero, &op::greater_than, false));

        fixture.some_uint = 0;
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::min();
        assert(!expr1->evaluate(fixture));
        assert(!expr2->evaluate(fixture));

        fixture.some_uint = 1;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = 500;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = std::numeric_limits<uint16_t>::max();
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr1->evaluate(fixture));
        assert(expr2->evaluate(fixture));
    }
}