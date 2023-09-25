// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#pragma once

#include "framework.h"

// Standard Template Library
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

// Graphics Libraries
#include <glew.h>
#include <glext.h>
#include <wglext.h>
#include <glm.hpp>
#include <constants.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include <gl/gl.h>

// Constants
constexpr double M_PI =  3.1415926535897932384626433832795;
constexpr double M_TAU = 6.2831853071795864769252867665590;