if(BUILD_TESTING) 
    
    add_executable( operators_test operators.cpp )
    add_test( operators_test ${EXECUTABLE_OUTPUT_PATH}/operators_test )

    add_executable( expression_tree_leaf_node_test expression_tree_leaf_node.cpp )
    add_test( expression_tree_leaf_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_leaf_node_test )

    add_executable( expression_tree_op_node_test expression_tree_op_node.cpp )
    add_test( expression_tree_op_node_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_op_node_test )

endif()