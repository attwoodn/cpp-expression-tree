#pragma once

namespace attwoodn::expression_tree {

    namespace op {
        
        template<typename T>
        inline bool less_than(T a, T b) {
            return a < b;
        }

        template<typename T>
        inline bool less_than(T* a, T* b) {
            if(a == nullptr || b == nullptr) return false;
            return *a < *b;
        }

        template<typename T>
        inline bool greater_than(T a, T b) {
            return a > b;
        }

        template<typename T>
        inline bool greater_than(T* a, T* b) {
            if(a == nullptr || b == nullptr) return false;
            return *a > *b;
        }

        template<typename T>
        inline bool equals(T a, T b) {
            return a == b;
        }

        template<typename T>
        inline bool equals(T* a, T* b) {
            if(a == nullptr && b == nullptr) return true;
            if(a == nullptr || b == nullptr) return false;
            return *a == *b;
        }

        template<typename T>
        inline bool not_equals(T a, T b) {
            return a != b;
        }
        
        template<typename T>
        inline bool not_equals(T* a, T* b) {
            if(a == nullptr && b == nullptr) return false;
            if(a == nullptr || b == nullptr) return true;
            return *a != *b;
        }
    }

    namespace node {

        /**
         * @brief The base class representing all expression tree nodes.
        */
        template<typename Obj>
        class expression_tree_node_base {
            public:
                virtual ~expression_tree_node_base() {};

                /**
                 * @brief Evaluates the given object to determine if it satisfies the expressions defined in this node and all child nodes.
                 * 
                 * @returns True if the given object satisfied the expression in this node and all the expressions of all nodes 
                 *              under this node in the expression tree;
                 * 
                 *          False if the given object did not satisfy the epression in this node and all the expressions of all 
                 *              nodes under this node in the expression tree. 
                */
                virtual bool evaluate(const Obj& obj) = 0;
        };

        /**
         * 
        */
        template<typename Obj, typename LeftChild, typename RightChild>
        class expression_tree_op_node : public expression_tree_node_base<Obj> {

        };
        
        template<typename Obj, typename Op, typename CompValue>
        class expression_tree_leaf_node : public expression_tree_node_base<Obj> {

        };

    }


}