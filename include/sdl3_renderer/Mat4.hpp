#pragma once
#include <cmath>
#include "Vec3.hpp"

namespace s3d {

struct Mat4 {
    float m[4][4];

    Mat4() {
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
                m[i][j] = (i==j) ? 1.0f : 0.0f;
    }

    static Mat4 identity() { return Mat4(); }

    static Mat4 translation(float x, float y, float z) {
        Mat4 r;
        r.m[0][3] = x; r.m[1][3] = y; r.m[2][3] = z;
        return r;
    }

    static Mat4 scale(float sx, float sy, float sz) {
        Mat4 r;
        r.m[0][0] = sx; r.m[1][1] = sy; r.m[2][2] = sz;
        return r;
    }

    static Mat4 rotationX(float a) {
        Mat4 r;
        float c = cos(a), s = sin(a);
        r.m[1][1] = c; r.m[1][2] = -s;
        r.m[2][1] = s; r.m[2][2] = c;
        return r;
    }

    static Mat4 rotationY(float a) {
        Mat4 r;
        float c = cos(a), s = sin(a);
        r.m[0][0] = c;  r.m[0][2] = s;
        r.m[2][0] = -s; r.m[2][2] = c;
        return r;
    }

    static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
        Vec3 f = (target - eye).normalized();
        Vec3 s = f.cross(up).normalized();
        Vec3 u = s.cross(f);

        Mat4 r;
        r.m[0][0]=s.x; r.m[0][1]=s.y; r.m[0][2]=s.z; r.m[0][3]=-s.dot(eye);
        r.m[1][0]=u.x; r.m[1][1]=u.y; r.m[1][2]=u.z; r.m[1][3]=-u.dot(eye);
        r.m[2][0]=-f.x;r.m[2][1]=-f.y;r.m[2][2]=-f.z;r.m[2][3]=f.dot(eye);
        r.m[3][0]=0;   r.m[3][1]=0;   r.m[3][2]=0;   r.m[3][3]=1;
        return r;
    }

    // Multiply two matrices
    Mat4 operator*(const Mat4& o) const {
        Mat4 r;
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++) {
                r.m[i][j] = 0.0f;
                for (int k=0;k<4;k++)
                    r.m[i][j] += m[i][k] * o.m[k][j];
            }
        return r;
    }

    Vec3 transformPoint(const Vec3& v) const {
        float x = v.x*m[0][0] + v.y*m[0][1] + v.z*m[0][2] + m[0][3];
        float y = v.x*m[1][0] + v.y*m[1][1] + v.z*m[1][2] + m[1][3];
        float z = v.x*m[2][0] + v.y*m[2][1] + v.z*m[2][2] + m[2][3];
        float w = v.x*m[3][0] + v.y*m[3][1] + v.z*m[3][2] + m[3][3];
        if (w != 0.0f) { x/=w; y/=w; z/=w; }
        return {x,y,z};
    }
};

}
