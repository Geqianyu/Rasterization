#include "../header/Math.h"

/******************************* vec3 ************************************/
GQYMath::vec2::vec2() : x(0.0), y(0.0)
{

}

GQYMath::vec2::vec2(const vec2& _vector) : x(_vector.x), y(_vector.y)
{

}

GQYMath::vec2::vec2(double _x, double _y) : x(_x), y(_y)
{

}

GQYMath::vec2::~vec2()
{

}
/***************************** end vec3 **********************************/


/******************************* vec3 ************************************/
GQYMath::vec3::vec3() : x(0.0), y(0.0), z(0.0)
{

}

GQYMath::vec3::vec3(const vec3& _vector) : x(_vector.x), y(_vector.y), z(_vector.z)
{

}

GQYMath::vec3::vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
{

}

GQYMath::vec3::~vec3()
{

}
/***************************** end vec3 **********************************/


/******************************* vec4 ************************************/
GQYMath::vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0)
{

}

GQYMath::vec4::vec4(const vec4& _vector) : x(_vector.x), y(_vector.y), z(_vector.z), w(_vector.w)
{

}

GQYMath::vec4::vec4(const vec3& _vector, double _w) : x(_vector.x), y(_vector.y), z(_vector.z), w(_w)
{

}

GQYMath::vec4::vec4(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w)
{

}

GQYMath::vec4::~vec4()
{

}
/***************************** end vec4 **********************************/


/******************************* mat3 ************************************/
GQYMath::mat3::mat3()
{

}

GQYMath::mat3::mat3(const mat3& _matrix)
{
    for (int i = 0; i < 3; i++)
    {
        element[i] = _matrix.element[i];
    }
}

GQYMath::mat3::mat3(const vec3& _vector1, const vec3& _vector2, const vec3& _vector3)
{
    element[0] = _vector1;
    element[1] = _vector2;
    element[2] = _vector3;
}

GQYMath::mat3::mat3(const double _value11, const double _value12, const double _value13
    , const double _value21, const double _value22, const double _value23
    , const double _value31, const double _value32, const double _value33)
{
    element[0].x = _value11;
    element[0].y = _value12;
    element[0].z = _value13;
    element[1].x = _value21;
    element[1].y = _value22;
    element[1].z = _value23;
    element[2].x = _value31;
    element[2].y = _value32;
    element[2].z = _value33;
}

GQYMath::mat3::~mat3()
{

}
/***************************** end mat3 **********************************/


/******************************* mat4 ************************************/
GQYMath::mat4::mat4()
{

}

GQYMath::mat4::mat4(const GQYMath::mat4& _matrix)
{
    for (int i = 0; i < 4; i++)
    {
        element[i] = _matrix.element[i];
    }
}

GQYMath::mat4::mat4(const GQYMath::mat3& _matrix, const double _value)
{
    for (int i = 0; i < 3; i++)
    {
        element[i] = vec4(_matrix.element[i], 0.0);
    }
    element[3] = vec4(0.0, 0.0, 0.0, _value);
}

GQYMath::mat4::mat4(const GQYMath::vec4& _vector1, const GQYMath::vec4& _vector2, const GQYMath::vec4& _vector3, const GQYMath::vec4& _vector4)
{
    element[0] = _vector1;
    element[1] = _vector2;
    element[2] = _vector3;
    element[3] = _vector4;
}

GQYMath::mat4::mat4(const double _value11, const double _value12, const double _value13, const double _value14
    , const double _value21, const double _value22, const double _value23, const double _value24
    , const double _value31, const double _value32, const double _value33, const double _value34
    , const double _value41, const double _value42, const double _value43, const double _value44)
{
    element[0].x = _value11;
    element[0].y = _value12;
    element[0].z = _value13;
    element[0].w = _value14;
    element[1].x = _value21;
    element[1].y = _value22;
    element[1].z = _value23;
    element[1].w = _value24;
    element[2].x = _value31;
    element[2].y = _value32;
    element[2].z = _value33;
    element[2].w = _value34;
    element[3].x = _value41;
    element[3].y = _value42;
    element[3].z = _value43;
    element[3].w = _value44;
}

GQYMath::mat4::~mat4()
{

}
/***************************** end mat4 **********************************/