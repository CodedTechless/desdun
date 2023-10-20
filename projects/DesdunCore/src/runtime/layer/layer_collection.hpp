#pragma once

#include <corelib/core.hpp>

#include "layer.hpp"

namespace DesdunCore 
{


	class LayerCollection 
	{
	public:
		LayerCollection() = default;
		~LayerCollection();

		void pushLayer(Layer* Layer);
		void pushOverlay(Layer* Overlay);
		void popLayer(Layer* Layer);
		void popOverlay(Layer* Overlay);

		void clear();

		List<Layer*>::iterator begin() { return layers.begin(); };
		List<Layer*>::iterator end() { return layers.end(); };

		List<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); };
		List<Layer*>::reverse_iterator rend() { return layers.rend(); };

	private:
		List<Layer*> layers = {};

		uint layerInsertIndex = 0; // this is the index that layers will be inserted

		friend class Core;
	};
}