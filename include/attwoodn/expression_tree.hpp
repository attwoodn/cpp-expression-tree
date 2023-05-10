#pragma once

#include <memory>
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

    namespace node {

        enum class boolean_op {
            AND,
            OR
        };

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
                virtual bool evaluate(const Obj& obj) const = 0;

                /**
                 * @brief Performs a deep clone of pointers to this base class to avoid object slicing.
                */
                auto clone() const {
                    return std::unique_ptr<expression_tree_node<Obj>>(clone_impl());
                }
                
            protected:
                virtual expression_tree_node<Obj>* clone_impl() const = 0;
        };

        /**
         * @brief Represents inner boolean operation nodes of the tree. These nodes contain references to a left and right 
         *        child node, as well as the boolean operation to be performed (e.g. left child AND right child, or left child OR right child).
        */
        template<typename Obj, typename LeftChild, typename RightChild>
        class expression_tree_op_node : public expression_tree_node<Obj> {
            public:
                using this_type = expression_tree_op_node<Obj, LeftChild, RightChild>;

                expression_tree_op_node() = delete;
                expression_tree_op_node(expression_tree_op_node&& other) = delete;
                expression_tree_op_node& operator=(const expression_tree_op_node& other) = delete;
                expression_tree_op_node& operator=(expression_tree_op_node&& other) = delete;

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

                bool evaluate(const Obj& obj) const override {
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

                /**
                 * Performs an AND operation with an expression_tree_leaf_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was AND'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherOp, typename OtherCompValue>
                auto* AND (expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>;
                    ret* op_node = new ret(boolean_op::AND);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an OR operation with an expression_tree_leaf_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was OR'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherOp, typename OtherCompValue>
                auto* OR (expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>;
                    ret* op_node = new ret(boolean_op::OR);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an AND operation with another expression_tree_op_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was AND'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherLeftChild, typename OtherRightChild>
                auto* AND (expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>;
                    ret* op_node = new ret(boolean_op::AND);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

                /**
                 * Performs an OR operation with another expression_tree_op_node to create a heap-allocated pointer
                 * to a new expression_tree_op_node. The returned expression_tree_op_node becomes the parent of both this node
                 * and the other node that was OR'ed with this node. This node becomes the left child. The other node becomes
                 * the right child.
                */
                template<typename OtherLeftChild, typename OtherRightChild>
                auto* OR (expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>;
                    ret* op_node = new ret(boolean_op::OR);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

            private:
                boolean_op bool_op_;
                LeftChild* left_ { nullptr };
                RightChild* right_ { nullptr };

            protected:
                virtual expression_tree_op_node<Obj, LeftChild, RightChild>* clone_impl() const override { 
                    return new expression_tree_op_node<Obj, LeftChild, RightChild>(*this); 
                }
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

                expression_tree_leaf_node() = delete;
                
                expression_tree_leaf_node(const expression_tree_leaf_node& other) = default;
                expression_tree_leaf_node(expression_tree_leaf_node&& other) = default;
                expression_tree_leaf_node& operator=(const expression_tree_leaf_node& other) = default;
                expression_tree_leaf_node& operator=(expression_tree_leaf_node&& other) = default;

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

                bool evaluate(const Obj& obj) const override {
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
                template<typename OtherOp, typename OtherCompValue>
                auto* AND (expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>;
                    ret* op_node = new ret(boolean_op::AND);
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
                template<typename OtherOp, typename OtherCompValue>
                auto* OR (expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_leaf_node<Obj, OtherOp, OtherCompValue>>;
                    ret* op_node = new ret(boolean_op::OR);
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
                template<typename OtherLeftChild, typename OtherRightChild>
                auto* AND (expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>;
                    ret* op_node = new ret(boolean_op::AND);
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
                template<typename OtherLeftChild, typename OtherRightChild>
                auto* OR (expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>* other) {
                    using ret = expression_tree_op_node<Obj, this_type, expression_tree_op_node<Obj, OtherLeftChild, OtherRightChild>>;
                    ret* op_node = new ret(boolean_op::OR);
                    op_node->set_left(this);
                    op_node->set_right(other);
                    return op_node;
                }

            private:
                CompValue (Obj::* member_func_)() const = nullptr;
                const CompValue Obj::* member_var_ = nullptr;
                Op logical_op_;
                CompValue comp_value_;

            protected:
                virtual expression_tree_leaf_node<Obj, Op, CompValue>* clone_impl() const override { 
                    return new expression_tree_leaf_node<Obj, Op, CompValue>(*this); 
                }
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

    template<typename Obj>
    class expression_tree { 
        public:
            expression_tree() = delete;

            expression_tree(node::expression_tree_node<Obj>* expr) {
                if(!expr) {
                    throw std::runtime_error("Attempted to construct an expression_tree using a null expression");
                }
                expr_ = expr->clone().release();
                delete expr;
            }

            expression_tree(std::unique_ptr<node::expression_tree_node<Obj>> expr)
                    : expression_tree(expr.release()) {}

            expression_tree(const expression_tree& other) {
                if(!other.expr_) {
                    throw std::runtime_error("Attempted to copy construct an expression_tree " + 
                        std::string("from an expression_tree with a null expression"));
                }
                expr_ = other.expr_->clone().release();
            }

            expression_tree(expression_tree&& other) {
                if(!other.expr_) {
                    throw std::runtime_error("Attempted to move construct an expression_tree " + 
                        std::string("from an expression_tree with a null expression"));
                }
                expr_ = other.expr_;
                other.expr_ = nullptr;
            }

            expression_tree& operator=(const expression_tree& other) {
                if(!other.expr_) {
                    throw std::runtime_error("Attempted copy assignment from an expression_tree with a null expression");
                }
                delete expr_;
                expr_ = other.expr_->clone().release();
                return *this;
            }

            expression_tree& operator=(expression_tree&& other) {
                if(!other.expr_) {
                    throw std::runtime_error("Attempted move assignment from an expression_tree with a null expression");
                }
                
                if(this != &other) {
                    delete expr_;
                    expr_ = other.expr_;
                    other.expr_ = nullptr;
                }
                return *this;
            }

            ~expression_tree() {
                delete expr_;
            }

            /**
             * @brief Evaluates the given object to determine if it satisfies the expressions defined in this expression tree.
             * 
             * @returns True if the given object satisfied the expression tree conditions;
             *          False if the given object did not satisfy the expression tree conditions. 
            */
            bool evaluate(const Obj& obj) const {
                if(!expr_) {
                    throw std::runtime_error("expression_tree has a null root expression node");
                }

                try {
                    return expr_->evaluate(obj);
                } catch(std::exception& e) {
                    return false;
                }
            }

        private:
            node::expression_tree_node<Obj>* expr_ = nullptr;
    };
}
