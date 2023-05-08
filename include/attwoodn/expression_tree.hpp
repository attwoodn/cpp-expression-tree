#pragma once

#include <iostream>

namespace attwoodn::expression_tree {

    namespace op {
        
        template<typename A, typename B>
        class less_than {
            bool operator()(A a, B b) {
                return a < b;
            }
        };

        template<typename A, typename B>
        class greater_than {
            bool operator()(A a, B b) {
                return a > b;
            }
        };

        template<typename A, typename B>
        class equals {
            bool operator()(A a, B b) {
                return a == b;
            }
        };

        template<typename A, typename B>
        class not_equals {
            bool operator()(A a, B b) {
                return a != b;
            }
        };
    }

    static inline void say_hello() {
        std::cout << "hello world!" << std::endl;
    }
}