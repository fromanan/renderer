#pragma once

#include "ShaderWnd.h"

class CMesh
{
public:
    CMesh();
    virtual ~CMesh();

    void InitGL();
    void RenderGL() const;
    void CleanGL();

    GLuint m_program;
    GLuint m_vao;
    GLuint m_vertexVBO;
    GLuint m_normalVBO;
    GLuint m_texVBO;

    void AddVertex(const vec3& v) { m_vertices.push_back(v); }
    void AddNormal(const vec3& n) { m_normals.push_back(n); }
    void AddTexCoord(const vec2& t) { m_tVertices.push_back(t); }
    void AddTriangleVertex(int v, int n, int t);

private:
    std::vector<vec3> m_vertices;
    std::vector<vec3> m_normals;
    std::vector<vec2> m_tVertices;

    std::vector<vec3> vertexArray;
    std::vector<vec3> normalArray;
    std::vector<vec2> texArray;

    // A triangle vertex description
    struct TV
    {
        int v; // Vertex
        int n; // Normal
        int t; // Texture coordinate
    };

    typedef std::vector<TV> Triangles;
    typedef Triangles::iterator PTV;
    Triangles m_triangles;

public:
    void AddFlatQuad(int a, int b, int c, int d, int n);
    void AddQuad(int a, int b, int c, int d);
    void ComputeSmoothNormals();
    void LoadOBJ(const char* filename);
    void CreateCube();
};
