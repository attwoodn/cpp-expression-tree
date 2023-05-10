#pragma once

#include <stdexcept>

namespace attwoodn::expression_tree {

    namespace op {
        
        template<typename T>
        inline bool less_than(const T a, const T b) {
            return a < b;
        }

        template<typename T>
        inline bool less_than(T* a, T* b) {
            if(a == nullptr || b == nullptr) return false;
            return *a < *b;
        }

        template<typename T>
        inline bool greater_than(const T a, const T b) {
            return a > b;
        }

        template<typename T>
        inline bool greater_than(T* a, T* b) {
            if(a == nullptr || b == nullptr) return false;
            return *a > *b;
        }

        template<typename T>
        inline bool equals(const T a, const T b) {
            return a == b;
        }

        template<typename T>
        inline bool equals(T* a, T* b) {
            if(a == nullptr && b == nullptr) return true;
            if(a == nullptr || b == nullptr) return false;
            return *a == *b;
        }

        template<typename T>
        inline bool not_equals(const T a, const T b) {
            return a != b;
        }
        
        template<typename T>
        inline bool not_equals(T* a, T* b) {
            if(a == nullptr && b == nullptr) return false;
            if(a == nullptr || b == nullptr) return true;
            return *a != *b;
        }
    }

    enum class boolean_op {
        AND,
        OR
    };

    namespace node {

        template<typename Obj, typename LeftChild, typename RightChild>
        class expression_tree_op_node;

        template<typename Obj, typename Op, typename CompValue>
        class expression_tree_leaf_node;

        /**
         * @brief The base class representing all expression tree nodes.
        */
        template<typename Obj>
        class expression_tree_node {
            public:
                virtual ~expression_tree_node() {};

                /**
                 * @brief Evaluates the given object to determine if it satisfies the expressions defined in this node and all child nodes.
                 * 
                 * @returns True if the given object satisfied the expression in this node and the expressions of all nodes 
                 *              under this node in the expression tree;
                 * 
                 *          False if the given object did not satisfy the expression in this node and the expressions of all 
                 *              nodes under this node in the expression tree. 
                */
                virtual bool evaluate(const Obj& obj) = 0;
        };

        /**
         * @brief Represents inner boolean operation nodes of the tree. These nodes contain references to a left and right 
         *        child node, as well as the boolean operation to be performed (e.g. left child AND right child, or left child OR right child).
        */
        template<typename Obj, typename LeftChild, typename RightChild>
        class expression_tree_op_node : public expression_tree_node<Obj> {
            public:
                using this_type = expression_tree_op_node<Obj, LeftChild, RightChild>;

                expression_tree_op_node(boolean_op bool_op)
                    : bool_op_(bool_op) {}

                expression_tree_op_node(const expression_tree_op_node& other) {
                    bool_op_ = other.bool_op_;
                    delete left_;
                    delete right_;
                    left_ = new LeftChild(*other.left_);
                    right_ = new RightChild(*other.right_);
                }

                ~expression_tree_op_node() override {
                    delete left_;
                    delete right_;
                }

                void set_right(RightChild* r) {
                    delete right_;
                    right_ = new RightChild(*r);
                    delete r;
                }

                void set_left(LeftChild* l) {
                    delete left_;
                    left_ = new LeftChild(*l);
                    delete l;
                }

                bool evaluate(const Obj& obj) override {
                    if(!left_ || !right_) {
                        throw std::runtime_error("expression_tree_op_node has a missing child node");
                    }

                    switch(bool_op_) {
                        case boolean_op::AND: {
                            return left_->evaluate(obj) && right_->evaluate(obj);
                        }

                        case boolean_op::OR: {
                            return left_->evaluate(obj) || right_->evaluate(obj);
                        }

                        default: {
                            throw std::runtime_error("expression_tree_op_node contained a non-implemented boolean expression");
                        }
                    }

                    return false;
                }

            private:
                boolean_op bool_op_;
                LeftChild* left_ { nullptr };
                RightChild* right_ { nullptr };
        };
        
        /**
         * @brief Represents leaf nodes of the tree. These nodes contain: a reference to a member variable or member function of the
         *        given Obj type; the requested logical operation to be performed (e.g. equals, greater_than, etc.); and the
         *        value to compare to the given member variable or member function of an Obj instance.
        */
        template<typename Obj, typename Op, typename CompValue>
        class expression_tree_leaf_node : public expression_tree_node<Obj> {
            public:
                using this_type = expression_tree_leaf_node<Obj, Op, CompValue>;

                /**
                 * @brief Constructor that accepts a reference to a member variable of Obj
                */
                expression_tree_leaf_node(const CompValue Obj::* obj_mem_var, Op op, CompValue comp_value)
                    : member_var_(obj_mem_var),
                      logical_op_(op),
                      comp_value_(comp_value) {}

                /**
                 * @brief Constructor that accepts a reference to a const member function of Obj
                */
                expression_tree_leaf_node(CompValue (Obj::* obj_mem_func)() const, Op op, CompValue comp_value)
                    : member_func_(obj_mem_func),
                      logical_op_(op),
                      comp_value_(comp_value) {}

                ~expression_tree_leaf_node() override {};

                bool evaluate(const Obj& obj) override {
                    if (member_func_ && member_var_) {
                        throw std::runtime_error("expression_tree_leaf_node has both a member function reference " + 
                            std::string("and member variable reference. Only one is permitted"));
                    }

                    else if (!member_func_ && !member_var_) {
                        throw std::runtime_error("expression_tree_leaf_node has a nullptr for both member function reference " + 
                            std::string("and member variable reference. At least one is required"));
                    }

                    CompValue actual_value;

                    if (member_func_) {
                        // invoke member function and store the result
                        actual_value = (obj.*member_func_)();
                    } 
                    
                    else if (member_var_) {
                        // get value from obj's data member
                        actual_value = obj.*member_var_;
                    }

                    else return false;

                    return logical_op_(actual_value, comp_value_);
                }

                /**
                 * Performs an AND operation with another expression_tree_leaf_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was AND'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherOp, typename OtherCompValue, typename OtherLeafNode,
                    std::enable_if<std::is_same<OtherLeafNode, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>::value>* = nullptr>
                expression_tree_op_node<Obj, this_type, OtherLeafNode>* AND (OtherLeafNode* other) {
                    auto* op_node = new expression_tree_op_node<Obj, this_type, OtherLeafNode>(boolean_op::AND);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an OR operation with another expression_tree_leaf_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was OR'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherOp, typename OtherCompValue, typename OtherLeafNode,
                    std::enable_if<std::is_same<OtherLeafNode, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>::value>* = nullptr>
                expression_tree_op_node<Obj, this_type, OtherLeafNode>* OR (OtherLeafNode* other) {
                    auto* op_node = new expression_tree_op_node<Obj, this_type, OtherLeafNode>(boolean_op::OR);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an AND operation with an expression_tree_op_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was AND'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherLeftChild, typename OtherRightChild, typename OtherOpNode, 
                    std::enable_if<std::is_same<OtherOpNode, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>::value>* = nullptr>
                expression_tree_op_node<Obj, this_type, OtherOpNode>* AND (OtherOpNode* other) {
                    auto* op_node = new expression_tree_op_node<Obj, this_type, OtherOpNode>(boolean_op::AND);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an OR operation with an expression_tree_op_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was OR'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherLeftChild, typename OtherRightChild, typename OtherOpNode,
                    std::enable_if<std::is_same<OtherOpNode, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>::value>* = nullptr>
                expression_tree_op_node<Obj, this_type, OtherOpNode>* OR (OtherOpNode* other) {
                    auto* op_node = new expression_tree_op_node<Obj, this_type, OtherOpNode>(boolean_op::OR);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

            private:
                CompValue (Obj::* member_func_)() const = nullptr;
                const CompValue Obj::* member_var_ = nullptr;
                Op logical_op_;
                CompValue comp_value_;
        };

    }

    template<class T> struct type_id{typedef T type;}; 

    /**
     * Makes an expression tree leaf node for comparing pointer-type member variables of a class/struct
    */
    template<typename Obj, typename CompValue, typename Op = typename type_id<bool (*)(CompValue*, CompValue*)>::type,
        typename std::enable_if<std::is_convertible<CompValue, CompValue*>::value, int>::type = 0>
    node::expression_tree_leaf_node<Obj, Op, CompValue>* make_expr( CompValue Obj::* member_var, Op op, CompValue comp_value ) {
        return new node::expression_tree_leaf_node<Obj, Op, CompValue>( member_var, op, comp_value );
    }

    /**
     * Makes an expression tree leaf node for comparing value-type member variables of a class/struct
    */
    template<typename Obj, typename CompValue, typename Op = typename type_id<bool (*)(CompValue, CompValue)>::type>
    node::expression_tree_leaf_node<Obj, Op, CompValue>* make_expr( const CompValue Obj::* member_var, Op op, CompValue comp_value ) {
        return new node::expression_tree_leaf_node<Obj, Op, CompValue>( member_var, op, comp_value );
    }

    /**
     * Makes an expression tree leaf node for comparing the return value from a class/struct's const member function
    */
    template<typename Obj, typename CompValue, typename Op = typename type_id<bool (*)(CompValue, CompValue)>::type>
    node::expression_tree_leaf_node<Obj, Op, CompValue>* make_expr( CompValue (Obj::* member_func)() const, Op op, CompValue comp_value ) {
        return new node::expression_tree_leaf_node<Obj, Op, CompValue>( member_func, op, comp_value );
    }
}