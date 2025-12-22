#pragma once
#include <functional>
#include <memory>
#include <fmt/core.h>

#include "TVector.h"


namespace VulcanEngine {
	class LogCategory;
	class AssetsManager;
	
	template<typename T>
	class IRegistry { // Owning registry of objects of type T
	public:
		IRegistry() = default;
		virtual ~IRegistry() = default;
		

		virtual void Load(std::function<TVector<std::unique_ptr<T>>()> InLoader) {
			Registry = InLoader();
		}
		

		virtual T& Register(std::unique_ptr<T> InObject) {
			T& ref = *InObject;
			Registry.push_back(std::move(InObject));
			return ref;
		}

		T* Get(size_t Index) {
			return Registry[Index].get();
		}
		

		template<typename Pred>
		T* FindIf(Pred&& InPred) const {
			for (auto& p : Registry) {
				if (InPred(*p)) {
					return p.get();
				}
			}

			return nullptr;
		}

		size_t Size() const {
			return Registry.size();
		}

		TVector<std::unique_ptr<T>>& GetAll() {
			return Registry;
		}
		

		auto begin() { return Registry.begin(); }
		auto end() { return Registry.end(); }
		auto begin() const { return Registry.begin(); }
		auto end() const { return Registry.end(); }
		auto cbegin() const { return Registry.cbegin(); }
		auto cend() const { return Registry.cend(); }
		

	protected:
		TVector<std::unique_ptr<T>> Registry;
	};
}

