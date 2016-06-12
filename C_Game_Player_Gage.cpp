//-----------------------------------------------------------
//プレイヤーのヒートケージ
//-----------------------------------------------------------

//--------------------------------------
//システムインクルード
#include "C_Game_Player_Gage.h"

c_Player_heat::c_Player_heat()
{
}
void c_Player_heat::InitPlayerHeat(c_Game_camera* Camera,c_Player* player)
{
	m_pCamera		= Camera;
	m_pPlayer		= player;
	m_fAlpha		= 1.0f;
	m_nChangeTime	= 0;
	m_nBeforeLevel	= 0;
	m_nRecLevel		= 0;
	m_nMarkMode		= MARK_MODE_KEEP;

	m_pHeatBG		= new c_Master_Primitive;
	m_pHeatEntity	= new c_Master_Primitive;
	m_pHeatMark		= new c_Master_Primitive;
	m_pHeatMarkBG	= new c_Master_Primitive;

	m_nRecHeat = g_nHeatLevel[0];
	m_nRecHeat = 0;

	m_pHeatBG->SetFileName(FILE_NAME_HEAT_BG);
	m_pHeatEntity->SetFileName(FILE_NAME_HEAT_ENTITY);
	m_pHeatMark->SetFileName(FILE_NAME_HEAT_FACE);
	m_pHeatMarkBG->SetFileName(FILE_NAME_HEAT_MARKBG);

	D3DXVECTOR3 pos = *m_pCamera->GetGameCameraPos();
	
	m_pHeatBG->SetPos(pos + HeatBGPos);
	m_pHeatEntity->SetPos(pos + HeatEntityPos);
	m_pHeatMark->SetPos(pos + HeatFacePos);
	m_pHeatMarkBG->SetPos(pos + HeatFacePos);

	m_pHeatBG->SetSize(HeatBGSize);
	m_pHeatEntity->SetSize(HeatEntitySIze);
	m_pHeatMark->SetSize(HeatFaceSize);
	m_pHeatMarkBG->SetSize(HeatFaceBGSize);

	m_pHeatBG->Init();
	m_pHeatEntity->Init();
	m_pHeatMark->Init();
	m_pHeatMarkBG->Init();

	D3DXVECTOR3 vOblique[2];
	vOblique[0] = HeatCageOblique;
	vOblique[1] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pHeatBG->SetOblique(vOblique);
	m_pHeatEntity->SetOblique(vOblique);

	D3DXVECTOR3 Fuv;
	D3DV_INIT(Fuv);
	Fuv.x = 1.0f / HEAT_LEVEL_MAX;
	Fuv.y = 1.0f;
	m_pHeatMark->SetTexUV(Fuv);
	D3DV_INIT(Fuv);
	Fuv.x = 1.0f / HEAT_TEX_COLOR_LEVEL;
	Fuv.y = 1.0f;
	m_pHeatEntity->SetTexUV(Fuv);
}

void c_Player_heat::UpdatePlayerHeat(void)
{
	D3DXVECTOR3 pos = *m_pCamera->GetGameCameraPos();
	
	m_pHeatBG->SetPos(pos + HeatBGPos);
	m_pHeatEntity->SetPos(pos + HeatEntityPos);
	m_pHeatMark->SetPos(pos + HeatFacePos);
	m_pHeatMarkBG->SetPos(pos + HeatFaceBGPos);
	D3DXVECTOR3 EntitySize; 
	D3DV_INIT(EntitySize);
	m_nRecHeat = m_pPlayer->GetPlayerHeat();
	EntitySize.x = m_nRecHeat * TEXSIZE_PER_HEAT;
	EntitySize.y = HeatEntitySIze.y;
	m_pHeatEntity->SetSize(EntitySize);
	m_pHeatEntity->UpdateCageStyle();
	m_pHeatEntity->SetTexRecUVFrame(m_nRecHeat * HEAT_TEX_COLOR_LEVEL / PLAYER_MAX_HEAT - 1,0);
	m_pHeatEntity->SetVerTexBuffUV();

	m_nRecLevel = m_nRecHeat/35;

	if(m_nRecHeat > PLAYER_MAX_HEAT * 0.8f)
	{
		m_nMarkMode = MARK_MODE_SHINING;
		D3DXVECTOR3 vSize;
		D3DV_INIT(vSize);

			if(m_nRecHeat % 2 == 0)
				m_fAlpha = 0.0f;
			else	m_fAlpha = 1.0f;
	}


	D3DXVECTOR3 vSize;
	D3DV_INIT(vSize);
	switch(m_nMarkMode)
	{
	case MARK_MODE_KEEP:
		if(m_nRecLevel != m_nBeforeLevel)
		{
			m_nBeforeLevel = m_nRecLevel;
			m_nMarkMode	   = MARK_MODE_CHANGE;
		}
		break;
	case MARK_MODE_CHANGE:
		m_nChangeTime++;
		vSize.x = sinf(m_nChangeTime * 3.14f / HEAT_TEX_COLOR_LEVEL);
		vSize.y = vSize.x;
		m_pHeatMark->SetSize(D3DXVECTOR3(vSize));
		if(m_nChangeTime >= MARK_CHANGE_TIME)
		{
			m_nChangeTime = 0;
			m_pHeatMark->SetSize(HeatFaceSize);
			m_nMarkMode = MARK_MODE_KEEP;
		}
		break;
	case MARK_MODE_SHINING:
		m_nChangeTime += 2;
		vSize.x = (sinf(m_nChangeTime * 3.14f / HEAT_TEX_COLOR_LEVEL) + 1.0f) * 0.5f * 0.1f + HeatFaceSize.x;
		vSize.y = vSize.x;
		m_pHeatMark->SetSize(vSize);
		m_pHeatMarkBG->SetSize(vSize * 1.8f);
		if(m_nRecHeat < PLAYER_MAX_HEAT * 0.8f)
		{
			m_nChangeTime = 0;
			m_pHeatMark->SetSize(HeatFaceSize);
			m_pHeatMarkBG->SetSize(HeatFaceBGSize);
			m_nMarkMode = MARK_MODE_KEEP;
		}

		break;

	}
	m_pHeatEntity->SetVerTexBuffAlpha(m_fAlpha);

	m_pHeatBG->UpdateCageStyle();

	
	m_pHeatMark->UpdatePrimitive();
	m_pHeatMark->SetTexRecUVFrame((m_nRecHeat/35),0);
	m_pHeatMark->SetVerTexBuffUV();
	m_pHeatMarkBG->UpdatePrimitive();
}
void c_Player_heat::UninitPlayerHeat(void)
{
	if(m_pHeatBG)
	{
		m_pHeatBG->Uninit();
		SAFE_DELETE(m_pHeatBG);
	}
	if(m_pHeatEntity)
	{
		m_pHeatEntity->Uninit();
		SAFE_DELETE(m_pHeatEntity);
	}
	if(m_pHeatMark)
	{
		m_pHeatMark->Uninit();
		SAFE_DELETE(m_pHeatMark);
	}
	if(m_pHeatMarkBG)
	{
		m_pHeatMarkBG->Uninit();
		SAFE_DELETE(m_pHeatMarkBG);
	}

}
void c_Player_heat::DrawPlayerHeat(void)
{

	m_pHeatEntity->DrawPrimitive();
	m_pHeatBG->DrawPrimitive();
	m_pHeatMarkBG->DrawPrimitive();
	m_pHeatMark->DrawAntialiasing();
	
}
