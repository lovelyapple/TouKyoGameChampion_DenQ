//-----------------------------------------------------------
//タイトルモードMGR.cpp
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Mgr_Title_Mode.h"

//宣言
//--------------------------------------
//初期化処理
c_Mgr_Title::c_Mgr_Title()
{

}
void  c_Mgr_Title::C_Mgr_Init(void)
{

	
	m_pTitle_Camera	= new c_Game_camera;
	m_pTitle_Logo = new c_Logo;
	m_pTitle_Logo->Init();
}
void c_Mgr_Title::C_Mgr_Uninit(void)
{

	SAFE_DELETE(m_pTitle_Camera);
	m_pTitle_Logo->Uninit();
	SAFE_DELETE(m_pTitle_Logo);
}
void  c_Mgr_Title::C_Mgr_Update(void)
{

	m_pTitle_Logo->Update();
	m_pTitle_Logo->Update();
	{
		D3DXVECTOR3 pos = m_pTitle_Logo->GetPos();
		D3DXMATRIX	mat = m_pTitle_Logo->GetMatrix();
	}
}
void  c_Mgr_Title::C_Mgr_Draw(void)
{

		m_pTitle_Logo->DrawPrimitive();
		m_pTitle_Logo->DrawPrimitive();
}