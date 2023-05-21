if(BUILD_TESTING) 

    add_executable( operators_test operators.cpp )
    target_link_libraries( operators_test "-fsanitize=address" )
    target_compile_options( operators_test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic -Werror )
    add_test( operators_test ${EXECUTABLE_OUTPUT_PATH}/operators_test )

    add_executable( expression_tree_leaf_node_test expression_tree_leaf_node.cpp )
    target_link_libraries( expression_tree_leaf_node_test "-fsanitize=address" )
    target_compile_options( expression_tree_leaf_node_test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic -Werror )
    add_test( expression_tree_leaf_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_leaf_node_test )

    add_executable( expression_tree_op_node_test expression_tree_op_node.cpp )
    target_link_libraries( expression_tree_op_node_test "-fsanitize=address" )
    target_compile_options( expression_tree_op_node_test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic -Werror )
    add_test( expression_tree_op_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_op_node_test )

    add_executable( expression_tree_test expression_tree.cpp )
    target_link_libraries( expression_tree_test "-fsanitize=address" )
    target_compile_options( expression_tree_test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic -Werror )
    add_test( expression_tree_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_test )

    add_executable( make_expr_safety_test make_expr_safety.cpp )
    target_link_libraries( make_expr_safety_test "-fsanitize=address" )
    target_compile_options( make_expr_safety_test PRIVATE -fsanitize=address -Wall -Wextra -Wpedantic -Werror )
    add_test( make_expr_safety_test ${EXECUTABLE_OUTPUT_PATH}/make_expr_safety_test )

endif()