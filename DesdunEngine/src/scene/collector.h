
#include <core_lib.hpp>
#include <app/runtime.h>

namespace Desdun
{

	class Collection
	{
	public:




	private:

		std::array<RuntimeObject*, MAX_INSTANCES>
	};

	class Collector
	{
	public:

		void addToGroup(RuntimeObject* object, const std::string& name);

	private:

		std::unordered_map<std::string, Collection>

	};

}