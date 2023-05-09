#include <attwoodn/expression_tree.hpp>
#include <limits>
#include <iomanip>
#include <cassert>

using namespace attwoodn::expression_tree;

void test_equals();
void test_not_equals();
void test_less_than();
void test_greater_than();

int main(int argc, char** argv) {
    test_equals();
    test_not_equals();
    test_less_than();
    test_greater_than();

    return EXIT_SUCCESS;
}

void test_equals() {
    // test string equality/inequality
    {
        std::string hello = "hello world";

        assert(op::equals(hello, hello));
        assert(op::equals(hello, std::string("hello world")));
        assert(op::equals(std::string("hello world"), std::string("hello world")));
        assert(op::equals(std::string("   "), std::string("   ")));
        assert(op::equals(std::string("100 100 100 10000"), std::string("100 100 100 10000")));
        
        // NOTE: pointer types are dereferenced prior to comparison. This may be misleading.
        // E.g., if the type is a char*, only the first character is compared.
        assert(op::equals("1", "1 "));
        assert(op::equals("test", "testing testing 123"));
        assert(op::equals("hello world", "hey, world"));
        assert(op::equals("A", "A"));
        
        assert(!op::equals("\"", "\'"));
        assert(!op::equals("1", " 1"));
        assert(!op::equals("A", "B"));
        assert(!op::equals(std::string("hello world"), std::string("hey, world")));
        assert(!op::equals(std::string("test"), std::string(" test ")));
        assert(!op::equals(std::string("   "), std::string("    ")));
        assert(!op::equals(std::string("1"), std::string("1 ")));
        assert(!op::equals(std::string("1"), std::string(" 1")));
    }

    // test integer equality/inequality
    {
        int low = 55, low_too = 55;
        int high = 999999, high_too = 999999;

        assert(op::equals(5, 5));
        assert(op::equals(0, 0));
        assert(op::equals(-5, -5));
        assert(op::equals(123456789, 123456789));
        assert(op::equals(123456789L, 123456789L));
        assert(op::equals(255, 0xff));
        assert(op::equals(0xbeef, 0xbeef));
        assert(op::equals(std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max()));
        assert(op::equals(std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max()));
        assert(op::equals(std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::min()));
        assert(op::equals(low, low));
        assert(op::equals(&low, &low));
        assert(op::equals(low, low_too));
        assert(op::equals(&low, &low_too));
        assert(op::equals(high, high));
        assert(op::equals(&high, &high));
        assert(op::equals(high, high_too));
        assert(op::equals(&high, &high_too));

        assert(!op::equals(-5, 5));
        assert(!op::equals(0, 1));
        assert(!op::equals(254, 0xff));
        assert(!op::equals(123456789L, 123456789000L));
        assert(!op::equals(low, high));
        assert(!op::equals(&low, &high));
    }

    // test float equality/inequality
    {
        float low = 55.5555, low_too = 55.5555;
        float high = 999999.999, high_too = 999999.999;

        assert(op::equals(5.0, 5.0));
        assert(op::equals(0.000, 0.000));
        assert(op::equals(-5.0, -5.0));
        assert(op::equals(3.400f, 3.4f));
        assert(op::equals((float) 99999.0, (float) 99999.0));
        assert(op::equals(12345.999f, 12345.999f));
        assert(op::equals((double) 99999.999, (double) 99999.999));
        assert(op::equals(low, low));
        assert(op::equals(&low, &low));
        assert(op::equals(low, low_too));
        assert(op::equals(&low, &low_too));
        assert(op::equals(high, high));
        assert(op::equals(&high, &high));
        assert(op::equals(high, high_too));
        assert(op::equals(&high, &high_too));

        assert(!op::equals(5.0, -5.0));
        assert(!op::equals(0.000, 0.000001));
        assert(!op::equals(-5.0, -4.999999));
        assert(!op::equals(low, high));
        assert(!op::equals(&low, &high));
    }

    // test other
    {
        char* a = nullptr;
        assert(op::equals(a, a));

        assert(!op::equals((char*) "a", a));
    }
}

void test_not_equals() {
    // test string equality/inequality
    {
        std::string hello = "hello world";

        assert(op::not_equals("\"", "\'"));
        assert(op::not_equals("1", " 1"));
        assert(op::not_equals("A", "B"));
        assert(op::not_equals(std::string("hello world"), std::string("hey, world")));
        assert(op::not_equals(std::string("test"), std::string(" test ")));
        assert(op::not_equals(std::string("   "), std::string("    ")));
        assert(op::not_equals(std::string("1"), std::string("1 ")));
        assert(op::not_equals(std::string("1"), std::string(" 1")));

        assert(!op::not_equals(hello, hello));
        assert(!op::not_equals(hello, std::string("hello world")));
        assert(!op::not_equals(std::string("hello world"), std::string("hello world")));
        assert(!op::not_equals(std::string("   "), std::string("   ")));
        assert(!op::not_equals(std::string("100 100 100 10000"), std::string("100 100 100 10000")));
        
        // NOTE: pointer types are dereferenced prior to comparison. This may be misleading.
        // E.g., if the type is a char*, only the first character is compared.
        assert(!op::not_equals("1", "1 "));
        assert(!op::not_equals("test", "testing testing 123"));
        assert(!op::not_equals("hello world", "hey, world"));
        assert(!op::not_equals("A", "A"));
    }

    // test integer equality/inequality
    {
        int low = 55, low_too = 55;
        int high = 999999, high_too = 999999;

        assert(op::not_equals(-5, 5));
        assert(op::not_equals(0, 1));
        assert(op::not_equals(254, 0xff));
        assert(op::not_equals(123456789L, 123456789000L));
        assert(op::not_equals(low, high));
        assert(op::not_equals(&low, &high));

        assert(!op::not_equals(5, 5));
        assert(!op::not_equals(0, 0));
        assert(!op::not_equals(-5, -5));
        assert(!op::not_equals(123456789, 123456789));
        assert(!op::not_equals(123456789L, 123456789L));
        assert(!op::not_equals(255, 0xff));
        assert(!op::not_equals(0xbeef, 0xbeef));
        assert(!op::not_equals(std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max()));
        assert(!op::not_equals(std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max()));
        assert(!op::not_equals(std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::min()));
        assert(!op::not_equals(low, low));
        assert(!op::not_equals(&low, &low));
        assert(!op::not_equals(low, low_too));
        assert(!op::not_equals(&low, &low_too));
        assert(!op::not_equals(high, high));
        assert(!op::not_equals(&high, &high));
        assert(!op::not_equals(high, high_too));
        assert(!op::not_equals(&high, &high_too));
    }

    // test float equality/inequality
    {
        float low = 55.5555, low_too = 55.5555;
        float high = 999999.999, high_too = 999999.999;

        assert(op::not_equals(5.0, -5.0));
        assert(op::not_equals(0.000, 0.000001));
        assert(op::not_equals(-5.0, -4.999999));
        assert(op::not_equals(low, high));
        assert(op::not_equals(&low, &high));

        assert(!op::not_equals(5.0, 5.0));
        assert(!op::not_equals(0.000, 0.000));
        assert(!op::not_equals(-5.0, -5.0));
        assert(!op::not_equals(3.400f, 3.4f));
        assert(!op::not_equals((float) 99999.0, (float) 99999.0));
        assert(!op::not_equals(12345.999f, 12345.999f));
        assert(!op::not_equals((double) 99999.999, (double) 99999.999));
        assert(!op::not_equals(low, low));
        assert(!op::not_equals(&low, &low));
        assert(!op::not_equals(low, low_too));
        assert(!op::not_equals(&low, &low_too));
        assert(!op::not_equals(high, high));
        assert(!op::not_equals(&high, &high));
        assert(!op::not_equals(high, high_too));
        assert(!op::not_equals(&high, &high_too));
    }

    // test other
    {
        char* a = nullptr;
        assert(op::not_equals((char*) "a", a));

        assert(!op::not_equals(a, a));
    }
}

void test_less_than() {
    assert(op::less_than(5, 6));
    assert(op::less_than(1, 10));
    assert(op::less_than(0, 1));
    assert(op::less_than(-1, 1));
    assert(op::less_than(-1, 0));
    assert(op::less_than(5.0, 6.665));
    assert(op::less_than(6.664, 6.665));
    assert(op::less_than(1.199999, 1.2));
    assert(op::less_than(0xfe, 0xff));
    assert(op::less_than(std::string("hello"), std::string("hi")));
    assert(op::less_than("a", "b"));
    assert(op::less_than("A", "C"));
    assert(op::less_than("Q", "Z"));
    assert(op::less_than(std::string("a"), std::string("abc")));

    assert(!op::less_than(0, -1));
    assert(!op::less_than(0, -1000));
    assert(!op::less_than(-1, -1));
    assert(!op::less_than(0, 0));
    assert(!op::less_than(999999, 999999));
    assert(!op::less_than(0xff, 0xff));
    assert(!op::less_than("hello", "hello"));
    assert(!op::less_than("a", "a"));
    assert(!op::less_than("z", "a"));
    assert(!op::less_than("E", "B"));
    assert(!op::less_than(std::string("abc"), std::string("a")));
    assert(!op::less_than(std::string("hi"), std::string("hello")));
}

void test_greater_than() {
    assert(op::greater_than(0, -1));
    assert(op::greater_than(0, -1000));
    assert(op::greater_than("z", "a"));
    assert(op::greater_than("E", "B"));
    assert(op::greater_than(std::string("abc"), std::string("a")));
    assert(op::greater_than(std::string("hi"), std::string("hello")));

    assert(!op::greater_than(5, 6));
    assert(!op::greater_than(1, 10));
    assert(!op::greater_than(0, 1));
    assert(!op::greater_than(-1, 1));
    assert(!op::greater_than(-1, 0));
    assert(!op::greater_than(-1, -1));
    assert(!op::greater_than(0, 0));
    assert(!op::greater_than(999999, 999999));
    assert(!op::greater_than(0xff, 0xff));
    assert(!op::greater_than("hello", "hello"));
    assert(!op::greater_than("a", "a"));
    assert(!op::greater_than(5.0, 6.665));
    assert(!op::greater_than(6.664, 6.665));
    assert(!op::greater_than(1.199999, 1.2));
    assert(!op::greater_than(0xfe, 0xff));
    assert(!op::greater_than(std::string("hello"), std::string("hi")));
    assert(!op::greater_than("a", "b"));
    assert(!op::greater_than("A", "C"));
    assert(!op::greater_than("Q", "Z"));
    assert(!op::greater_than(std::string("a"), std::string("abc")));
}