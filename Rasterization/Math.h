#ifndef _GQY_MATH_H_
#define _GQY_MATH_H_

#include <iostream>
#include <cmath>

/*
* Math 库，包括 vec2, vec3, vec4, mat3, mat4
*/
namespace GQYMath
{
    class vec2
    {
    public:
        vec2();
        vec2(const vec2& _vector);
        vec2(double _x, double _y);
        ~vec2();

        inline vec2 operator - () const
        {
            return vec2(-x, -y);
        }

        inline vec2& operator = (const vec2& _vector)
        {
            x = _vector.x;
            y = _vector.y;
            return *this;
        }

        inline vec2& operator += (const vec2& _vector)
        {
            x += _vector.x;
            y += _vector.y;
            return *this;
        }

        inline vec2& operator *= (const double _t)
        {
            x *= _t;
            y *= _t;
            return *this;
        }

        inline vec2& operator /= (const double _t)
        {
            x /= _t;
            y /= _t;
            return *this;
        }

        inline double length() const
        {
            return std::sqrt(x * x + y * y);
        }

        inline bool near_zero()
        {
            return std::abs(x) < 1e-8 && std::abs(y) < 1e-8;
        }

    public:
        double x;
        double y;
        double& u = x;
        double& v = y;
    };

    class vec3
    {
    public:
        vec3();
        vec3(const vec3& _vector);
        vec3(double _x, double _y, double _z);
        ~vec3();

        inline vec3 operator - () const
        {
            return vec3(-x, -y, -z);
        }

        inline vec3& operator = (const vec3& _vector)
        {
            x = _vector.x;
            y = _vector.y;
            z = _vector.z;
            return *this;
        }

        inline vec3& operator += (const vec3& _vector)
        {
            x += _vector.x;
            y += _vector.y;
            z += _vector.z;
            return *this;
        }

        inline vec3& operator -= (const vec3& _vector)
        {
            x -= _vector.x;
            y -= _vector.y;
            z -= _vector.z;
            return *this;
        }

        inline vec3& operator *= (const double _t)
        {
            x *= _t;
            y *= _t;
            z *= _t;
            return *this;
        }

        inline vec3& operator /= (const double _t)
        {
            x /= _t;
            y /= _t;
            z /= _t;
            return *this;
        }

        inline double length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        inline bool near_zero()
        {
            return std::abs(x) < 1e-8 && std::abs(y) < 1e-8 && std::abs(z) < 1e-8;
        }

    public:
        double x;
        double y;
        double z;
        double& r = x;
        double& g = y;
        double& b = z;
    };

    class vec4
    {
    public:
        vec4();
        vec4(const vec4& _vector);
        vec4(const vec3& _vector, double _w = 1.0);
        vec4(double _x, double _y, double _z, double _w = 1.0);
        ~vec4();

        inline vec4 operator - () const
        {
            return vec4(-x, -y, -z, -w);
        }

        inline vec4& operator = (const vec4& _vector)
        {
            x = _vector.x;
            y = _vector.y;
            z = _vector.z;
            w = _vector.w;
            return *this;
        }

        inline vec4& operator += (const vec4& _vector)
        {
            x += _vector.x;
            y += _vector.y;
            z += _vector.z;
            w += _vector.w;
            return *this;
        }

        inline vec4& operator *= (const double _t)
        {
            x *= _t;
            y *= _t;
            z *= _t;
            w *= _t;
            return *this;
        }

        inline vec4& operator /= (const double _t)
        {
            x /= _t;
            y /= _t;
            z /= _t;
            w /= _t;
            return *this;
        }

    public:
        double x;
        double y;
        double z;
        double w;
        double& r = x;
        double& g = y;
        double& b = z;
    };

    class mat3
    {
    public:
        mat3();
        mat3(const mat3& _matrix);
        mat3(const vec3& _vector1, const vec3& _vector2, const vec3& _vector3);
        mat3(const double _value11, const double _value12, const double _value13
            , const double _value21, const double _value22, const double _value23
            , const double _value31, const double _value32, const double _value33);
        ~mat3();

        inline mat3 operator - () const
        {
            return mat3(-element[0], -element[1], -element[2]);
        }

        inline mat3& operator = (const mat3& _matrix)
        {
            for (int i = 0; i < 3; i++)
            {
                element[i] = _matrix.element[i];
            }
            return *this;
        }

        inline mat3& operator += (const mat3& _matrix)
        {
            for (int i = 0; i < 3; i++)
            {
                element[i] += _matrix.element[i];
            }
            return *this;
        }

        inline mat3& operator *= (const double _t)
        {
            for (int i = 0; i < 3; i++)
            {
                element[i] *= _t;
            }
            return *this;
        }

        inline mat3& operator /= (const double _t)
        {
            for (int i = 0; i < 3; i++)
            {
                element[i] /= _t;
            }
            return *this;
        }

    public:
        vec3 element[3];
    };

    class mat4
    {
    public:
        mat4();
        mat4(const mat4& _matrix);
        mat4(const mat3& _matrix, const double _value = 1.0);
        mat4(const vec4& _vector1, const vec4& _vector2, const vec4& _vector3, const vec4& _vector4);
        mat4(const double _value11, const double _value12, const double _value13, const double _value14
            , const double _value21, const double _value22, const double _value23, const double _value24
            , const double _value31, const double _value32, const double _value33, const double _value34
            , const double _value41, const double _value42, const double _value43, const double _value44);
        ~mat4();

        inline mat4 operator - () const
        {
            return mat4(-element[0], -element[1], -element[2], -element[3]);
        }

        inline mat4& operator = (const mat4& _matrix)
        {
            for (int i = 0; i < 4; i++)
            {
                element[i] = _matrix.element[i];
            }
            return *this;
        }

        inline mat4& operator += (const mat4& _matrix)
        {
            for (int i = 0; i < 4; i++)
            {
                element[i] += _matrix.element[i];
            }
            return *this;
        }

        inline mat4& operator *= (const double _t)
        {
            for (int i = 0; i < 4; i++)
            {
                element[i] *= _t;
            }
            return *this;
        }

        inline mat4& operator /= (const double _t)
        {
            for (int i = 0; i < 4; i++)
            {
                element[i] /= _t;
            }
            return *this;
        }

    public:
        vec4 element[4];
    };
};


/******************************* vec2 ************************************/
inline std::ostream& operator << (std::ostream& _out, const GQYMath::vec2& _vector)
{
    _out << _vector.x << " " << _vector.y;
    return _out;
}

inline GQYMath::vec2 normalized_vector(const GQYMath::vec2& _vector)
{
    double length = _vector.length();
    return GQYMath::vec2(_vector.x / length, _vector.y / length);
}

inline GQYMath::vec2 operator + (const GQYMath::vec2& _vector1, const GQYMath::vec2& _vector2)
{
    return GQYMath::vec2(_vector1.x + _vector2.x, _vector1.y + _vector2.y);
}

inline GQYMath::vec2 operator - (const GQYMath::vec2& _vector1, const GQYMath::vec2& _vector2)
{
    return GQYMath::vec2(_vector1.x - _vector2.x, _vector1.y - _vector2.y);
}

inline GQYMath::vec2 operator * (const GQYMath::vec2& _vector1, const GQYMath::vec2& _vector2)
{
    return GQYMath::vec2(_vector1.x * _vector2.x, _vector1.y * _vector2.y);
}

inline GQYMath::vec2 operator * (double _t, const GQYMath::vec2& _vector)
{
    return GQYMath::vec2(_vector.x * _t, _vector.y * _t);
}

inline GQYMath::vec2 operator * (const GQYMath::vec2& _vector, double _t)
{
    return _t * _vector;
}

inline GQYMath::vec2 operator / (GQYMath::vec2 _vector, double _t)
{
    return GQYMath::vec2(_vector.x / _t, _vector.y / _t);
}

inline double dot(const GQYMath::vec2& _vector1, const GQYMath::vec2& _vector2)
{
    return _vector1.x * _vector2.x + _vector1.y * _vector2.y;
}
/***************************** end vec2 **********************************/


/******************************* vec3 ************************************/
inline std::ostream& operator << (std::ostream& _out, const GQYMath::vec3& _vector)
{
    _out << _vector.x << " " << _vector.y << " " << _vector.z;
    return _out;
}

inline GQYMath::vec3 normalized_vector(const GQYMath::vec3& _vector)
{
    double length = _vector.length();
    return GQYMath::vec3(_vector.x / length, _vector.y / length, _vector.z / length);
}

inline GQYMath::vec3 operator + (const GQYMath::vec3& _vector1, const GQYMath::vec3& _vector2)
{
    return GQYMath::vec3(_vector1.x + _vector2.x, _vector1.y + _vector2.y, _vector1.z + _vector2.z);
}

inline GQYMath::vec3 operator - (const GQYMath::vec3& _vector1, const GQYMath::vec3& _vector2)
{
    return GQYMath::vec3(_vector1.x - _vector2.x, _vector1.y - _vector2.y, _vector1.z - _vector2.z);
}

inline GQYMath::vec3 operator * (const GQYMath::vec3& _vector1, const GQYMath::vec3& _vector2)
{
    return GQYMath::vec3(_vector1.x * _vector2.x, _vector1.y * _vector2.y, _vector1.z * _vector2.z);
}

inline GQYMath::vec3 operator * (double _t, const GQYMath::vec3& _vector)
{
    return GQYMath::vec3(_vector.x * _t, _vector.y * _t, _vector.z * _t);
}

inline GQYMath::vec3 operator * (const GQYMath::vec3& _vector, double _t)
{
    return _t * _vector;
}

inline GQYMath::vec3 operator / (GQYMath::vec3 _vector, double _t)
{
    return GQYMath::vec3(_vector.x / _t, _vector.y / _t, _vector.z / _t);
}

inline double dot(const GQYMath::vec3& _vector1, const GQYMath::vec3& _vector2)
{
    return _vector1.x * _vector2.x + _vector1.y * _vector2.y + _vector1.z * _vector2.z;
}

inline GQYMath::vec3 cross(const GQYMath::vec3& _vector1, const GQYMath::vec3& _vector2)
{
    return GQYMath::vec3(_vector1.y * _vector2.z - _vector1.z * _vector2.y, _vector1.z * _vector2.x - _vector1.x * _vector2.z, _vector1.x * _vector2.y - _vector1.y * _vector2.x);
}
/***************************** end vec3 **********************************/


/******************************* vec4 ************************************/
inline std::ostream& operator << (std::ostream& _out, const GQYMath::vec4& _vector)
{
    _out << _vector.x << " " << _vector.y << " " << _vector.z << " " << _vector.w;
    return _out;
}

inline GQYMath::vec4 operator + (const GQYMath::vec4& _vector1, const GQYMath::vec4& _vector2)
{
    return GQYMath::vec4(_vector1.x + _vector2.x, _vector1.y + _vector2.y, _vector1.z + _vector2.z, _vector1.w + _vector2.w);
}

inline GQYMath::vec4 operator - (const GQYMath::vec4& _vector1, const GQYMath::vec4& _vector2)
{
    return GQYMath::vec4(_vector1.x - _vector2.x, _vector1.y - _vector2.y, _vector1.z - _vector2.z, _vector1.w - _vector2.w);
}

inline GQYMath::vec4 operator * (const GQYMath::vec4& _vector1, const GQYMath::vec4& _vector2)
{
    return GQYMath::vec4(_vector1.x * _vector2.x, _vector1.y * _vector2.y, _vector1.z * _vector2.z, _vector1.w * _vector2.w);
}

inline GQYMath::vec4 operator * (double _t, const GQYMath::vec4& _vector)
{
    return GQYMath::vec4(_vector.x * _t, _vector.y * _t, _vector.z * _t, _vector.w * _t);
}

inline GQYMath::vec4 operator * (const GQYMath::vec4& _vector, double _t)
{
    return _t * _vector;
}

inline GQYMath::vec4 operator / (GQYMath::vec4 _vector, double _t)
{
    return GQYMath::vec4(_vector.x / _t, _vector.y / _t, _vector.z / _t, _vector.w / _t);
}

inline double dot(const GQYMath::vec4& _vector1, const GQYMath::vec4& _vector2)
{
    return _vector1.x * _vector2.x + _vector1.y * _vector2.y + _vector1.z * _vector2.z + _vector1.w * _vector2.w;
}
/***************************** end vec4 **********************************/


/******************************* mat3 ************************************/
inline std::ostream& operator << (std::ostream& _out, const GQYMath::mat3& _matrix)
{
    _out << _matrix.element[0].x << " " << _matrix.element[0].y << " " << _matrix.element[0].z << "\n"
        << _matrix.element[1].x << " " << _matrix.element[1].y << " " << _matrix.element[1].z << "\n"
        << _matrix.element[2].x << " " << _matrix.element[2].y << " " << _matrix.element[2].z;
    return _out;
}

inline GQYMath::mat3 operator + (GQYMath::mat3 _matrix1, GQYMath::mat3 _matrix2)
{
    return GQYMath::mat3(_matrix1.element[0] + _matrix2.element[0], _matrix1.element[1] + _matrix2.element[1], _matrix1.element[2] + _matrix2.element[2]);
}

inline GQYMath::mat3 operator - (GQYMath::mat3 _matrix1, GQYMath::mat3 _matrix2)
{
    return GQYMath::mat3(_matrix1.element[0] - _matrix2.element[0], _matrix1.element[1] - _matrix2.element[1], _matrix1.element[2] - _matrix2.element[2]);
}

inline GQYMath::mat3 operator * (GQYMath::mat3 _matrix1, GQYMath::mat3 _matrix2)
{
    return GQYMath::mat3(
        _matrix1.element[0].x * _matrix2.element[0].x + _matrix1.element[0].y * _matrix2.element[1].x + _matrix1.element[0].z * _matrix2.element[2].x, _matrix1.element[0].x * _matrix2.element[0].y + _matrix1.element[0].y * _matrix2.element[1].y + _matrix1.element[0].z * _matrix2.element[2].y, _matrix1.element[0].x * _matrix2.element[0].z + _matrix1.element[0].y * _matrix2.element[1].z + _matrix1.element[0].z * _matrix2.element[2].z
        , _matrix1.element[1].x * _matrix2.element[0].x + _matrix1.element[1].y * _matrix2.element[1].x + _matrix1.element[1].z * _matrix2.element[2].x, _matrix1.element[1].x * _matrix2.element[0].y + _matrix1.element[1].y * _matrix2.element[1].y + _matrix1.element[1].z * _matrix2.element[2].y, _matrix1.element[1].x * _matrix2.element[0].z + _matrix1.element[1].y * _matrix2.element[1].z + _matrix1.element[1].z * _matrix2.element[2].z
        , _matrix1.element[2].x * _matrix2.element[0].x + _matrix1.element[2].y * _matrix2.element[1].x + _matrix1.element[2].z * _matrix2.element[2].x, _matrix1.element[2].x * _matrix2.element[0].y + _matrix1.element[2].y * _matrix2.element[1].y + _matrix1.element[2].z * _matrix2.element[2].y, _matrix1.element[2].x * _matrix2.element[0].z + _matrix1.element[2].y * _matrix2.element[1].z + _matrix1.element[2].z * _matrix2.element[2].z
    );
}
/***************************** end mat3 **********************************/


/******************************* mat4 ************************************/
inline std::ostream& operator << (std::ostream& _out, const GQYMath::mat4& _matrix)
{
    _out << _matrix.element[0].x << " " << _matrix.element[0].y << " " << _matrix.element[0].z << " " << _matrix.element[0].w << "\n"
        << _matrix.element[1].x << " " << _matrix.element[1].y << " " << _matrix.element[1].z << " " << _matrix.element[1].w << "\n"
        << _matrix.element[2].x << " " << _matrix.element[2].y << " " << _matrix.element[2].z << " " << _matrix.element[2].w << "\n"
        << _matrix.element[3].x << " " << _matrix.element[3].y << " " << _matrix.element[3].z << " " << _matrix.element[3].w << "\n";
    return _out;
}

inline GQYMath::mat4 operator + (GQYMath::mat4 _matrix1, GQYMath::mat4 _matrix2)
{
    return GQYMath::mat4(_matrix1.element[0] + _matrix2.element[0], _matrix1.element[1] + _matrix2.element[1], _matrix1.element[2] + _matrix2.element[2], _matrix1.element[3] + _matrix2.element[3]);
}

inline GQYMath::mat4 operator - (GQYMath::mat4 _matrix1, GQYMath::mat4 _matrix2)
{
    return GQYMath::mat4(_matrix1.element[0] - _matrix2.element[0], _matrix1.element[1] - _matrix2.element[1], _matrix1.element[2] - _matrix2.element[2], _matrix1.element[3] - _matrix2.element[3]);
}

inline GQYMath::mat4 operator * (GQYMath::mat4 _matrix1, GQYMath::mat4 _matrix2)
{
    return GQYMath::mat4(
        _matrix1.element[0].x * _matrix2.element[0].x + _matrix1.element[0].y * _matrix2.element[1].x + _matrix1.element[0].z * _matrix2.element[2].x + _matrix1.element[0].w * _matrix2.element[3].x, _matrix1.element[0].x * _matrix2.element[0].y + _matrix1.element[0].y * _matrix2.element[1].y + _matrix1.element[0].z * _matrix2.element[2].y + _matrix1.element[0].w * _matrix2.element[3].y, _matrix1.element[0].x * _matrix2.element[0].z + _matrix1.element[0].y * _matrix2.element[1].z + _matrix1.element[0].z * _matrix2.element[2].z + _matrix1.element[0].w * _matrix2.element[3].z, _matrix1.element[0].x * _matrix2.element[0].w + _matrix1.element[0].y * _matrix2.element[1].w + _matrix1.element[0].z * _matrix2.element[2].w + _matrix1.element[0].w * _matrix2.element[3].w
        , _matrix1.element[1].x * _matrix2.element[0].x + _matrix1.element[1].y * _matrix2.element[1].x + _matrix1.element[1].z * _matrix2.element[2].x + _matrix1.element[1].w * _matrix2.element[3].x, _matrix1.element[1].x * _matrix2.element[0].y + _matrix1.element[1].y * _matrix2.element[1].y + _matrix1.element[1].z * _matrix2.element[2].y + _matrix1.element[1].w * _matrix2.element[3].y, _matrix1.element[1].x * _matrix2.element[0].z + _matrix1.element[1].y * _matrix2.element[1].z + _matrix1.element[1].z * _matrix2.element[2].z + _matrix1.element[1].w * _matrix2.element[3].z, _matrix1.element[1].x * _matrix2.element[0].w + _matrix1.element[1].y * _matrix2.element[1].w + _matrix1.element[1].z * _matrix2.element[2].w + _matrix1.element[1].w * _matrix2.element[3].w
        , _matrix1.element[2].x * _matrix2.element[0].x + _matrix1.element[2].y * _matrix2.element[1].x + _matrix1.element[2].z * _matrix2.element[2].x + _matrix1.element[2].w * _matrix2.element[3].x, _matrix1.element[2].x * _matrix2.element[0].y + _matrix1.element[2].y * _matrix2.element[1].y + _matrix1.element[2].z * _matrix2.element[2].y + _matrix1.element[2].w * _matrix2.element[3].y, _matrix1.element[2].x * _matrix2.element[0].z + _matrix1.element[2].y * _matrix2.element[1].z + _matrix1.element[2].z * _matrix2.element[2].z + _matrix1.element[2].w * _matrix2.element[3].z, _matrix1.element[2].x * _matrix2.element[0].w + _matrix1.element[2].y * _matrix2.element[1].w + _matrix1.element[2].z * _matrix2.element[2].w + _matrix1.element[2].w * _matrix2.element[3].w
        , _matrix1.element[3].x * _matrix2.element[0].x + _matrix1.element[3].y * _matrix2.element[1].x + _matrix1.element[3].z * _matrix2.element[2].x + _matrix1.element[3].w * _matrix2.element[3].x, _matrix1.element[3].x * _matrix2.element[0].y + _matrix1.element[3].y * _matrix2.element[1].y + _matrix1.element[3].z * _matrix2.element[2].y + _matrix1.element[3].w * _matrix2.element[3].y, _matrix1.element[3].x * _matrix2.element[0].z + _matrix1.element[3].y * _matrix2.element[1].z + _matrix1.element[3].z * _matrix2.element[2].z + _matrix1.element[3].w * _matrix2.element[3].z, _matrix1.element[3].x * _matrix2.element[0].w + _matrix1.element[3].y * _matrix2.element[1].w + _matrix1.element[3].z * _matrix2.element[2].w + _matrix1.element[3].w * _matrix2.element[3].w
    );
}
/***************************** end mat4 **********************************/


/******************************* mat3 and vec3 ************************************/
inline GQYMath::vec3 operator * (const GQYMath::mat3& _matrix, const GQYMath::vec3 _vector)
{
    return GQYMath::vec3(dot(_matrix.element[0], _vector), dot(_matrix.element[1], _vector), dot(_matrix.element[2], _vector));
}
/***************************** end mat3 and vec3 **********************************/


/******************************* mat4 and vec4 ************************************/
inline GQYMath::vec4 operator * (const GQYMath::mat4& _matrix, const GQYMath::vec4 _vector)
{
    return GQYMath::vec4(dot(_matrix.element[0], _vector), dot(_matrix.element[1], _vector), dot(_matrix.element[2], _vector), dot(_matrix.element[3], _vector));
}
/***************************** end mat4 and vec4 **********************************/

using Point3 = GQYMath::vec3;
using Point4 = GQYMath::vec4;
using Color = GQYMath::vec3;

#endif // !_GQY_MATH_H_
