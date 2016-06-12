//-----------------------------------------------------------
//PauseMenu
//-----------------------------------------------------------

//--------------------------------------
//システムインクルード
#include "C_HUD_Pause_Menu.h"
const char* FileNamePauseMenu[PAUSE_MAX] = {
	"data/Texture/menu_00.png",
	"data/Texture/menu_01.png",
	"data/Texture/menu_02.png"
};
c_PauseMenu::c_PauseMenu()
{
	m_nRecSelect = 0;
	m_bPause	 = true;
}
c_PauseMenu::~c_PauseMenu()
{
}
void c_PauseMenu::InitMenu(c_Game_camera* camera)
{
	g_pGameCamera	= camera;
	m_vPos			= *camera->GetGameCameraPos();
	m_pCursor		= new c_Selection(CURSOR_FILE_NAME,CURSOR_SIZE);
	m_pCursor->Init();
	m_pCursor->SetRot(DEFAULT_ROT_MENU);
	m_pPauseList	= new c_SelectionList;
	m_pPauseList->InitSelectionList();
	m_pPauseList->CreatList(FileNamePauseMenu,PAUSE_MAX,m_vPos,CURSOR_SIZE);
	m_pPauseList->SetListRot(DEFAULT_ROT_MENU);
}
void c_PauseMenu::UninitMenu(void)
{
	m_pCursor->Uninit();
	SAFE_DELETE(m_pCursor);
	m_pPauseList->UninitSelectionList();
	SAFE_DELETE(m_pPauseList);
	g_pGameCamera = NULL;
}
bool c_PauseMenu::GetPause(void)
{
	return m_bPause;
}
void c_PauseMenu::RefreashPos(void)
{
		m_vPos = *g_pGameCamera->GetGameCameraPos();
		m_vPos += RANGE_FROM_CAMERA;
		m_pPauseList->SetListPos(m_vPos);
}
void c_PauseMenu::UpdateMenu(void)
{
	if(GetKeyboardTrigger(KEY_PAUSE))
	{
		m_bPause = !m_bPause;
		RefreashPos();
	}
	RefreashPos();
	if(m_bPause)
	{
		if(GetKeyboardTrigger(KEY_ENTER))
		{

		}
		else if(GetKeyboardTrigger(KEY_DIR_UP))
		{
			m_nRecSelect = ( PAUSE_MAX + m_nRecSelect - 1) % PAUSE_MAX;
		}
		else if(GetKeyboardTrigger(KEY_DIR_DOWN))
		{
			m_nRecSelect = (m_nRecSelect + 1) % PAUSE_MAX;
		}

		{
			//ここでカーソルのエフェクト処理を行う
			//m_pCursor->SetAlpha
			//m_pCursor->SetSize
			//m_pCursor->m_vRot
			//などいずれも絶対値となる

		}

		m_pCursor->SetPos(m_pPauseList->m_pSelection[m_nRecSelect]->GetPos());
		m_pCursor->Update();
		m_pPauseList->UpdateList();
	}

}
void c_PauseMenu::DrawMenu(void)
{
	if(m_bPause)
	{
	
	m_pPauseList->DrawList();
	m_pCursor->DrawPrimitive();
	}
}
