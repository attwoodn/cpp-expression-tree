#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include <cassert>

using namespace attwoodn::expression_tree;

void test_simple_expression_tree();
void test_complex_expression_tree();
void test_moved_expression_tree();
void test_copied_expression_tree();
void test_user_defined_operator();

int main(int argc, char** argv) {
    test_simple_expression_tree();
    test_complex_expression_tree();
    test_moved_expression_tree();
    test_copied_expression_tree();
    test_user_defined_operator();

    return EXIT_SUCCESS;
}

void test_simple_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
        fixture.some_string = "hello!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello          world!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello,world!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello, world!";
        assert(expr.evaluate(fixture));
    };

    // test raw pointer creation of expression_tree
    {
        expression_tree<test_fixture> expr {
            make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
        };

        test_procedure(expr);
    }

    // test unique_ptr creation of expression_tree
    {
        expression_tree<test_fixture> expr {
            std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
            )
        };

        test_procedure(expr);
    }
}

void test_complex_expression_tree() {

    // expression: (uint > 0 AND (some_string > "a" AND some_string < "z")) OR (some_string > "0" AND some_string < "9")
    expression_tree<test_fixture> expr {
        (make_expr(&test_fixture::is_some_uint_greater_than_zero, op::equals, true)
            ->AND((make_expr(&test_fixture::some_string, op::greater_than, std::string("a"))
                ->AND(make_expr(&test_fixture::some_string, op::less_than, std::string("z")))
            ))
        )
        ->OR((make_expr(&test_fixture::some_string, op::greater_than, std::string("0"))
                ->AND(make_expr(&test_fixture::some_string, op::less_than, std::string("9")))
            )
        )
    };

    test_fixture fixture;

    fixture.some_uint = 0;

    // test left-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "a";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "aaa";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "c";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "yyyyy";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "B";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "ZZZ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "/";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "red";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "                              ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "tree fiddy";
        assert(!expr.evaluate(fixture));
    }

    // test right-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "000";
        assert(expr.evaluate(fixture));

        fixture.some_string = "00";
        assert(expr.evaluate(fixture));

        fixture.some_string = "0";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "12345";
        assert(expr.evaluate(fixture));

        fixture.some_string = "7";
        assert(expr.evaluate(fixture));

        fixture.some_string = "89999";
        assert(expr.evaluate(fixture));

        fixture.some_string = "9";
        assert(!expr.evaluate(fixture));
    }

    fixture.some_uint = 1;
    
    // test left-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "a";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "aaa";
        assert(expr.evaluate(fixture));

        fixture.some_string = "c";
        assert(expr.evaluate(fixture));

        fixture.some_string = "yyyyy";
        assert(expr.evaluate(fixture));

        fixture.some_string = "B";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "ZZZ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "/";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "red";
        assert(expr.evaluate(fixture));

        fixture.some_string = "                              ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "tree fiddy";
        assert(expr.evaluate(fixture));
    }

    // test right-hand side of the expression tree when some_uint is 1
    {
        fixture.some_string = "000";
        assert(expr.evaluate(fixture));

        fixture.some_string = "00";
        assert(expr.evaluate(fixture));

        fixture.some_string = "0";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "12345";
        assert(expr.evaluate(fixture));

        fixture.some_string = "7";
        assert(expr.evaluate(fixture));

        fixture.some_string = "89999";
        assert(expr.evaluate(fixture));

        fixture.some_string = "9";
        assert(!expr.evaluate(fixture));
    }


}

void test_moved_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
    
        fixture.some_uint = 345;
        assert(expr.evaluate(fixture));
        
        fixture.some_uint = 123;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 543;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0x04;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 3;
        assert(!expr.evaluate(fixture));
    };

    expression_tree<test_fixture> expr {
        make_expr(&test_fixture::some_uint, op::equals, (uint16_t) 345)
    };
    test_procedure(expr);

    expression_tree<test_fixture> move_constructed_expr(std::move(expr));
    test_procedure(move_constructed_expr);
    
    expression_tree<test_fixture> move_assigned_expr = std::move(move_constructed_expr);
    test_procedure(move_assigned_expr);
}

void test_copied_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
    
        fixture.some_uint = 345;
        assert(expr.evaluate(fixture));
        
        fixture.some_uint = 123;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 543;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0x04;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 3;
        assert(!expr.evaluate(fixture));
    };

    expression_tree<test_fixture> expr {
        make_expr(&test_fixture::some_uint, op::equals, (uint16_t) 345)
    };
    test_procedure(expr);

    expression_tree<test_fixture> copy_constructed_expr(expr);
    test_procedure(copy_constructed_expr);
    
    expression_tree<test_fixture> copy_assigned_expr = copy_constructed_expr;
    test_procedure(copy_assigned_expr);

    // ensure both of the old copied versions still work after copying
    test_procedure(expr);
    test_procedure(copy_constructed_expr);
}

void test_user_defined_operator() {

}