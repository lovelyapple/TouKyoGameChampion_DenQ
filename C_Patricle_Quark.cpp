//-----------------------------------------------------------
//C_PARTICLE_QUARK_H
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Patricle_Quark.h"

c_Quark::c_Quark()
{
	InitQuarkStatus();
}
c_Quark::~c_Quark()
{
}
void c_Quark::InitQuarkStatus()
{
	D3DV_INIT(m_vPos);			//
	
	D3DV_INIT(m_vRot);
	D3DV_INIT(m_vSize);
	D3DV_INIT(m_vSpeed);
	D3DM_INIT(m_mMatrix);
	m_vSize					= D3DXVECTOR3(3.0f,3.0f,0.0f);
	m_bUse					= false;
	m_bWatchCamera			= false;;	//
	m_bRecycle				= false;
	m_fAlpha				= 1.0f;
	m_fVerTexUSize			= 1.0f;
	m_nVerTexFrame			= 0;
	m_nTimePerFrame			= 0;	//TimeFrame Per AnimationFrame
	m_nMaxFrame				= 0;	//MAX Frame
	m_nRecFrame				= 0;	//Recent Frame
	m_nMoveMode				= 0;	//
	m_nRecTime				= 0;
	m_nLife					= 0;
	m_nStopTime				= 0;
	for(int nCntStep = 0; nCntStep < QUARK_STATS_MAX;nCntStep++)
	{
		m_nMoveStep[nCntStep] = QUARK_MOVE_MODE_MOVE_RETURN;
		D3DV_INIT(m_vDestPosAndSpeed[nCntStep]);
	}
}

void c_Quark::UninitQuark()
{
}
void c_Quark::UpdateQuark()
{

	m_vPos += m_vSpeed;
	UpdateQuarkMatrix();
}
void c_Quark::UpdateQuarkMatrix(void)
{
	D3DXMATRIX	matRotate;													// 回転マトリックス
	D3DXMATRIX	matTrans;													// 平行移動マトリックス
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;
	D3DM_INIT(m_mMatrix);

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// 回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);			// 平行移動マトリックスを生成

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;							//オフセットを切る（回転行列だけにして）
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
}


void c_Quark::Set_Quark_Stats(QUARK_STATS stats,D3DXVECTOR3 vInput)
{
	switch(stats)
	{
	case QUARK_STATS_POS:		m_vPos = vInput;
		break;
	case QUARK_STATS_ROT:		m_vRot = vInput;
		break;
	case QUARK_STATS_SIZE:		m_vSize = vInput;
		break;
	case QUARK_STATS_SPEED:		m_vSpeed = vInput;
		break;
	}

}
void c_Quark::Set_Quark_Stats(QUARK_STATS stats,int nInput)
{
	switch(stats)
	{
	case QUARK_STATS_MAX_TIME:		m_nMaxTime		= nInput;
		break;
	case QUARK_STATS_FRAMETIME:		m_nTimePerFrame = nInput;
		break;
	case QUARK_STATS_MAX_FRAME:		m_nMaxFrame = nInput;
		break;
	case QUARK_STATS_STOP_TIME:		m_nStopTime = nInput;
		break;
	case QUARK_STATS_MOVE_MODE:		m_nRecFrame = nInput;
		break;
	}
}
void c_Quark::Set_Quark_Stats(QUARK_STATS stats,bool nInput)
{
	switch(stats)
	{
	case QUARK_STATS_USE:		m_bUse		= nInput;
		break;
	case QUARK_STATS_RECYCLE:	m_bRecycle		= nInput;
		break;
	case QUARK_STATS_WATCH:		m_bWatchCamera		= nInput;
		break;
	}
}
void c_Quark::Set_Quark_Stats(QUARK_STATS stats,float fInput)
{
	switch(stats)
	{
	case QUARK_STATS_ALPHA:		m_fAlpha			= fInput;
		break;
	case QUARK_STATS_USIZE:		m_fVerTexUSize		= fInput;
		break;
	}
}
	//m_nMaxFrame = 3 * 60;
	//m_nMoveStep[0] = QUARK_MOVE_MODE_KEEP_ORIGIN;
	//m_nMoveStep[1] = QUARK_MOVE_MODE_MOVE_A;
	//m_nMoveStep[2] = QUARK_MOVE_MODE_KEEP_A;
	//m_nMoveStep[3] = QUARK_MOVE_MODE_MOVE_RETURN;
	//m_vDestPosAndSpeed[0] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//m_vDestPosAndSpeed[2] = D3DXVECTOR3(10.0f,3.0f,0.0f);
	//m_vDestPosAndSpeed[1] = (m_vDestPosAndSpeed[2] - m_vDestPosAndSpeed[0]) / m_nMaxTime;
	//m_vDestPosAndSpeed[3] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//switch(this->m_nMoveMode)
	//{
	//case QUARK_MOVE_MODE_KEEP_ORIGIN:
	//	if(m_bRecycle)
	//	{
	//		m_nRecTime	= m_nMaxTime;
	//		m_nMoveMode	= m_nMoveStep[m_nMoveMode+1];
	//		m_vSpeed	= m_vDestPosAndSpeed[m_nMoveMode];
	//		
	//	}
	//	break;
	//case QUARK_MOVE_MODE_MOVE_A:
	//	m_nRecTime--;
	//	m_vPos += m_vSpeed;
	//	if(m_nRecTime < 0)
	//	{
	//		m_nRecTime	= m_nStopTime;
	//		m_nMoveMode	= m_nMoveStep[m_nMoveMode+1];
	//		m_vPos		= m_vDestPosAndSpeed[m_nMoveMode];
	//	}
	//	break;
	//case QUARK_MOVE_MODE_KEEP_A:
	//	m_nRecTime--;
	//	if(m_nRecTime < 0)
	//	{
	//		m_nRecTime	= m_nMaxTime;
	//		m_nMoveMode = m_nMoveStep[m_nMoveMode+1];
	//		m_vSpeed	= m_vDestPosAndSpeed[m_nMoveMode];
	//	}
	//	break;
	//case QUARK_MOVE_MODE_MOVE_RETURN:
	//	break;
	//}