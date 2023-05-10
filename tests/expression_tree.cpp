#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include <cassert>

using namespace attwoodn::expression_tree;

void test_expression_tree_std_string_template();
void test_simple_expression_tree();
void test_complex_expression_tree();
void test_moved_expression_tree();
void test_copied_expression_tree();

int main(int argc, char** argv) {
    test_expression_tree_std_string_template();
    test_simple_expression_tree();
    test_complex_expression_tree();
    test_moved_expression_tree();
    test_copied_expression_tree();

    return EXIT_SUCCESS;
}

void test_expression_tree_std_string_template() {
    expression_tree<std::string> expr {
        make_expr(&std::string::empty, op::equals, true)
    };

    assert(expr.evaluate(""));
    assert(!expr.evaluate(" "));
    assert(!expr.evaluate("hello"));
    assert(!expr.evaluate("good bye"));
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

    expression_tree<test_fixture> move_constructed_expr( std::move(expr) );
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

    expression_tree<test_fixture> copy_constructed_expr( expr );
    test_procedure(copy_constructed_expr);
    
    expression_tree<test_fixture> copy_assigned_expr = copy_constructed_expr;
    test_procedure(copy_assigned_expr);

    // ensure both of the old copied versions still work after copying
    test_procedure(expr);
    test_procedure(copy_constructed_expr);
}