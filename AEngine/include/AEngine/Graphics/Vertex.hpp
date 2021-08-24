#ifndef AE_VERTEX_HPP
#define AE_VERTEX_HPP

#include "AE_API.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace aengine
{
    struct AE_API Vertex
    {
        glm::vec3   Position;
        glm::vec4   Color;
        glm::vec2   TexCoord;
        float       TexIndex;
    };
}

#endif
