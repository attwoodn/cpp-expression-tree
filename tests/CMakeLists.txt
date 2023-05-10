if(BUILD_TESTING) 

    add_executable( operators_test operators.cpp )
    target_link_libraries( operators_test "-fsanitize=address" )
    target_compile_options( operators_test PRIVATE -fsanitize=address )
    add_test( operators_test ${EXECUTABLE_OUTPUT_PATH}/operators_test )

    add_executable( expression_tree_leaf_node_test expression_tree_leaf_node.cpp )
    target_link_libraries( expression_tree_leaf_node_test "-fsanitize=address" )
    target_compile_options( expression_tree_leaf_node_test PRIVATE -fsanitize=address )
    add_test( expression_tree_leaf_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_leaf_node_test )

    add_executable( expression_tree_op_node_test expression_tree_op_node.cpp )
    target_link_libraries( expression_tree_op_node_test "-fsanitize=address" )
    target_compile_options( expression_tree_op_node_test PRIVATE -fsanitize=address )
    add_test( expression_tree_op_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_op_node_test )

endif()