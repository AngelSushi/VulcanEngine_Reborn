#pragma once
#include <complex>
#include <imgui.h>

#include "VMath.h"
#include <nlohmann/json.hpp>


namespace VMath {
    template<typename T>
    class Vector2 {

    public:

        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

        T x;
        T y;
        Vector2() {
            this->x = 0;
            this->y = 0;
        }

        Vector2(T x, T y) {
            this->x = x; 
            this->y = y;
        }

        template<typename U>
        Vector2(const Vector2<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
        }
/*
        Vector2(const ImVec2& v) {
            x = static_cast<T>(v.x);
            y = static_cast<T>(v.y);
        }
  */      
        template<typename U>
        Vector2<T> operator =(const Vector2<U> vec) {
            return { (T)vec.x, (T)vec.y };
        }

        Vector2<T> operator +(const Vector2& vec) const {
            return { vec.x + x,vec.y + y };
        }

        Vector2<T>& operator +=(const Vector2& vec) {
            x += vec.x;
            y += vec.y;
                
            return *this;
        }

        Vector2 operator-() const {
            return { -x, -y };
        }
        Vector2<T> operator -(const Vector2& vec) const {
            return { x - vec.x,y - vec.y };
        }

        Vector2<T>& operator -=(const Vector2& vec) {
            x -= vec.x;
            y -= vec.y;
            
            return *this;
        }

        Vector2<T> operator *(const Vector2& vec) const {
            return { x * vec.x, y * vec.y };
        }

        Vector2<T> operator *(const T val) const {
            return { x * val, y * val };
        }

        Vector2<T> operator *=(const Vector2& vec) {
            x *= vec.x;
            y *= vec.y;

            return *this;
        }

        Vector2<T> operator *=(const T val) {
            x *= val;
            y *= val;

            return *this;
        }

        Vector2<T> operator /(const Vector2& vec) const {
            return { x / vec.x, y / vec.y };
        }

        Vector2<T> operator /=(const Vector2& vec) {
            x /= vec.x;
            y /= vec.y;

            return *this;   
        }

        Vector2<T> operator /(const float& val) const {
            return { x / val, y / val };
        }

        Vector2<T> operator /=(const float& val) {
            x /= val;
            y /= val;

            return *this;
        }

        bool operator <(const Vector2& vec) const {
            return x < vec.x && y < vec.y;
        }

        bool operator <=(const Vector2& vec) const {
            return x <= vec.x && y <= vec.y;
        }

        bool operator >(const Vector2& vec) const {
            return x > vec.x && y > vec.y;
        }

        bool operator >=(const Vector2& vec) const {
            return x >= vec.x && y >= vec.y;
        }

        bool operator ==(const Vector2& vec) const {
            return x == vec.x && y == vec.y;
        }

        operator ImVec2() const { 
            return ImVec2{static_cast<float>(x),static_cast<float>(y) };
        }
        

       /* T operator *(T a, T b) {
            return { a.x * b.x, a.y * b.y };
        }
        */

        // Rajoutez les différents operator float , vecteur

        static Vector2<T> Rotate(const Vector2& vec, float degrees) {
            float radRotation = Deg2Rad *degrees;
            float s = std::sin(radRotation);
            float c = std::cos(radRotation);

            Vector2 rotatedVec;
            rotatedVec.x = vec.x * c - vec.y * s;
            rotatedVec.y = vec.x * s + vec.y * c;

            return rotatedVec;
        }

        Vector2<T> Normalize() {
            return T(x, y) / Magnitude();
        }

        static float Distance(const Vector2<T>& a, const Vector2<T>& b) {
            return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
        }

        float Distance(const Vector2<T>& b) {
            return sqrt(pow(x - b.x, 2) + pow(y - b.y, 2));
        }

        float Magnitude() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        std::string ToString() {
            return "[x=" + std::to_string(x) + ",y=" + std::to_string(y) + "]";
        }

        static Vector2<T> Zero() {
            return { 0,0 };
        }

        static Vector2<T> One() {
            return { 1,1 };
        }

    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;

    template<typename T>
    void to_json(nlohmann::json& j, const Vector2<T>& v) {
        j = nlohmann::json::array({v.x,v.y});
    }

    template<typename T>
    void from_json(const nlohmann::json& j, Vector2<T>& v) {
        v.x = j.at(0).get<T>();
        v.y = j.at(1).get<T>();
    }
    
    
}

