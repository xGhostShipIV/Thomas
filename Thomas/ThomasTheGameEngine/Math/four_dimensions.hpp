#pragma once
#include "three_dimensions.hpp"

class Quat { //q = {w,{x,y,z}} ==> q = {cos(9/2), {x sin (9/2), y sin(9/2), z sin(9/2)}}
public:
	float w;
	Vec3 vector;

	//--------------------------------Constructors and Factories------------------------------------\\

	Quat();
	Quat(float, Vec3);
	Quat(float, float, float, float);

	//--------------------------------Operator Overloading-------------------------------------------\\

	 Quat operator*(const Quat&);
	 Quat operator*(const float&);
	 Quat operator*(const Vec3&);
	 Quat operator+(const Quat&);
	 Quat operator-(const Quat&);
	 Quat operator/(const float&);

	//--------------------------------Actual Maths----------------------------------------------------\\

	 Quat conjugate();
	 Quat inverse();
	void NormalizeThis();

	static Vec3 rotate(Quat, Vec3);
	static float length(Quat);
	static float dot(Quat, Quat);

};

class Vec4 {
public:
	float w, x, y, z;

	//--------------------------------Constructors and Factories------------------------------------\\

	Vec4();
	Vec4(float, float, float, float);
	static Vec4 Zero();
	static Vec4 BasisW();
	static Vec4 BasisX();
	static Vec4 BasisY();
	static Vec4 BasisZ();
	static Vec4 HomoVec3(Vec3);

	//--------------------------------Operator Overloading-------------------------------------------\\

	 Vec4 operator+(const Vec4&);
	 Vec4 operator+=(const Vec4&);
	 Vec4 operator-(const Vec4&);
	 Vec4 operator-=(const Vec4&);
	 Vec4 operator*(const float&);
	 Vec4 operator*=(const float&);
	 Vec4 operator/(const float&);
	 Vec4 operator/=(const float&);
	 void operator=(const Vec4&);
	 std::string Vec4::toString();

	//--------------------------------Actual Maths----------------------------------------------------\\

	void NormalizeThis();
	static float length(Vec4);
	Vec4 Normalized();
	static float dot(Vec4, Vec4);
};

class Matrix4 {
public:
	float values[16];

	//--------------------------------Constructors and Factories------------------------------------\\

	Matrix4();
	Matrix4(
		float, float, float, float,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float);

	static Matrix4 Rotate(Quat); //TODO -- Take other stuff??
	static Matrix4 Translate(float, float, float); //x,y,z
	static Matrix4 Zero();
	static Matrix4 Identity();

	//--------------------------------Operator Overloading-------------------------------------------\\

	 Matrix4 operator+(const Matrix4&);
	 Matrix4 operator+=(const Matrix4&);
	 Matrix4 operator-(const Matrix4&);
	 Matrix4 operator-=(const Matrix4&);
	 Matrix4 operator*(const Matrix4&);
	 Matrix4 operator*=(const Matrix4&);
	 Matrix4 operator*(const float&);
	 Matrix4 operator*=(const float&);
	 void operator=(const Matrix4&);
	 Vec4 operator*(const Vec4&);
	 std::string toString();

	//--------------------------------Actual Maths----------------------------------------------------\\

	Matrix3 minor(int);
	Matrix4 transpose();
	Matrix4 inverse();
	Matrix4 cofactor();
	Matrix4 adjoint();
	Vec4 getRowVector(int) const;
	Vec4 getColVector(int) const;
	float det();
};