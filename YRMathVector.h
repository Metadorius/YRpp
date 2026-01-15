//pd's Vector classes (math sense)
#pragma once

#include <math.h>

/*==========================================
============ 2D Vector =====================
==========================================*/

template <typename T> class Vector2D
{
public:
	static const Vector2D Empty;

	//no constructor, so this class stays aggregate and can be initialized using the curly braces {}
	T X, Y;

	//operator overloads
	template<typename T2>
	void operator=(const Vector2D<T2>& a)
	{
		this->X = static_cast<T>(a.X);
		this->Y = static_cast<T>(a.Y);
	}
	//addition
	Vector2D operator+(const Vector2D& a) const
	{
		return Vector2D{ X + a.X, Y + a.Y };
	}
	//addition
	Vector2D& operator+=(const Vector2D& a)
	{
		X += a.X;
		Y += a.Y;
		return *this;
	}
	//substraction
	Vector2D operator-(const Vector2D& a) const
	{
		return Vector2D{ X - a.X, Y - a.Y };
	}
	//substraction
	Vector2D& operator-=(const Vector2D& a)
	{
		X -= a.X;
		Y -= a.Y;
		return *this;
	}
	//negation
	Vector2D operator-() const
	{
		return Vector2D{ -X, -Y };
	}
	//equality
	bool operator==(const Vector2D& a) const
	{
		return (X == a.X && Y == a.Y);
	}
	//unequality
	bool operator!=(const Vector2D& a) const
	{
		return (X != a.X || Y != a.Y);
	}
	//scalar multiplication
	Vector2D operator*(double r) const
	{
		return Vector2D{ static_cast<T>(X * r), static_cast<T>(Y * r) };
	}
	//scalar multiplication
	Vector2D& operator*=(double r)
	{
		X *= r;
		Y *= r;
		return *this;
	}
	//vector multiplication
	double operator*(const Vector2D& a) const
	{
		return static_cast<double>(X) * a.X + static_cast<double>(Y) * a.Y;
	}
	// for map key
	bool operator<(const Vector2D& other) const
	{
		return other.X >= X || (other.X < X && other.Y >= Y);
	}
	//magnitude
	double Magnitude() const
	{
		return sqrt(MagnitudeSquared());
	}
	//magnitude squared
	double MagnitudeSquared() const
	{
		return *this * *this;
	}
	//distance from another vector
	double DistanceFrom(const Vector2D& a) const
	{
		return (a - *this).Magnitude();
	}
	//distance from another vector, squared
	double DistanceFromSquared(const Vector2D& a) const
	{
		return (a - *this).MagnitudeSquared();
	}
	//collinearity
	bool IsCollinearTo(const Vector2D& a) const
	{
		auto const c = static_cast<double>(X) * a.Y;
		return c == static_cast<double>(Y) * a.X;
	}
	//find scalar
	double FindScalar(const Vector2D& a) const
	{
		double r = static_cast<double>(a.X) / static_cast<double>(X);
		if (static_cast<T>(r * Y) == a.Y) {
			return r;
		}
		else {
			//the vectors are not collinear, return NaN!
			unsigned long NaN[2] = { 0xFFFFFFFF,0x7FFFFFFF };
			return *reinterpret_cast<double*>(NaN);
		}
	}
	//is empty
	bool IsEmpty()
	{
		return X == Empty.X && Y == Empty.Y;
	}
};

template <typename T>
const Vector2D<T> Vector2D<T>::Empty = { T(), T() };

/*==========================================
============ 3D Vector =====================
==========================================*/

template <typename T> class Vector3D
{
public:
	static const Vector3D Empty;

	//no constructor, so this class stays aggregate and can be initialized using the curly braces {}
	T X, Y, Z;

	//operator overloads
	template<typename T2>
	void operator=(const Vector3D<T2>& a)
	{
		this->X = static_cast<T>(a.X);
		this->Y = static_cast<T>(a.Y);
		this->Z = static_cast<T>(a.Z);
	}
	//addition
	Vector3D operator+(const Vector3D& a) const
	{
		return Vector3D{ X + a.X, Y + a.Y, Z + a.Z };
	}
	//addition
	Vector3D& operator+=(const Vector3D& a)
	{
		X += a.X;
		Y += a.Y;
		Z += a.Z;
		return *this;
	}
	//substraction
	Vector3D operator-(const Vector3D& a) const
	{
		return Vector3D{ X - a.X, Y - a.Y, Z - a.Z };
	}
	//substraction
	Vector3D& operator-=(const Vector3D& a)
	{
		X -= a.X;
		Y -= a.Y;
		Z -= a.Z;
		return *this;
	}
	//negation
	Vector3D operator-() const
	{
		return Vector3D{ -X, -Y, -Z };
	}
	//equality
	bool operator==(const Vector3D& a) const
	{
		return (X == a.X && Y == a.Y && Z == a.Z);
	}
	//unequality
	bool operator!=(const Vector3D& a) const
	{
		return (X != a.X || Y != a.Y || Z != a.Z);
	}
	//scalar multiplication
	Vector3D operator*(double r) const
	{
		return Vector3D{
			static_cast<T>(X * r),
			static_cast<T>(Y * r),
			static_cast<T>(Z * r) };
	}
	//scalar multiplication
	Vector3D& operator*=(double r)
	{
		X *= r;
		Y *= r;
		Z *= r;
		return *this;
	}
	//vector multiplication
	double operator*(const Vector3D& a) const
	{
		return static_cast<double>(X) * a.X
			+ static_cast<double>(Y) * a.Y
			+ static_cast<double>(Z) * a.Z;
	}
	// for map key
	bool operator<(const Vector3D& other) const
	{
		return other.X >= X || (other.X < X && other.Y >= Y) || (other.X < X && other.Y < Y && other.Z >= Z);
	}
	//magnitude
	double Magnitude() const
	{
		return sqrt(MagnitudeSquared());
	}
	//magnitude squared
	double MagnitudeSquared() const
	{
		return *this * *this;
	}
	//distance from another vector
	double DistanceFrom(const Vector3D& a) const
	{
		return (a - *this).Magnitude();
	}
	//distance from another vector, squared
	double DistanceFromSquared(const Vector3D& a) const
	{
		return (a - *this).MagnitudeSquared();
	}
	//collinearity
	bool IsCollinearTo(const Vector3D& a) const
	{
		return CrossProduct(a).MagnitudeSquared() == 0;
	}
	//find scalar
	double FindScalar(const Vector3D& a) const
	{
		double r = static_cast<double>(a.X) / static_cast<double>(X);
		if ((static_cast<T>(r * Y) == a.Y) && (static_cast<T>(r * Z) == a.Z)) {
			return r;
		}
		else {
			//the vectors are not collinear, return NaN!
			unsigned long NaN[2] = { 0xFFFFFFFF,0x7FFFFFFF };
			return *reinterpret_cast<double*>(NaN);
		}
	}
	//cross product
	Vector3D CrossProduct(const Vector3D& a) const
	{
		return Vector3D{
			Y * a.Z - Z * a.Y,
			Z * a.X - X * a.Z,
			X * a.Y - Y * a.X };
	}
	//is empty
	bool IsEmpty()
	{
		return X == Empty.X && Y == Empty.Y && Z == Empty.Z;
	}
};

template <typename T>
const Vector3D<T> Vector3D<T>::Empty = { T(), T(), T() };
