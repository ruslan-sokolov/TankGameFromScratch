// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


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

#define BIT(x) (1 << x)