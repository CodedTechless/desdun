#pragma once

#include <runtime/layer/layer.hpp>

#define dd_define(object, ...) vm.new_usertype<object>(#object, __VA_ARGS__)
#define dd_define_type(object, ...) Runtime::add<object>({ #object }); vm.new_usertype<object>(#object, __VA_ARGS__)
#define dd_define_type_inheritence(object, inheritence, ...) Runtime::add<object>({ #object, inheritence }); vm.new_usertype<object>(#object, __VA_ARGS__)

namespace DesdunCore
{

	class ScriptLayer : public Layer
	{
	public:

		void onAwake() override;

	private:
		sol::state vm = {};
		List<String> environmentLibs;

	};

}