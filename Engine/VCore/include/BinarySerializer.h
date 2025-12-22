#pragma once
#include <cstdint>


namespace VulcanCore {
	
	class BinarySerializer {
	public:
		template<typename T>
		static void Serialize(std::vector<uint8_t>& byteArray, T value) {
			size_t offset = byteArray.size();
			byteArray.resize(offset + sizeof(value));
			memcpy(&byteArray[offset], &value, sizeof(value));
		}

		template<>
		static void Serialize(std::vector<uint8_t>& byteArray, std::string value) {
			Serialize(byteArray, static_cast<uint8_t>(value.size()));

			size_t offset = byteArray.size();
			byteArray.resize(offset + value.size());
			memcpy(&byteArray[offset], &value[0], value.size());
		}

		template<typename T>
		static T Unserialize(const std::vector<uint8_t>& byteArray,size_t& offset) {
			if (offset + sizeof(T) > byteArray.size()) {
				throw std::runtime_error("Unserialize: Out of bounds");
			}

			T value;
			memcpy(&value, &byteArray[offset], sizeof(T));
			offset += sizeof(T);

			return value;
		}

		template<>
		static std::string Unserialize(const std::vector<uint8_t>& byteArray, size_t& offset) {
			uint8_t size = Unserialize<uint8_t>(byteArray, offset);

			if (offset + size > byteArray.size()) {
				throw std::runtime_error("Unserialize: Out of bounds");
			}

			std::string value(reinterpret_cast<const char*>(&byteArray[offset]), size);
			offset += size;

			return value;
		}
		
	};


}
