#include <attwoodn/expression_tree.hpp>
#include <limits>
#include <iomanip>
#include <cassert>

using namespace attwoodn::expression_tree;

void test_equals();

int main(int argc, char** argv) {
    test_equals();

    return EXIT_SUCCESS;
}

void test_equals() {
    // test string equality/inequality
    {
        std::string hello = "hello world";

        assert(op::equals(hello, hello));
        assert(op::equals(hello, "hello world"));
        assert(op::equals("hello world", "hello world"));
        assert(op::equals("   ", "   "));

        assert(!op::equals("   ", "    "));
        assert(!op::equals("hello world", "hey, world"));
        assert(!op::equals("test", " test "));
    }

    // test integer equality/inequality
    {
        assert(op::equals(5, 5));
        assert(op::equals(0, 0));
        assert(op::equals(-5, -5));
        assert(op::equals(123456789, 123456789));
        assert(op::equals(123456789, 123456789L));
        assert(op::equals(255, 0xff));
        assert(op::equals(0xbeef, 0xbeef));
        assert(op::equals(std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max()));
        assert(op::equals(std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max()));
        assert(op::equals(std::numeric_limits<int16_t>::max(), std::numeric_limits<uint16_t>::max() / 2));

        assert(!op::equals(-5, 5));
        assert(!op::equals(0, 1));
        assert(!op::equals(254, 0xff));
        assert(!op::equals(123456789, 123456789000L));
        assert(!op::equals(std::numeric_limits<int16_t>::max(), std::numeric_limits<uint16_t>::max() / 2.0));
    }

    // test float equality/inequality
    {
        assert(op::equals(5.0, 5.0));
        assert(op::equals(0.000, 0.000));
        assert(op::equals(-5.0, -5.0));
        assert(op::equals(3.400f, 3.4f));
        assert(op::equals((float) 99999.0, (double) 99999.0));
        assert(op::equals(12345.999f, 12345.999f));

        assert(!op::equals(5.0, -5.0));
        assert(!op::equals(0.000, 0.000001));
        assert(!op::equals(-5.0, -4.999999));

        // there are some understandable difficulties with comparing floats directly. These should be equal
        assert(!op::equals((float) 99999.999, (double) 99999.999));
    }
}