
#include "desdun_core.hpp"

namespace glm
{
    void to_json(json& jsonObject, const glm::vec2& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y }
        };
    };

    void to_json(json& jsonObject, const glm::vec3& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y },
            { "z", vec.z }
        };
    };

    void to_json(json& jsonObject, const glm::vec4& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y },
            { "z", vec.z },
            { "w", vec.w }
        };
    };

    void from_json(const json& j, glm::vec2& vec)
    {
        vec = glm::vec2(
            j.at("x").get<float>(),
            j.at("y").get<float>()
        );
    };

    void from_json(const json& j, glm::vec3& vec)
    {
        vec = glm::vec3(
            j.at("x").get<float>(),
            j.at("y").get<float>(),
            j.at("z").get<float>()
        );
    };

    void from_json(const json& j, glm::vec4& vec)
    {
        vec = glm::vec4(
            j.at("x").get<float>(),
            j.at("y").get<float>(),
            j.at("z").get<float>(),
            j.at("w").get<float>()
        );
    };
}