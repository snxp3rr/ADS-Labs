export module matrix;

import std;

template <typename>
struct is_complex : std::false_type {};

template <typename U>
struct is_complex<std::complex<U>> : std::true_type {};

template <typename T>
inline constexpr bool is_complex_v = is_complex<T>::value;

export template <typename T>
class Matrix {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;
    static constexpr double kEpsilon = 1e-9;

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

    Matrix(std::size_t rows, std::size_t cols, const T& lower, const T& upper) : rows_(rows), cols_(cols) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        data_ = new T[rows * cols];

        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(lower, upper);
            for (std::size_t i = 0; i < rows * cols; ++i) {
                data_[i] = dist(gen);
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(lower, upper);
            for (std::size_t i = 0; i < rows * cols; ++i) {
                data_[i] = dist(gen);
            }
        }else {
            T zero = T{};
            using RealType = decltype(zero.real());
            RealType r_lower = lower.real();
            RealType r_upper = upper.real();

            std::uniform_real_distribution<RealType> dist(r_lower, r_upper);
            for (std::size_t i = 0; i < rows * cols; ++i) {
                data_[i] = T(dist(gen), dist(gen));
            }
        }
    }

    T& operator()(std::size_t i, std::size_t j) {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[i * cols_ + j];
    }

    const T& operator()(std::size_t i, std::size_t j) const {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[i * cols_ + j];
    }

        bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same size");
        }
        Matrix result(rows_, cols_, T{});
        for (std::size_t i = 0; i < rows_ * cols_; ++i) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        return *this + (-other);
    }

    Matrix operator-() const {
        Matrix result(rows_, cols_, T{});
        for (std::size_t i = 0; i < rows_ * cols_; ++i) {
            result.data_[i] = -data_[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        }
        Matrix result(rows_, other.cols_, T{});
        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < other.cols_; ++j) {
                T sum = T{};
                for (std::size_t k = 0; k < cols_; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix operator*(const T& scalar) const {
        Matrix result(rows_, cols_, T{});
        for (std::size_t i = 0; i < rows_ * cols_; ++i) {
            result.data_[i] = data_[i] * scalar;
        }
        return result;
    }

    friend Matrix operator*(const T& scalar, const Matrix& m) {
        return m * scalar;
    }

    Matrix operator/(const T& scalar) const {
        if (scalar == T{}) {
            throw std::invalid_argument("Division by zero");
        }
        return *this * (T{1} / scalar);
    }
}