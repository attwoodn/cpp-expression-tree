if(BUILD_TESTING) 
    add_executable( expression_tree_test test.cpp )
    add_test( expression_tree_test ${EXECUTABLE_OUTPUT_PATH}/expression_tree_test )
endif()