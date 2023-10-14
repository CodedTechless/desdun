

#include "runtime.hpp"

namespace DesdunCore
{

	Map<Type, BaseRuntimeClass*> Runtime::types = {};
	Map<String, BaseRuntimeClass*> Runtime::typeNames = {};

}