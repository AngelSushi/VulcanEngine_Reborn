#include <Components/Transform.h>
#include <fmt/core.h>
#include <imgui.h>

#include <Entity.h>

#include <VDrawHelper.h>

#include <MatrixFloat.h>

namespace VulcanEngine {
	Transform::Transform(VMath::Vector3f InPosition, float InRotation, VMath::Vector3f InScale) : _Parent(nullptr),Position(InPosition),Rotation(InRotation),Scale(InScale) {
		//fmt::println("Constructeur par copie de Transform");
	}

	Transform::Transform(Transform&& MoveTransform) noexcept : _Childrens(std::move(MoveTransform._Childrens)),_Parent(nullptr) {
		fmt::println("Constructeur par mouvement de Transform");
		
		Position = MoveTransform.Position;
		Rotation = MoveTransform.Rotation;
		Scale = MoveTransform.Scale;

		SetParent(MoveTransform._Parent);

		for (Transform* Child : _Childrens) {
			Child->_Parent = this;
		}
	}

	Transform& Transform::operator=(const Transform& CopyTransform) {
		fmt::println("Affectation par copie de Transform");

		Position = CopyTransform.Position;
		Rotation = CopyTransform.Rotation;
		Scale = CopyTransform.Scale;

		SetParent(CopyTransform._Parent);

		return *this;
	}

	Transform& Transform::operator=(Transform&& MoveTransform) noexcept {
		fmt::println("Affectation par mouvement de Transform");

		for (Transform* Child : _Childrens) {
			Child->_Parent = nullptr;
		}

		_Childrens = std::move(MoveTransform._Childrens);
		
		Position = MoveTransform.Position;
		Rotation = MoveTransform.Rotation;
		Scale = MoveTransform.Scale;

		SetParent(MoveTransform._Parent);

		for (Transform* Child : _Childrens) {
			Child->_Parent = this;
		}

		return *this;
	}

	VMath::MatrixFloat Transform::GetTransformMatrix() const {
		VMath::MatrixFloat TransformMatrix = VMath::MatrixFloat::Translate(Position) * VMath::MatrixFloat::Rotate(Rotation) * VMath::MatrixFloat::Scale(Scale);
	
		if (_Parent) {
			TransformMatrix = TransformMatrix * _Parent->GetTransformMatrix();
		}

		return TransformMatrix;
	}

	VMath::Vector3f Transform::GetGlobalPosition()  {
		if (!_Parent) {
			return GetPosition();
		}

		return _Parent->TransformPoint(GetPosition());
	}

	float Transform::GetGlobalRotation()  {
		if (!_Parent) {
			return GetRotation();
		}
		
		return _Parent->GetGlobalRotation() + GetRotation();
	}

	VMath::Vector3f Transform::GetGlobalScale()  {
		if (!_Parent) {
			return GetScale();
		}

		return _Parent->GetGlobalScale() * GetScale();
	}

	void Transform::Translate(VMath::Vector3f Translation) {
		Position += Translation;
	}

	void Transform::Rotate(float Angle) {
		Rotation += Angle;
	}

	void Transform::SelfScale(VMath::Vector3f InScale) {
		Scale *= InScale;
	}

	void Transform::SelfScale(float InScale) {
		Scale *= InScale;
	}

	void Transform::SetParent(Transform* NewParent) {
		if (NewParent == _Parent) {
			return;
		}

		if (_Parent) {
			_Parent->DetachChild(this);
		}

		_Parent = NewParent;

		if (_Parent) {
			_Parent->AttachChild(this);
		}
	}

	void Transform::SetPosition(VMath::Vector3f NewPosition) {
		Position = NewPosition;
	}

	void Transform::SetScale(VMath::Vector3f NewScale) {
		Scale = NewScale;
	}

	void Transform::SetRotation(float NewRotation) {
		Rotation = NewRotation;
	}

	VMath::Vector3f Transform::TransformPoint(VMath::Vector3f Point) {
		
		Point *= GetGlobalScale();

		Point = VMath::Vector3f::Rotate(Point, GetGlobalRotation());

		if (_Parent) {
			Point += _Parent->TransformPoint(Position);
		}
		else {
			Point += Position;
		}

		return Point;
	}

	VMath::Vector3f Transform::TransformInversePoint(VMath::Vector3f Point)  {
		if (_Parent) {
			Point -= _Parent->TransformPoint(Position);
		}
		else {
			Point -= Position;
		}

		Point = VMath::Vector3f::Rotate(Point, -GetGlobalRotation());

		Point /= GetGlobalScale();

		return Point;
	}

	void Transform::AttachChild(Transform* Child) {
		_Childrens.push_back(Child);
	}

	void Transform::DetachChild(Transform* Child) {
		auto it = std::find(_Childrens.begin(), _Childrens.end(), Child);

		if (it != _Childrens.end()) {
			_Childrens.erase(it);
		}
	}
	
	void Transform::LoadComponent(const nlohmann::json& Descr) {
		if (Descr.contains("Position")) {
			Position = Descr["Position"].get<VMath::Vector3f>();
		}

		if (Descr.contains("Rotation")) {
			Rotation = Descr["Rotation"].get<float>();
		}

		if (Descr.contains("Scale")) {
			Scale = Descr["Scale"].get<VMath::Vector3f>();
		}
	}

	void Transform::SaveComponent(std::vector<std::uint8_t>& ByteArray) {}

	Transform::~Transform() {
		if (_Parent) {
			_Parent->DetachChild(this);
		}

		for (Transform* Child : _Childrens) {
			Child->_Parent = nullptr;
		}
	}



}
