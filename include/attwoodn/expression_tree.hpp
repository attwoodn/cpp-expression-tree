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