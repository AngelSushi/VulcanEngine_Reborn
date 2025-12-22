#pragma once

#include <complex>

#include "VMath.h"
#include <nlohmann/json.hpp>

namespace VMath {
    template<typename T>
    class Vector3 {

    public:

        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

        T x;
        T y;
        T z;

        Vector3() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Vector3(T X, T Y, T Z) {
            this->x = X;
            this->y = Y;
            this->z = Z;
        }

        Vector3<T> operator +(const Vector3<T>& vec) const {
            return { x + vec.x, y + vec.y, z + vec.z };
        }

        Vector3<T> operator +=(const Vector3<T>& vec) const {
            return { x + vec.x, y + vec.y, z + vec.z };
        }

        Vector3<T> operator -(const Vector3<T>& vec) const {
            return { x - vec.x,y - vec.y, z - vec.z };
        }

        Vector3<T> operator -=(const Vector3<T>& vec) const {
            return { x - vec.x,y - vec.y,z - vec.z };
        }

        Vector3<T> operator *(const Vector3<T>& vec) const {
            return { x * vec.x, y * vec.y,z * vec.z };
        }

        Vector3<T> operator *=(const Vector3<T>& vec) const {
            return { x * vec.x, y * vec.y, z * vec.z };
        }

        Vector3 operator *=(const float& value) const {
            return { x * value, y * value, z * value };
        }

        Vector3<T> operator /(const Vector3<T>& vec) const {
            return { x / vec.x, y / vec.y, z / vec.z };
        }

        Vector3<T> operator /=(const Vector3<T>& vec) const {
            return { x / vec.x, y / vec.y, z / vec.z };
        }

        Vector3<T> operator /(const float& value) const {
            return { x / value, y / value,z / value };
        }

        bool operator >(const Vector3<T>& vec) const {
            return x > vec.x && y > vec.y && z > vec.z;
        }

        bool operator >=(const Vector3<T>& vec) const {
            return x >= vec.x && y >= vec.y && z >= vec.z;
        }

        bool operator <(const Vector3<T>& vec) const {
            return x < vec.x && y < vec.y && z < vec.z;
        }

        bool operator <=(const Vector3<T>& vec) const {
            return x <= vec.x && y <= vec.y && z <= vec.z;
        }

        bool operator ==(const Vector3<T>& vec) const {
            return x == vec.x && y == vec.y && z == vec.z;
        }

        Vector3<T> Normalize() {
            return Vector3<T>{ x,y,z } / Magnitude();
        }

        static Vector3 Rotate(const Vector3& vec, float degrees) { // Note: This rotation is only around the Z axis for 3D vectors
            float radRotation = Deg2Rad *degrees;
            float s = std::sin(radRotation);
            float c = std::cos(radRotation);

            Vector3 rotatedVec;
            rotatedVec.x = vec.x * c - vec.y * s;
            rotatedVec.y = vec.x * s + vec.y * c;

            return rotatedVec;
        }

        static float Distance(const Vector3<T>& a, const Vector3<T>& b) {
            return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
        }

        float Distance(const Vector3<T>& b) {
            return sqrt(pow(x - b.x, 2) + pow(y - b.y, 2) + pow(z - b.z, 2));
        }

        static Vector3<T> Cross(const Vector3<T>& a,const Vector3<T>& b) {
            return { a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x };
        }

        static float Dot(const Vector3<T>& a, const Vector3<T> & b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        float Magnitude() {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        std::string ToString() {
            return "[X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ",Z=" + std::to_string(z) + "]";
        }

        static Vector3 Zero() {
            return { 0,0,0 };
        }

        static Vector3 One() {
            return { 1,1,1 };
        }
    };

    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    
    template<typename T>
    void to_json(nlohmann::json& j, const Vector3<T>& v) {
        j = nlohmann::json::array({v.x,v.y,v.z});
    }

    template<typename T>
    void from_json(const nlohmann::json& j, Vector3<T>& v) {
        v.x = j.value("x",0);
        v.y = j.value("y",0);
        v.z = j.value("z",0);
    }
}
