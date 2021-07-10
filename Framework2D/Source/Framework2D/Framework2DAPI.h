#pragma once

#ifdef ENGINE_WIN_PLATFORM
	#ifdef FRAMEWORK_BUILD_DLL
		#define FRAMEWORK2D_API __declspec(dllexport)
	#else
		#define	FRAMEWORK2D_API __declspec(dllimport)
	#endif
#else
	#error Engine only support Windows Platform!
#endif