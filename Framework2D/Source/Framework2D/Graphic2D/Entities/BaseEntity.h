#pragma once

#include <Framework2D/Framework2DAPI.h>
#include "Engine.h"

#include <Framework2D/Structs/Vectors.h>

namespace Framework2D {

	class Group;

	class FRAMEWORK2D_API BaseEntity
	{
		friend class Group;
	
	protected:
		Group* EntityGroup;
		const std::string Name;

		BaseEntity(const std::string& Name, VecInt2D Size = VecInt2D::VecZero, VecInt2D Position = VecInt2D::VecZero, bool bRenderEnable = false) 
			: Name(Name), Size(Size), Position(Position), bRenderEnabled(bRenderEnable), EntityGroup(nullptr) {}
		virtual ~BaseEntity();

		VecInt2D Size;
		VecInt2D Position;
		bool bRenderEnabled;

	public:
		inline Group* GetGroup() const { return EntityGroup; }
		inline bool HasGroup() const { return EntityGroup != nullptr; }
		inline std::string GetName() const { return Name; }

		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void OnEvent(Engine::Event& e) = 0;

		inline VecInt2D GetSize() const { return Size; }
		inline VecInt2D GetPosition() const { return Position; }
		inline void SetSize(VecInt2D& Size) { this->Size = Size; }
		inline void SetPosition(VecInt2D& Position) { this->Position = Position; }
		
		inline void SetEnableRender(bool bEnable) { bRenderEnabled = bEnable; }
		inline bool IsRenderEnabled() const { return bRenderEnabled;}
	};
}