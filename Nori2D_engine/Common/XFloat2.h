#pragma once
#include <math.h>

/**Util macro for conversion from degrees to radians.*/
#define MATH_DEG_TO_RAD(x) ((x) * 0.0174532925f)
/**Util macro for conversion from radians to degrees.*/
#define MATH_RAD_TO_DEG(x) ((x) * 57.29577951f)



struct XFloat2
{
	union
	{
		struct
		{
			float x;
			float y;
		};

		// The size alias
		struct
		{
			float width;
			float height;
		};

		struct
		{
			float u;
			float v;
		};
	};

	XFloat2() {}
	constexpr XFloat2(float xx, float yy) : x(xx), y(yy) {}

	static const XFloat2 ZERO;

	float getAngle() const { return atan2f(y, x); }
	float getAngle(const XFloat2& other) const;


	// angle in radians을 갖는 단위벡터를 반환한다.
	static XFloat2 forAngle(const float a) { return {cosf(a), sinf(a)}; }
	
	bool isZero() const { return x == 0.0f && y == 0.0f; }
	
	XFloat2 floor() { return { floorf(x), floorf(y) }; }

	// return Vec2 vector with an angle of this.getAngle() + other.getAngle(),
	//	                       and a length of this.getLength()* other.getLength().
	XFloat2 rotate(const XFloat2& other) const
	{ 
		return {x * other.x - y * other.y, x * other.y + y * other.x};
	}

	XFloat2 rotateByAngle(const XFloat2& pivot, float angle) const
	{
		return pivot + (*this - pivot).rotate(XFloat2::forAngle(angle));
	}

	float dot(const XFloat2& v) const
	{ 
		return (x * v.x + y * v.y);
	}
	
	float cross(const XFloat2& other) const 
	{ 
		return x * other.y - y * other.x;
	}

	bool equals(const XFloat2& target) const
	{
		return (std::abs(this->x - target.x) < FLT_EPSILON) && (std::abs(this->y - target.y) < FLT_EPSILON);
	}

	void normalize();
	XFloat2 getNormalized() const
	{
		XFloat2 v ={x,y}; v.normalize();
		return v;
	}

	float distance(const XFloat2& v) const
	{
		float dx = v.x - x;
		float dy = v.y - y;

		return std::sqrt(dx * dx + dy * dy);
	}

	float distanceSq(const XFloat2& v) const
	{
		float dx = v.x - x;
		float dy = v.y - y;
		return (dx * dx + dy * dy);
	}

	void smooth(const XFloat2& target, float elapsedTime, float responseTime)
	{
		if (elapsedTime > 0)
		{
			*this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
		}
	}







	XFloat2 operator+(const XFloat2& other) const
	{
		return { x + other.x, y + other.y };
	}

	XFloat2 operator-(const XFloat2& other) const
	{
		return { x - other.x, y - other.y };
	}

	XFloat2 operator*(float scalar) const
	{
		return { x * scalar, y * scalar };
	}

	XFloat2 operator/(float scalar) const
	{
		return { x / scalar, y / scalar };
	}

	XFloat2& operator+=(const XFloat2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	XFloat2& operator-=(const XFloat2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	XFloat2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	XFloat2& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	bool operator==(const XFloat2& v) const { return x == v.x && y == v.y; }
	bool operator!=(const XFloat2& v) const { return x != v.x || y != v.y; }
};


inline XFloat2 operator*(float lhs, const XFloat2& rhs)
{
	XFloat2 result(rhs);
	result *= lhs;
	return result;
}

