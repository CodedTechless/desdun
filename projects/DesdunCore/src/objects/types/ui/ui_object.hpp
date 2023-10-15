#pragma once

#include <objects/object.hpp>

namespace DesdunCore
{

	template<typename T = float>
	struct UDim
	{
		T scale = 0.f;
		T offset = 0.f;
	};

	template<typename T = float>
	struct UDim2
	{
		UDim<T> x = {};
		UDim<T> y = {};
	};

	using UDim2f = UDim2<float>;

	class UIObject : public Object
	{
	public:
		serialisable(UIObject);

		UDim2f position = {};
		UDim2f scale = { { 0.f, 40.f }, { 0.f, 40.f } };

		Vector2f anchor = { 0.f, 0.f };

	};

}