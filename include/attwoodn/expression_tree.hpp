#pragma once

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

    namespace tree {

        /**
         * The base class representing expression tree nodes
        */
        template<typename Obj>
        class expression_tree_node_base {
            public:
                virtual ~expression_tree_node_base() {};
                virtual bool evaluate(const Obj& obj) = 0;
        };

        class expression_tree_op_node;
        class expression_tree_leaf_node;
        

    }
}