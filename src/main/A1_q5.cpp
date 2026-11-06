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

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    const std::size_t rows = grid.size();
    if (rows == 0) {
        return {};
    }
    const std::size_t cols = grid[0].size();
    if (cols == 0) {
        throw std::invalid_argument("map has zero columns");
    }
    for (const std::string& row : grid) {
        if (row.size() != cols) {
            throw std::invalid_argument("rows have different lengths");
        }
        for (char cell : row) {
            if (cell != '.' && cell != '#') {
                throw std::invalid_argument("invalid map character");
            }
        }
    }

    static constexpr int kDr[4] = {-1, 1, 0, 0};
    static constexpr int kDc[4] = {0, 0, -1, 1};

    std::vector<std::vector<int>> out(rows, std::vector<int>(cols, 0));
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
            if (grid[r][c] == '#') {
                out[r][c] = -1;
                continue;
            }
            int obstacles = 0;
            for (int dir = 0; dir < 4; ++dir) {
                const std::size_t nr = static_cast<std::size_t>(static_cast<long long>(r) + kDr[dir]);
                const std::size_t nc = static_cast<std::size_t>(static_cast<long long>(c) + kDc[dir]);
                if (nr < rows && nc < cols && grid[nr][nc] == '#') {
                    ++obstacles;
                }
            }
            out[r][c] = obstacles;
        }
    }
    return out;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
