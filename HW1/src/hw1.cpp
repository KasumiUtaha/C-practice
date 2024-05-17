#include "hw1.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>

using std::cin;
using std::cout;
using std::setprecision;

Matrix algebra::init(size_t n, size_t m, int value)
{
    if (n <= 0 || m <= 0)
    {
        throw std::logic_error("Wrong Col or Row!");
    }
    Matrix matrix;
    for (int i = 0; i < n; i++)
    {
        vector<double> tmp(m, value);
        matrix.push_back(tmp);
    }
    return matrix;
}

Matrix algebra::zeros(size_t n, size_t m)
{
    return init(n, m, 0);
}

Matrix algebra::ones(size_t n, size_t m)
{
    return init(n, m, 1);
}

Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    if (min > max)
    {
        throw std::logic_error("min should not greater than max!");
    }
    Matrix matrix = init(n, m, 0);
    std::default_random_engine e(time(0));
    std::uniform_real_distribution u(min, max);

    for (auto &x : matrix)
    {
        for (auto &y : x)
        {
            y = u(e);
        }
    }
    return matrix;
}

void algebra::show(const Matrix &matrix)
{
    for (auto x : matrix)
    {
        for (auto y : x)
        {
            cout << std::fixed << setprecision(3) << y << ' ';
        }
        cout << '\n';
    }
}

Matrix algebra::multiply(const Matrix &matrix, double c)
{
    Matrix ans = matrix;
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            ans[i][j] = matrix[i][j] * c;
        }
    }
    return ans;
}

Matrix algebra::multiply(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.empty())
        return matrix2;
    if (matrix2.empty())
        return matrix1;
    if (matrix1[0].size() != matrix2.size())
    {
        throw std::logic_error("matrix1 and matrix2 cannot multiply!");
    }
    Matrix ans = algebra::init(matrix1.size(), matrix2[0].size(), 0);
    int column = matrix1[0].size();
    int row = matrix1.size();
    for (int k = 0; k < column; k++)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < (int)matrix2[0].size(); j++)
            {
                ans[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return ans;
}

Matrix algebra::sum(const Matrix &matrix, double c)
{
    if (matrix.empty())
        return matrix;
    Matrix ans = matrix;
    int row = matrix.size();
    int column = matrix[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            ans[i][j] = matrix[i][j] + c;
        }
    }
    return ans;
}

Matrix algebra::sum(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.empty() && !matrix2.empty())
        throw std::logic_error("one of matrix is empty!");
    else if (matrix2.empty() && !matrix1.empty())
        throw std::logic_error("one of matrix is empty!");
    else if (matrix1.empty() && matrix2.empty())
        return matrix1;
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
    {
        throw std::logic_error("the size of matrix1 is not equal to that of matrix2");
    }
    Matrix ans = matrix1;
    int row = matrix1.size();
    int column = matrix1[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            ans[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return ans;
}

Matrix algebra::transpose(const Matrix &matrix)
{
    if (matrix.empty())
        return matrix;
    Matrix ans = algebra::init(matrix[0].size(), matrix.size(), 0);
    int row = matrix.size();
    int column = matrix[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            ans[j][i] = matrix[i][j];
        }
    }
    return ans;
}


Matrix algebra::minor(const Matrix& matrix , size_t n ,size_t m)
{
    if(matrix.empty() || matrix.size() < n || matrix[0].size() < m)
    {  
        throw std::logic_error("can't create!");
    }
    Matrix ans = matrix;
    ans.erase(ans.begin() + n);
    for(auto& x : ans)
    {
        x.erase(x.begin() + m);
    }
    return ans;
}


