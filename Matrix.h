//
// Created by DELL on 2018/10/18.
//

#ifndef OJONLY_MATRIX_H
#define OJONLY_MATRIX_H
template <typename T>
struct Matrix {
   public:
    T mat[105][105];
    int rows, cols;
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        memset(mat, 0, sizeof(T) * rows * cols);
    }

    void identity() {
        for (int i = 0; i < rows; i++) {
            mat[i][i] = 1;
        }
    }
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%-8.2lf", mat[i * cols + j]);
            }
            printf("\n");
        }
    }
    Matrix<T> multiply(const Matrix<T>& other) const {
        Matrix<T> ret(this->rows, other.cols);
        int n = other.rows;
        for (int i = 0; i < ret.rows; i++) {
            for (int j = 0; j < ret.cols; j++) {
                ret.mat[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    ret.mat[i][j] += this->mat[i][k] * other.mat[j][k];
                }
            }
        }
        return ret;
    }

    Matrix<T> multiply(const Matrix<T>& other, long long mod) const {
        Matrix<T> ret(this->rows, other.cols);
        int n = other.rows;
        for (int i = 0; i < ret.rows; i++) {
            for (int j = 0; j < ret.cols; j++) {
                ret.mat[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    ret.mat[i][j] += this->mat[i][k] * other.mat[k][j];
                    ret.mat[i][j] %= mod;
                }
            }
        }
        return ret;
    }
};

template <typename T>
Matrix<T> fastexp(Matrix<T> mat, long long pow, int mod) {
    Matrix<T> ans(mat.rows, mat.cols);
    ans.identity();
    while (pow > 0) {
        if (pow & 1) ans = ans.multiply(mat, mod);
        pow >>= 1;
        mat = mat.multiply(mat, mod);
    }
    return ans;
}
#endif  // OJONLY_MATRIX_H
