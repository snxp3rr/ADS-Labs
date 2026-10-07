import matrix;
import lu;
import std;

int main() {
    try {
        Matrix<double> A(3, 3, 1.0, 10.0);
        std::cout << "Random matrix A:\n" << A << "\n";

        Matrix<int> B(4, 4, 10);
        std::cout << "Value matrix B:\n" << B << "\n";

        Matrix<double> L(3, 3, 0.0);
        Matrix<double> U(3, 3, 0.0);

        luDecomposition(A, L, U);

        std::cout << "Lower triangular matrix L of matrix A:\n" << L << "\n";
        std::cout << "Upper triangular matrix U of matrix A:\n" << U << "\n";

        Matrix<double> result = L * U;
        std::cout << "Reconstructed matrix A (L * U):\n" << result << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}