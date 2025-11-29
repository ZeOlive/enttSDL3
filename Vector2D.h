#pragma once
#include <ostream>
#include <type_traits>

template <typename T>
class Vector2D {
	static_assert(std::is_aritmetic_v<T>, "Vector2D<T>: T must be an arithmetic type");

private:
	T x{};
	T y{};

public:

	constexpr Vector2D() = default;
	constexpr Vector2D(T x, T y) noexcept : x(x), y(y) {}

	constexpr Vector2D& Add(const Vector2D& v) noexcept { x += v.x; y += v.y; return *this; }
	constexpr Vector2D& Subtract(const Vector2D& v) noexcept { x -= v.x; y -= v.y; return *this; }
	constexpr Vector2D& Multiply(const Vector2D& v) noexcept { x *= v.x; y *= v.y; return *this; }
	constexpr Vector2D& Divide(const Vector2D& v) noexcept { x /= v.x; y /= v.y; return *this; }

	//Compound assignment operators (vector–vector)
	constexpr Vector2D& operator+=(const Vector2D& v) noexcept { return Add(v); }
	constexpr Vector2D& operator-=(const Vector2D& v) noexcept { return Subtract(v); }
	constexpr Vector2D& operator*=(const Vector2D& v) noexcept { return Multiply(v); }
	constexpr Vector2D& operator/=(const Vector2D& v) noexcept { return Divide(v); }

	// Scalar operations
	friend constexpr Vector2D& operator+=(const T& s) noexcept { x += s; y += s; return *this; }
	friend constexpr Vector2D& operator-=(const T& s) noexcept { x -= s; y -= s; return *this; }
	friend constexpr Vector2D& operator*=(const T& s) noexcept { x *= s; y *= s; return *this; }
	friend constexpr Vector2D& operator/=(const T& s) noexcept { x /= s; y /= s; return *this; }

    // Unary operators
    constexpr Vector2D operator-() const noexcept {
        return Vector2D(-x, -y);
    }

    // Friend free arithmetic operators (vector–vector)
    friend constexpr Vector2D operator+(Vector2D lhs, const Vector2D& rhs) noexcept {
        lhs += rhs;
        return lhs;
    }
    friend constexpr Vector2D operator-(Vector2D lhs, const Vector2D& rhs) noexcept {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr Vector2D operator*(Vector2D lhs, const Vector2D& rhs) noexcept {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr Vector2D operator/(Vector2D lhs, const Vector2D& rhs) noexcept {
        lhs /= rhs;
        return lhs;
    }

    // Friend free arithmetic operators (vector–scalar and scalar–vector)
    friend constexpr Vector2D operator+(Vector2D lhs, T scalar) noexcept {
        lhs += scalar;
        return lhs;
    }
    friend constexpr Vector2D operator+(T scalar, Vector2D rhs) noexcept {
        rhs += scalar;
        return rhs;
    }

    friend constexpr Vector2D operator-(Vector2D lhs, T scalar) noexcept {
        lhs -= scalar;
        return lhs;
    }
    friend constexpr Vector2D operator-(T scalar, Vector2D rhs) noexcept {
        // special case: scalar - vector
        rhs.x = scalar - rhs.x;
        rhs.y = scalar - rhs.y;
        return rhs;
    }

    friend constexpr Vector2D operator*(Vector2D lhs, T scalar) noexcept {
        lhs *= scalar;
        return lhs;
    }
    friend constexpr Vector2D operator*(T scalar, Vector2D rhs) noexcept {
        rhs *= scalar;
        return rhs;
    }

    friend constexpr Vector2D operator/(Vector2D lhs, T scalar) noexcept {
        lhs /= scalar;
        return lhs;
    }
    friend constexpr Vector2D operator/(T scalar, Vector2D rhs) noexcept {
        rhs.x = scalar / rhs.x;
        rhs.y = scalar / rhs.y;
        return rhs;
    }

    // Output stream (for debugging / printing)
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};
