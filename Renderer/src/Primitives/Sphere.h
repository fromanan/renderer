#pragma once

#include "ShaderHeaders.h"

#include "Drawawble.h"
#include "graphics/GrTexture.h"

class CSphere : public Drawable
{
public:
    CSphere();
    ~CSphere();

    void SetRadius(double r) {m_radius = r;}

private:
    void SphereFace(int p_recurse, double p_radius, double *a,
                            double *b, double *c);

    double m_radius;
	
public:
	GLuint m_vao;
	GLuint m_vertexVBO;
	GLuint m_normalVBO;
	GLuint m_texVBO;

	void InitGL() override;
	void RenderGL() override;
private:
	std::vector<vec3> vertexArray;
	std::vector<vec3> normalArray;
	std::vector<vec2> texArray;
};

