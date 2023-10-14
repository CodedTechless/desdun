

#include <glm/glm.hpp>

namespace DesdunCore
{


	using Color4 = glm::vec4;
	using Color4f = glm::f32vec4;

	class Color
	{
	public:

		static Color4f fromRGB(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);

	};

}