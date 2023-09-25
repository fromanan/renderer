#pragma once

#include "GrTexture.h"

using namespace glm;

class Drawable
{
public:
    virtual void InitGL() = 0;
    virtual void RenderGL() = 0;
    virtual void CleanGL() { }

    virtual void SetTexture(CGrTexture *texture) { m_texture = texture; }
    virtual CGrTexture *GetTexture() { return m_texture; }
    CGrTexture *m_texture;  // Texture to use for the sphere

    virtual GLuint GetProgram() { return m_program; }
    GLuint m_program;
};
