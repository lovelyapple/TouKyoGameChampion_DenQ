//=========================================================================
//DirectX Base Graphics.h
//=========================================================================
#ifndef _SYS_GRAHPICS_H_
#define _SYS_GRAHPICS_H_

#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Game.h"
#include "Sys_Shader.h"
#include "Sys_Macro.h"

HRESULT	InitDXGraphics(void);
HRESULT Render(void);
HRESULT	Init3DObject(void);
HRESULT CleanupD3DObject(void);
bool UninitDXGraphics(void);



#endif