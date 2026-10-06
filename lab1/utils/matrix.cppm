export module matrix;

import std;

export template <typename T>
class Matrix {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;
}