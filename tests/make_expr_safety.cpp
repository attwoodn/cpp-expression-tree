#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include <cassert>

using namespace attwoodn::expression_tree;

void make_expr_memory_safety_test();

int main(int argc, char** argv) {
    make_expr_memory_safety_test();

    return EXIT_SUCCESS;
}

void make_expr_memory_safety_test() {

    {
        // The heap-allocated expression node pointer returned by make_expr becomes owned by the expression_tree
        expression_tree<my_type> expr_tree_raw {
            make_expr(&my_type::my_bool, op::equals, true)
        };

        expression_tree<my_type> expr_tree_raw_AND {
            make_expr(&my_type::my_bool, op::equals, true)
            ->AND(make_expr(&my_type::my_int, op::greater_than, 10))
        };
    }

    {
        // The heap-allocated expression node pointer returned by make_expr becomes owned by the unique_ptr
        std::unique_ptr<node::expression_tree_node<my_type>> smart_expr {
            make_expr(&my_type::my_bool, op::equals, true)
        };

        // the expression_tree takes ownership of the unique_ptr
        expression_tree<my_type> expr_tree_smart(std::move(smart_expr));
    }

    {
        // The heap-allocated expression node pointer returned by make_expr must be explicitly deleted
        auto* expr_raw = make_expr(&my_type::my_bool, op::equals, true);
        delete expr_raw;

        auto* expr_raw_AND = make_expr(&my_type::my_bool, op::equals, true)
                                ->AND(make_expr(&my_type::my_int, op::greater_than, 10));
        delete expr_raw_AND;
    }
}