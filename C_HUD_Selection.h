//-----------------------------------------------------------
//PauseMenu
//-----------------------------------------------------------
#ifndef _C_SELECTION_H
#define _C_SELECTION_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Primitive.h"
//--------------------------------------
//マクロ宣言


//-------------------------------------
//クラス宣言
class c_Selection: public c_Master_Primitive
{
public:
	c_Selection(LPCSTR fzName,D3DXVECTOR3 size);
	~c_Selection();
	void Update(void);
	void SetVerTexBuff(void);
	void SetAlpha(float fAlpha);


private:

	float				m_fAlpha;			//透明度
};

#endif