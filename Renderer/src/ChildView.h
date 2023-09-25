//
// ChildView.h : interface of the CChildView class
//

#pragma once

#include "ShaderWnd.h"

#include "Mesh.h"
#include "Sphere.h"
#include "Torus.h"
#include "GrTexture.h"
#include "GrCubeTexture.h"

// CChildView window

class CChildView final : public CShaderWnd
{
// Construction
public:
	CChildView();

// Overrides
protected:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;

// Implementation
public:
	~CChildView() override;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	void RenderGL() override;
	void InitGL() override;
	void CleanGL() override;
private:
	GLuint m_program;
	CGrTexture m_bunnyTex;
	CGrTexture m_fishTex;
	CGrTexture m_sphereTex;
	CGrTexture m_torusTex;
	CGrCubeTexture m_cubeTex;
	CMesh m_bunny;
	CMesh m_fish;
	CSphere m_sphere;
	CSphere m_metallicSphere;
	CTorus m_torus;
	CMesh m_skybox;
};

