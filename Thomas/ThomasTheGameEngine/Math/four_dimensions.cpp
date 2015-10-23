#include "four_dimensions.hpp"

//Quats

//--------------------------------Constructors and Factories------------------------------------\\

Quat::Quat() {
	w = 1;
	vector = Vec3::Zero();
}

Quat::Quat(float _w, Vec3 _vector) {
	w = _w;
	vector = _vector;
}

Quat::Quat(float _w, float _x, float _y, float _z) {
	w = _w;
	vector.x = _x;
	vector.y = _y;
	vector.z = _z;
}

//--------------------------------Operator Overloading-------------------------------------------\\

 Quat Quat::operator*(const Quat& other) {
	return Quat(w * other.w - Vec3::dot(vector, other.vector), Vec3(other.vector * w + vector * other.w + Vec3::cross(vector, other.vector)));
}

 Quat Quat::operator*(const float& other) {
	return (Quat(w * other, vector * other));
}

 Quat Quat::operator*(const Vec3& other) {
	return *this * Quat(0, other);
}

 Quat Quat::operator+(const Quat& other) {
	return Quat(w + other.w, vector + other.vector);
}

 Quat Quat::operator-(const Quat& other) {
	return Quat(w - other.w, vector - other.vector);
}

 Quat Quat::operator/(const float& other) {
	return Quat(w / other, vector / other);
}

//--------------------------------Actual Maths----------------------------------------------------\\

 Quat Quat::conjugate() {
	return Quat(w, vector * -1);
}

 Quat Quat::inverse() {
	return conjugate() / (Quat::length(*this) * Quat::length(*this));
}

void Quat::NormalizeThis() {
	w /= Quat::length(*this);
	vector /= Quat::length(*this);
}

Vec3 Quat::rotate(Quat rotation, Vec3 value) { //Assumes quat is normalized
	return Quat(rotation * value * rotation.inverse()).vector;
}

float Quat::length(Quat value) {
	return sqrt(value.w * value.w +
		value.vector.x * value.vector.x +
		value.vector.y * value.vector.y +
		value.vector.z * value.vector.z);
}

float Quat::dot(Quat first, Quat second) {
	return first.w * second.w + Vec3::dot(first.vector, second.vector);
}

//--------------------------------Constructors and Factories------------------------------------\\

Vec4::Vec4() {
	w = 0;
	x = 0;
	y = 0;
	z = 0;
}

Vec4::Vec4(float _w, float _x, float _y, float _z) {
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}

Vec4 Vec4::Zero() {
	return Vec4(0, 0, 0, 0);
}

Vec4 Vec4::BasisW() {
	return Vec4(1, 0, 0, 0);
}

Vec4 Vec4::BasisX() {
	return Vec4(0, 1, 0, 0);
}

Vec4 Vec4::BasisY() {
	return Vec4(0, 0, 1, 0);
}

Vec4 Vec4::BasisZ() {
	return Vec4(0, 0, 0, 1);
}

Vec4 Vec4::HomoVec3(Vec3 value) {
	return Vec4(value.x, value.y, value.z, 1);
}

//--------------------------------Operator Overloading-------------------------------------------\\

 Vec4 Vec4::operator+(const Vec4& value) {
	return Vec4(w + value.w, x + value.x, y + value.y, z + value.z);
}

 Vec4 Vec4::operator+=(const Vec4& value) {
	w += value.w;
	x += value.x;
	y += value.y;
	z += value.z;
	return *this;
}

 Vec4 Vec4::operator-(const Vec4& value) {
	return Vec4(w - value.w, x - value.x, y - value.y, z - value.z);
}

 Vec4 Vec4::operator-=(const Vec4& value) {
	w -= value.w;
	x -= value.x;
	y -= value.y;
	z -= value.z;
	return *this;
}

 Vec4 Vec4::operator*(const float& value) {
	return Vec4(w * value, x * value, y * value, z * value);
}

 Vec4 Vec4::operator*=(const float& value) {
	w *= value;
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

 Vec4 Vec4::operator/(const float& value) {
	return Vec4(w / value, x / value, y / value, z / value);
}

 Vec4 Vec4::operator/=(const float& value) {
	w /= value;
	x /= value;
	y /= value;
	z /= value;
	return *this;
}
 void Vec4::operator=(const Vec4& value) {
	w = value.w;
	x = value.x;
	y = value.y;
	z = value.z;
}

 std::string Vec4::toString() {
	 return ("<" + std::to_string(w) + " , " + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ">");
 }

//--------------------------------Actual Maths----------------------------------------------------\\

void Vec4::NormalizeThis() {
	float size = Vec4::length(*this);
	w /= size;
	x /= size;
	y /= size;
	z /= size;
}

float Vec4::length(Vec4 value) {
	return sqrt(value.w * value.w + value.x * value.x + value.y * value.y + value.z * value.z);
}

Vec4 Vec4::Normalized() {
	float size = length(*this);
	return Vec4(w / size, x / size, y / size, z / size);
}

float Vec4::dot(Vec4 first, Vec4 second) {
	return first.w * second.w + first.x * second.x + first.y * second.y + first.z * second.z;
}

//Matrix

//--------------------------------Constructors and Factories------------------------------------\\

//Default identity matrix
Matrix4::Matrix4(
	float _0, float _1, float _2, float _3,
	float _4, float _5, float _6, float _7,
	float _8, float _9, float _10, float _11,
	float _12, float _13, float _14, float _15) 
{
	values[0] = _0; values[1] = _1; values[2] = _2; values[3] = _3;
	values[4] = _4; values[5] = _5; values[6] = _6; values[7] = _7;
	values[8] = _8; values[9] = _9; values[10] = _10; values[11] = _11;
	values[12] = _12; values[13] = _13; values[14] = _14; values[15] = _15;
}

//Matrix4 Rotate(Quat); TODO -- Take a quat (vec4)?

Matrix4 Matrix4::Rotate(float angle_x, float angle_y, float angle_z)
{
	float toRads = 3.141592653589793f / 180.0f;

	angle_x = angle_x * toRads; 
	angle_y = angle_y * toRads;
	angle_z = angle_z * toRads;

	Matrix4 transformMatrix, xRotation, yRotation, zRotation;

	xRotation = Matrix4(1, 0, 0, 0,
		0, cos(angle_x), -sin(angle_x), 0,
		0, sin(angle_x), cos(angle_x), 0);

	yRotation = Matrix4(cos(angle_y), 0, sin(angle_y), 0,
		0, 1, 0, 0,
		-sin(angle_y), 0, cos(angle_y), 0);

	zRotation = Matrix4(cos(angle_z), -sin(angle_z), 0, 0,
		sin(angle_z), cos(angle_z), 0, 0);

	transformMatrix = xRotation * yRotation * zRotation;

	return transformMatrix;
}

Matrix4 Matrix4::Translate(float _x, float _y, float _z) {
	return Matrix4(
		1, 0, 0, _x,
		0, 1, 0, _y,
		0, 0, 1, _z,
		0, 0, 0, 1);
}

Matrix4 Matrix4::Zero() {
	return Matrix4(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
}

Matrix4 Matrix4::Identity() {
	return Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

//--------------------------------Operator Overloading-------------------------------------------\\

 Matrix4 Matrix4::operator*(const Matrix4& other) {
	return Matrix4(
		Vec4::dot(getRowVector(0), other.getColVector(0)), Vec4::dot(getRowVector(0), other.getColVector(1)), Vec4::dot(getRowVector(0), other.getColVector(2)), Vec4::dot(getRowVector(0), other.getColVector(3)),
		Vec4::dot(getRowVector(1), other.getColVector(0)), Vec4::dot(getRowVector(1), other.getColVector(1)), Vec4::dot(getRowVector(1), other.getColVector(2)), Vec4::dot(getRowVector(1), other.getColVector(3)),
		Vec4::dot(getRowVector(2), other.getColVector(0)), Vec4::dot(getRowVector(2), other.getColVector(1)), Vec4::dot(getRowVector(2), other.getColVector(2)), Vec4::dot(getRowVector(2), other.getColVector(3)),
		Vec4::dot(getRowVector(3), other.getColVector(0)), Vec4::dot(getRowVector(3), other.getColVector(1)), Vec4::dot(getRowVector(3), other.getColVector(2)), Vec4::dot(getRowVector(3), other.getColVector(3)));
}

 Matrix4 Matrix4::operator*=(const Matrix4& other) {
	for (int i = 0; i < 16; i++) {
		values[i] = Vec4::dot(getRowVector(i / 4), getColVector(i % 4));
	}
	return *this;
}

 Matrix4 Matrix4::operator+(const Matrix4& other) {
	return Matrix4(
		values[0] + other.values[0], values[1] + other.values[1], values[2] + other.values[2], values[3] + other.values[3],
		values[4] + other.values[4], values[5] + other.values[5], values[6] + other.values[6], values[7] + other.values[7],
		values[8] + other.values[8], values[9] + other.values[9], values[10] + other.values[10], values[11] + other.values[11],
		values[12] + other.values[12], values[13] + other.values[13], values[14] + other.values[14], values[15] + other.values[15]);
}

 Matrix4 Matrix4::operator+=(const Matrix4& other) {
	for (int i = 0; i < 16; i++) {
		values[i] += other.values[i];
	}
	return *this;
}

 Matrix4 Matrix4::operator-(const Matrix4& other) {
	return Matrix4(
		values[0] - other.values[0], values[1] - other.values[1], values[2] - other.values[2], values[3] - other.values[3],
		values[4] - other.values[4], values[5] - other.values[5], values[6] - other.values[6], values[7] - other.values[7],
		values[8] - other.values[8], values[9] - other.values[9], values[10] - other.values[10], values[11] - other.values[11],
		values[12] - other.values[12], values[13] - other.values[13], values[14] - other.values[14], values[15] - other.values[15]);
}

 Matrix4 Matrix4::operator-=(const Matrix4& other) {
	for (int i = 0; i < 16; i++) {
		values[i] -= other.values[i];
	}
	return *this;
}

 Matrix4 Matrix4::operator*=(const float& other) {
	for (int i = 0; i < 16; i++) {
		values[i] *= other;
	}
	return *this;
}

 Matrix4 Matrix4::operator*(const float& other) {
	 Matrix4 result = Matrix4::Zero();
	 for (int i = 0; i < 16; i++) {
		 result.values[i] = values[i] * other;
	 }
	 return result;
 }

 void Matrix4::operator=(const Matrix4& other) {
	 for (int i = 0; i < 16; i++) {
		 values[i] = other.values[i];
	 }
 }

 Vec4 Matrix4::operator*(const Vec4& other) {
	 return Vec4(
		 Vec4::dot(Matrix4::getRowVector(0), other),
		 Vec4::dot(Matrix4::getRowVector(1), other),
		 Vec4::dot(Matrix4::getRowVector(2), other),
		 Vec4::dot(Matrix4::getRowVector(3), other));
 }

 std::string Matrix4::toString() {
	 return (
		 "{" + std::to_string(values[0]) + "," + std::to_string(values[1]) + "," + std::to_string(values[2]) + "," + std::to_string(values[3]) + "\n" +
		 std::to_string(values[4]) + "," + std::to_string(values[5]) + "," + std::to_string(values[6]) + "," + std::to_string(values[7]) + "\n" +
		 std::to_string(values[8]) + "," + std::to_string(values[9]) + "," + std::to_string(values[10]) + "," + std::to_string(values[11]) + "\n" +
		 std::to_string(values[12]) + "," + std::to_string(values[13]) + "," + std::to_string(values[14]) + "," + std::to_string(values[15]) + "}");
 }

//--------------------------------Actual Maths----------------------------------------------------\\

Matrix4 Matrix4::transpose() {
	return Matrix4(
		values[0], values[4], values[8], values[12],
		values[1], values[5], values[9], values[13],
		values[2], values[6], values[10], values[14],
		values[3], values[7], values[11], values[15]);
}

Matrix4 Matrix4::inverse() {
	return adjoint() * (1 / det());
}

Matrix3 Matrix4::minor(int index) {
	Matrix3 result;
	int oldIndex = 0;
	for (int i = 0; i < 9; i++) {
		while (oldIndex / 4 == index / 4 || oldIndex % 4 == index % 4) {
			oldIndex++;
		}
		result.values[i] = values[oldIndex++];
	}
	return result;
}

Matrix4 Matrix4::cofactor() {
	Matrix4 cofactorMatrix;
	for (int i = 0; i < 16; i++) {
		cofactorMatrix.values[i] = pow(-1, i % 4 + i / 4) * minor(i).det();
	}
	return cofactorMatrix;
}

Matrix4 Matrix4::adjoint() {
	return cofactor().transpose();
}

float Matrix4::det() {
	float determ = 0;
	for (int i = 0; i < 4; i++) {
		determ += pow(-1,i) * values[i] * minor(i).det();
	}
	return determ;
}

Vec4 Matrix4::getRowVector(int row) const {
	return Vec4(values[0 + row * 4], values[1 + row * 4], values[2 + row * 4], values[3 + row * 4]);
}

Vec4 Matrix4::getColVector(int col) const {
	return Vec4(values[0 + col], values[4 + col], values[8 + col], values[12 + col]);
}