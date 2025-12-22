#pragma once
#include <Export.h>
#include <vector>
#include <Components/VComponent.h>

#include <MatrixFloat.h>
#include <Vector2.h>
#include "ComponentRegistry.h"
#include <Transform.vht.h>

namespace VulcanEngine {

	class Transform;

	REGISTER_COMPONENT(Transform)

	VCLASS()
	class VULCAN_ENGINE_API Transform : public VComponent {
	
		class Entity;

		VCLASS_BODY()
	public:

		// Constructors
		Transform(VMath::Vector3f InPosition =VMath::Vector3f::Zero(), float InRotation = 0.F, VMath::Vector3f InScale = VMath::Vector3f::One());
		Transform(const Transform&) = delete;
		Transform(Transform&& MoveTransform) noexcept;
		
		// Operators
		Transform& operator=(const Transform&);
		Transform& operator=(Transform&& MoveTransform) noexcept;

		VMath::Vector3f GetGlobalPosition();
		VMath::Vector3f GetPosition() { return Position; }
		
		const std::vector<Transform*>& GetChildrens() { return _Childrens; }
		
		const bool HasParent() { return _Parent != nullptr; }
		Transform* GetParent() { return _Parent; }

		float GetGlobalRotation();
		float GetRotation() { return Rotation; }
		
		VMath::Vector3f GetGlobalScale();
		VMath::Vector3f GetScale() { return Scale; }

		VMath::MatrixFloat GetTransformMatrix() const;
	
		void SetParent(Transform* NewParent);

		void SetPosition(VMath::Vector3f NewPosition);
		void SetScale(VMath::Vector3f NewScale);
		void SetRotation(float NewRotation);

		void Translate(VMath::Vector3f Translation);
		void Rotate(float Angle);
		void SelfScale(VMath::Vector3f Scale);
		void SelfScale(float Scale);

		VMath::Vector3f TransformPoint(VMath::Vector3f Point);
		VMath::Vector3f TransformInversePoint(VMath::Vector3f Point);

		// VComponent Function

		std::string GetComponentName() override {
			return "Transform";
		}

		void LoadComponent(const nlohmann::json& Descr) override;
		virtual void SaveComponent(std::vector<std::uint8_t>& ByteArray);

		// Destructor
		~Transform();
	
	private:

		void AttachChild(Transform* Child);
		void DetachChild(Transform* Child);

		VPROPERTY()
		VMath::Vector3f Position;

		VPROPERTY()
		float Rotation;

		VPROPERTY()
		VMath::Vector3f Scale;

		std::vector<Transform*> _Childrens;
		Transform* _Parent;

	};
}

