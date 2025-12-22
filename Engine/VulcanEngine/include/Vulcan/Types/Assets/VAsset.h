#pragma once
#include <nlohmann/json.hpp>
#include <Export.h>
#include <random>
#include "Reflection/VMacros.h"
#include "Reflection/VObject.h"
#include "CoreAPI/VSurface.h"
#include <VAsset.vht.h>

namespace VulcanEngine {

	VCLASS()
	class VULCAN_ENGINE_API VAsset : public VulcanCore::VObject {

		VCLASS_BODY()
		
	public:
		//virtual VAsset(const VAsset&) = delete;
		//VAsset(VAsset&&) noexcept;
		~VAsset() = default;

		//virtual VAsset& operator=(const VAsset&);
	//	VAsset& operator=(VAsset&& Asset) noexcept;

		static std::string GenerateGUID() {
			static std::random_device rd;
			static std::mt19937_64 gen(rd());

			uint64_t part1 = gen();
			uint64_t part2 = gen();

			std::stringstream ss;
			ss << std::hex << std::setfill('0') << std::setw(16) << part1 << std::setw(16) << part2;
			return ss.str();
		}

		static std::vector<std::string> GetAvailableExtensions();
		
		virtual void ConstructJSON(const std::string_view& InPath) {}
		virtual void ConstructBinary(const std::vector<uint8_t>& Buffer) {}
		
		virtual std::string ToJson() const { return "";}

		const std::string& GetFilePath() const { return FilePath; }
		const std::string& GetName() const { return AssetName; }
		const std::string& GetGUID() const { return GUID; }

		void SetName(const std::string_view& Name) {
			AssetName = Name;
		}

		void SetFilePath(const std::string_view& Path) {
			FilePath = Path;
		}

	protected:
		VAsset() = default;
		
		explicit VAsset(std::string FilePath);
		explicit VAsset(std::string FilePath,std::string Name);

		std::string GUID;
		std::string AssetName;
		std::string FilePath;
		nlohmann::json Description{};
	};
}

