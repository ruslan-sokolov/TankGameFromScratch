#pragma once

#ifdef ENGINE_WIN_PLATFORM
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define	ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Engine only support Windows Platform!
#endif