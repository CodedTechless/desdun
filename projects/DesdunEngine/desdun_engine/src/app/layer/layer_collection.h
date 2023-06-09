#pragma once

#include <desdun_engine/include/desdun_core.hpp>

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

		void clear();

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