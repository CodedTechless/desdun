

#include "script_layer.hpp"

#include <objects/index.hpp>
#include <corelib/core.hpp>

namespace DesdunCore
{
	void ScriptLayer::onAwake()
	{

        environmentLibs = {
            "print", "warn", "error",
            "math", "coroutine", "string",
            "require", "assert", "tostring",
            "tonumber", "pcall",
            "table", "next", "pairs", "ipairs"
        };

        vm.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::utf8);

        dd_define(Vector2,
            sol::constructors<Vector2(), Vector2(float, float)>(),

            "x", &Vector2::x,
            "y", &Vector2::y,

            "magnitude", [](Vector2& vec) -> float
            {
                return glm::length(vec);
            },

            "abs", [](Vector2& vec) -> Vector2
            {
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A + B; },
                [](Vector2 A, float B) -> Vector2 { return A + B; },
                [](float A, Vector2 B) -> Vector2 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A - B; },
                [](Vector2 A, float B) -> Vector2 { return A - B; },
                [](float A, Vector2 B) -> Vector2 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A * B; },
                [](Vector2 A, float B) -> Vector2 { return A * B; },
                [](float A, Vector2 B) -> Vector2 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A / B; },
                [](Vector2 A, float B) -> Vector2 { return A / B; },
                [](float A, Vector2 B) -> Vector2 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector2 A) -> Vector2 { return -A; }

        );

        dd_define(Vector3,
            sol::constructors<Vector3(), Vector3(float, float, float)>(),

            "x", &Vector3::x,
            "y", &Vector3::y,
            "z", &Vector3::z,

            "magnitude", [](Vector3& vec) -> float
            {
                return glm::length(vec);
            },

            "abs", [](Vector3& vec) -> Vector3
            {
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A + B; },
                [](Vector3 A, float B) -> Vector3 { return A + B; },
                [](float A, Vector3 B) -> Vector3 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A - B; },
                [](Vector3 A, float B) -> Vector3 { return A - B; },
                [](float A, Vector3 B) -> Vector3 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A * B; },
                [](Vector3 A, float B) -> Vector3 { return A * B; },
                [](float A, Vector3 B) -> Vector3 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A / B; },
                [](Vector3 A, float B) -> Vector3 { return A / B; },
                [](float A, Vector3 B) -> Vector3 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector3 A) -> Vector3 { return -A; }
        );

        dd_define(Vector4,
            sol::constructors<Vector4(), Vector4(float, float, float, float)>(),

            "x", &Vector4::x,
            "y", &Vector4::y,
            "z", &Vector4::z,
            "w", &Vector4::w,

            "magnitude", [](Vector4& vec) -> float
            {
                return glm::length(vec);
            },

            "abs", [](Vector4& vec) -> Vector4
            {
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A + B; },
                [](Vector4 A, float B) -> Vector4 { return A + B; },
                [](float A, Vector4 B) -> Vector4 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A - B; },
                [](Vector4 A, float B) -> Vector4 { return A - B; },
                [](float A, Vector4 B) -> Vector4 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A * B; },
                [](Vector4 A, float B) -> Vector4 { return A * B; },
                [](float A, Vector4 B) -> Vector4 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A / B; },
                [](Vector4 A, float B) -> Vector4 { return A / B; },
                [](float A, Vector4 B) -> Vector4 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector4 A) -> Vector4 { return -A; }
        );

        vm.new_enum<Input::KeyCode>("KeyCode",
            {
                {"None", Input::KeyCode::None},

                {"CapsLock", Input::KeyCode::CapsLock},
                {"ScrollLock", Input::KeyCode::ScrollLock},

                {"NumLock", Input::KeyCode::NumLock},
                {"Keypad0", Input::KeyCode::Keypad0},
                {"Keypad1", Input::KeyCode::Keypad1},
                {"Keypad2", Input::KeyCode::Keypad2},
                {"Keypad3", Input::KeyCode::Keypad3},
                {"Keypad4", Input::KeyCode::Keypad4},
                {"Keypad5", Input::KeyCode::Keypad5},
                {"Keypad6", Input::KeyCode::Keypad6},
                {"Keypad7", Input::KeyCode::Keypad7},
                {"Keypad8", Input::KeyCode::Keypad8},
                {"Keypad9", Input::KeyCode::Keypad9},

                {"KeypadAdd", Input::KeyCode::KeypadAdd},
                {"KeypadEqual", Input::KeyCode::KeypadEqual},
                {"KeypadDivide", Input::KeyCode::KeypadDivide},
                {"KeypadDecimal", Input::KeyCode::KeypadDecimal},
                {"KeypadEnter", Input::KeyCode::KeypadEnter},
                {"KeypadSubtract", Input::KeyCode::KeypadSubtract},
                {"KeypadMultiply", Input::KeyCode::KeypadMultiply},

                {"Num0", Input::KeyCode::Num0},
                {"Num1", Input::KeyCode::Num1},
                {"Num2", Input::KeyCode::Num2},
                {"Num3", Input::KeyCode::Num3},
                {"Num4", Input::KeyCode::Num4},
                {"Num5", Input::KeyCode::Num5},
                {"Num6", Input::KeyCode::Num6},
                {"Num7", Input::KeyCode::Num7},
                {"Num8", Input::KeyCode::Num8},
                {"Num9", Input::KeyCode::Num9},

                {"F1", Input::KeyCode::F1},
                {"F2", Input::KeyCode::F2},
                {"F3", Input::KeyCode::F3},
                {"F4", Input::KeyCode::F4},
                {"F5", Input::KeyCode::F5},
                {"F6", Input::KeyCode::F6},
                {"F7", Input::KeyCode::F7},
                {"F8", Input::KeyCode::F8},
                {"F9", Input::KeyCode::F9},
                {"F10", Input::KeyCode::F10},
                {"F11", Input::KeyCode::F11},
                {"F12", Input::KeyCode::F12},
                {"F13", Input::KeyCode::F13},
                {"F14", Input::KeyCode::F14},
                {"F15", Input::KeyCode::F15},
                {"F16", Input::KeyCode::F16},
                {"F17", Input::KeyCode::F17},
                {"F18", Input::KeyCode::F18},
                {"F19", Input::KeyCode::F19},
                {"F20", Input::KeyCode::F20},
                {"F21", Input::KeyCode::F21},
                {"F22", Input::KeyCode::F22},
                {"F23", Input::KeyCode::F23},
                {"F24", Input::KeyCode::F24},
                {"F25", Input::KeyCode::F25},

                {"Menu", Input::KeyCode::Menu},
                {"Tab", Input::KeyCode::Tab},
                {"Home", Input::KeyCode::Home},
                {"End", Input::KeyCode::End},
                {"PrintScreen", Input::KeyCode::PrintScreen},
                {"Pause", Input::KeyCode::Pause},
                {"Backspace", Input::KeyCode::Backspace},
                {"Delete", Input::KeyCode::Delete},
                {"Escape", Input::KeyCode::Escape},

                {"Minus", Input::KeyCode::Minus},
                {"Equal", Input::KeyCode::Equal},

                {"A", Input::KeyCode::A},
                {"B", Input::KeyCode::B},
                {"C", Input::KeyCode::C},
                {"D", Input::KeyCode::D},
                {"E", Input::KeyCode::E},
                {"F", Input::KeyCode::F},
                {"G", Input::KeyCode::G},
                {"H", Input::KeyCode::H},
                {"I", Input::KeyCode::I},
                {"J", Input::KeyCode::J},
                {"K", Input::KeyCode::K},
                {"L", Input::KeyCode::L},
                {"M", Input::KeyCode::M},
                {"N", Input::KeyCode::N},
                {"O", Input::KeyCode::O},
                {"P", Input::KeyCode::P},
                {"Q", Input::KeyCode::Q},
                {"R", Input::KeyCode::R},
                {"S", Input::KeyCode::S},
                {"T", Input::KeyCode::T},
                {"U", Input::KeyCode::U},
                {"V", Input::KeyCode::V},
                {"W", Input::KeyCode::W},
                {"X", Input::KeyCode::X},
                {"Y", Input::KeyCode::Y},
                {"Z", Input::KeyCode::Z},

                {"Period", Input::KeyCode::Period},
                {"Comma", Input::KeyCode::Comma},
                {"Semicolon", Input::KeyCode::Semicolon},
                {"Apostrophe", Input::KeyCode::Apostrophe},
                {"GraveAccent", Input::KeyCode::GraveAccent},

                {"Slash", Input::KeyCode::Slash},
                {"Backslash", Input::KeyCode::Backslash},

                {"LeftAlt", Input::KeyCode::LeftAlt},
                {"LeftShift", Input::KeyCode::LeftShift},
                {"LeftSuper", Input::KeyCode::LeftSuper},
                {"LeftControl", Input::KeyCode::LeftControl},
                {"LeftBracket", Input::KeyCode::LeftBracket},

                {"RightAlt", Input::KeyCode::RightAlt},
                {"RightShift", Input::KeyCode::RightShift},
                {"RightSuper", Input::KeyCode::RightSuper},
                {"RightControl", Input::KeyCode::RightControl},
                {"RightBracket", Input::KeyCode::RightBracket},

                {"Up", Input::KeyCode::Up},
                {"Down", Input::KeyCode::Down},
                {"Left", Input::KeyCode::Left},
                {"Right", Input::KeyCode::Right},

                {"Insert", Input::KeyCode::Insert},
                {"Space", Input::KeyCode::Space},
                {"Enter", Input::KeyCode::Enter},

                {"PageUp", Input::KeyCode::PageUp},
                {"PageDown", Input::KeyCode::PageDown},

                {"World1", Input::KeyCode::World1},
                {"World2", Input::KeyCode::World2}
            });

        vm.new_enum<Input::MouseCode>("MouseCode",
            {
                { "None", Input::MouseCode::None },

                { "Button0", Input::MouseCode::Button0 },
                { "Button1", Input::MouseCode::Button1 },
                { "Button2", Input::MouseCode::Button2 },
                { "Button3", Input::MouseCode::Button3 },
                { "Button4", Input::MouseCode::Button4 },
                { "Button5", Input::MouseCode::Button5 },
                { "Button6", Input::MouseCode::Button6 },
                { "Button7", Input::MouseCode::Button7 },

                { "ButtonLeft", Input::MouseCode::ButtonLeft },
                { "ButtonRight", Input::MouseCode::ButtonRight },
                { "ButtonMiddle", Input::MouseCode::ButtonMiddle }
            });

        dd_define_type(Object,
            sol::no_constructor,
            "parent", sol::property(&Object::getParent, &Object::setParent),
            "clone", &Object::clone,
            "scene", sol::property(&Object::getScene),
            "instanceId", sol::property(&Object::getInstanceId)
        );

        dd_define_type_inheritence(Entity2D, { Runtime::get<Object>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Object>(),

            "zIndex", &Entity2D::zIndex,
            "visible", &Entity2D::visible,
            "interpolate", &Entity2D::interpolate,

            "position", sol::property(&Entity2D::getPosition, &Entity2D::setPosition),
            "scale", sol::property(&Entity2D::getScale, &Entity2D::setScale),
            "rotation", sol::property(&Entity2D::getRotation, &Entity2D::setRotation),

            "globalPosition", sol::property(&Entity2D::getGlobalPosition),
            "globalScale", sol::property(&Entity2D::getGlobalScale),
            "globalRotation", sol::property(&Entity2D::getGlobalRotation),

            "translate", &Entity2D::translate,
            "resize", &Entity2D::resize,
            "rotate", &Entity2D::rotate
        );

        // todo: figure out a way to get these values into the inspector
        // for now we can just pull it through lua but that'd be inefficient due to marshalling
        dd_define_type_inheritence(Camera2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>(),

            "subject", &Camera2D::subject,
            "offset", &Camera2D::offset,

            "targetViewportSize", &Camera2D::targetViewportSize,
            "smoothFollow", &Camera2D::smoothFollow,
            "adjustToAspectRatio", &Camera2D::adjustToAspectRatio,

            "getMouseInWorld", &Camera2D::getMouseInWorld
        );

        dd_define_type_inheritence(Script, { Runtime::get<Object>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Object>()
        );

        dd_define_type_inheritence(SoundEmitter2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(ParticleEmitter2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(Sprite, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(AnimatedSprite, { Runtime::get<Sprite>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Sprite>()
        );

        dd_define_type_inheritence(TileMap, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );
	}
}