#include <attwoodn/expression_tree.hpp>
#include <cassert>

using namespace attwoodn::expression_tree;

void expression_memory_safety_example();

struct my_type {
   int my_int = 5;
   bool my_bool = true;
};

int main(int argc, char** argv) {
    expression_memory_safety_example();

    return EXIT_SUCCESS;
}

void expression_memory_safety_example() {
    // The heap-allocated expression node pointer returned by make_expr becomes owned by the expression_tree
    expression_tree<my_type> expr_tree_raw {
        make_expr(&my_type::my_bool, op::equals, true)
    };


    // ...


    // The heap-allocated expression node pointer returned by make_expr becomes owned by the unique_ptr
    std::unique_ptr<node::expression_tree_node<my_type>> smart_expr {
        make_expr(&my_type::my_bool, op::equals, true)
    };

    // the expression_tree takes ownership of the unique_ptr
    expression_tree<my_type> expr_tree_smart(std::move(smart_expr));


    // ...


    // The heap-allocated expression node pointer returned by make_expr must be explicitly deleted
    auto* expr_raw = make_expr(&my_type::my_bool, op::equals, true);
    delete expr_raw;
}