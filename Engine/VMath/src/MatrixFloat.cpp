#include <cmath>

#include <MatrixFloat.h>

namespace VMath {
	MatrixFloat::MatrixFloat(std::array<float, 4 * 4> Values) :
		_Values(Values) {
	}

	float MatrixFloat::Determinant() const {
		float det = Value(0, 0) * (Value(1, 1) * Value(2, 2) - Value(2, 1) * Value(1, 2)) -
			Value(0, 1) * (Value(1, 0) * Value(2, 2) - Value(1, 2) * Value(2, 0)) +
			Value(0, 2) * (Value(1, 0) * Value(2, 1) - Value(1, 1) * Value(2, 0));

		// Complete for 3D

		return det;
	}

	MatrixFloat MatrixFloat::GetInverse() const {
		float invDet = 1.0f / Determinant();

		MatrixFloat result;
		result(0, 0) = (Value(1, 1) * Value(2, 2) - Value(2, 1) * Value(1, 2)) * invDet;
		result(0, 1) = -(Value(0, 1) * Value(2, 2) - Value(0, 2) * Value(2, 1)) * invDet;
		result(0, 2) = (Value(0, 1) * Value(1, 2) - Value(0, 2) * Value(1, 1)) * invDet;
		result(1, 0) = -(Value(1, 0) * Value(2, 2) - Value(1, 2) * Value(2, 0)) * invDet;
		result(1, 1) = (Value(0, 0) * Value(2, 2) - Value(0, 2) * Value(2, 0)) * invDet;
		result(1, 2) = -(Value(0, 0) * Value(1, 2) - Value(1, 0) * Value(0, 2)) * invDet;
		result(2, 0) = (Value(1, 0) * Value(2, 1) - Value(2, 0) * Value(1, 1)) * invDet;
		result(2, 1) = -(Value(0, 0) * Value(2, 1) - Value(2, 0) * Value(0, 1)) * invDet;
		result(2, 2) = (Value(0, 0) * Value(1, 1) - Value(1, 0) * Value(0, 1)) * invDet;

		// Complete for 3D 

		return result;
	}

	MatrixFloat MatrixFloat::GetTransposed() const {
		MatrixFloat mat;
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t j = 0; j < 4; ++j)
				mat(j, i) = Value(i, j);
		}

		return mat;
	}

	float& MatrixFloat::Value(std::size_t i, std::size_t j) {
		return _Values[i * 4 + j];
	}

	const float& MatrixFloat::Value(std::size_t i, std::size_t j) const {
		return _Values[i * 4 + j];
	}

	float& MatrixFloat::operator()(std::size_t i, std::size_t j) {
		return Value(i, j);
	}

	const float& MatrixFloat::operator()(std::size_t i, std::size_t j) const {
		return Value(i, j);
	}

	MatrixFloat MatrixFloat::operator*(const MatrixFloat& rhs) const {
		MatrixFloat result;
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t j = 0; j < 4; ++j) {
				float sum = 0.0f;
				for (std::size_t k = 0; k < 4; ++k)
					sum += Value(i, k) * rhs(k, j);

				result(i, j) = sum;
			}
		}

		return result;
	}


	MatrixFloat MatrixFloat::Identity() {
		return MatrixFloat({
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			});
	}

	MatrixFloat MatrixFloat::Rotate(float degreeAngle) {
		float sinAngle = std::sin(-degreeAngle /* * VMath::Deg2Rad*/);
		float cosAngle = std::cos(-degreeAngle /* * VMath::Deg2Rad*/ );

		return MatrixFloat({
			cosAngle, -sinAngle, 0.0f, 0.0f,
			sinAngle,  cosAngle, 0.0f, 0.0f,
			0.0f,          0.0f, 1.0f, 0.0f,
			0.0f,		   0.0f, 0.0F, 1.0f,
		});
	}
}
