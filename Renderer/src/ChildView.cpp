//
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Renderer.h"
#include "ChildView.h"

// CChildView

CChildView::CChildView() = default;

CChildView::~CChildView() = default;

BEGIN_MESSAGE_MAP(CChildView, CShaderWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CShaderWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::InitGL()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Load the Skybox
	m_cubeTex.LoadFiles(L"textures/right.jpg", L"textures/left.jpg", L"textures/top.jpg",
		L"textures/bottom.jpg", L"textures/front.jpg", L"textures/back.jpg");
	m_skybox.CreateCube();
	m_skybox.m_program = LoadShaders("shaders/vertexSky.glsl", "shaders/fragmentSky.glsl");
	m_skybox.InitGL();

	// Load the Bunny
	m_bunnyTex.LoadFile(L"models/bunny-atlas.jpg");
	m_bunny.LoadOBJ("models/bunny.obj");
	m_bunny.m_program = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	m_bunny.InitGL();

	// Load the Fish
	m_fishTex.LoadFile(L"models/BLUEGILL.bmp");
	m_fish.LoadOBJ("models/fish4.obj");
	m_fish.m_program = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	m_fish.InitGL();

	// Regular Sphere
	m_sphereTex.LoadFile(L"textures/bumpmap.jpg");
	m_sphere.SetRadius(3);
	m_sphere.m_program = LoadShaders("shaders/vertexSphere.glsl", "shaders/fragmentSphere.glsl");
	m_sphere.InitGL();

	// Metallic Sphere
	m_metallicSphere.SetRadius(3);
	m_metallicSphere.m_program = LoadShaders("shaders/vertexSphere2.glsl", "shaders/fragmentSphere2.glsl");
	m_metallicSphere.InitGL();

	// Torus
	//m_torus.SetR1(3);
	//m_torus.SetR2(3);
	m_torus.m_program = LoadShaders("shaders/vertexSphere2.glsl", "shaders/fragmentSphere2.glsl");
	m_torus.InitGL();
}

void CChildView::RenderGL()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Bunny
	m_program = m_bunny.m_program;
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "diffuse_mat"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mPVM");
	m_nVM = glGetUniformLocation(m_program, "mVM");

	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(m_mPVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(m_mVM));

	vec4 light_position(-5.f, 5.f, -5.f, 0.f);
	vec4 light_ambient(0.2f, 0.2f, 0.2f, 1.f);
	vec4 light_diffuse(1.f, 1.f, 1.f, 1.f);
	vec4 light_specular(1.f, 1.f, 1.f, 1.f);

	vec4 material_ambient(1.f, 1.f, 1.f, 1.f);
	vec4 material_diffuse(1.f, 1.f, 1.f, 1.f);
	vec4 material_specular(1.f, 1.f, 1.f, 1.f);
	float material_shininess = 100.0f;

	vec4 ambient_product = light_ambient * material_ambient;
	vec4 diffuse_product = light_diffuse * material_diffuse;
	vec4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(m_program, "AmbientProduct"), 1, value_ptr(ambient_product));
	glUniform4fv(glGetUniformLocation(m_program, "DiffuseProduct"), 1, value_ptr(diffuse_product));
	glUniform4fv(glGetUniformLocation(m_program, "SpecularProduct"), 1, value_ptr(specular_product));
	glUniform4fv(glGetUniformLocation(m_program, "LightPosition"), 1, value_ptr(light_position));
	glUniform1f(glGetUniformLocation(m_program, "Shininess"), material_shininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_bunnyTex.TexName());

	m_bunny.RenderGL();

	// Render the Fish
	m_program = m_fish.m_program;
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "diffuse_mat"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mPVM");
	m_nVM = glGetUniformLocation(m_program, "mVM");

	mat4 M = translate(mat4(1.f), vec3(0., 0., 10.))
		* rotate(mat4(1.f), -90.f, vec3(1., 0., 0.));
	mat4 VM = m_mVM * M;
	mat4 PVM = m_mPVM * M;

	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(PVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(VM));

	glUniform4fv(glGetUniformLocation(m_program, "AmbientProduct"), 1, value_ptr(ambient_product));
	glUniform4fv(glGetUniformLocation(m_program, "DiffuseProduct"), 1, value_ptr(diffuse_product));
	glUniform4fv(glGetUniformLocation(m_program, "SpecularProduct"), 1, value_ptr(specular_product));
	glUniform4fv(glGetUniformLocation(m_program, "LightPosition"), 1, value_ptr(light_position));
	glUniform1f(glGetUniformLocation(m_program, "Shininess"), material_shininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fishTex.TexName());

	m_fish.RenderGL();

	// Render Sphere
	m_program = m_sphere.m_program;
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "bump_map"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mPVM");
	m_nVM = glGetUniformLocation(m_program, "mVM");

	M = translate(mat4(1.f), vec3(-10., 0., 0.))
		* rotate(mat4(1.f), 90.f, vec3(1., 0., 0.));
	VM = m_mVM * M;
	PVM = m_mPVM * M;

	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(PVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(VM));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_sphereTex.TexName());

	m_sphere.RenderGL();

	// Render the Metallic Sphere
	m_program = m_metallicSphere.m_program;
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "env_map"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mPVM");
	m_nVM = glGetUniformLocation(m_program, "mVM");

	M = translate(mat4(1.f), vec3(10., 0., 0.));
	VM = m_mVM * M;
	PVM = m_mPVM * M;

	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(PVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(VM));
	m_metallicSphere.RenderGL();

	// Render the Torus
	m_program = m_torus.m_program;
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "bump_map"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mPVM");
	m_nVM = glGetUniformLocation(m_program, "mVM");

	M = translate(mat4(1.f), vec3(0., 0., -10.))
		* rotate(mat4(1.f), 90.f, vec3(1., 0., 0.));
	VM = m_mVM * M;
	PVM = m_mPVM * M;

	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(PVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(VM));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_torusTex.TexName());

	m_torus.RenderGL();

	// Render the Skybox
	m_program = m_skybox.m_program;
	glUseProgram(m_program);
	glUniform1i(glGetUniformLocation(m_program, "skybox"), 0);

	m_nPVM = glGetUniformLocation(m_program, "mP");
	m_nVM = glGetUniformLocation(m_program, "mV");
	glUniformMatrix4fv(m_nPVM, 1, GL_FALSE, value_ptr(m_mProjection));
	mat4 view = mat4(mat3(m_mVM));
	glUniformMatrix4fv(m_nVM, 1, GL_FALSE, value_ptr(view));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTex.TexName());
	glDepthFunc(GL_LEQUAL);
	m_skybox.RenderGL();
}

void CChildView::CleanGL() { }
