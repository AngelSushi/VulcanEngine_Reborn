#pragma once
#include <iostream>
#include <mutex>
#include <streambuf>
#include <string>

#include "LogSystem.h"

namespace VulcanEngine {
	
	class LogRedirectBuffer : public std::streambuf {
	public:
		LogRedirectBuffer(LogLevel InLvl) : Level(InLvl) {}

	protected:
		int overflow(int c) override {
			if (c == '\n') {
				Flush();
			}
			else if (c != EOF) {
				Buffer += static_cast<char>(c);
			}

			return c;
		}

		void Flush() {
			if (!Buffer.empty()) {
				LogSystem::Instance().Log(Buffer,Level, Other, "", 0);
				Buffer.clear();
			}
		}
	private:
		std::string Buffer{};
		LogLevel Level{};
	};

	inline void RedirectLogSystem() {
		static LogRedirectBuffer coutBuffer(LogLevel::Info);
		static LogRedirectBuffer cerrBuffer(LogLevel::Error);

		std::cout.rdbuf(&coutBuffer);
		std::cerr.rdbuf(&cerrBuffer);
	}
}

