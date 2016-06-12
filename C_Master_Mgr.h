//-----------------------------------------------------------
//マネージャーマスターズクラス
//-----------------------------------------------------------
#ifndef _C_MASTER_MGR_H_
#define _C_MASTER_MGR_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//クラス宣言
class c_Master_Mgr
{
public:
	c_Master_Mgr();
	~c_Master_Mgr();
	virtual void C_Mgr_Init(void);
	virtual void C_Mgr_Uninit(void);
	virtual void C_Mgr_Update(void);
	virtual void C_Mgr_Draw(void);
private:
};
#endif