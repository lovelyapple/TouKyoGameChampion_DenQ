//-----------------------------------------------------------
//�G�f�B�^�[���[�hMGR.cpp
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h
#include "C_Mgr_Game_Mode.h"
#include "Sys_RenderTarget.h"
#include "Sys_Game.h"

//--------------------------------------
//�v���g�^�C�v�̐錾
//--------------------------------------
//�W���O���[�o���ϐ��錾
//--------------------------------------
//����������
void c_Mgr_Game_Mode::C_Mgr_Init(c_Game_camera* camera)
{
	m_pBlockList	= new c_TaskList;
	m_pActiveBlock	= new c_Block(BLOCK_TYPE_NOMAL_ELE,&C_FIELDPLACE(0,0));
	m_pStage		= new c_Stage(m_pBlockList,C_FIELDPLACE(0,0));
	m_pStage->InitAllBlock();//���蓮������
	m_pBackGround	= new c_StageBG(FILENAME_STAGEBG,D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pCamera		= camera;

	m_pPlayer		= new c_Player(C_FIELDPLACE(3,5));
	m_pPlayer->Init();
	m_pPlayer->SetStage(m_pStage);
	m_pPlayerEffect = new c_PlayerLight(m_pPlayer);
	m_pPlayerEffect->Init();
	m_pPlayerCage	= new c_Player_heat;
	m_pPlayerCage->InitPlayerHeat(this->m_pCamera,m_pPlayer);

	m_pFont			= new c_Font;
	m_pFont->CreatFont(NULL,18);

	m_fLightRange	= 10.0f;

	m_pMgr_Item		= new c_Mgr_Field_Item(m_pPlayer);
	m_pMgr_Item->Init_MGR_Entity();


	//InitRenderTarget();
}
void c_Mgr_Game_Mode::SetGameMode(int mode)
{
	m_bGameMode = mode;
}

void c_Mgr_Game_Mode::SetLightSys(c_Mgr_Light* LightSys)
{
	m_pLightMgr = LightSys;
}

//--------------------------------------
//�I������
void c_Mgr_Game_Mode::C_Mgr_Uninit(void)
{

	m_pActiveBlock->CleanArray();
	m_pActiveBlock->UninitModel();
	SAFE_DELETE(m_pActiveBlock);

	m_pStage->ClearAllBlock();
	SAFE_DELETE(m_pStage);

	m_pBlockList->UninitTaskList();
	SAFE_DELETE(m_pBlockList);

	m_pBackGround->UninitModel();
	SAFE_DELETE(m_pBackGround);

	m_pPlayerEffect->Uninit();
	SAFE_DELETE(m_pPlayerEffect);

	m_pPlayer->Uninit();
	SAFE_DELETE(m_pPlayer);

	m_pPlayerCage->UninitPlayerHeat();
	SAFE_DELETE(m_pPlayerCage);

	m_pMgr_Item->Uninit_MGR_Entity();
	SAFE_DELETE(m_pMgr_Item);

	m_pCamera = NULL;
	m_pLightMgr = NULL;

	//FinRenderTarget();	// �����_�����O �^�[�Q�b�g���

}

//--------------------------------------
//�X�V����
void c_Mgr_Game_Mode::C_Mgr_Update(void)
{
	//======��������̓X�e�[�W�Ɋւ��鑀��=====//
	int nInput = 99;
	if(m_bGameMode == GAME_MODE_EDITOR)
	{
		nInput = GetIniputBLockMove();
	
		if(nInput != 99)
		{
			switch(nInput)
			{
			case MOVE_KEY_X_UP:		m_pActiveBlock->m_uPlace.x--;
				break;
			case MOVE_KEY_X_DWON:	m_pActiveBlock->m_uPlace.x++;
				break;
			case MOVE_KEY_Y_UP:		m_pActiveBlock->m_uPlace.y++;
				break;
			case MOVE_KEY_Y_DOWN:	m_pActiveBlock->m_uPlace.y--;
				break;
			}
			m_pActiveBlock->FieldCheck();
			if(m_bGameMode == GAME_MODE_EDITOR)
			{
				m_pCamera->SetDestPos(m_pActiveBlock->GetModelPos());
				m_pCamera->SetLooktAtTarget(m_pActiveBlock->GetModelMatrix());
				m_pLightMgr->m_pCLight[g_Num_Light_Player]->SetLightState(LIGHT_STATS_POSITION,*m_pActiveBlock->GetModelPos());


			}
		}
		else if(GetKeyboardTrigger(DIK_RETURN))
		{
			m_pStage->CreatBlockSingle(m_pActiveBlock->m_uPlace,0);
		}
		else if(GetKeyboardTrigger(DIK_C))
		{
			//�����̓��T�C�N���̒��ɓ���Ȃ��Ă�����
			m_pStage->ClearBlockSingle(m_pActiveBlock->m_uPlace);
		}
		else if(GetKeyboardTrigger(DIK_N))
		{
			m_pStage->SaveStage();
		}
		else if(GetKeyboardTrigger(DIK_M))
		{
			m_pStage->LoadStage();
		}
	}
	//======�����܂ł̓X�e�[�W�Ɋւ��鑀��=====//
	
	if(m_bGameMode == GAME_MODE_PLAY)
	{
		m_pMgr_Item->Update_MGR_Entity();
		m_pPlayer->Update();
		D3DXVECTOR3 Playerpos;
		D3DV_INIT(Playerpos);
		Playerpos = m_pPlayer->GetPos();
		m_pLightMgr->m_pCLight[g_Num_Light_Player]->SetLightState(LIGHT_STATS_POSITION,
														Playerpos);
		Playerpos.z -= 3.0f;
		m_pLightMgr->m_pCLight[g_Num_Light_PlayerSub]->SetLightState(LIGHT_STATS_POSITION,
														Playerpos);
		bool bLight = m_pPlayer->GetLightSwitch();
		m_pLightMgr->m_pCLight[g_Num_Light_Player]->SwitchForLight(bLight);
		m_pLightMgr->m_pCLight[g_Num_Light_PlayerSub]->SwitchForLight(bLight);
		m_pPlayerEffect->GetPlayerLight(bLight);//�v���C���[�̔w�ʃG�t�F�N�g
		m_pPlayerEffect->Update();
		m_pPlayerCage->UpdatePlayerHeat();
		//===============�����Ńv���C���[�̃��C�g�𒲐�����====================//
		if(bLight)
		{
			m_fLightRange += PLAYER_LIGHT_CHANGE;
			if(m_fLightRange > MAX_PLAYER_LIGHT_VALUE)
				m_fLightRange = MAX_PLAYER_LIGHT_VALUE;
		}
		else
		{
			m_fLightRange = MIN_PLAYER_LIGHT_VALUE;
		}
		
		m_pLightMgr->m_pCLight[g_Num_Light_Player]->SetLightState(LIGHT_STATS_RANGE,
														m_fLightRange);
		m_pLightMgr->m_pCLight[g_Num_Light_PlayerSub]->SetLightState(LIGHT_STATS_RANGE,
														m_fLightRange);
		//===============�����Ńv���C���[�̃��C�g�𒲐�����====================//

		D3DXVECTOR3 pos = m_pPlayer->GetPos();
		D3DXMATRIX	mat = m_pPlayer->GetMatrix();
		
		m_pCamera->SetDestPos(&pos);
		m_pCamera->SetLooktAtTarget(&mat);


		//===========�e�X�g�p�̏I�_����
		
		if(m_pMgr_Item->m_pEntity[FinishPointNum]->Entity_HitPlayerChecker() && m_pPlayer->GetPlayerHeat() >= 99)
		{
			D3DXVECTOR3 pos;
			D3DV_INIT(pos);
			SetPosFromFeildPlace(&C_FIELDPLACE(3,3),&pos);
			m_pPlayer->SetPos(pos);
		}
		

	}

	m_pCamera->Update();
	m_pBackGround->Update();
	m_pBlockList->RunActiveList();
	m_pBlockList->RunRecycleList();
}
void c_Mgr_Game_Mode::ShaderSetLight(void)
{

	D3DXVECTOR3 pos = m_pLightMgr->m_pCLight[g_Num_Light_Player]->m_pLight->Position;
	D3DXVECTOR3 dir =D3DXVECTOR3(0,0,1);
	SetLightShader(&dir);
}

//--------------------------------------
//�`�揈��
void c_Mgr_Game_Mode::C_Mgr_Draw(void)
{
	//SaveRenderTarget();		// �����_�����O���ޔ�

	//ChangeRenderTarget(1);	// �����_�����O����e�N�X�`����
	BeginShader();
			m_pCamera->Draw();
			ShaderSetLight();
			m_pBackGround->ShaderDraw();
	EndShader();
	//ResetRenderTarget();	// �����_�����O���ʏ�ɖ߂�
	m_pActiveBlock->DrawBlock();
	m_pBlockList->DrawTaskList();
	if(m_bGameMode == GAME_MODE_PLAY)
	{
		m_pPlayer->DrawPrimitive();	
		m_pPlayerCage->DrawPlayerHeat();
		m_pMgr_Item->Draw_MGR_Entity();
		m_pPlayerEffect->DrawPrimitive();//�����l���邽�߁A�Ō�ŕ`��
		
	}	

	//-------------tes--------------ob
	
#ifdef _DEBUG
	DebugDraw();
#endif

}
void c_Mgr_Game_Mode::DebugDraw(void)
{
	m_pFont->DrawCord("�v���C���[�̃t���[����",
		(int)m_pPlayer->GetPlayerFrame(),
		D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pFont->DrawCord("�v���C���[�̌��݉��x",
		(int)m_pPlayer->GetPlayerHeat(),
		D3DXVECTOR3(200.0f,0.0f,0.0f));

	int FtL,FtR;
	if(m_pPlayer->GetFootRTorF()) FtR = 10;else FtR = 0;
	if(m_pPlayer->GetFootLTorF()) FtL = 10;else FtL = 0;
	m_pFont->DrawCord("�v���C���[�̉E��10�Ȃ���Ă�� ",FtR,
		D3DXVECTOR3(0.0f,20.0f,0.0f));
	m_pFont->DrawCord("�v���C���[�̉E��10�Ȃ���Ă�� ",FtL,
		D3DXVECTOR3(0.0f,40.0f,0.0f));
}
int c_Mgr_Game_Mode::GetIniputBLockMove(void)
{
	//�ȉ��̃}�N����`��SysMacro��`���ɂ���
	int nInputCode = 99;
		 if(GetKeyboardTrigger(KEY_DIR_LEFT))	
			 nInputCode = MOVE_KEY_X_UP;
	else if(GetKeyboardTrigger(KEY_DIR_RIGHT))	nInputCode = MOVE_KEY_X_DWON;
	else if(GetKeyboardTrigger(KEY_DIR_UP))		nInputCode = MOVE_KEY_Y_UP;
	else if(GetKeyboardTrigger(KEY_DIR_DOWN))	nInputCode = MOVE_KEY_Y_DOWN;
	else nInputCode = 99;

	return nInputCode;
}
