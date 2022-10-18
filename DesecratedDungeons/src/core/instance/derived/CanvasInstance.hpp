#pragma once

#include <core/instance/derived/WorldInstance.hpp>
#include <core/resource/external/image.h>

using namespace Desdun;

// Instance > WorldInstance > CanvasInstance

class CanvasInstance : public WorldInstance
{
public:
	CanvasInstance() = default;

	virtual void OnFrameUpdate(const float Delta) {};

	void DrawImage(ptr<Image> image, const Vector2 position, const Vector2 scale = { 1.f, 1.f }, const float orientation = 0.f, const Color4 colour = { 1.f, 1.f, 1.f, 1.f }) const
	{

	};


};