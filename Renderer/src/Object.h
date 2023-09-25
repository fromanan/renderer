#pragma once

#include "ShaderHeaders.h"

#include "Mesh.h"
#include "Transform.h"
#include "Material.h"

#include "graphics/GrTexture.h"

struct Object
{
    std::shared_ptr<Drawable> Mesh;
    Renderer::Transform Transform;
    std::string MapName;
    std::shared_ptr<CGrTexture> Texture = nullptr;
    std::shared_ptr<Renderer::Material> Material = nullptr;

    Object(std::shared_ptr<Drawable> mesh,
           Renderer::Transform transform,
           std::string mapName,
           const std::string& textureFilename = "",
           std::shared_ptr<Renderer::Material> material = nullptr)
    : Mesh(std::move(mesh)), Transform(std::move(transform)), MapName(std::move(mapName))
    {
        if (!textureFilename.empty())
        {
            Texture = std::make_shared<CGrTexture>();
            Texture->LoadFile(CA2T(textureFilename.c_str()));
        }

        if (material != nullptr)
        {
            Material = std::move(material);
        }
    }

    Object(std::shared_ptr<Drawable> mesh,
               Renderer::Transform transform,
               std::string mapName,
               std::shared_ptr<CGrTexture> texture,
               std::shared_ptr<Renderer::Material> material = nullptr)
    : Mesh(std::move(mesh)), Transform(std::move(transform)), MapName(std::move(mapName)), Texture(std::move(texture))
    {
        if (material != nullptr)
        {
            Material = std::move(material);
        }
    }
};
