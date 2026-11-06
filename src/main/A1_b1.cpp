#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
bool parse_i32(const std::string& text, int& output) {
    constexpr long long kMaxPositive = 2147483647LL;
    constexpr long long kMaxMagnitude = 2147483648LL;

    std::size_t index = 0;
    bool negative = false;
    if (!text.empty() && (text[0] == '+' || text[0] == '-')) {
        negative = text[0] == '-';
        index = 1;
    }
    if (index >= text.size()) {
        return false;
    }

    long long magnitude = 0;
    for (; index < text.size(); ++index) {
        const unsigned char c = static_cast<unsigned char>(text[index]);
        if (c < '0' || c > '9') {
            return false;
        }
        const long long digit = c - '0';
        if (magnitude > (std::numeric_limits<long long>::max() - digit) / 10) {
            return false;
        }
        magnitude = magnitude * 10 + digit;
    }

    if (negative) {
        if (magnitude > kMaxMagnitude) {
            return false;
        }
        output = magnitude == kMaxMagnitude ? -2147483647 - 1
                                            : static_cast<int>(-magnitude);
    } else {
        if (magnitude > kMaxPositive) {
            return false;
        }
        output = static_cast<int>(magnitude);
    }
    return true;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
