//=======================================================================================
//game cpp
//=======================================================================================
//-------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Game.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
#include "Sys_Input.h"
//-------------------------------------
//���i�C���N���[�h
#include "C_HUD_Pause_Menu.h"
//-------------------------------------
//�}�X�^�[�Y�C���N���[�g
#include "C_Master_Camera.h"
#include "C_Master_Model.h"
//-------------------------------------
//�C���X�^���X�C���N���[�g
#include "C_Game_Camera.h"
//-------------------------------------
//MGR�C���N���[�h
#include "C_Mgr_Game_Mode.h"
#include "C_Mgr_Title_Mode.h"
#include "C_Mgr_Light_Sys.h"
#include "C_Particle_Master_List.h"

//-------------------------------------------------------
//�v���g�^�C�v�錾
void SetMode(int nMode);

//-------------------------------------------------------
//
const char* StageName[MAX_STAGE]={
	"data/Sys_Data/DefaultStage.csv",
	"data/Sys_Data/Stage01.csv",
	"data/Sys_Data/Stage02.csv"
};

//-------------------------------------------------------
//�O���[�o���ϐ��錾
c_Game_camera*		g_pGameCamera;
c_Mgr_Game_Mode*	g_pMgr_Game;
c_Mgr_Title*		g_pMgr_Title;
c_Mgr_Light*		g_pMgr_Light;
c_Particle_Master*	g_pMgr_Particle;
c_PauseMenu*		g_pPauseMenu;
D3DXVECTOR3			g_CameraTarget;
//-------------------------------------------------------
//����O���[�o���ϐ��錾
int g_nGameMode;
int g_nRecMode;
int g_nStageNum;
//-------------------------------------------------------
//�}�N����`
const D3DXVECTOR3 MenuPos = D3DXVECTOR3(-50.0f,0.0f,0.0f);
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT Initgame(void)
{
	//----------------�Q�[���̊�{�v�f������----------------------//
	g_nRecMode = g_nGameMode = GAME_MODE_PLAY;

	//g_nRecMode = g_nGameMode = GAME_MODE_EDITOR;
	g_nStageNum = 1;
	//�J����
	g_pGameCamera	= new c_Game_camera;
	//���C�g
	g_pMgr_Light	= new c_Mgr_Light;
	g_pMgr_Light->C_Mgr_Init();
	g_pMgr_Light->m_pCLight[g_Num_Light_Sun] = new c_Light;
	g_pMgr_Light->m_pCLight[g_Num_Light_Sun]->CreatLightSunDefault(g_Num_Light_Sun);
	g_pMgr_Light->m_pCLight[g_Num_Light_Player] = new c_Light;
	g_pMgr_Light->m_pCLight[g_Num_Light_Player]->CreatLightPointDefault(g_Num_Light_Player);
	g_pMgr_Light->m_pCLight[g_Num_Light_PlayerSub] = new c_Light;
	g_pMgr_Light->m_pCLight[g_Num_Light_PlayerSub]->CreatLightPointDefault(g_Num_Light_PlayerSub);
	g_pMgr_Light->m_pCLight[g_Num_Light_Sun]->ActiveLightSYS();
	//----------------�Q�[���̊�{�v�f������----------------------//


	//--------------------------------------//
	//�Q�[���̃}�l�[�W���V�X�e��������
	g_pMgr_Game = new c_Mgr_Game_Mode;			//�Q�[�����[�h�̖{�̂�
	g_pMgr_Game->C_Mgr_Init(g_pGameCamera);		//��{������
	g_pMgr_Game->SetLightSys(g_pMgr_Light);		//���C�g�V�X�e���̃C���^�t�F�[�X���擾
	g_pMgr_Game->SetGameMode(g_nRecMode);
	g_pMgr_Game->m_pStage->SetStageName(StageName[1]);
	g_pMgr_Game->m_pStage->LoadStage();
	g_pMgr_Light->m_pCLight[4] = new c_Light;
	g_pMgr_Light->m_pCLight[4]->CreatLightSpotDefault(4,&g_pMgr_Game->m_pPlayer->GetPos(),D3DXVECTOR3(4.0f,4.0f,0.0f));

	g_pMgr_Particle = new c_Particle_Master;
	g_pMgr_Particle->Init_Particle("data/Texture/Effect/Effect_Dark_Explo_13.png",13,5);
	//=======================================//
	//�V�X�e�����i������
	g_pPauseMenu = new c_PauseMenu();
	g_pPauseMenu->InitMenu(g_pGameCamera);
	return S_OK;
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void Uninitgame(void)
{
	//g_pMgr_Title->C_Mgr_Uninit();
	//SAFE_DELETE(g_pMgr_Title);
	g_pMgr_Game->C_Mgr_Uninit();
	SAFE_DELETE(g_pMgr_Game);

	SAFE_DELETE(g_pGameCamera);
	g_pMgr_Light->ClearAllLight();
	SAFE_DELETE(g_pMgr_Light);

	g_pPauseMenu->UninitMenu();
	SAFE_DELETE(g_pPauseMenu);

	g_pMgr_Particle->Uninit_Particle();
	SAFE_DELETE(g_pMgr_Particle);

}
//------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void Updategame(void)
{
	switch(g_nGameMode)
	{
		case GAME_MODE_TITLE:
			g_pMgr_Title->C_Mgr_Update();
		break;
		case GAME_MODE_EDITOR:		
		case GAME_MODE_PLAY:
			g_pMgr_Light->m_pCLight[4]->m_vTargetPos = &g_pMgr_Game->m_pPlayer->GetPos();
			g_pMgr_Game->C_Mgr_Update();
		break;
	}
	g_pPauseMenu->UpdateMenu();
	g_pMgr_Light->UpdateLight();
	g_pMgr_Particle->Update_Particle();

}

//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void Drawgame(void)
{
	switch(g_nGameMode)
	{
		case GAME_MODE_TITLE:
			g_pMgr_Title->C_Mgr_Draw();
		break;
		case GAME_MODE_EDITOR:		
		case GAME_MODE_PLAY:
			g_pMgr_Game->C_Mgr_Draw();
		break;
	}
	g_pPauseMenu->DrawMenu();
	g_pMgr_Particle->Draw_Particle(D3DBLEND_SRCALPHA);
}
void SetMode(int nMode)
{
	g_nRecMode = g_nGameMode;
	switch(nMode)
	{
	case GAME_MODE_TITLE:	
		break;
	case GAME_MODE_EDITOR:
		break;
	case GAME_MODE_PLAY:
		break;	
	}

	switch(g_nRecMode)
	{
	case GAME_MODE_TITLE:	
		break;
	case GAME_MODE_EDITOR:
		break;
	case GAME_MODE_PLAY:
		break;	
	}
}


