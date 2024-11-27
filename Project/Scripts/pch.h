#pragma once

#include "framework.h"

#include <Engine/global.h>
#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_D")
#else
#pragma comment(lib, "Engine\\Engine")
#endif

#include "ScriptManager.h"