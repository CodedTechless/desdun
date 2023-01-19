

#include "layer_collection.h"

namespace Desdun {

	LayerCollection::~LayerCollection()
	{
		for (auto& Layer : Layers) 
		{
			Layer->OnDestroyed();
			delete Layer;
		}
	}

	void LayerCollection::PushLayer(Layer* Layer)
	{
		Layers.emplace(Layers.begin() + LayerInsertIndex, Layer);
		LayerInsertIndex++;

		Layer->OnAwake();
	}

	void LayerCollection::PopLayer(Layer* Layer)
	{
		auto Loc = Layers.begin() + LayerInsertIndex;

		auto Iterator = std::find(Layers.begin(), Loc, Layer);
		if (Iterator != Loc) 
		{
			Layer->OnDestroyed();
			Layers.erase(Iterator);

			LayerInsertIndex--;
		}
	}

	void LayerCollection::PushOverlay(Layer* Overlay)
	{
		Layers.emplace_back(Overlay);
		Overlay->OnAwake();
	}

	void LayerCollection::PopOverlay(Layer* Overlay)
	{
		auto Loc = Layers.begin() + LayerInsertIndex;

		auto Iterator = std::find(Loc, Layers.end(), Overlay);
		if (Iterator != Layers.end()) 
		{
			Overlay->OnDestroyed();
			Layers.erase(Iterator);
		}
	}
}