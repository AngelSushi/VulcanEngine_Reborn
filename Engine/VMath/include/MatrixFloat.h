#pragma once

#include <array>

#include "Vector2.h"
#include "Vector3.h"


namespace VMath {

	class MatrixFloat {
		public:
			MatrixFloat() = default;
			MatrixFloat(std::array<float,4 * 4> Values);
	
			float Determinant() const;
	
			MatrixFloat GetInverse() const;
			MatrixFloat GetTransposed() const;
	
			float& Value(std::size_t i, std::size_t j);
			const float& Value(std::size_t i, std::size_t j) const;
	
			float& operator()(std::size_t i, std::size_t j);
			const float& operator()(std::size_t i, std::size_t j) const;
	
			float& operator[](size_t index) {
				return _Values[index];
			}
	
			const float& operator[](size_t index) const {
				return _Values[index];
			}
	
			MatrixFloat operator*(const MatrixFloat& rhs) const;
	
			template<typename T>
			Vector2<T> operator*(const Vector2<T>& vec) const;
	
			float* ToArray() {
				float Data[16];
	
				for (int i = 0; i < _Values.size(); i++) {
					Data[i] = _Values[i];
				}
	
				return Data;
			}
	
	
			static MatrixFloat Identity();
			static MatrixFloat Rotate(float degreeAngle);
	
			template<typename T>
			static MatrixFloat Scale(const Vector2<T>& scale);

			template<typename T>
			static MatrixFloat Scale(const Vector3<T>& scale);
	
			template<typename T>
			static MatrixFloat Translate(const Vector2<T>& translation);

			template<typename T>
			static MatrixFloat Translate(const Vector3<T>& translation);
	
		private:
			std::array<float,4 * 4> _Values;
		};
	
		template<typename T>
		MatrixFloat MatrixFloat::Scale(const Vector2<T>& scale) {
			return MatrixFloat({
				scale.x, 0.0f,	  0.0f,	  0.0F,
				0.0f,    scale.y, 0.0f,	  0.0F,
				0.f,     0.0f,    1.0f,	  0.0F,
				0.F,	 0.0F,	  0.0F,	  1.0F,
				});
		}

		template <typename T>
		MatrixFloat MatrixFloat::Scale(const Vector3<T>& scale) {
			return MatrixFloat({
				scale.x, 0.0f,	  0.0f,	  0.0F,
				0.0f,    scale.y, 0.0f,	  0.0F,
				0.f,     0.0f,    scale.z,	  0.0F,
				0.F,	 0.0F,	  0.0F,	  1.0F,
				});
		}

		template<typename T>
		MatrixFloat MatrixFloat::Translate(const Vector2<T>& translation) {
			return MatrixFloat({
				1.0f, 0.0f, translation.x, 0.0f,
				0.0f, 1.0f, translation.y, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				});
		}

		template <typename T>
		MatrixFloat MatrixFloat::Translate(const Vector3<T>& translation) {
			return MatrixFloat({
				1.0f, 0.0f, translation.x, 0.0f,
				0.0f, 1.0f, translation.y, 0.0f,
				0.0f, 0.0f, translation.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				});
		}

		template<typename T>
		Vector2<T> MatrixFloat::operator*(const Vector2<T>& vec) const {
	
			Vector2<T> result;
			result.x = Value(0, 0) * vec.x + Value(0, 1) * vec.y + Value(0, 2);
			result.y = Value(1, 0) * vec.x + Value(1, 1) * vec.y + Value(1, 2);
	
			return result;
		}
		
}




