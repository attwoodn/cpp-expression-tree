#include <attwoodn/expression_tree.hpp>
#include "test_utils.hpp"
#include "release_asserts.hpp"
#include <functional>
#include <vector>

using namespace attwoodn::expression_tree;

void test_quick_example_expression_tree();
void test_expression_tree_std_string_template();
void test_expression_tree_std_vector_template();
void test_simple_expression_tree();
void test_complex_expression_tree();
void test_moved_expression_tree();
void test_copied_expression_tree();
void test_user_defined_operator();

int main(int argc, char** argv) {
    test_quick_example_expression_tree();
    test_expression_tree_std_string_template();
    test_expression_tree_std_vector_template();
    test_simple_expression_tree();
    test_complex_expression_tree();
    test_moved_expression_tree();
    test_copied_expression_tree();
    test_user_defined_operator();

    return EXIT_SUCCESS;
}

void test_quick_example_expression_tree() {
    expression_tree<my_type> expr {
        make_expr(&my_type::my_bool, op::equals, true)
        ->OR((make_expr(&my_type::get_my_int, op::greater_than, 0)
            ->AND(make_expr(&my_type::my_int, op::less_than, 10))
            )
        )
    };
    
    my_type obj;
    
    obj.my_bool = true;
    obj.my_int = 4;
    assert(expr.evaluate(obj));

    obj.my_bool = true;
    obj.my_int = 12;
    assert(expr.evaluate(obj));

    obj.my_bool = false;
    obj.my_int = 0;
    assert(!expr.evaluate(obj));
}

void test_expression_tree_std_string_template() {
    expression_tree<std::string> expr {
        make_expr(&std::string::empty, op::equals, true)
    };

    assert(expr.evaluate(""));
    assert(!expr.evaluate(" "));
    assert(!expr.evaluate("hello"));
    assert(!expr.evaluate("good bye"));
}

void test_expression_tree_std_vector_template() {
    struct my_vec_wrapper {
        std::vector<int> int_vec;
    };

    expression_tree<my_vec_wrapper> expr {
        make_expr(&my_vec_wrapper::int_vec, op::equals, {1, 2, 3})
    };

    my_vec_wrapper obj;
    
    obj.int_vec = {1, 2, 3};
    assert(expr.evaluate(obj));

    obj.int_vec = {1, 2, 3, 4};
    assert(!expr.evaluate(obj));

    obj.int_vec = {3, 2, 1};
    assert(!expr.evaluate(obj));

    obj.int_vec = {};
    assert(!expr.evaluate(obj));

    obj.int_vec = {1, 2, 3, 1};
    assert(!expr.evaluate(obj));

    obj.int_vec = {1, 2, 3, 2, 1};
    assert(!expr.evaluate(obj));
}

void test_simple_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
        fixture.some_string = "hello!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello          world!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello,world!";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "hello, world!";
        assert(expr.evaluate(fixture));
    };

    // test raw pointer creation of expression_tree
    {
        expression_tree<test_fixture> expr {
            make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
        };

        test_procedure(expr);
    }

    // test unique_ptr creation of expression_tree
    {
        expression_tree<test_fixture> expr {
            std::unique_ptr<node::expression_tree_node<test_fixture>>(
                make_expr(&test_fixture::some_string, op::equals, std::string("hello, world!"))
            )
        };

        test_procedure(expr);
    }
}

void test_complex_expression_tree() {

    // expression: (uint > 0 AND (some_string > "a" AND some_string < "z")) OR (some_string > "0" AND some_string < "9")
    expression_tree<test_fixture> expr {
        (make_expr(&test_fixture::is_some_uint_greater_than_zero, op::equals, true)
            ->AND((make_expr(&test_fixture::some_string, op::greater_than, std::string("a"))
                ->AND(make_expr(&test_fixture::some_string, op::less_than, std::string("z")))
            ))
        )
        ->OR((make_expr(&test_fixture::some_string, op::greater_than, std::string("0"))
                ->AND(make_expr(&test_fixture::some_string, op::less_than, std::string("9")))
            )
        )
    };

    test_fixture fixture;

    fixture.some_uint = 0;

    // test left-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "a";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "aaa";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "c";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "yyyyy";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "B";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "ZZZ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "/";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "red";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "                              ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "tree fiddy";
        assert(!expr.evaluate(fixture));
    }

    // test right-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "000";
        assert(expr.evaluate(fixture));

        fixture.some_string = "00";
        assert(expr.evaluate(fixture));

        fixture.some_string = "0";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "12345";
        assert(expr.evaluate(fixture));

        fixture.some_string = "7";
        assert(expr.evaluate(fixture));

        fixture.some_string = "89999";
        assert(expr.evaluate(fixture));

        fixture.some_string = "9";
        assert(!expr.evaluate(fixture));
    }

    fixture.some_uint = 1;
    
    // test left-hand side of the expression tree when some_uint is 0
    {
        fixture.some_string = "a";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "aaa";
        assert(expr.evaluate(fixture));

        fixture.some_string = "c";
        assert(expr.evaluate(fixture));

        fixture.some_string = "yyyyy";
        assert(expr.evaluate(fixture));

        fixture.some_string = "B";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "ZZZ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "/";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "red";
        assert(expr.evaluate(fixture));

        fixture.some_string = "                              ";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "tree fiddy";
        assert(expr.evaluate(fixture));
    }

    // test right-hand side of the expression tree when some_uint is 1
    {
        fixture.some_string = "000";
        assert(expr.evaluate(fixture));

        fixture.some_string = "00";
        assert(expr.evaluate(fixture));

        fixture.some_string = "0";
        assert(!expr.evaluate(fixture));

        fixture.some_string = "12345";
        assert(expr.evaluate(fixture));

        fixture.some_string = "7";
        assert(expr.evaluate(fixture));

        fixture.some_string = "89999";
        assert(expr.evaluate(fixture));

        fixture.some_string = "9";
        assert(!expr.evaluate(fixture));
    }


}

void test_moved_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
    
        fixture.some_uint = 345;
        assert(expr.evaluate(fixture));
        
        fixture.some_uint = 123;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 543;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0x04;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 3;
        assert(!expr.evaluate(fixture));
    };

    expression_tree<test_fixture> expr {
        make_expr(&test_fixture::some_uint, op::equals, (uint16_t) 345)
    };
    test_procedure(expr);

    expression_tree<test_fixture> move_constructed_expr(std::move(expr));
    test_procedure(move_constructed_expr);
    
    expression_tree<test_fixture> move_assigned_expr = std::move(move_constructed_expr);
    test_procedure(move_assigned_expr);
}

void test_copied_expression_tree() {
    auto test_procedure = [](const expression_tree<test_fixture>& expr) {
        test_fixture fixture;
    
        fixture.some_uint = 345;
        assert(expr.evaluate(fixture));
        
        fixture.some_uint = 123;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 543;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0x04;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = -1;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 0;
        assert(!expr.evaluate(fixture));

        fixture.some_uint = 3;
        assert(!expr.evaluate(fixture));
    };

    expression_tree<test_fixture> expr {
        make_expr(&test_fixture::some_uint, op::equals, (uint16_t) 345)
    };
    test_procedure(expr);

    expression_tree<test_fixture> copy_constructed_expr(expr);
    test_procedure(copy_constructed_expr);
    
    expression_tree<test_fixture> copy_assigned_expr = copy_constructed_expr;
    test_procedure(copy_assigned_expr);

    // ensure both of the old copied versions still work after copying
    test_procedure(expr);
    test_procedure(copy_constructed_expr);
}

void test_user_defined_operator() {
    auto is_small_packet_payload = [](const packet_payload& incoming, const packet_payload&) -> bool {
        if(incoming.error_code == 0 && incoming.checksum_ok && incoming.payload_size() <= 10) {
            return true;
        }
        return false;
    };

    // only accept small, non-errored data packets from Jim. 
    // evaluate packet contents using the user-defined lambda operator defined above
    expression_tree<data_packet> expr {
        make_expr(&data_packet::sender_name, op::equals, std::string("Jim"))
        ->AND(make_expr(&data_packet::payload, is_small_packet_payload, packet_payload()))
    };

    data_packet incoming_packet;

    // Jim sends a small, non-errored data packet
    incoming_packet.sender_name = "Jim";
    incoming_packet.payload.checksum_ok = true;
    incoming_packet.payload.data = "hello!";
    incoming_packet.payload.error_code = 0;
    assert(expr.evaluate(incoming_packet));      // passes evaluation

    // Pam sends the same packet payload
    incoming_packet.sender_name = "Pam";
    assert(!expr.evaluate(incoming_packet));     // fails evaluation. No messages from Pam are accepted (sorry Pam)

    // Jim sends a packet with a bad checksum
    incoming_packet.sender_name = "Jim";
    incoming_packet.payload.checksum_ok = false;
    assert(!expr.evaluate(incoming_packet));     // fails evaluation. The packet was from Jim, but the checksum was bad

    // Jim sends a packet whose payload is too big
    incoming_packet.payload.checksum_ok = true;
    incoming_packet.payload.data = "Boy do I have a long story for you - so I was talking to Pam ...";
    assert(!expr.evaluate(incoming_packet));     // fails evaluation. The packet's payload was too big. Give me the TLDR next time, Jim

    // Jim sends a small, rude packet
    incoming_packet.payload.data = "Dwight sux";
    assert(expr.evaluate(incoming_packet));      // passes evaluation. The packet's payload was the right size this time

    // Jim sends a packet has an error code
    incoming_packet.payload.error_code = 404;
    assert(!expr.evaluate(incoming_packet));     // fails evaluation. The packet's payload had an error code
}