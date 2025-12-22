#pragma once
#include <functional>
#include <memory>
#include <fmt/core.h>

#include "TVector.h"


namespace VulcanEngine {
	
	template<typename T>
	class ObjectRegistry { // No-owning registry of objects of type T
	public:
		ObjectRegistry() = default;
		virtual ~ObjectRegistry() = default;
		

		virtual void Load(std::function<TVector<T*>()> Loader) {
			Registry = Loader();
		}
		

		virtual T& Register(T* Object) {
			Registry.push_back(Object);
			return *Object;
		}

		T* Get(size_t Index) {
			return Registry[Index];
		}
		

		template<typename Pred>
		T* FindIf(Pred&& InPred) const {
			for (auto& p : Registry) {
				if (InPred(*p)) {
					return p;
				}
			}

			return nullptr;
		}

		size_t Size() const {
			return Registry.size();
		}

		TVector<T*>& GetAll() {
			return Registry;
		}
		

		auto begin() { return Registry.begin(); }
		auto end() { return Registry.end(); }
		auto begin() const { return Registry.begin(); }
		auto end() const { return Registry.end(); }
		auto cbegin() const { return Registry.cbegin(); }
		auto cend() const { return Registry.cend(); }
		

	protected:
		TVector<T*> Registry;
	};
}

