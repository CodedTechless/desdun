#pragma once

#include "../resource.hpp"


namespace DesdunCore
{

	class Script : public Resource
	{
	public:


	protected:
		void load() override;
		void unload() override;

	};

}