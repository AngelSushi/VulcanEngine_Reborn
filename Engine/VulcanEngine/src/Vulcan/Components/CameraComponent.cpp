#include <Components/CameraComponent.h>
#include <imgui.h>
#include <Components/VComponent.h>

#include <MatrixFloat.h>

namespace VulcanEngine {

	
	void CameraComponent::LookAt(const VMath::Vector3f eye, const VMath::Vector3f at,VMath::Vector3f up,VMath::MatrixFloat& Matrix) {
		VMath::Vector3f X, Y, Z, tmp;

		tmp.x = eye.x - at.x;
		tmp.y = eye.y - at.y;
		tmp.z = eye.z - at.z;
		
		Z = tmp.Normalize();
		Y = up.Normalize();
	
		tmp = VMath::Vector3f::Cross(Y, Z);
		X = tmp.Normalize();

		tmp = VMath::Vector3f::Cross(Z, X);
		Y = tmp.Normalize();

		Matrix[0] = X.x;
		Matrix[1] = Y.x;
		Matrix[2] = Z.x;
		Matrix[3] = 0.0f;
		Matrix[4] = X.y;
		Matrix[5] = Y.y;
		Matrix[6] = Z.y;
		Matrix[7] = 0.0f;
		Matrix[8] = X.z;
		Matrix[9] = Y.z;
		Matrix[10] = Z.z;
		Matrix[11] = 0.0f;
		Matrix[12] = -VMath::Vector3f::Dot(X, eye);
		Matrix[13] = -VMath::Vector3f::Dot(Y, eye);
		Matrix[14] = -VMath::Vector3f::Dot(Z, eye);
		Matrix[15] = 1.0f;
	}

	void CameraComponent::Init() {
		VComponent::Init();
	}

	void CameraComponent::Frustum(float left, float right, float bottom, float top, float znear, float zfar,VMath::MatrixFloat& Matrix) {
		float temp, temp2, temp3, temp4;
		temp = 2.0f * znear;
		temp2 = right - left;
		temp3 = top - bottom;
		temp4 = zfar - znear;
		Matrix[0] = temp / temp2;
		Matrix[1] = 0.0;
		Matrix[2] = 0.0;
		Matrix[3] = 0.0;
		Matrix[4] = 0.0;
		Matrix[5] = temp / temp3;
		Matrix[6] = 0.0;
		Matrix[7] = 0.0;
		Matrix[8] = (right + left) / temp2;
		Matrix[9] = (top + bottom) / temp3;
		Matrix[10] = (-zfar - znear) / temp4;
		Matrix[11] = -1.0f;
		Matrix[12] = 0.0;
		Matrix[13] = 0.0;
		Matrix[14] = (-temp * zfar) / temp4;
		Matrix[15] = 0.0;
	}

	void CameraComponent::Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar,VMath::MatrixFloat& Matrix) {
		float ymax, xmax;
		ymax = znear * tanf(fovyInDegrees * 3.141592f / 180.0f);
		xmax = ymax * aspectRatio;
		Frustum(-xmax, xmax, -ymax, ymax, znear, zfar, Matrix);
	}

	void CameraComponent::Orthographic(const float l, float r, float b, const float t, float zn, const float zf,VMath::MatrixFloat& Matrix) {
		Matrix[0] = 2 / (r - l);
		Matrix[1] = 0.0f;
		Matrix[2] = 0.0f;
		Matrix[3] = 0.0f;
		Matrix[4] = 0.0f;
		Matrix[5] = 2 / (t - b);
		Matrix[6] = 0.0f;
		Matrix[7] = 0.0f;
		Matrix[8] = 0.0f;
		Matrix[9] = 0.0f;
		Matrix[10] = 1.0f / (zf - zn);
		Matrix[11] = 0.0f;
		Matrix[12] = (l + r) / (l - r);
		Matrix[13] = (t + b) / (b - t);
		Matrix[14] = zn / (zn - zf);
		Matrix[15] = 1.0f;
	}


	void CameraComponent::LoadComponent(const nlohmann::json& Descr) {}

	void CameraComponent::SaveComponent(std::vector<std::uint8_t>& ByteArray) {}

	

	

}
