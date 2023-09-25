#pragma once

#include <cassert>
#include <GL/glu.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef UNICODE
#define tstring wstring
#else
#define tstring string
#endif