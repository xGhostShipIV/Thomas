#pragma once
#include "two_dimensions.hpp"

class Vec3 {
public:
	float x, y, z;

	//--------------------------------Constructors and Factories------------------------------------\\

	Vec3(void);
	Vec3(float, float, float);
	~Vec3();
	static Vec3 Zero();
	static Vec3 BasisX();
	static Vec3 BasisY();
	static Vec3 BasisZ();

	//--------------------------------Operator Overloading-------------------------------------------\\


	inline Vec3 operator+(const Vec3&) const;
	inline Vec3 operator+=(const Vec3&);
	inline void operator=(const Vec3&);
	inline Vec3 operator-(const Vec3&) const;
	inline Vec3 operator-=(const Vec3&);
	inline Vec3 operator*(const float&) const;
	inline Vec3 operator*=(const float&);
	inline Vec3 operator/(const float&) const;
	inline Vec3 operator/=(const float&);

	//--------------------------------Actual Maths----------------------------------------------------\\

	static float length(Vec3);
	void NormalizeThis();
	Vec3 Normalized();
	static float dot(Vec3, Vec3);
	static Vec3 cross(Vec3, Vec3);
};

class Matrix3 {
public:
	float values[9];

	//--------------------------------Constructors and Factories------------------------------------\\

	Matrix3();
	Matrix3(float, float, float, float, float, float, float, float, float); //9 for building a custom matrix
	~Matrix3();
	static Matrix3 Identity();
	static Matrix3 Rotate(float, int); //Angle - Axis (0 = x, 1 = y, 2 = z) This rotate is only for rotation about a basis axis (x/y/z)
	static Matrix3 Translate(float, float);
	//Matrix3 Skew(); //Not sure how this works yet but will check it.

	//---------------------------------Operator Overloading-------------------------------------------\\

	inline Matrix3 operator+(const Matrix3&);
	inline Matrix3 operator+=(const Matrix3&);
	inline Matrix3 operator-(const Matrix3&);
	inline Matrix3 operator-=(const Matrix3&);
	inline Matrix3 operator*(const float&);
	inline Matrix3 operator*=(const float&);
	inline Matrix3 operator/(const float&);
	inline Matrix3 operator/=(const float&);
	inline Matrix3 operator=(const Matrix3&);
	inline Matrix3 operator*(const Matrix3&);
	inline Matrix3 operator*=(const Matrix3&);

	//------------------------------------Actual Maths----------------------------------------------\\

	Matrix3 transpose();
	Matrix3 inverse();
	Matrix3 cofactor();
	Matrix3 adjoint();
	Matrix2 minor(int);

	float det();

	Vec3 getRowVector(int) const;
	Vec3 getColVector(int) const;
};