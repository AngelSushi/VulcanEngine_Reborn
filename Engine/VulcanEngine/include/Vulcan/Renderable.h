#pragma once
#include <Export.h>
#include <CoreAPI/VRenderer.h>

#include <MatrixFloat.h>

namespace VulcanEngine {

	
	class VULCAN_ENGINE_API Renderable {

		
	public:
		Renderable() = default;
		virtual ~Renderable() = default;

		virtual void Draw(Graphics::VRenderer& Renderer, const VMath::MatrixFloat& Matrix,const float Color[4]) const = 0;

		virtual SDL_Rect GetBounds() const = 0;
	};
}


