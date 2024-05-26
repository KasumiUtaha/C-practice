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
    std::uniform_real_distribution<double> u(min, max);

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

Matrix algebra::minor(const Matrix &matrix, size_t n, size_t m)
{
    if (matrix.empty() || matrix.size() < n || matrix[0].size() < m)
    {
        throw std::logic_error("can't create!");
    }
    Matrix ans = matrix;
    ans.erase(ans.begin() + n);
    for (auto &x : ans)
    {
        x.erase(x.begin() + m);
    }
    return ans;
}

double algebra::determinant(const Matrix &matrix)
{
    if (matrix.empty())
        return 1;
    if (matrix.size() != matrix[0].size())
    {
        throw std::logic_error("don't have determinant!");
    }
    if (matrix.size() == 1)
        return matrix[0][0];
    double sum = 0;
    int flag = 1;
    for (auto i = 0; i < (int)matrix.size(); i++)
    {
        sum += determinant(minor(matrix, i, 0)) * flag * matrix[i][0];
        flag = -flag;
    }
    return sum;
}

Matrix algebra::inverse(const Matrix &matrix)
{
    double det = determinant(matrix);
    if (matrix.empty())
        return matrix;
    if (det == 0.0)
    {
        throw std::logic_error("No inverse!");
    }
    int row = matrix.size();
    int column = matrix[0].size();
    Matrix ans = zeros(row, column);
    for (int i = 0; i < row; i++)
    {
        double flag = 1;
        if (i & 1)
            flag = -1;
        for (int j = 0; j < column; j++)
        {
            ans[i][j] = determinant(minor(matrix, i, j)) / det * flag;
            flag = -flag;
        }
    }
    return transpose(ans);
}

Matrix algebra::concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis = 0)
{
    if (axis != 0 && axis != 1)
    {
        throw std::logic_error("wrong axis!");
    }
    if (matrix1.empty())
        return matrix2;
    if (matrix2.empty())
        return matrix1;
    if (!axis)
    {
        if (matrix1[0].size() != matrix2[0].size())
        {
            throw std::logic_error("can't concatenate");
        }
        Matrix ans = matrix1;
        for (int i = 0; i < matrix2.size(); i++)
        {
            ans.push_back(matrix2[i]);
        }
        return ans;
    }
    else
    {
        if (matrix1.size() != matrix2.size())
        {
            throw std::logic_error("can't concatenate");
        }
        Matrix ans = matrix1;
        for (int i = 0; i < matrix1.size(); i++)
        {
            for (int j = 0; j < matrix2[i].size(); j++)
            {
                ans[i].push_back(matrix2[i][j]);
            }
        }
        return ans;
    }
}

Matrix algebra::ero_swap(const Matrix &matrix, size_t r1, size_t r2)
{
    if (r1 >= matrix.size() || r2 >= matrix.size() || r1 < 0 || r2 < 0)
    {
        throw std::logic_error("wrong row number");
    }
    Matrix ans;
    for (int i = 0; i < matrix.size(); i++)
    {
        if (i == r1)
            ans.push_back(matrix[r2]);
        else if (i == r2)
            ans.push_back(matrix[r1]);
        else
            ans.push_back(matrix[i]);
    }
    return ans;
}

Matrix algebra::ero_multiply(const Matrix &matrix, size_t r, double c)
{
    if (r >= matrix.size() || r < 0)
    {
        throw std::logic_error("wrong row number!");
    }
    Matrix ans = matrix;
    for (int i = 0; i < matrix[r].size(); i++)
    {
        ans[r][i] *= c;
    }
    return ans;
}

Matrix algebra::ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2)
{
    if (r1 >= matrix.size() || r2 >= matrix.size() || r1 < 0 || r2 < 0)
    {
        throw std::logic_error("wrong row number");
    }
    Matrix ans = matrix;
    for (int i = 0; i < ans[r1].size(); i++)
    {
        ans[r2][i] += ans[r1][i] * c;
    }
    return ans;
}

Matrix algebra::upper_triangular(const Matrix& matrix)
{
    if(matrix.empty()) return matrix;
    if(matrix.size() != matrix[0].size()) 
    {
        throw std::logic_error("have no upper_triangle!");
    }
    int row=matrix.size();
    int column=matrix[0].size();
    Matrix ans=matrix;
    for(int i=0;i<row;i++)
    {
        int nxtrow=i;
        if(ans[i][i] == 0)
        {
            for(int j=i+1;j<row;j++)
            {
                if(ans[j][i] != 0)
                {
                    nxtrow=j;
                    break;
                }
            }
        }
        ans=ero_swap(ans,i,nxtrow);
        for(int j=i+1;j<row;j++)
        {
            if(ans[j][i] != 0)
            {
                ans=ero_sum(ans,i,-ans[j][i]/ans[i][i],j);

            }
        }
    }
    return ans;
}

