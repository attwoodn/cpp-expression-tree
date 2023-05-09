if(BUILD_TESTING) 
    add_executable( expression_tree_test test.cpp )
    add_test( expression_tree_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_test )

    add_executable( operators_test operators.cpp )
    add_test( operators_test ${EXECUTABLE_OUTPUT_PATH}/operators_test )
endif()