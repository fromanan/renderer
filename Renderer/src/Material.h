#pragma once

namespace Renderer
{
    struct Material
    {
        glm::vec4 Ambient;
        glm::vec4 Diffuse;
        glm::vec4 Specular;
        float Shininess;
    };
}