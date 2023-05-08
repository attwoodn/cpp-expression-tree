#pragma once

#include <iostream>

namespace attwoodn::expression_tree {

    namespace op {
        
        template<typename A, typename B>
        inline bool less_than(A a, B b) {
            return a < b;
        }

        template<typename A, typename B>
        inline bool greater_than(A a, B b) {
            return a > b;
        }

        template<typename A, typename B>
        inline bool equals(A a, B b) {
            return a == b;
        }

        template<typename A, typename B>
        inline bool not_equals(A a, B b) {
            return a != b;
        }
        
    }

    static inline void say_hello() {
        std::cout << "hello world!" << std::endl;
    }
}