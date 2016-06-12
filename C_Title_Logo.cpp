//-----------------------------------------------------------
//�^�C�g���N���X
//-----------------------------------------------------------
#include "C_Title_logo.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
c_Logo::c_Logo()
{
	m_pszFName = TEXTURE_TITLE;
}
HRESULT c_Logo :: Init(void)
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
		VBuffer[0].x  = -TEXTURE_WIDTH;	// ���_�O
		VBuffer[0].y  =  TEXTURE_HEIGHT;		
		VBuffer[0].z  =  0.0f;	
		VBuffer[0].nx =  0.0f;	VBuffer[0].ny =   0.0f;				VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[0].tu  =   0.0f;	VBuffer[0].tv =  0.0f;
		
		VBuffer[1].x  =  TEXTURE_WIDTH;	// ���_�P
		VBuffer[1].y  =  TEXTURE_HEIGHT;	
		VBuffer[1].z  =   0.0f;	
		VBuffer[1].nx =    0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].tu  =   1.0f;	VBuffer[1].tv  =  0.0f;

		VBuffer[2].x  =  -TEXTURE_WIDTH; // ���_3
		VBuffer[2].y  =   0.0f;	
		VBuffer[2].z  =   0.0f;
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].tu  =    0.0f;	VBuffer[2].tv  =  1.0f;

		VBuffer[3].x  =   TEXTURE_WIDTH; // ���_�Q	
		VBuffer[3].y  =   0.0f;	
		VBuffer[3].z  =   0.0f;
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].tu  =    1.0f;	VBuffer[3].tv  =  1.0f;


		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}	return S_OK;
}
void c_Logo::Update(void)
{
	SetVerTxBuff();
}
void c_Logo::SetVerTxBuff(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{	
		VBuffer[0].x  =	 -TEXTURE_WIDTH;	// ���_�O
		VBuffer[0].y  =   TEXTURE_HEIGHT;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   TEXTURE_WIDTH;	// ���_�P
		VBuffer[1].y  =   TEXTURE_HEIGHT;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -TEXTURE_WIDTH; // ���_3
		VBuffer[2].y  =  -TEXTURE_HEIGHT;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   TEXTURE_WIDTH; // ���_�Q	
		VBuffer[3].y  =  -TEXTURE_HEIGHT;	
		VBuffer[3].z  =   0.0f;

		VBuffer[0].nx =  0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);

	/*	if(m_uMoveType>= MOVE_TYPE_MAX)
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
		VBuffer[3].tv =  m_uMoveType * m_vVerTexSizeH + m_vVerTexSizeH;*/

		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}

}