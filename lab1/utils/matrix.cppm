export module matrix;

import std;

export template <typename T>
class Matrix {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;

public:
    Matrix(std::size_t rows, std::size_t cols, const T& value) : rows_(rows), cols_(cols) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        data_ = new T[rows * cols];
        for (std::size_t i = 0; i < rows * cols; ++i) {
            data_[i] = value;
        }
    }
}