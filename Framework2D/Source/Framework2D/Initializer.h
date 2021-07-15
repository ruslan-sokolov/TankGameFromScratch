#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	class FRAMEWORK2D_API Initializer
	{
		bool bIsGlewInitialized;

	public:
		Initializer();
		virtual ~Initializer();

		virtual void Init();
	};

	Initializer* CreateInitializer();
}