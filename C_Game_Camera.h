//=======================================================================================
//game camera h
//=======================================================================================
#ifndef _GAME_CAMERA_H_
#define _GAME_CAMERA_H_

#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "C_Master_Camera.h"
//---------------------------------
//マクロ定義
#define MAX_MOVE_FRMAE	( 60)
#define BALUE_MOVE_COE	(5)
//---------------------------------
//マクロ定義
#define DEFAULT_RANGE_Z			(5.0f)
class c_Game_camera:public c_Camera
{
public:
	c_Game_camera();
	void Update(void);
	void SetDestPos(D3DXVECTOR3* DestPos);
	void SetLooktAtTarget(D3DXMATRIX* Target);
	void MoveToDestPosAuto(void);
	D3DXVECTOR3* GetGameCameraPos(void);
	
private:
	D3DXVECTOR3	m_fRotSpeed;
	float		m_fRangeZ;

	int			m_nMoveframe;
	float		m_fMoveCoefficient;
	D3DXVECTOR3 m_vDestPos;
	D3DXVECTOR3	m_vMoveSpeed;

	D3DXVECTOR3 m_vRecPos;

	D3DXMATRIX	m_matTarget;
};

#endif