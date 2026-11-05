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

// Assessment 01 Q4; see 题面.pdf.
namespace aim::q4 {
struct CommandResult { long long value; int accepted; int rejected; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw
CommandResult execute(const std::vector<std::string>& lines) {
    constexpr long long kLimit = 1000000;
    CommandResult result{0, 0, 0};

    for (const std::string& line : lines) {
        std::istringstream input(line);
        std::string head;
        std::string tail;
        long long candidate = 0;
        bool ok = false;

        if (input >> head) {
            if (head == "RESET") {
                if (!(input >> tail)) {
                    ok = true;
                }
            } else if (head == "ADD" || head == "SET") {
                long long x = 0;
                if (input >> x) {
                    if (!(input >> tail) && x >= -kLimit && x <= kLimit) {
                        candidate = head == "ADD" ? result.value + x : x;
                        ok = candidate >= -kLimit && candidate <= kLimit;
                    }
                }
            }
        }

        if (ok) {
            result.value = candidate;
            ++result.accepted;
        } else {
            ++result.rejected;
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q4;
int main() {
    try {
        { aim::q4::CommandResult r=execute({"ADD 5","SET 8 x","RESET","ADD -2"}); CHECK(r.value==-2 && r.accepted==3 && r.rejected==1); }
        { aim::q4::CommandResult r=execute({}); CHECK(r.value==0 && r.accepted==0 && r.rejected==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
