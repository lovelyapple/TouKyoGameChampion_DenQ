//============================================================================
//C_2D_Master.h
//============================================================================
//-----------------------------------
//�V�X�e���C���N���[�h
#include "C_Master_2DBase.h"
#include "Sys_Macro.h"
c_2DMaster::c_2DMaster()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vMove);

	m_bAnimation	= false;
	m_nRecFrame		= 0;
	m_nMaxFrame		= 0;
	m_fFrameSize	= 1.0f;

	m_fTexSizeNor.x	= 0.0f;
	m_fTexSizeNor.y	= 0.0f;

	m_fTexSizePro.x	= 0.0f;
	m_fTexSizePro.y	= 0.0f;

	m_nAlphaPeriod  = 0;
	m_nAlphaTime	= 0;
	m_fAlpha		= 0.0f;

}
c_2DMaster::~c_2DMaster()
{
}
void c_2DMaster::SetpTexture(LPDIRECT3DTEXTURE9 *pTexture)
{
	m_pTexture = *pTexture;
}

HRESULT c_2DMaster::MakeVertex(void)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}
{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = m_vPos.x - m_fTexSizePro.x;
		pVtx[0].pos.y = m_vPos.y - m_fTexSizePro.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_vPos.x;
		pVtx[1].pos.y = m_vPos.y - m_fTexSizePro.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_vPos.x;
		pVtx[2].pos.y = m_vPos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_vPos.x + m_fTexSizePro.x;
		pVtx[3].pos.y = m_vPos.y;
		pVtx[3].pos.z = 0.0f;
		// rhw�̐ݒ�
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
	return S_OK;
}
void c_2DMaster::SetVerTex(void)
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = m_vPos.x - m_fTexSizePro.x;
	pVtx[0].pos.y = m_vPos.y - m_fTexSizePro.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_vPos.x;
	pVtx[1].pos.y = m_vPos.y - m_fTexSizePro.y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_vPos.x;
	pVtx[2].pos.y = m_vPos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_vPos.x + m_fTexSizePro.x;
	pVtx[3].pos.y = m_vPos.y;
	pVtx[3].pos.z = 0.0f;
	// rhw�̐ݒ�
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f,1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}
void c_2DMaster::Update(void)
{
	SetVerTex();
}
void c_2DMaster::Uninit(void)
{
	if(m_pTexture != NULL)
	{// �e�N�X�`���̊J��
		m_pTexture = NULL;
	}

	if(m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
void c_2DMaster::Draw(void)
{
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	g_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	g_pD3DDevice->SetTexture(0,m_pTexture);

	// �|���S���̕`��
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//set
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//in
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//set
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// out

}

//============================================================================
//End of  File
//============================================================================