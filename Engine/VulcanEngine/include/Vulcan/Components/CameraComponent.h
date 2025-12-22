#pragma once
#include <Export.h>
#include <Components/VComponent.h>
#include "MatrixFloat.h"
#include "Vector3.h"

#include <CameraComponent.vht.h>


namespace VulcanEngine {

	enum VULCAN_ENGINE_API CameraMode {
		ORTHOGRAPHIC,
		PERSPECTIVE,
	};

	VCLASS()
	class VULCAN_ENGINE_API CameraComponent : public VComponent {
	
		VCLASS_BODY()
		
	public:
		
		// Getters&Setters
		CameraMode& GetCurrentMode() { return _Mode; }
		void SetMode(CameraMode Mode) { _Mode = Mode; }
		float& GetFOV() { return _FOV; }
		float& GetDistance() { return _Distance; }
		float& GetWidth() { return _ViewWidth; }

		VMath::MatrixFloat& GetView() { return _View; }
		VMath::MatrixFloat& GetProjection() { return _Projection; }

		void LookAt(VMath::Vector3f eye,VMath::Vector3f at,VMath::Vector3f up,VMath::MatrixFloat& Matrix);

		// VComponent's Functions
		void Init() override;
		void LoadComponent(const nlohmann::json& Descr) override;
		void SaveComponent(std::vector<std::uint8_t>& ByteArray) override;
		
		void Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar, VMath::MatrixFloat& Matrix);
		void Orthographic(const float l, float r, float b, const float t, float zn, const float zf, VMath::MatrixFloat& Matrix);

	private:
		CameraMode _Mode;
		float _FOV = 27.F;
		VMath::MatrixFloat _View;
		VMath::MatrixFloat _Projection;
		float _Distance = 8.F;
		float _ViewWidth = 10.F;

		void Frustum(float left, float right, float bottom, float top, float znear, float zfar, VMath::MatrixFloat& Matrix);
	};



	
}

