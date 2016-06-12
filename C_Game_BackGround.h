//-----------------------------------------------------------
//ステージクラス
//-----------------------------------------------------------
#ifndef _C_GAME_SATGE_BACKGOUNRD_H
#define _C_GAME_SATGE_BACKGOUNRD_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Shader.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Model.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define FILENAME_STAGEBG	("data/model/Box.x")
//--------------------------------------
//クラス宣言
class c_StageBG : public c_Model
{
public:
	c_StageBG(LPCSTR File,D3DXVECTOR3 pos);
	~c_StageBG();
	void Update(void);
	void ShaderDraw(void);
private:
};

#endif