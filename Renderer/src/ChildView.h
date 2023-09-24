//
// ChildView.h : interface of the CChildView class
//

#pragma once

#include "ShaderWnd.h"

#include "Mesh.h"
#include "Primitives/Sphere.h"
#include "Primitives/Torus.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCubeTexture.h"

// CChildView window

class CChildView : public CShaderWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void RenderGL();
	virtual void InitGL();
	virtual void CleanGL();

private:
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

