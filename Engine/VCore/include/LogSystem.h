#pragma once
#include <mutex>
#include <filesystem>
#include <string>
#include <vector>

#include <VTime.h>

#include <Vector3.h>
#include <Reflection/VMacros.h>
#include <Reflection/VObject.h>
#include <Types/VColor.h>
#include <CoreAPI/IRegistry.h>

#include <LogCategory.vht.h>


namespace VulcanEngine {

	VENUM()
	enum class LogLevel {
		Info,
		Debug,
		Warning,
		Error
	};

	VCLASS()
	class LogCategory : public VulcanCore::ReflectionBase {

		VCLASS_BODY()
		
	public:
		LogCategory(const std::string& InName) : Name(InName), Enabled(true) {}

		const std::string& GetName() const { return Name; }
		bool& IsEnabled() { return Enabled; }
		void SetEnabled(bool inEnabled) { Enabled = inEnabled; }

	private:
		VPROPERTY()
		std::string Name;

		VPROPERTY(UI_Combo)
		bool Enabled;
	};
	
	struct LogMessage {
		
		LogMessage(const std::string& InMessage,LogLevel InLevel,const std::string& InTimestamp,LogCategory& InCategory,const std::string& InFile,int InLine) : Message(InMessage),Level(InLevel),Timestamp(InTimestamp),Category(InCategory),File(InFile),Line(InLine) {}
		
		std::string Message;
		LogLevel Level;
		std::string Timestamp;
		LogCategory& Category;
		std::string File;
		int Line;

		VMath::Vector3f GetColorForLevel() {
			switch (Level) {
				default:
				case LogLevel::Debug:
				case LogLevel::Info:
					return VMath::Vector3f(0.04f,0.69f,0.69f);

				case LogLevel::Warning:
					return VMath::Vector3f(0.75f,0.75f,0.02f);

				case LogLevel::Error:
					return VMath::Vector3f(0.85f,0.12f,0.12f);
			}
		}
	};
	
	
	class VULCAN_ENGINE_API LogSystem {

	public:
		static LogSystem& Instance() {
			static LogSystem instance;
			return instance;
		}

		void Log(const std::string& message, LogLevel level,LogCategory& InCategory, const std::string& InFile, int InLine) {
			std::lock_guard<std::mutex> lock(Mutex);
			
			std::filesystem::path filePath(InFile);
		
			Messages.push_back(LogMessage(message, level, VTime::ToString(VTime::GetActualTime()), InCategory,filePath.filename().string(),InLine));
		}

		std::vector<LogMessage> GetMessages() const {
			return Messages;
		}

		void Clear() {
			Messages.clear();
		}

	private:
		std::vector<LogMessage> Messages;
		std::mutex Mutex;
	};

	
	//VULCAN_ENGINE_API IRegistry<LogCategory> LogCategoryRegistry;
	extern IRegistry<LogCategory> LogCategoryRegistry;
	

	#define VLOG_BASE(cat, lvl, msg, ...) \
	VulcanEngine::LogSystem::Instance().Log( \
	fmt::format(msg, ##__VA_ARGS__), lvl, cat, __FILE__, __LINE__)

	#define VLOG_INFO(cat, msg, ...)  VLOG_BASE(cat, VulcanEngine::LogLevel::Info, msg, ##__VA_ARGS__)
	#define VLOG_WARN(cat, msg, ...)  VLOG_BASE(cat, VulcanEngine::LogLevel::Warning, msg, ##__VA_ARGS__)
	#define VLOG_ERROR(cat, msg, ...) VLOG_BASE(cat, VulcanEngine::LogLevel::Error, msg, ##__VA_ARGS__)
	#define VLOG_DEBUG(cat, msg, ...) VLOG_BASE(cat, VulcanEngine::LogLevel::Debug, msg, ##__VA_ARGS__)

	#define DECLARE_LOG_CATEGORY(name) \
	extern VulcanEngine::LogCategory& name

	#define DEFINE_LOG_CATEGORY(name) \
	VulcanEngine::LogCategory& name = \
	VulcanEngine::LogCategoryRegistry.Register( \
	std::make_unique<VulcanEngine::LogCategory>(#name))
		
	DECLARE_LOG_CATEGORY(Other);
}

