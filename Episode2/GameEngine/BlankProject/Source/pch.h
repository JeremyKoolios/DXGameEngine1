#pragma once

#include <windows.h>

#define MAX_NAME_STRING 256											//#define is a macro the replaces all occurences with something
#define HInstance() GetModuleHandle(NULL)							//returns current hInstance