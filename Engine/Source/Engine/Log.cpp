#include "Log.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Log::CoreLogger;
	std::shared_ptr<spdlog::logger> Log::ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		CoreLogger = spdlog::stdout_color_mt("Engine");
		CoreLogger->set_level(spdlog::level::trace);
		ClientLogger = spdlog::stdout_color_mt("App");
		CoreLogger->set_level(spdlog::level::trace);
	}
}

