#pragma once

#include <math.h>
#include <vector>
#include "XFloat2.h"



struct XMatrix2D
{
    float _11, _12, _13;
    float _21, _22, _23;
    float _31, _32, _33;

    //multiplies m_Matrix with mIn
    inline void  MatrixMultiply(XMatrix2D& mIn);


public:

    XMatrix2D()
    {
        Identity();
    }

    //create an identity matrix
    inline void Identity();

    //create a transformation matrix
    inline void Translate(float x, float y);

    //create a scale matrix
    inline void Scale(float xScale, float yScale);

    //create a rotation matrix
    inline void  Rotate(float rotation);

    //create a rotation matrix from a fwd and side 2D vector
    inline void  Rotate(const XFloat2& fwd, const XFloat2& side);

    //applys a transformation matrix to a std::vector of points
    inline void TransformVector2Ds(std::vector<XFloat2>& vPoints);

    //applys a transformation matrix to a point
    inline void TransformVector2Ds(XFloat2& vPoint);
};



//multiply two matrices together
inline void XMatrix2D::MatrixMultiply(XMatrix2D& mIn)
{
    XMatrix2D mat_temp;

    //first row
    mat_temp._11 = (_11 * mIn._11) + (_12 * mIn._21) + (_13 * mIn._31);
    mat_temp._12 = (_11 * mIn._12) + (_12 * mIn._22) + (_13 * mIn._32);
    mat_temp._13 = (_11 * mIn._13) + (_12 * mIn._23) + (_13 * mIn._33);

    //second
    mat_temp._21 = (_21 * mIn._11) + (_22 * mIn._21) + (_23 * mIn._31);
    mat_temp._22 = (_21 * mIn._12) + (_22 * mIn._22) + (_23 * mIn._32);
    mat_temp._23 = (_21 * mIn._13) + (_22 * mIn._23) + (_23 * mIn._33);

    //third
    mat_temp._31 = (_31 * mIn._11) + (_32 * mIn._21) + (_33 * mIn._31);
    mat_temp._32 = (_31 * mIn._12) + (_32 * mIn._22) + (_33 * mIn._32);
    mat_temp._33 = (_31 * mIn._13) + (_32 * mIn._23) + (_33 * mIn._33);

    *this = mat_temp;
}

inline void XMatrix2D::TransformVector2Ds(std::vector<XFloat2>& vPoint)
{
    for (unsigned int i = 0; i < vPoint.size(); ++i)
    {
        float tempX = (_11 * vPoint[i].x) + (_21 * vPoint[i].y) + (_31);

        float tempY = (_12 * vPoint[i].x) + (_22 * vPoint[i].y) + (_32);

        vPoint[i].x = tempX;

        vPoint[i].y = tempY;

    }
}

inline void XMatrix2D::TransformVector2Ds(XFloat2& vPoint)
{

    float tempX = (_11 * vPoint.x) + (_21 * vPoint.y) + (_31);

    float tempY = (_12 * vPoint.x) + (_22 * vPoint.y) + (_32);

    vPoint.x = tempX;

    vPoint.y = tempY;
}

inline void XMatrix2D::Identity()
{
    _11 = 1; _12 = 0; _13 = 0;

    _21 = 0; _22 = 1; _23 = 0;

    _31 = 0; _32 = 0; _33 = 1;

}

inline void XMatrix2D::Translate(float x, float y)
{
    XMatrix2D mat;

    mat._11 = 1; mat._12 = 0; mat._13 = 0;

    mat._21 = 0; mat._22 = 1; mat._23 = 0;

    mat._31 = x; mat._32 = y;    mat._33 = 1;

    MatrixMultiply(mat);
}

inline void XMatrix2D::Scale(float xScale, float yScale)
{
    XMatrix2D mat;

    mat._11 = xScale; mat._12 = 0; mat._13 = 0;

    mat._21 = 0; mat._22 = yScale; mat._23 = 0;

    mat._31 = 0; mat._32 = 0; mat._33 = 1;

    MatrixMultiply(mat);
}


//create a rotation matrix
inline void XMatrix2D::Rotate(float rot)
{
    XMatrix2D mat;

    float Sin = sinf(rot);
    float Cos = cosf(rot);

    mat._11 = Cos;  mat._12 = Sin; mat._13 = 0;

    mat._21 = -Sin; mat._22 = Cos; mat._23 = 0;

    mat._31 = 0; mat._32 = 0; mat._33 = 1;

    MatrixMultiply(mat);
}


//create a rotation matrix from a 2D vector
inline void XMatrix2D::Rotate(const XFloat2& fwd, const XFloat2& side)
{
    XMatrix2D mat;

    mat._11 = fwd.x;  mat._12 = fwd.y; mat._13 = 0;

    mat._21 = side.x; mat._22 = side.y; mat._23 = 0;

    mat._31 = 0; mat._32 = 0; mat._33 = 1;

    MatrixMultiply(mat);
}



