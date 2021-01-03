#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math {
	
	/*
	* Constants
	*/
	constexpr float PI = 3.1415926535f;
	constexpr float PI2 = PI * 2.0f;
	constexpr float PIOver2 = PI / 2.0f;
	constexpr float INF = std::numeric_limits<float>::infinity();
	constexpr float NEGINF = -std::numeric_limits<float>::infinity();

	/*
	* Formulas
	*/

	inline float ToRadians(const float& degrees) {	return degrees * PI / 180.0f; }

	inline float ToDegrees(const float& radians) {  return radians * 180.0f / PI; }

	inline bool NearZero(const float& val, float epsilon = 0.001f) { return (fabs(val <= epsilon) ? true : false); }

	template <typename T>
	T Max(const T& a, const T& b) { return (a < b ? b : a); }

	template <typename T>
	T Min(const T& a, const T& b) {	return (a < b ? a : b);	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper) { return Min(upper, Max(lower, value)); 	}

	inline float Abs(const float& value) { return fabs(value); }

	inline float Cos(const float& angle) {	return cosf(angle);	}

	inline float Sin(const float& angle) {	return sinf(angle);	}

	inline float Tan(const float& angle) {	return tanf(angle); }

	inline float Acos(const float& value) { return acosf(value); }

	inline float Atan2(const float& y, const float& x) { return atan2f(y, x); }

	inline float Cot(float angle) {	return 1.0f / Tan(angle); }

	inline float Lerp(float a, float b, float f) { return a + f * (b - a); }

	inline float Sqrt(float value) { return sqrtf(value); }

	inline float Fmod(float numer, float denom)	{ return fmod(numer, denom); }

}

/*
* 2D Vector
*/
struct Vec2 {

	// default constructors
	Vec2() :
		x(0.0f), y(0.0f)
	{}

	Vec2(const float& f) :
		x(f),
		y(f)
	{}

	Vec2(const float& x, const float& y) :
		x(x),
		y(y)
	{}

	Vec2(const Vec2& other) :
		x(other.x),
		y(other.y)
	{}

	~Vec2() {}

	inline float length2() { return x * x + y * y; }

	inline float length() {	return std::sqrtf(length2()); }

	Vec2& normalize() {
		norm();
		return *this;
	}

	void norm() {
		float oneOverLength = 1.f / length();
		x *= oneOverLength;
		y *= oneOverLength;
	}

	void norm(const float& f) {
		float oneOverLength = 1.f / f;
		x *= oneOverLength;
		y *= oneOverLength;
	}


	// operators
	Vec2& operator =(const Vec2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vec2& operator +=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator -=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2& operator *=(const float& f) {
		x *= f;
		y *= f;
		return *this;
	}
	Vec2& operator /=(const float& f) {
		x /= f;
		y /= f;
		return *this;
	}

	float operator [](const int& idx) {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else return 0.0f;
	}

	float operator [](const int& idx) const {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else return 0.0f;
	}

	float x, y;

};

namespace Templates {
	// Statics
	static const Vec2 Zero(0.0f, 0.0f);
	static const Vec2 UnitX(1.0f, 0.0f);
	static const Vec2 UnitY(0.0f, 1.0f);
	static const Vec2 NegUnitX(-1.0f, 0.0f);
	static const Vec2 NegUnitY(0.0f, -1.0f);

}

// operators
inline Vec2 operator +(const Vec2& v1, const Vec2& v2) { return Vec2(v1.x + v2.x, v1.y + v2.y); }

inline Vec2 operator -(const Vec2& v1, const Vec2& v2) { return Vec2(v1.x - v2.x, v1.y - v2.y); }

inline Vec2 operator *(const Vec2& v1, const Vec2& v2) { return Vec2(v1.x * v2.x, v1.y * v2.y); }

inline Vec2 operator *(const Vec2& v, float f) { return Vec2(v.x * f, v.y * f); }

inline Vec2 operator *(float f, const Vec2& v) { return Vec2(f * v.x, f * v.y); }

inline Vec2 operator /(const Vec2& v1, const Vec2& v2) { return Vec2(v1.x / v2.x, v1.y / v2.y); }

inline Vec2 operator /(const Vec2& v, float f) { return Vec2(v.x / f, v.y / f); }

inline Vec2 operator /(float f, const Vec2& v) { return Vec2(f / v.x, f / v.y); }

// dot
//float dot(const Vec2& v1, const Vec2& v2) { return v1.x * v2.x + v1.y * v2.y; }

// reflect
//Vec2 reflect(const Vec2& v1, const Vec2& v2) { return Vec2(v1 - v2 * 2.0f * dot(v1, v2)); }

/*

struct Vec3 {

	// default constructors
	Vec3() :
		x(0.0f), y(0.0f), z(0.0f)
	{}

	Vec3(const float& f) :
		x(f),
		y(f),
		z(f)
	{}

	Vec3(const float& x, const float& y, const float& z) :
		x(x),
		y(y),
		z(z)
	{}

	Vec3(const float& x, const float& y, const float& z, const float& w) :
		x(x),
		y(y),
		z(z)
	{}

	~Vec3() {}

	// copy constructor
	Vec3(const Vec3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}

	// move constructor
	Vec3(Vec3&& other) noexcept {
		x = other.x;
		y = other.y;
		z = other.z;
	}

	inline float length2() { return x * x + y * y + z * z; }

	inline float length() { return std::sqrt(length2()); }

	Vec3& normalize() {
		norm();
		return *this;
	}

	void norm() {
		float oneOverLength = 1.f / length();
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
	}

	void norm(const float& f) {
		float oneOverLength = 1.f / f;
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
	}


	// operators
	Vec3& operator =(const Vec3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}



	Vec3& operator =(Vec3&& other) noexcept {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}


	Vec3& operator +=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& operator -=(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vec3& operator *=(float f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	Vec3& operator /=(float f) {
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	float operator [](const int& idx) {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else if (idx == 2) return z;
		else return 0.0f;
	}

	float operator [](const int& idx) const {
		if (idx == 0) return x;
		else if (idx == 1) return y;
		else if (idx == 2) return z;
		else return 0.0f;
	}

	float x, y, z;

};


// add operators
inline Vec3 operator +(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

inline Vec3 operator -(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

inline Vec3 operator *(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

inline Vec3 operator *(const Vec3& v, float f)
{
	return Vec3(v.x * f,
		v.y * f,
		v.z * f
	);
}

inline Vec3 operator *(float f, const Vec3& v)
{
	return Vec3(f * v.x,
		f * v.y,
		f * v.z);
}

inline Vec3 operator /(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

inline Vec3 operator /(const Vec3& v, float f)
{
	return Vec3(v.x / f,
		v.y / f,
		v.z / f
	);
}

inline Vec3 operator /(float f, const Vec3& v)
{
	return Vec3(f / v.x,
		f / v.y,
		f / v.z);
}


// Vector operations

// dot
float dot(const Vec3& v1, const Vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// cross
Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return
		Vec3(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
}

// reflect
Vec3 reflect(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1 - v2 * 2.0f * dot(v1, v2));
}

*/