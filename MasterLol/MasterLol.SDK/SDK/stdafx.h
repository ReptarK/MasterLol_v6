#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif

#define _DEBUG_VERSION

#include <SDKDDKVer.h>

// C RunTime Header Files
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <Windows.h>

#include "Macros.h"

#include "Patchables.h"
#include "Offsets.h"
#include "LolString.h"

typedef unsigned int uint;

