

#include "layer_collection.h"

namespace Desdun {

	LayerCollection::~LayerCollection()
	{
		clear();
	}

	void LayerCollection::clear()
	{
		for (auto* Layer : Layers)
		{
			Layer->onDestroyed();
			delete Layer;
		}

		Layers.clear();
	}

	void LayerCollection::PushLayer(Layer* Layer)
	{
		Layers.emplace(Layers.begin() + LayerInsertIndex, Layer);
		LayerInsertIndex++;

		Layer->onAwake();
	}

	void LayerCollection::PopLayer(Layer* Layer)
	{
		auto Loc = Layers.begin() + LayerInsertIndex;

		auto Iterator = std::find(Layers.begin(), Loc, Layer);
		if (Iterator != Loc) 
		{
			Layer->onDestroyed();
			Layers.erase(Iterator);

			LayerInsertIndex--;
		}
	}

	void LayerCollection::PushOverlay(Layer* Overlay)
	{
		Layers.emplace_back(Overlay);
		Overlay->onAwake();
	}

	void LayerCollection::PopOverlay(Layer* Overlay)
	{
		auto Loc = Layers.begin() + LayerInsertIndex;

		auto Iterator = std::find(Loc, Layers.end(), Overlay);
		if (Iterator != Layers.end()) 
		{
			Overlay->onDestroyed();
			Layers.erase(Iterator);
		}
	}
}