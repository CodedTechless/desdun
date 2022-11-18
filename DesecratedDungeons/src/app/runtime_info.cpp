

#include "runtime_info.h"

namespace Desdun
{

	std::unordered_map<std::type_index, std::string> RuntimeInfo::Types = {};
	std::unordered_map<std::string, std::function<Instance* ()>> RuntimeInfo::Constructors = {};

}