

#include "layer_collection.hpp"

namespace DesdunCore {

	LayerCollection::~LayerCollection()
	{
		clear();
	}

	void LayerCollection::clear()
	{
		for (auto* layer : layers)
		{
			layer->onDestroyed();
			delete layer;
		}

		layers.clear();
	}

	void LayerCollection::pushLayer(Layer* Layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, Layer);
		layerInsertIndex++;

		Layer->onAwake();
	}

	void LayerCollection::popLayer(Layer* layer)
	{
		auto location = layers.begin() + layerInsertIndex;

		auto it = std::find(layers.begin(), location, layer);
		if (it != location)
		{
			layer->onDestroyed();
			layers.erase(it);

			layerInsertIndex--;
		}
	}

	void LayerCollection::pushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->onAwake();
	}

	void LayerCollection::popOverlay(Layer* overlay)
	{
		auto location = layers.begin() + layerInsertIndex;

		auto Iterator = std::find(location, layers.end(), overlay);
		if (Iterator != layers.end())
		{
			overlay->onDestroyed();
			layers.erase(Iterator);
		}
	}
}