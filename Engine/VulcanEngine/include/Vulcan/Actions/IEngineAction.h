#pragma once
#include <Export.h>

namespace VulcanEngine {
	class VULCAN_ENGINE_API IEngineAction {
	public:
		
		template<typename T>
		static std::unique_ptr<T> Create() {
			auto instance = std::make_unique<T>();
			instance->RegisterBindings();
			return instance;
		}
		
		virtual void RegisterBindings() = 0;
		
		virtual ~IEngineAction() = default;

	};

}

