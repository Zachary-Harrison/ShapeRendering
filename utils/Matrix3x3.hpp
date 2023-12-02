#pragma once

#include "../utils/Triple.hpp"

#include <initializer_list>

template <typename T>
class Matrix3x3
{
  public:
    T m[3][3];

    Matrix3x3()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                m[i][j] = 0;
            }
        }
    }

    Matrix3x3(std::initializer_list<std::initializer_list<T>> list)
    {
        int i = 0;
        for (const auto& l : list)
        {
            int j = 0;
            for (const auto& element : l)
            {
                m[i][j] = element;
                ++j;
            }
            ++i;
        }
    }

    Matrix3x3 operator*(const Matrix3x3& other) const;
    Triple<T> operator*(const Triple<T>& v) const;

    static Matrix3x3<T> rotationX(T angle)
    {
        T sinX = sin(angle);
        T cosX = cos(angle);
        return {
            { 1, 0, 0 },
            { 0, cosX, -sinX },
            { 0, sinX, cosX }
        };
    }

    static Matrix3x3<T> rotationY(T angle)
    {
        T sinY = sin(angle);
        T cosY = cos(angle);
        return {
            { cosY, 0, sinY },
            { 0, 1, 0 },
            { -sinY, 0, cosY }
        };
    }

    static Matrix3x3<T> rotationZ(T angle)
    {
        T sinZ = sin(angle);
        T cosZ = cos(angle);
        return {
            { cosZ, -sinZ, 0 },
            { sinZ, cosZ, 0 },
            { 0, 0, 1 }
        };
    }
};

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3& other) const
{
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

template <typename T>
Triple<T> Matrix3x3<T>::operator*(const Triple<T>& v) const
{
    Triple<T> result;
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
    return result;
}