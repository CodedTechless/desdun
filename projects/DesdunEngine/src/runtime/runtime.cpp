

#include "runtime.h"

namespace Desdun
{

	Map<Type, BaseRuntimeClass*> Runtime::types = {};
	Map<String, BaseRuntimeClass*> Runtime::typeNames = {};

}