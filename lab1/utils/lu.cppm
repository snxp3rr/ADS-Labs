export module lu;

import std;
import matrix;

export template <typename T>
void luDecomposition(const Matrix<T>& A, Matrix<T>& L, Matrix<T>& U) {
    std::size_t n = A.rows();

    if (A.rows() != A.cols()) {
        throw std::invalid_argument("Matrix must be square for LU decomposition");
    }

    U = A;
    L = Matrix<T>(n, n, T{});

    for (std::size_t i = 0; i < n; ++i) {
        L(i, i) = T{1};
    }

    for (std::size_t k = 0; k < n; ++k) {
        if (U(k, k) == T{}) {
            throw std::runtime_error("Zero pivot encountered. LU decomposition failed.");
        }

        for (std::size_t i = k + 1; i < n; ++i) {
            T factor = U(i, k) / U(k, k);
            L(i, k) = factor;

            for (std::size_t j = k; j < n; ++j) {
                U(i, j) = U(i, j) - factor * U(k, j);
            }
        }
    }
}