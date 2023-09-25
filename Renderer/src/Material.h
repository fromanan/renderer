#pragma once

#include "ShaderHeaders.h"

namespace Renderer
{
    struct Material
    {
        vec4 Ambient;
        vec4 Diffuse;
        vec4 Specular;
        float Shininess;
    };
}