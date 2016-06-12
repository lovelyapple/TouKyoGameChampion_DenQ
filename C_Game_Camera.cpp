//-----------------------------------------------------------
//game camera cpp
//-----------------------------------------------------------
#include "C_Game_Camera.h"
#include "Sys_input.h"

c_Game_camera::c_Game_camera()
{
	m_nMoveframe		= MAX_MOVE_FRMAE;
	m_fMoveCoefficient	= 1.0f;
	D3DV_INIT(m_vDestPos);
	D3DV_INIT(m_vRecPos);
	D3DV_INIT(m_vMoveSpeed);
	D3DM_INIT(m_matTarget);
	m_fRangeZ = DEFAULT_RANGE_Z;
}
void c_Game_camera::SetDestPos(D3DXVECTOR3* DestPos)
{
	m_nMoveframe	= MAX_MOVE_FRMAE;
	m_vDestPos = *DestPos;
	m_vDestPos.z = -10.0f;
	m_vMoveSpeed = (m_vDestPos - m_vRecPos) / MAX_MOVE_FRMAE;// / m_nMoveframe;
}
void c_Game_camera::MoveToDestPosAuto(void)
{
	if(m_vRecPos != m_vDestPos)
	{
		m_vRecPos += m_vMoveSpeed;
		m_nMoveframe--;
		if(m_nMoveframe <= 0)
		{
			m_nMoveframe	= MAX_MOVE_FRMAE;
			m_vRecPos		= m_vDestPos;
			D3DV_INIT(m_vMoveSpeed);		
		}
	}
}
void c_Game_camera::SetLooktAtTarget(D3DXMATRIX* Target)
{
	m_matTarget = *Target;
}

void c_Game_camera::Update(void)
{
	if(GetKeyboardPress(DIK_Z))
	{
		m_fRangeZ += 0.5f;
	}
	else if(GetKeyboardPress(DIK_X))
	{
		m_fRangeZ -= 0.5f;
	}
	if(m_fRangeZ <= 0.2 * DEFAULT_RANGE_Z) m_fRangeZ = 0.2 * DEFAULT_RANGE_Z;
	if(m_fRangeZ >= 3 * DEFAULT_RANGE_Z) m_fRangeZ = 3 * DEFAULT_RANGE_Z;

	MoveToDestPosAuto();
	D3DXMATRIX matrix;
	D3DM_INIT(matrix);
	D3DXMatrixTranslation(&matrix,m_vRecPos.x,m_vRecPos.y,m_vRecPos.z);

	D3DXVec3TransformCoord(&m_vCamera,
		&D3DXVECTOR3(0.0f,0.0f,-m_fRangeZ),
		&matrix);

	D3DM_INIT(matrix);
	D3DXMatrixTranslation(&matrix,m_vRecPos.x,m_vRecPos.y,0.0f);
	D3DXVECTOR3 vLook;
	D3DXVec3TransformCoord(&vLook,
		&D3DXVECTOR3(0.0f,0.0f,0.0f),
		&matrix);
	D3DXVECTOR3 vUP;
	D3DXVec3TransformNormal(&vUP,
		&D3DXVECTOR3(0.0f,1.0f,0.0f),
		&m_matTarget);


	D3DXMatrixLookAtLH(&m_matView,
		&m_vCamera,&vLook,&vUP);
}
D3DXVECTOR3* c_Game_camera::GetGameCameraPos(void)
{
	return &this->m_vRecPos;
}
