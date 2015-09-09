#pragma once
#include <cmath>

class Vec2 {
public:
	float x, y;

	//--------------------------------Constructors and Factories------------------------------------\\

	Vec2();
	Vec2(float, float);
	static Vec2 Zero();
	static Vec2 BasisX();
	static Vec2 BasisY();

	//--------------------------------Operator Overloading-------------------------------------------\\

	inline Vec2 operator+(const Vec2&) const;
	inline Vec2 operator+=(const Vec2&);
	inline void operator=(const Vec2&);
	inline Vec2 operator-(const Vec2&) const;
	inline Vec2 operator-=(const Vec2&);
	inline Vec2 operator*(const float&) const;
	inline Vec2 operator*=(const float&);
	inline Vec2 operator/(const float&) const;
	inline Vec2 operator/=(const float&);

	//--------------------------------Actual Maths----------------------------------------------------\\

	void NormalizeThis();
	static float length(Vec2);
	Vec2 Normalized();
	static float dot(Vec2, Vec2);
	static Vec2 ortho(Vec2);
};

class Matrix2 {
public:
	float values[4];

	//--------------------------------Constructors and Factories------------------------------------\\

	Matrix2();
	Matrix2(float, float, float, float); //4 in for 2x2
	static Matrix2 Identity();
	static Matrix2 Rotate(float);

	//--------------------------------Operator Overloading-------------------------------------------\\

	inline Matrix2 operator+(const Matrix2&);
	inline Matrix2 operator+=(const Matrix2&);
	inline Matrix2 operator-(const Matrix2&);
	inline Matrix2 operator-=(const Matrix2&);
	inline Matrix2 operator*(const float&);
	inline Matrix2 operator*=(const float&);
	inline Matrix2 operator/(const float&);
	inline Matrix2 operator/=(const float&);
	inline Matrix2 operator=(const Matrix2&);
	inline Matrix2 operator*(const Matrix2&);
	inline Matrix2 operator*=(const Matrix2&);

	//------------------------------------Actual Maths----------------------------------------------\\

	float minor(int index);
	float det();
	Vec2 getRowVector(int) const;
	Vec2 getColVector(int) const;

};