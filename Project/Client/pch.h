#pragma once

#include <Engine/Global.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_D")
#else
#pragma comment(lib, "Engine\\Engine")
#endif

#ifdef _DEBUG
#pragma comment(lib, "Scripts\\Scripts_D")
#else
#pragma comment(lib, "Scripts\\Scripts")
#endif