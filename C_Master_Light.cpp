//-----------------------------------------------------------
//Light�}�X�^�[�Y�N���X
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h
#include "C_Master_Light.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾

c_Light::~c_Light()
{
}
void c_Light::CreatLightTYPE(D3DLIGHTTYPE nType,int name)
{
	//////���s����		//D3DLIGHT_DIRECTIONAL;
	//////�_����		//D3DLIGHT_POINT
	//////�X�|�b�g���C�g//D3DLIGHT_SPOT
	

	m_pLight = new D3DLIGHT9;
	ZeroMemory(m_pLight,sizeof(D3DLIGHT9));
	m_nLightNumber		= name;
	m_pLight->Type		= nType;
	m_bLookAtTarget		= false;
	
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
}
void c_Light::CreatLightPointDefault(int name)
{
	m_pLight			= new D3DLIGHT9;
	ZeroMemory(m_pLight,sizeof(D3DLIGHT9));
	m_nLightNumber		= name;
	m_pLight->Type		= D3DLIGHT_POINT;
	m_pLight->Diffuse	= D3DXCOLOR(1.0f, 1.0f, 100.0f/255, 1.0f);
	m_pLight->Specular	= D3DXCOLOR(0.3f, 0.0f, 0.2f, 0.3f);
	m_pLight->Ambient	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	m_pLight->Position	= D3DXVECTOR3(3.0f, 3.0f, -3.0f);
	m_pLight->Falloff	= 0.01f;
	m_pLight->Attenuation0	= 1.0f;
	m_pLight->Attenuation1	= 0.01f;
	m_pLight->Attenuation2	= 0.0f;
	m_pLight->Range		= 5.0f;
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
	g_pD3DDevice->LightEnable(m_nLightNumber,TRUE);

}
void c_Light::CreatLightSunDefault(int name)
{
	m_pLight			= new D3DLIGHT9;
	ZeroMemory(m_pLight,sizeof(D3DLIGHT9));
	m_nLightNumber		= name;
	m_pLight->Type		= D3DLIGHT_DIRECTIONAL;
	m_pLight->Diffuse	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.9f);
	m_pLight->Specular	= D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);
	m_pLight->Ambient	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.7f);
	m_pLight->Attenuation0	= 1.0f;
	m_pLight->Attenuation1	= 0.1f;
	m_pLight->Attenuation2	= 0.0f;

	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
	g_pD3DDevice->LightEnable(m_nLightNumber,TRUE);
}
void c_Light::CreatLightSpotDefault(int name,D3DXVECTOR3* target,D3DXVECTOR3 pos)
{
	m_pLight			= new D3DLIGHT9;
	ZeroMemory(m_pLight,sizeof(D3DLIGHT9));
	m_nLightNumber		= name;
	m_pLight->Type		= D3DLIGHT_SPOT;
	m_pLight->Position	= pos;
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,target);
	m_pLight->Direction	= dir;
	m_pLight->Diffuse	= D3DXCOLOR(1.0f/255, 50.0f/255, 1.0f/255, 1.0f);
	m_pLight->Specular	= D3DXCOLOR(0.3f, 0.0f, 0.2f, 0.3f);
	m_pLight->Ambient	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	m_pLight->Attenuation0	= 0.0f;
	m_pLight->Attenuation1	= 0.1f;
	m_pLight->Attenuation2	= 0.0f;
	m_pLight->Falloff		= 1.0f;
	m_pLight->Phi			= D3DXToRadian(90.0f);
	m_pLight->Theta			= D3DXToRadian(60.0f);
	m_pLight->Range			= 10.0f;
	m_vTargetPos = target;
	m_bLookAtTarget = true;
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
	g_pD3DDevice->LightEnable(m_nLightNumber,TRUE);
}

void c_Light::SetLightState(int STATE,D3DXVECTOR3 pos)
{
	if(STATE == LIGHT_STATS_POSITION)
	{
		m_pLight->Position = pos;
	}
	else if(STATE == LIGHT_STATS_DIRCATION)
	{
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir,&pos);
		m_pLight->Direction = dir;
	}
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);

}
void  c_Light::SetLightState(int STATE,D3DXCOLOR fInput)
{
	switch(STATE)
	{
	case LIGHT_STATS_DIFFUSE:
		m_pLight->Diffuse = fInput;
		break;
	case LIGHT_STATS_AMBIENT:
		m_pLight->Ambient = fInput;
		break;
	case LIGHT_STATS_SPECULAR:
		m_pLight->Specular= fInput;
		break;
	}
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);

}
void c_Light::SetLightState(int STATE,float fInput)
{
	switch(STATE)
	{
	case LIGHT_STATS_RANGE:		m_pLight->Range = fInput;
		break;
	case LIGHT_STATS_FALLOFF:	m_pLight->Falloff = fInput;
		break;
	case LIGHT_STATS_THETA:		m_pLight->Theta = fInput;
		break;
	case LIGHT_STATS_PHI:		m_pLight->Phi = fInput;
		break;
	case LIGHT_STATS_ATTE01:	m_pLight->Attenuation0 = fInput;
		break;
	case LIGHT_STATS_ATTE02:	m_pLight->Attenuation1 = fInput;
		break;
	case LIGHT_STATS_ATTE03:	m_pLight->Attenuation2 = fInput;
		break;
	}
	g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
}
void c_Light::ActiveLightSYS(void)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT,0x00101010);
}
void c_Light::SwitchForLight(bool input)
{
	g_pD3DDevice->LightEnable(m_nLightNumber, input);
}
void c_Light::Update(void)
{
	if(m_bLookAtTarget == true)
	{
		D3DXVECTOR3 dir;
		D3DV_INIT(dir);
		D3DXVec3Normalize(&dir,&(*m_vTargetPos - m_pLight->Position));
		m_pLight->Direction = dir;
		g_pD3DDevice->SetLight(m_nLightNumber, m_pLight);
		g_pD3DDevice->LightEnable(m_nLightNumber,TRUE);
	}

}
void c_Light::Uninit(void)
{
	g_pD3DDevice->LightEnable(m_nLightNumber, FALSE);
	if(m_pLight) m_pLight = NULL;
}




