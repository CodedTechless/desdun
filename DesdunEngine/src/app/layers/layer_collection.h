#pragma once

#include <core_lib.hpp>

#include "layer.h"

namespace Desdun {
	class LayerCollection {
	public:
		LayerCollection() = default;
		~LayerCollection();

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);
		void PopLayer(Layer* Layer);
		void PopOverlay(Layer* Overlay);

		std::vector<Layer*>::iterator begin() { return Layers.begin(); };
		std::vector<Layer*>::iterator end() { return Layers.end(); };

		std::vector<Layer*>::reverse_iterator rbegin() { return Layers.rbegin(); };
		std::vector<Layer*>::reverse_iterator rend() { return Layers.rend(); };
	private:
		std::vector<Layer*> Layers;
		unsigned short int LayerInsertIndex = 0; // this is the index that layers will be inserted

		friend class Core;
	};
}