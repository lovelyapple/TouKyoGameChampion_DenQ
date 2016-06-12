//-----------------------------------------------------------
//�v���C���[�N���X
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h
#include "C_Game_Player.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h

//--------------------------------------
//�C���X�^���X�C���N���[�h
c_Player::c_Player()
{
	Reset();
	m_pszFName = FILE_NAME_PLAYER;
}
c_Player::c_Player(C_FIELDPLACE place)
{
	Reset();
	m_pszFName = FILE_NAME_PLAYER;
	SetMoveTypeFrame(0,24);
	SetMoveTypeFrame(1,24);
	m_vVerTexSizeH		  = 1.0f / MOVE_TYPE_MAX;
	SetPosFromFeildPlace(&place,&m_vPos);
}
void c_Player::Reset(void)
{
	D3DV_INIT(m_vAcceleration);		//�����x
	D3DV_INIT(m_vRecSpeed);			//���݂̑��x
	m_uMoveType			= 0;		//�ړ����
	InitFootState(&m_uLeftFoot);
	InitFootState(&m_uLeftFoot);
	m_bDirection		= true;
	m_fHeat				= 30;
	m_nTimeFrame		= 0;
	for(int f = 0;f<MOVE_TYPE_MAX;f++)
	{
		m_nMaxFrame[f] = 0;
	}

	m_nRecFrame			= 0;
	m_vVerTexSizeH		= 1.0f;
	m_pStage			= NULL;
	m_bAllTouched			= false;
	for(int i= 0;i<MOVE_TYPE_MAX;i++) m_vVerTexSizeW[i] = 1.0f;
}

HRESULT c_Player::Init(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	// ���_�o�b�t�@�쐬
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(DVERTEX_PRIMITIVE) * 4, 0, 0, D3DPOOL_DEFAULT,
															&m_pD3DVertexBuffer, NULL))) {
		MessageBox(g_hWnd, _T("���_�o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), m_pszFName, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	//-------- ��������e�N�X�`�����[�h����
	// �e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, m_pszFName, &m_pD3DTexture))) 
	{
		MessageBox(g_hWnd, _T("�e�N�X�`���I�u�W�F�N�g�̍쐬�Ɏ��s���܂���,�f�t�H�[���g���g�p"), _T("error"), 
			MB_OK | MB_ICONERROR);
		if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, m_pszFName, &m_pD3DTexture))) 
		{
			MessageBox(g_hWnd, _T("�f�t�H�[���g�e�N�X�`���I�u�W�F�N�g�̍쐬�Ɏ��s���܂���,"), _T("error"), 
				MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
		
	}
	
	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	 -PLAYER_WIDTH;	// ���_�O
		VBuffer[0].y  =   PLAYER_HEIGHT;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   PLAYER_WIDTH;	// ���_�P
		VBuffer[1].y  =   PLAYER_HEIGHT;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -PLAYER_WIDTH; // ���_3
		VBuffer[2].y  =  -PLAYER_HEIGHT;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   PLAYER_WIDTH; // ���_�Q	
		VBuffer[3].y  =  -PLAYER_HEIGHT;	
		VBuffer[3].z  =   0.0f;

		VBuffer[0].nx =  0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);

		if(m_uMoveType>= MOVE_TYPE_MAX)
		{
			m_uMoveType = 0;
		}
		float TexSizeW = m_vVerTexSizeW[m_uMoveType];
		VBuffer[0].tu =  m_nRecFrame * TexSizeW;	
		VBuffer[0].tv =  m_uMoveType * m_vVerTexSizeH;
		
		VBuffer[1].tu =  m_nRecFrame * TexSizeW + TexSizeW;	
		VBuffer[1].tv =  m_uMoveType * m_vVerTexSizeH;


		VBuffer[2].tu =  m_nRecFrame * TexSizeW;	
		VBuffer[2].tv =  m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;

		VBuffer[3].tu =  m_nRecFrame * TexSizeW + TexSizeW;	
		VBuffer[3].tv =  m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;


		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}	return S_OK;
}
void c_Player::Update(void)
{
	switch(m_uMoveType)
	{
	case MOVE_TYPE_WALK:
		//�����ړ�����
		if(GetKeyboardPress(KEY_DIR_RIGHT))
		{
			if(GetKeyboardTrigger(KEY_DIR_RIGHT))
			{
				m_nRecFrame++;
			}
			if(GetKeyboardPress(KEY_DUSH))
			{
				m_vRecSpeed.x += VALUE_DUSH_SPEED;
				if(m_vRecSpeed.x >= VALUE_DUSH_MAX_SPEED)
					m_vRecSpeed.x = VALUE_DUSH_MAX_SPEED;
				
				m_nTimeFrame += VALUE_DUSH_FRAMETIMES ;
				m_bDirection = true;
			}
			else
			{
				m_vRecSpeed.x += VALUE_WALK_SPEED;
				if(m_vRecSpeed.x >= VALUE_WALK_MAX_SPEED)
					m_vRecSpeed.x = VALUE_WALK_MAX_SPEED;
				
				m_nTimeFrame ++ ;
				m_bDirection = true;
			}

		}
		else if(GetKeyboardPress(KEY_DIR_LEFT))
		{
			if(GetKeyboardTrigger(KEY_DIR_LEFT))
			{
				m_nRecFrame ++;
			}
			if(GetKeyboardPress(KEY_DUSH))
			{
				m_vRecSpeed.x -= VALUE_DUSH_SPEED;
				if(m_vRecSpeed.x <= -VALUE_DUSH_MAX_SPEED)
					m_vRecSpeed.x = -VALUE_DUSH_MAX_SPEED;
				
				m_nTimeFrame += VALUE_DUSH_FRAMETIMES ;
				m_bDirection = false;
			}
			else
			{
				m_vRecSpeed.x -= VALUE_WALK_SPEED;
				if(m_vRecSpeed.x <= -VALUE_WALK_MAX_SPEED)
					m_vRecSpeed.x = -VALUE_WALK_MAX_SPEED;
				m_bDirection = false;
				m_nTimeFrame++;
			}
		}
		else
		{
			//���x�̕���
			m_vRecSpeed.x *= VALUE_SPEED_ATTENUSUION;
			if(m_vRecSpeed.x > -VALUE_SPPED_RESET && m_vRecSpeed.x < VALUE_SPPED_RESET)
			{
				m_vRecSpeed.x = 0;
			}

			//�t���[���̕���
			//m_nTimeFrame = 0;//�������Ƃ��ɁATimeFrame�����Z�b�g
		/*	if(m_nRecFrame > g_FrameDislight[0] && m_nRecFrame < g_FrameDislight[1])
				m_nRecFrame = (g_FrameDislight[0] + g_FrameDislight[1]) / 2;
			else if(m_nRecFrame > g_FrameDislight[2] && m_nRecFrame < g_FrameDislight[3])
				m_nRecFrame = (g_FrameDislight[2] + g_FrameDislight[3]) / 2;
			else if (m_nRecFrame <= g_FrameDislight[1]) m_nRecFrame = g_FrameDislight[0] - 1;
			else if (m_nRecFrame >  g_FrameDislight[1]) m_nRecFrame = g_FrameDislight[2] - 1;*/
		}

//----------------------------------------------------------
//�}�X����
		if(m_bDirection)
		{
			if(m_nTimeFrame > FRAME_PER_TIME-1)
			{
				m_nTimeFrame = 0;
				m_nRecFrame ++;
				if(m_nRecFrame > m_nMaxFrame[m_uMoveType]-1)
				{
					m_nRecFrame = 0;
				}
			}
		}
		else
		{
			if(m_nTimeFrame > FRAME_PER_TIME-1)
			{
				m_nTimeFrame = 0;
				m_nRecFrame --;
				if(m_nRecFrame < -m_nMaxFrame[m_uMoveType] + 1)
				{
					m_nRecFrame = 0;
				}

			}
		}

//------------------------------------------------------------------------------
//���n����
		GronudTouchedCheck();

		//�W�����v����
		if(m_uLeftFoot.bTouched == true || m_uRightFoot.bTouched == true)
		{
			if(GetKeyboardTrigger(KEY_JUMP))
			{
				m_vRecSpeed.y = VALUE_JUMP_SPEED;
				m_uMoveType = MOVE_TYPE_JUMP;
				m_nRecFrame	= 0;
			}
		}
		break;
//*******************************************************************************
	case MOVE_TYPE_JUMP:

		if(GetKeyboardPress(KEY_DIR_LEFT))
		{
			m_bDirection = false;
			if(m_vRecSpeed.x >= -VALUE_JUMP_MAX_MOVE_SPEED)
				m_vRecSpeed.x -= VALUE_JUMP_MOVE_SPEED;
		}
		else if(GetKeyboardPress(KEY_DIR_RIGHT))
		{
			m_bDirection = true;
			if(m_vRecSpeed.x <= VALUE_JUMP_MAX_MOVE_SPEED)
				m_vRecSpeed.x += VALUE_JUMP_MOVE_SPEED;
		}
//----------------------------------------------------------
//�}�X����
		m_nTimeFrame+= 6;

		if(m_nTimeFrame > FRAME_PER_TIME)
		{
			m_nTimeFrame = 0;
			if(m_bDirection)
			{
				m_nRecFrame ++;
				if(m_nRecFrame > m_nMaxFrame[m_uMoveType] - 1)
				{
					m_nRecFrame = 0;
				}
			}
			else
			{
				m_nRecFrame --;
				if(m_nRecFrame < 0 )
				{
					m_nRecFrame = m_nMaxFrame[m_uMoveType];
				}
			}

		}


		GronudTouchedCheck();
		if(m_uLeftFoot.bTouched || m_uRightFoot.bTouched)
		{
			m_uMoveType = MOVE_TYPE_WALK;
			m_nRecFrame = 0;
		}

		break;
	}

//------------------------------------------------------------------------------
//���C�g�Ɋւ��鏈��
	m_bLighted = true;
	if(m_nRecFrame > g_FrameDislight[0] && m_nRecFrame < g_FrameDislight[1])
		m_bLighted =false;
	else if(m_nRecFrame > g_FrameDislight[2] && m_nRecFrame < g_FrameDislight[3])
		m_bLighted = false;
	else
		if(m_uLeftFoot.bTouched == true && m_uRightFoot.bTouched == true) 
		{
				m_bLighted = true;

		}
		else 
		{
				m_bLighted = false;

		}

	if(m_bLighted)
	{
		this->m_fHeat += PLAYER_HEAT_PER_TIME;
		if(GetKeyboardPress(KEY_DUSH) && (GetKeyboardPress(KEY_DIR_LEFT) || GetKeyboardPress(KEY_DIR_RIGHT)))
			this->m_fHeat += PLAYER_HEAT_PER_TIME * 2;
		if(m_fHeat > PLAYER_MAX_HEAT)
			m_fHeat = PLAYER_MAX_HEAT;
	}
	else
	{
		this->m_fHeat -= PLAYER_COOL_PER_TIME;
		if(m_fHeat < 0)
			m_fHeat = 0;
	}


//------------------------------------------------------------------------------
//�d�͂̒ǉ�
	if(m_uLeftFoot.bTouched == false && m_uRightFoot.bTouched == false)
	FreeFallRealTime(&m_vRecSpeed);	

//------------------------------------------------------------------------------
//Alert>>>>>>>>>>�ύX�֎~
	
	MoveCheck();
	m_vPos += m_vRecSpeed;

//------------------------------------------------------------------------------
//Alert>>>>>>>>>>�ύX�֎~
	D3DXMATRIX	matRotate;		// ��]�}�g���b�N�X
	D3DXMATRIX	matTrans;		// ���s�ړ��}�g���b�N�X
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// ��]�}�g���b�N�X�𐶐�
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);	// ���s�ړ��}�g���b�N�X�𐶐�

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;  //�I�t�Z�b�g��؂�i��]�s�񂾂��ɂ��āj
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
	SetVerTxBuff();
}
void c_Player::GronudTouchedCheck(void)
{

	InitFootState(&m_uLeftFoot);
	InitFootState(&m_uRightFoot);

	D3DXVECTOR3 PlayerUnder = m_vPos;
	PlayerUnder.y -= PLAYER_HEIGHT/* * 0.5f*/; // �v���C���[�̉����W

	int PlayerRecFlamePt = m_nRecFrame % (MAX_FRAME / 2);
	
	D3DXVECTOR3 PlayerRFootPos, PlayerLFootPos;  
	D3DV_INIT(PlayerRFootPos);
	D3DV_INIT(PlayerLFootPos);


	if(m_bDirection == true){ // �v���C���[�̉E�������̈ʒu
		PlayerRFootPos = D3DXVECTOR3(PlayerUnder.x + g_WalkState[PlayerRecFlamePt].fRDist,
									 PlayerUnder.y, 0.0f);

		PlayerLFootPos = D3DXVECTOR3(PlayerUnder.x - g_WalkState[PlayerRecFlamePt].fLDist,
									 PlayerUnder.y, 0.0f);
		m_uLeftFoot.bTouched = g_WalkState[PlayerRecFlamePt].bLTouch;
		m_uRightFoot.bTouched = g_WalkState[PlayerRecFlamePt].bRTouch;
	}
	else{
		PlayerRFootPos = D3DXVECTOR3(PlayerUnder.x + g_WalkState[PlayerRecFlamePt].fRDist,
									 PlayerUnder.y, 0.0f);

		PlayerLFootPos = D3DXVECTOR3(PlayerUnder.x - g_WalkState[PlayerRecFlamePt].fLDist,
									 PlayerUnder.y, 0.0f);
		m_uLeftFoot.bTouched = g_WalkState[PlayerRecFlamePt].bRTouch;
		m_uRightFoot.bTouched = g_WalkState[PlayerRecFlamePt].bLTouch;

	}

	for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
		for(int x = 0;x < MAX_FIELD_WIDTH; x++)
		{
			if(m_pStage->m_uBlock[y][x] == NULL) continue;
			if(PlayerUnder.y < m_pStage->m_uBlock[y][x]->m_vPos.y) continue;
			
			
			D3DXVECTOR3 BlockUp = D3DXVECTOR3( m_pStage->m_uBlock[y][x]->m_vPos.x,
											   m_pStage->m_uBlock[y][x]->m_vPos.y + BLOCK_SIZE * 0.5f, 
											   0.0f);

			D3DXVECTOR3 BlockC	= D3DXVECTOR3(	m_pStage->m_uBlock[y][x]->m_vPos.x,
												m_pStage->m_uBlock[y][x]->m_vPos.y,
													0.0f);

			if(fabs(PlayerRFootPos.y - BlockUp.y) < 0.2f /*&& m_uRightFoot.touched == true)*/){
				if(BlockUp.x - BLOCK_SIZE * 0.5f <= 
					PlayerRFootPos.x && BlockUp.x + BLOCK_SIZE * 0.5f >= PlayerRFootPos.x){ 
					float DistR = fabs(fabs(PlayerRFootPos.x) - fabs(BlockUp.x));
					if(DistR < m_uRightFoot.nNearBoxDist){
						m_uRightFoot.nNearBoxDist = DistR;
						m_uRightFoot.nNearBox_X = x;
						m_uRightFoot.nNearBox_Y = y;
						m_uRightFoot.bTouched   = true;
					}
				}
			}
			if( fabs(PlayerLFootPos.y - BlockUp.y) < 0.2f /* && m_uLeftFoot.touched == true)*/){
				if(BlockUp.x - BLOCK_SIZE * 0.5f <= 
					PlayerLFootPos.x && BlockUp.x + BLOCK_SIZE * 0.5f >= PlayerLFootPos.x){ 
					float DistL = fabs(fabs(PlayerLFootPos.x) - fabs(BlockUp.x));
					if(DistL < m_uLeftFoot.nNearBoxDist){
						m_uLeftFoot.nNearBoxDist = DistL;
						m_uLeftFoot.nNearBox_X = x;
						m_uLeftFoot.nNearBox_Y = y;
						m_uLeftFoot.bTouched   = true;
					}
				}
			}
		}// Box��for���I��
	if(!(m_uRightFoot.nNearBoxDist <= BLOCK_SIZE * 0.5f))
		m_uRightFoot.bTouched = false;

	if(!(m_uLeftFoot.nNearBoxDist <= BLOCK_SIZE * 0.5f))
		m_uLeftFoot.bTouched = false;		
}
int c_Player::MoveCheck(void)
{
	int Dir = 99;
	for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
		for(int x = 0;x < MAX_FIELD_WIDTH; x++)
		{
			if(m_pStage->m_uBlock[y][x] == NULL) continue;
			bool	touched = false;
			D3DXVECTOR3 playerC = D3DXVECTOR3(	m_vPos.x,// + m_vRecSpeed.x,
												m_vPos.y,// + PLAYER_HEIGHT * 0.5f,
												0.0f);

			D3DXVECTOR3 BlockC	= D3DXVECTOR3(	m_pStage->m_uBlock[y][x]->m_vPos.x,
												m_pStage->m_uBlock[y][x]->m_vPos.y,
												 0.0f);
			touched = HitBoxWorld_2D(playerC,	PLAYER_HEIGHT,		PLAYER_WIDTH,
									 BlockC,	BLOCK_SIZE * 0.5f,	BLOCK_SIZE * 0.5f,
									 10);
			if(touched == false) continue;
			
			this->HitExclusion2D(m_vPos,PLAYER_WIDTH,PLAYER_HEIGHT,m_pStage->m_uBlock[y][x]->m_vPos,BLOCK_SIZE*0.5f,BLOCK_SIZE*0.5f,m_vRecSpeed,0.01f);
		}
		return Dir;
}
int c_Player::GetPlayerFrame(void)
{
	return m_nRecFrame;
}
bool c_Player::GetLightSwitch(void)
{

	return m_bLighted;
}

void c_Player::SetVerTxBuff(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		
		

		VBuffer[0].x  =	 -PLAYER_WIDTH;	// ���_�O
		VBuffer[0].y  =   PLAYER_HEIGHT;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   PLAYER_WIDTH;	// ���_�P
		VBuffer[1].y  =   PLAYER_HEIGHT;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -PLAYER_WIDTH; // ���_3
		VBuffer[2].y  =  -PLAYER_HEIGHT;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   PLAYER_WIDTH; // ���_�Q	
		VBuffer[3].y  =  -PLAYER_HEIGHT;	
		VBuffer[3].z  =   0.0f;


		VBuffer[0].nx =  0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);

		if(m_uMoveType>= MOVE_TYPE_MAX)
		{
			m_uMoveType = 0;
		}
		float TexSizeW = m_vVerTexSizeW[m_uMoveType];

		if(m_bDirection)
		{
			VBuffer[0].tu =  m_nRecFrame * TexSizeW;	
			VBuffer[0].tv =  m_uMoveType * m_vVerTexSizeH;
		
			VBuffer[1].tu =  m_nRecFrame * TexSizeW + TexSizeW;	
			VBuffer[1].tv =  m_uMoveType * m_vVerTexSizeH;


			VBuffer[2].tu =  m_nRecFrame * TexSizeW;	
			VBuffer[2].tv =  m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;

			VBuffer[3].tu =  m_nRecFrame * TexSizeW + TexSizeW;	
			VBuffer[3].tv =  m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;
		}
		else
		{
			VBuffer[0].tu =  -m_nRecFrame * TexSizeW;	
			VBuffer[0].tv =   m_uMoveType * m_vVerTexSizeH;
		
  			VBuffer[1].tu =  -m_nRecFrame * TexSizeW - TexSizeW;	
			VBuffer[1].tv =   m_uMoveType * m_vVerTexSizeH;


			VBuffer[2].tu =  -m_nRecFrame * TexSizeW;	
			VBuffer[2].tv =   m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;

			VBuffer[3].tu =  -m_nRecFrame * TexSizeW - TexSizeW;	
			VBuffer[3].tv =   m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;
		}

		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}

}
void c_Player::SetMoveTypeFrame(int nType,int MaxFrame)
{
	m_vVerTexSizeW[nType] = 1.0f / MaxFrame;
	m_nMaxFrame[nType] = MaxFrame;

}
void c_Player::SetStage(c_Stage* pStage)
{
	m_pStage = pStage;
}
int c_Player::GetPlayerHeat(void)
{
	return m_fHeat;
}
void c_Player::InitFootState(FOOT_STATS *Foot)
{
	Foot->nNearBoxDist = 1000.0f;
	Foot->nNearBox_X = 0;
	Foot->nNearBox_Y = 0;
	Foot->bTouched   = false;
}
bool c_Player::GetFootRTorF(void)
{
	if(m_uRightFoot.bTouched == true)
		return true;
	else
		return false;
}
bool c_Player::GetFootLTorF(void)
{
	if(m_uLeftFoot.bTouched == true)
		return true;
	else
		return false;
}
D3DXVECTOR3* c_Player::GetPlayerSpeed(void)
{
	return &this->m_vRecSpeed;
}
D3DXVECTOR3* c_Player::GetPlayerPosAdress(void)
{
	return &this->m_vPos;
}

