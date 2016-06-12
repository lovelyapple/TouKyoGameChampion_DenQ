//-----------------------------------------------------------
//C_MASTER_MASTER_LIST
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h
#include "C_Particle_Master_List.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
//--------------------------------------
//�\���̐錾

c_Particle_Master::c_Particle_Master()
{
	m_pD3DTexture = NULL;
	m_pD3DVertexBuffer = NULL;
	m_nMaxQuark = MAX_PARTICLE_QUARK;
	D3DV_INIT(m_vParticlePos);
	m_nMaxQuarkLife = VALUE_PATRICLE_MAX_LIFE;
	m_nPatricleMaxFrame		= 0;
	for(int nCntQuark = 0;nCntQuark < m_nMaxQuark;nCntQuark++)
	{
		m_pQuark[nCntQuark] = NULL;
	}
}
c_Particle_Master::~c_Particle_Master()
{
}
void c_Particle_Master::Init_Particle(LPCSTR FileName)
{
	m_lpzFileName = FileName;
	CreateTexBuff_Particle();
}
void c_Particle_Master::Init_Particle(LPCSTR FileName,int nMaxFrame,int TimePerFrame)
{
	m_lpzFileName	= FileName;
	m_nPatricleMaxFrame		= nMaxFrame;
	m_nPatricleTimePerFrame	= TimePerFrame;
	CreateTexBuff_Particle();
}
void c_Particle_Master:: CreateQuarkSingle(void)
{
	for(int nCntQuark = 0; nCntQuark < m_nMaxQuark;nCntQuark++)
	{
		if(m_pQuark[nCntQuark]) continue;
		if(nCntQuark >= m_nMaxQuark-1)
			break;
		m_pQuark[nCntQuark] = new c_Quark;
		m_pQuark[nCntQuark]->InitQuarkStatus();
		m_pQuark[nCntQuark]->m_nLife = m_nMaxQuarkLife;
		m_pQuark[nCntQuark]->Set_Quark_Stats(QUARK_STATS_MAX_TIME,m_nMaxQuarkLife);
		m_pQuark[nCntQuark]->Set_Quark_Stats(QUARK_STATS_SPEED,D3DXVECTOR3(0.0f,0.0f,-0.1f));
		m_pQuark[nCntQuark]->Set_Quark_Stats(QUARK_STATS_SIZE,D3DXVECTOR3(2.0f,2.0f,0.0f));
		if(m_nPatricleMaxFrame != 0)
		{
			m_pQuark[nCntQuark]->m_nMaxFrame		= m_nPatricleMaxFrame;
			m_pQuark[nCntQuark]->m_fVerTexUSize		= (float)(1.0f / m_nPatricleMaxFrame);
			m_pQuark[nCntQuark]->m_nTimePerFrame	= this->m_nPatricleTimePerFrame;
		}

		break;
	}
}
void c_Particle_Master::Update_Particle(void)
{
	if(GetKeyboardTrigger(DIK_O))
	{
		CreateQuarkSingle();
	}

	for(int nCntQuark = 0; nCntQuark < m_nMaxQuark;nCntQuark++)
	{
		if(!m_pQuark[nCntQuark]) continue;

		m_pQuark[nCntQuark]->m_nLife --;
		if(m_pQuark[nCntQuark]->m_nLife < 0)
		{
			m_pQuark[nCntQuark] = NULL;
		}
		else
		{
			m_pQuark[nCntQuark]->UpdateQuark();
			if(m_nPatricleMaxFrame != 0)
			{
				m_pQuark[nCntQuark]->m_nRecTime ++;
				if(m_pQuark[nCntQuark]->m_nRecTime > m_pQuark[nCntQuark]->m_nTimePerFrame)// == 0)
				{
					m_pQuark[nCntQuark]->m_nRecTime -= m_pQuark[nCntQuark]->m_nTimePerFrame;
					m_pQuark[nCntQuark]->m_nRecFrame = ( m_pQuark[nCntQuark]->m_nRecFrame + 1 ) % m_nPatricleMaxFrame;
				}

			}

		}
	}
	SetVerTexBuff_Particle();
}
void c_Particle_Master::Uninit_Particle(void)
{
	for(int nCntQuark = 0;nCntQuark < m_nMaxQuark;nCntQuark++)
	{
		if(!m_pQuark[nCntQuark]) continue;
		m_pQuark[nCntQuark]->UninitQuark();
		m_pQuark[nCntQuark] = NULL;
	}
	if(m_pD3DTexture)
	{
		SAFE_RELEASE(m_pD3DTexture);
	}
	if(m_pD3DVertexBuffer)
	{
		SAFE_RELEASE(m_pD3DVertexBuffer);
	}
}
void c_Particle_Master::Draw_Particle(D3DBLEND Effect)
{
	// ���ߐF(�����F)���\�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ���u�����h��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���ߐF(�����F)�̕�����Z�o�b�t�@�ɏ������܂Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DBLEND blend = Effect;
	//D3DBLEND_SRCALPHA
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, Effect);//set
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//in
	// �`��ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ���C�e�B���O���Ȃ�

	for(int nCntQuark = m_nMaxQuark-1; nCntQuark >= 0;nCntQuark--)
	{
		if(!m_pQuark[nCntQuark]) continue;
		//���[���h�ϊ��ݒ�
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_pQuark[nCntQuark]->m_mMatrix);	
		//�`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
		g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// ���_�o�b�t�@��o�^
		g_pD3DDevice->SetTexture(0, m_pD3DTexture);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntQuark * 4,2);

	}
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, Effect);//set
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// out
	//�����_�[�ݒ�̕���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��
}
HRESULT c_Particle_Master::CreateTexBuff_Particle(void)
{

	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, 
		m_lpzFileName, 
		&m_pD3DTexture))) 
	{
		MessageBox(g_hWnd, _T("�f�t�H�[���g�e�N�X�`���I�u�W�F�N�g�̍쐬�Ɏ��s���܂���,"), _T("error"), 
			MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	// ���_�o�b�t�@�쐬
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(DVERTEX_PRIMITIVE) * 4 * m_nMaxQuark,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pD3DVertexBuffer, NULL))) 
	{	
		return E_FAIL;
	}
	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		for(int nCntQuark = 0; nCntQuark < m_nMaxQuark;nCntQuark++,VBuffer +=4)
		{
			VBuffer[0].x  =	 -1.0f;	// ���_�O
			VBuffer[0].y  =   1.0f;		
			VBuffer[0].z  =   0.0f;	

			VBuffer[1].x  =   1.0f;	// ���_�P
			VBuffer[1].y  =   1.0f;	
			VBuffer[1].z  =   0.0f;

			VBuffer[2].x  =  -1.0f; // ���_3
			VBuffer[2].y  =  -1.0f;	
			VBuffer[2].z  =   0.0f;

			VBuffer[3].x  =   1.0f; // ���_�Q	
			VBuffer[3].y  =  -1.0f;	
			VBuffer[3].z  =   0.0f;

			VBuffer[0].nx =   0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
			VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
			VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;		
			VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;

			VBuffer[0].tu =  0.0f;
			VBuffer[0].tv =  0.0f;
		
			VBuffer[1].tu =  1.0f;
			VBuffer[1].tv =  0.0f;


			VBuffer[2].tu =  0.0f;	
			VBuffer[2].tv =  1.0f;

			VBuffer[3].tu =  1.0f;
			VBuffer[3].tv =  1.0f;

			VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
		}

		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}
	return S_OK;
}
void c_Particle_Master::SetVerTexBuff_Particle(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		for(int nCntQuark = 0; nCntQuark < m_nMaxQuark;nCntQuark++,VBuffer+=4)
		{
			if(!m_pQuark[nCntQuark]) continue;

			VBuffer[0].x  =	 -m_pQuark[nCntQuark]->m_vSize.x;	// ���_�O
			VBuffer[0].y  =   m_pQuark[nCntQuark]->m_vSize.y;		
			VBuffer[0].z  =   0.0f;	

			VBuffer[1].x  =   m_pQuark[nCntQuark]->m_vSize.x;	// ���_�P
			VBuffer[1].y  =   m_pQuark[nCntQuark]->m_vSize.y;	
			VBuffer[1].z  =   0.0f;

			VBuffer[2].x  =  -m_pQuark[nCntQuark]->m_vSize.x; // ���_3
			VBuffer[2].y  =  -m_pQuark[nCntQuark]->m_vSize.y;	
			VBuffer[2].z  =   0.0f;

			VBuffer[3].x  =   m_pQuark[nCntQuark]->m_vSize.x; // ���_�Q	
			VBuffer[3].y  =  -m_pQuark[nCntQuark]->m_vSize.y;	
			VBuffer[3].z  =   0.0f;

			VBuffer[0].nx =   0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
			VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
			VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;		
			VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;

			if(m_nPatricleMaxFrame != 0)
			{
				VBuffer[0].tu =  m_pQuark[nCntQuark]->m_fVerTexUSize * m_pQuark[nCntQuark]->m_nRecFrame;
				VBuffer[0].tv =  0.0f;
		
				VBuffer[1].tu =  m_pQuark[nCntQuark]->m_fVerTexUSize * m_pQuark[nCntQuark]->m_nRecFrame
								+  m_pQuark[nCntQuark]->m_fVerTexUSize;
				VBuffer[1].tv =  0.0f;


				VBuffer[2].tu =  m_pQuark[nCntQuark]->m_fVerTexUSize * m_pQuark[nCntQuark]->m_nRecFrame;	
				VBuffer[2].tv =  1.0f;

				VBuffer[3].tu =  m_pQuark[nCntQuark]->m_fVerTexUSize * m_pQuark[nCntQuark]->m_nRecFrame
								+  m_pQuark[nCntQuark]->m_fVerTexUSize;
				VBuffer[3].tv =  1.0f;
			}
			else
			{
				VBuffer[0].tu =  0.0f;
				VBuffer[0].tv =  0.0f;
		
				VBuffer[1].tu =  1.0f;
				VBuffer[1].tv =  0.0f;


				VBuffer[2].tu =  0.0f;	
				VBuffer[2].tv =  1.0f;

				VBuffer[3].tu =  1.0f;
				VBuffer[3].tv =  1.0f;
			}
			VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
			VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(1 * 255));
		}

		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}
}