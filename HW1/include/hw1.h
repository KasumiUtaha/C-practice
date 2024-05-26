#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
using std::size_t;
using std::vector;
using Matrix = vector<vector<double>>;

namespace algebra
{

    Matrix init(size_t n, size_t m, int value);

    Matrix zeros(size_t n, size_t m);

    Matrix ones(size_t n, size_t m);

    Matrix random(size_t n, size_t m, double min, double max);

    void show(const Matrix &matrix);

    Matrix multiply(const Matrix &matrix, double c);

    Matrix multiply(const Matrix &matrix1, const Matrix &matrix2);

    Matrix sum(const Matrix &matrix, double c);

    Matrix sum(const Matrix &matrix1, const Matrix &matrix2);

    Matrix transpose(const Matrix &matrix);

    Matrix minor(const Matrix &matrix, size_t n, size_t m);

    double determinant(const Matrix &matrix);

    Matrix inverse(const Matrix &matrix);

    Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis);
}

#endif // AP_HW1_H
