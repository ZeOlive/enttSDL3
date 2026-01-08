#include <iostream>
#include <type_traits>

template <typename T>
class Vector2D {
public:
    T x{};
    T y{};

    // Constructors
    constexpr Vector2D() noexcept = default;
    constexpr Vector2D(T x, T y) noexcept : x(x), y(y) {}

    // Basic arithmetic
    constexpr Vector2D& Add(const Vector2D& vec) noexcept {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    constexpr Vector2D& Subtract(const Vector2D& vec) noexcept {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    constexpr Vector2D& Multiply(const Vector2D& vec) noexcept {
        x *= vec.x;
        y *= vec.y;
        return *this;
    }

    constexpr Vector2D& Divide(const Vector2D& vec) noexcept {
        x /= vec.x;
        y /= vec.y;
        return *this;
    }

    // Compound assignment operators
    constexpr Vector2D& operator+=(const Vector2D& vec) noexcept { return Add(vec); }
    constexpr Vector2D& operator-=(const Vector2D& vec) noexcept { return Subtract(vec); }
    constexpr Vector2D& operator*=(const Vector2D& vec) noexcept { return Multiply(vec); }
    constexpr Vector2D& operator/=(const Vector2D& vec) noexcept { return Divide(vec); }

    // Scalar operations
    constexpr Vector2D& operator*=(T scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr Vector2D& operator/=(T scalar) noexcept {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Reset to zero
    constexpr Vector2D& Zero() noexcept {
        x = static_cast<T>(0);
        y = static_cast<T>(0);
        return *this;
    }

    // Binary operators (return new vectors, not references!)
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

    // Scalar versions
    friend constexpr Vector2D operator*(Vector2D lhs, T scalar) noexcept {
        lhs *= scalar;
        return lhs;
    }

    friend constexpr Vector2D operator/(Vector2D lhs, T scalar) noexcept {
        lhs /= scalar;
        return lhs;
    }

    // Output stream
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        return os << "(" << vec.x << ", " << vec.y << ")";
    }
};