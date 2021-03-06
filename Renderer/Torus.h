#pragma once
#include "ShaderWnd\ShaderWnd.h"
#include "gl/gl.h"
#include "graphics/GrTexture.h"

//! This class allows you to draw a torus

class CTorus
{
public:
    CTorus(void);
    virtual ~CTorus(void);

    //! Set the large radius of the torus
    /*! This is the radius of the entire torus. The
        default is 5cm.
        \param r Radius in cm */
    void SetR1(double r) {m_r1 = r;}

    //! Gets the large radus of the torus
    double GetR1() const {return m_r1;}

    //! Set the small radius of the torus
    /*! This is the radius of a cross section of the torus.
        The default is 1cm.
        \param r Radius in cm */
    void SetR2(double r) {m_r2 = r;}
    double GetR2() const {return m_r2;}

    //! Set the number of steps around the large radius.
    /*! This is the number of tessellation steps around the 
        large radius of the torus. The default is 50.
        \param s Number of steps */
    void SetSteps1(double s) {m_steps1 = s;}

    //! Get the number of steps around the large radius.
    double GetSteps1() const {return m_steps1;}

    //! Set the number of steps around the small radius.
    /*! This is the number of tessellation steps around the 
        small radius (cross section) of the torus. The default is 20.
        \param s Number of steps */
    void SetSteps2(double s) {m_steps2 = s;}

    //! Get the number of steps around the small radius.
    double GetSteps2() const {return m_steps2;}

    //! Draw the torus
    void Draw();


    /// Shader-based OpenGL Properties

    void InitGL();
    void RenderGL();
    void CleanGL();

public:
    void SetTexture(CGrTexture* texture) { m_texture = texture; }
    CGrTexture* GetTexture() { return m_texture; }

    GLuint m_program;
    GLuint m_vao;
    GLuint m_vertexVBO;
    GLuint m_normalVBO;
    GLuint m_texVBO;

private:
    CGrTexture* m_texture;  // Texture to use for the sphere

    std::vector<glm::vec3> vertexArray;
    std::vector<glm::vec3> normalArray;
    std::vector<glm::vec2> texArray;

private:
    void TorusVertex(double a1, double r1, double a2, double r2);
                         
    //! Large radius of the torus
    //! This is the radius of the entire torus
    double  m_r1;

    //! Small radius of the torus
    //! This is the radius of a cross section of the torus
    double  m_r2;

    //! Number of steps in the large radius
    double  m_steps1;

    //! Number of steps in the small radius
    double  m_steps2;
};

