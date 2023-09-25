#pragma once

#include "ShaderWnd.h"

#include "Sphere.h"
#include "Torus.h"
#include "Mesh.h"

class MeshFactory
{
public:
    static std::shared_ptr<CMesh> CreateCube(CShaderWnd* window, const std::string& vertexShader, const std::string& fragmentShader)
    {
        auto cube = std::make_shared<CMesh>();
        cube->CreateCube();
        cube->m_program = window->LoadShaders(vertexShader, fragmentShader);
        return cube;
    }
    
    static std::shared_ptr<CMesh> CreateMesh(CShaderWnd* window, const std::string& vertexShader, const std::string& fragmentShader, const std::string& filename)
    {
        auto mesh = std::make_shared<CMesh>();
        mesh->LoadOBJ(filename.c_str());
        mesh->m_program = window->LoadShaders(vertexShader, fragmentShader);
        return mesh;
    }
    
    static std::shared_ptr<CSphere> CreateSphere(CShaderWnd* window, const std::string& vertexShader, const std::string& fragmentShader, const float radius)
    {
        auto sphere =  std::make_shared<CSphere>();
        sphere->SetRadius(radius);
        sphere->m_program = window->LoadShaders(vertexShader, fragmentShader);
        return sphere;
    }
    
    static std::shared_ptr<CTorus> CreateTorus(CShaderWnd* window, const std::string& vertexShader, const std::string& fragmentShader, const float radius1, const float radius2)
    {
        auto torus =  std::make_shared<CTorus>();
        //cube.SetR1(3);
        //cube.SetR2(3);
        torus->m_program = window->LoadShaders(vertexShader, fragmentShader);
        return torus;
    }
};
