#include "pch.h"

#include "Torus.h"

CTorus::CTorus()
{
    //
    // Default values
    //

    // Large radius of the torus
    // This is the radius of the entire torus
    m_r1 = 5;

    // Small radius of the torus
    // This is the radius of a cross section of the torus
    m_r2 = 1;

    // Number of steps in the large radius
    m_steps1 = 50;

    // Number of steps in the small radius
    m_steps2 = 20;
}

CTorus::~CTorus() = default;

void CTorus::InitGL()
{
    Draw();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(vec3),
                 vertexArray.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normalArray.size() * sizeof(vec3),
                 normalArray.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_texVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_texVBO);
    glBufferData(GL_ARRAY_BUFFER, texArray.size() * sizeof(vec2),
                 texArray.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

//
// Name :         CChildView::Draw()
// Description :  Render a Torus of large radius m_r1 and small radius m_r2
//                m_steps1 is the number of steps we do for the large
//                radius and m_steps2 is the number of steps for the
//                small radius.  There will be m_steps1 * m_steps2 
//                quadrilaterals in the torus.
//
void CTorus::Draw()
{
    // How large are the angular steps in radians
    const double step1r = M_TAU / m_steps1;
    const double step2r = M_TAU / m_steps2;

    // We build the torus in slices that go from a1a to a1b
    double a1a = 0;
    double a1b = step1r;

    for (int s = 0; s < m_steps1; s++, a1a = a1b, a1b += step1r)
    {
        // We build a slice out of quadrilaterals that range from 
        // angles a2a to a2b.

        double a2a = 0;
        double a2b = step2r;

        for (int s2 = 0; s2 < m_steps2; s2++, a2a = a2b, a2b += step2r)
        {
            TorusVertex(a1a, m_r1, a2a, m_r2);
            TorusVertex(a1b, m_r1, a2a, m_r2);
            TorusVertex(a1b, m_r1, a2b, m_r2);

            TorusVertex(a1a, m_r1, a2a, m_r2);
            TorusVertex(a1b, m_r1, a2b, m_r2);
            TorusVertex(a1a, m_r1, a2b, m_r2);
        }
    }
}

//
// Name :         CTorus::TorusVertex()
// Description :  Compute the x,y,z coordinates and surface normal for a 
//                torus vertex.  
// Parameters :   a1 - The angle relative to the center of the torus
//                r1 - Radius of the entire torus
//                a2 - The angle relative to the center of the torus slice
//                r2 - Radius of the torus ring cross-section
//                v - Returns vertex
//                n - Returns surface normal
//
void CTorus::TorusVertex(double a1, double r1, double a2, double r2)
{
    double n[3], v[3];

    // Some sines and cosines we'll need.
    const double ca1 = cos(a1);
    const double sa1 = sin(a1);
    const double ca2 = cos(a2);
    const double sa2 = sin(a2);

    // What is the center of the slice we are on.
    const double centerx = r1 * ca1;
    const double centerz = -r1 * sa1; // Note, y is zero

    // Compute the surface normal
    n[0] = ca2 * ca1; // x
    n[1] = sa2; // y
    n[2] = -ca2 * sa1; // z

    // And the vertex
    v[0] = centerx + r2 * n[0];
    v[1] = r2 * n[1];
    v[2] = centerz + r2 * n[2];

    // Calculate the Texture Coordinates
    const double tx = 10. * a1 / M_TAU;
    const double ty = 2. * a2 / M_TAU;

    // Push the Points to the Arrays
    texArray.emplace_back(tx, ty);
    vertexArray.emplace_back(v[0], v[1], v[2]);
    normalArray.emplace_back(n[0], n[1], n[2]);
}

void CTorus::RenderGL()
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertexArray.size()));
}