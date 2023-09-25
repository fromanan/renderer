#pragma once

#include "ShaderHeaders.h"

#include "Quaternion.h"

namespace Renderer
{
    struct Transform
    {
        mat4 Position;
        mat4 Rotation;

        Transform() : Position(Quaternion::Identity), Rotation(Quaternion::Identity) {}
        
        explicit Transform(const vec3& position)
            : Position(translate(Quaternion::Identity, position)), Rotation(Quaternion::Identity) {}
        
        Transform(const mat4& position, const mat4& rotation)
            : Position(position), Rotation(rotation) {}
        
        Transform(const vec3& position, const vec3& rotation, const float angle)
            : Position(translate(Quaternion::Identity, position)),
              Rotation(rotate(Quaternion::Identity, angle, rotation)) {}
    };
}
