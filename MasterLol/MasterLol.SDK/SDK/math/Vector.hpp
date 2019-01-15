#pragma once

#include <sstream>

class Vector3
{
public:
    Vector3(void)
    {
        Invalidate();
    }
    Vector3(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    Vector3(const float* clr)
    {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        x = ix; y = iy; z = iz;
    }
    bool IsValid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }
    void Invalidate()
    {
        x = y = z = std::numeric_limits<float>::infinity();
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }
    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    void Zero()
    {
        x = y = z = 0.0f;
    }

    bool operator==(const Vector3& src) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const Vector3& src) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    Vector3& operator+=(const Vector3& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vector3& operator-=(const Vector3& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vector3& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    Vector3& operator*=(const Vector3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vector3& operator/=(const Vector3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    Vector3& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    Vector3& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    Vector3& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    void NormalizeInPlace()
    {
        *this = Normalized();
    }
    Vector3 Normalized() const
    {
        Vector3 res = *this;
        float l = res.Length();
        if(l != 0.0f) {
            res /= l;
        } else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }

    float DistTo(const Vector3 &vOther) const
    {
        Vector3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }
    float DistToSqr(const Vector3 &vOther) const
    {
        Vector3 delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr();
    }
    float Dot(const Vector3& vOther) const
    {
        return (x*vOther.x + y*vOther.y + z*vOther.z);
    }

	//A x B = (aYbZ  -   aZbY,     aZbX   -   aXbZ,     aXbY   -   aYbX)
	static Vector3 crossProduct(Vector3 a, Vector3 b)
	{
		Vector3 n;

		n.x = a.x*b.z - a.z*b.y;
		n.y = a.z*b.x - a.x*b.z;
		n.z = a.x*b.y - a.y*b.x;

		return n;
	}

	Vector3 perpendicularTo()
	{
		return Vector3(z, y, -x);
	}

	// Project this vector on the vOther
	Vector3 ProjectionOn(const Vector3& vOther) const
	{
		Vector3 toProject = Vector3(x, y, z);
		float scale = (toProject.Dot(vOther)) / (vOther.Dot(vOther));
		return vOther * scale;
	}

	Vector3 sameDirectionAs(const Vector3& vOther)
	{
		return vOther.Normalized() * this->Length();
	}

	Vector3 to2D()
	{
		return Vector3(this->x, 0, this->z);
	}

    float Length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    float LengthSqr(void) const
    {
        return (x*x + y*y + z*z);
    }
    float Length2D() const
    {
        return sqrt(x*x + y*y);
    }

	//angle = acos(|u|•|v|)
	static float angleBetween(Vector3 u, Vector3 v)
	{
		u.Normalized();
		v.Normalized();
		return std::acos(u.Dot(v));
	}


    Vector3& operator=(const Vector3 &vOther)
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    Vector3 operator-(void) const
    {
        return Vector3(-x, -y, -z);
    }
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    Vector3 operator*(float fl) const
    {
        return Vector3(x * fl, y * fl, z * fl);
    }
    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }
    Vector3 operator/(float fl) const
    {
        return Vector3(x / fl, y / fl, z / fl);
    }
    Vector3 operator/(const Vector3& v) const
    {
        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    float x, y, z;
};

inline Vector3 operator*(float lhs, const Vector3& rhs)
{
    return rhs * lhs;
}
inline Vector3 operator/(float lhs, const Vector3& rhs)
{
    return rhs / lhs;
}



class __declspec(align(16)) VectorAligned : public Vector3
{
public:
    inline VectorAligned(void) {};
    inline VectorAligned(float X, float Y, float Z)
    {
        Init(X, Y, Z);
    }

public:
    explicit VectorAligned(const Vector3 &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
    }

    VectorAligned& operator=(const Vector3 &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
        return *this;
    }

    VectorAligned& operator=(const VectorAligned &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
        return *this;
    }

    float w;
};