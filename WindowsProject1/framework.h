// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <cassert>

#include <memory>

#include <unordered_map>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

#pragma push_macro("#define IMGUI_DEFINE_MATH_OPERATORS")
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui_internal.h"
#pragma pop_macro("#define IMGUI_DEFINE_MATH_OPERATORS")