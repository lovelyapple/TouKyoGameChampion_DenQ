//============================================================================
//C_MGR_LIGHTR.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "C_Mgr_Light_Sys.h"
c_Mgr_Light::c_Mgr_Light()
{
}
c_Mgr_Light::~c_Mgr_Light()
{
}
void c_Mgr_Light::C_Mgr_Init(void)
{
	for(int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		if(m_pCLight[nCntLight])
		{
			m_pCLight[nCntLight] = NULL;
		}
	}

}
void c_Mgr_Light::UpdateLight(void)
{
	for(int nCntLight =0;nCntLight < MAX_LIGHT;nCntLight++)
	{
		if(!m_pCLight[nCntLight]) continue;
		m_pCLight[nCntLight]->Update();

	}

}

void c_Mgr_Light::ClearAllLight(void)
{
	for(int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		if(m_pCLight[nCntLight])
		{
			m_pCLight[nCntLight]->SwitchForLight(FALSE);
			m_pCLight[nCntLight] = NULL;
		}
	}
}

int c_Mgr_Light::GetLightNumber(void)
{
	int Num = 0;
	for(int nCntLight = 4; nCntLight < MAX_LIGHT;nCntLight++)
	{
		if(m_pCLight[nCntLight]) continue;
		else
		{
			Num = nCntLight;
			break;
		}
		if(nCntLight == MAX_LIGHT-1)
			Num = 3;
	}
	return Num;
}