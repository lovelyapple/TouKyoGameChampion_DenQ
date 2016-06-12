//-----------------------------------------------------------
//カメラマスタークラスh
//-----------------------------------------------------------
#ifndef _CLASS_CAMERA_MASTER_H_
#define _CLASS_CAMERA_MASTER_H_

#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
#include "Sys_Shader.h"

class c_Camera
{
public :
	c_Camera();
	HRESULT InitCamera(bool bWindow);
	virtual	void Update(void);
	virtual void Draw(void);
	void	UninitCamera(void);

	D3DXMATRIX	m_matProj;		// プロジェクション マトリックス
	D3DXMATRIX	m_matView;		// ビュー マトリックス
	D3DXVECTOR3	m_vCamera;		// カメラの実際の座標
	D3DXVECTOR3 m_vRot;			// カメラの回転
	//D3DXVECTOR3	m_vAngle;		// カメラの回転（π）
private:

};

#endif