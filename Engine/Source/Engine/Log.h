#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Engine
{
	class ENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;

	};
}


#define LOG_ERR   error
#define LOG_WARN  warn
#define LOG_TRACE trace
#define LOG_INFO  info
#define LOG_FATAL fatal

#define ENGINE_LOG(type, ...) ::Engine::Log::GetCoreLogger()->type(__VA_ARGS__)
#define APP_LOG(type, ...)    ::Engine::Log::GetCoreLogger()->type(__VA_ARGS__)