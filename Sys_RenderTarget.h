// レンダリング ターゲット切り替え
#pragma once

// ヘッダ
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"

// 関数プロトタイプ
HRESULT InitRenderTarget();								// 生成
void FinRenderTarget();									// 解放
LPDIRECT3DTEXTURE9 GetRenderTexture(int nTarget = 0, int nMulti = 0);// 参照
void SaveRenderTarget();								// 退避
void ChangeRenderTarget(int nTarget = 0);				// 切り替え
void ResetRenderTarget();								// 元に戻す