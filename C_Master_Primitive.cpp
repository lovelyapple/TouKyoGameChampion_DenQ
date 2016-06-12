//============================================================================
//Ship.h
//============================================================================
//-----------------------------------
//�V�X�e���C���N���[�h
#include "C_Master_Primitive.h"
c_Master_Primitive::c_Master_Primitive()
{
	ResetPrimitive();
}
c_Master_Primitive::c_Master_Primitive(LPCSTR fzName)
{
	ResetPrimitive();
	m_pszFName		= fzName;

}
void	c_Master_Primitive::SetFileName(LPCSTR fzName)
{
	m_pszFName = fzName;
}

void c_Master_Primitive::ResetPrimitive(void)
{
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vRot);
	D3DV_INIT(m_vOblique[0]);
	D3DV_INIT(m_vOblique[1]);
	D3DV_INIT(m_vSizeUV);
	D3DM_INIT(m_mMatrix);
	m_bWatchCamera	= false;
	m_pszFName		= FILE_NAME_DEAULT_PRIMITIVE;
	m_pD3DVertexBuffer	= NULL;
	m_pD3DTexture		= NULL;
	m_vSize.x			= 1.0f;
	m_vSize.y			= 1.0f;
	m_vSize.z			= 0.0f;
}
HRESULT c_Master_Primitive::Init()
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^
	//short*				IBuffer;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	// ���_�o�b�t�@�쐬
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(DVERTEX_PRIMITIVE) * 4, 0, 0, D3DPOOL_DEFAULT,
															&m_pD3DVertexBuffer, NULL))) {
		MessageBox(g_hWnd, _T("���_�o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), m_pszFName, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	//// �C���f�b�N�X�o�b�t�@�쐬
	//if(FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(short) * 4, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
	//														&g_pD3DIndexBuffer, NULL))) {
	//	MessageBox(g_hWnd, _T("�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	//	return E_FAIL;
	//}

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
		VBuffer[0].x  =  -2.0f;	VBuffer[0].y  =  4.0f;	VBuffer[0].z  =   0.0f;	// ���_�O
		VBuffer[0].nx =    0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[0].tu  =   0.0f;	VBuffer[0].tv  =  0.0f;
		
		VBuffer[1].x  =   2.0f;	VBuffer[1].y  =  4.0f;	VBuffer[1].z  =   0.0f;	// ���_�P
		VBuffer[1].nx =    0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].tu  =   1.0f;	VBuffer[1].tv  =  0.0f;

		VBuffer[2].x  =  -2.0f;	VBuffer[2].y  =   0.0f;	VBuffer[2].z  =   0.0f;	// ���_3
		VBuffer[2].nx =    0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].tu  =    0.0f;	VBuffer[2].tv  =  1.0f;

		VBuffer[3].x  =   2.0f;	VBuffer[3].y  =   0.0f;	VBuffer[3].z  =   0.0f;	// ���_�Q
		VBuffer[3].nx =    0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].tu  =    1.0f;	VBuffer[3].tv  =  1.0f;


		m_pD3DVertexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	}
	//// �C���f�b�N�X�o�b�t�@�ɒl���Z�b�g
	//if (FAILED(g_pD3DIndexBuffer->Lock(0, 0, (LPVOID*)&IBuffer, 0))) {
	//	MessageBox(NULL, _T("�C���f�b�N�X�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	//} else {
	//	IBuffer[0] = 0;			// ���_�O
	//	IBuffer[1] = 1;			// ���_�P
	//	IBuffer[2] = 2;			// ���_�Q
	//	IBuffer[3] = 3;			// ���_�Q
	//	g_pD3DIndexBuffer->Unlock();					// �o�b�t�@���A�����b�N
	//}

	return S_OK;
}

c_Master_Primitive::~c_Master_Primitive()
{
		Uninit();
}

void c_Master_Primitive::Uninit(void)
{
	if(m_pD3DVertexBuffer)
	{
		m_pD3DVertexBuffer->Release();
		m_pD3DVertexBuffer = NULL;
	}
	if(m_pD3DTexture)
	{
		m_pD3DTexture->Release();
		m_pD3DTexture = NULL;
	}

}
void c_Master_Primitive::SetWatchCamera(bool input)
{
	m_bWatchCamera = input;
}

void c_Master_Primitive::SetPos(D3DXVECTOR3 Pos)
{
	m_vPos = Pos;
}
void c_Master_Primitive::SetRot(D3DXVECTOR3 Rot)
{
	m_vRot = Rot;
}

void c_Master_Primitive::UpdatePrimitive(void)
{
	D3DXMATRIX	matRotate;		// ��]�}�g���b�N�X
	D3DXMATRIX	matTrans;		// ���s�ړ��}�g���b�N�X
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;
	D3DM_INIT(m_mMatrix);

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
	SetVerTexBuff();
}

void c_Master_Primitive::UpdateCageStyle()
{
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
	SetVerTexBuffCageStylePos();
}

void c_Master_Primitive::SetVerTexBuff(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	 -m_vSize.x;	// ���_�O
		VBuffer[0].y  =   m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   m_vSize.x;	// ���_�P
		VBuffer[1].y  =   m_vSize.y;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -m_vSize.x; // ���_3
		VBuffer[2].y  =  -m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   m_vSize.x; // ���_�Q	
		VBuffer[3].y  =  -m_vSize.y;	
		VBuffer[3].z  =   0.0f;

		VBuffer[0].nx =   0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;		
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[1].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[2].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
		VBuffer[3].color = D3DCOLOR_ARGB(0xff,0xff,0xff,0xff);
	}
}
void c_Master_Primitive::SetVerTexBuffCageStylePos(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].x  =	  m_vOblique[0].x + 0.0f;//m_vSize.x;	// ���_�O
		VBuffer[0].y  =   m_vOblique[0].y + m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   m_vOblique[0].x + m_vSize.x;	// ���_�P
		VBuffer[1].y  =   m_vOblique[0].y + m_vSize.y;	
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =   m_vOblique[1].x + 0.0f; // ���_3
		VBuffer[2].y  =   m_vOblique[1].y - m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   m_vOblique[1].x + m_vSize.x; // ���_�Q	
		VBuffer[3].y  =   m_vOblique[1].y - m_vSize.y;	
		VBuffer[3].z  =   0.0f;


	}
}
void c_Master_Primitive::SetVerTexBuffUV(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].tu =	  m_vSizeUV.x * m_nRecUVFrameX;	
		VBuffer[0].tv =   m_vSizeUV.y * m_nRecUVFrameY;	

		VBuffer[1].tu =   m_vSizeUV.x * m_nRecUVFrameX + m_vSizeUV.x;	
		VBuffer[1].tv =   m_vSizeUV.y * m_nRecUVFrameY;	

		VBuffer[2].tu =   m_vSizeUV.x * m_nRecUVFrameX;	
		VBuffer[2].tv =   m_vSizeUV.y * m_nRecUVFrameY + m_vSizeUV.y;

		VBuffer[3].tu =   m_vSizeUV.x * m_nRecUVFrameX + m_vSizeUV.x;	
		VBuffer[3].tv =   m_vSizeUV.y * m_nRecUVFrameY + m_vSizeUV.y;	

	}
}
void c_Master_Primitive::SetVerTexBuffAlpha(float Alpha)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// ���_�o�b�t�@�ւ̃|�C���^	// ���_�o�b�t�@�ɒl���Z�b�g
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(Alpha * 255));
		VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(Alpha * 255));
		VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(Alpha * 255));
		VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(Alpha * 255));
	}
}

void c_Master_Primitive::Release(void)
{
	SAFE_RELEASE(m_pD3DTexture);				// �e�N�X�`���I�u�W�F�N�g�����
	SAFE_RELEASE(m_pD3DVertexBuffer);			// ���_�o�b�t�@�I�u�W�F�N�g�����
}
void c_Master_Primitive::DrawAntialiasing(void)
{
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_NONE);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_NONE);

	// ���ߐF(�����F)�̕�����Z�o�b�t�@�ɏ������܂Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �`��ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ���C�e�B���O���Ȃ�
	
	//���[���h�ϊ��ݒ�
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// ���_�o�b�t�@��o�^
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//�����_�[�ݒ�̕���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);
}

void c_Master_Primitive::DrawPrimitive(void)
{
	// ���ߐF(�����F)���\�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ���u�����h��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���ߐF(�����F)�̕�����Z�o�b�t�@�ɏ������܂Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �`��ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ���C�e�B���O���Ȃ�
	
	//���[���h�ϊ��ݒ�
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// ���_�o�b�t�@��o�^
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//�����_�[�ݒ�̕���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��

}
void c_Master_Primitive::DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture)
{
	// ���ߐF(�����F)���\�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ���u�����h��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ���ߐF(�����F)�̕�����Z�o�b�t�@�ɏ������܂Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �`��ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// ���C�e�B���O���Ȃ�
	
	//���[���h�ϊ��ݒ�
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D_PRIM);
	g_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(DVERTEX_PRIMITIVE));	// ���_�o�b�t�@��o�^
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);	
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//�����_�[�ݒ�̕���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��
}

void c_Master_Primitive::SetTexRecUVFrame(int nFrameX,int nFrameY)
{
	m_nRecUVFrameX = nFrameX;
	m_nRecUVFrameY = nFrameY;
}

void c_Master_Primitive::SetTexUV(D3DXVECTOR3 UV)
{
	m_vSizeUV = UV;
}
void c_Master_Primitive::SetSize(D3DXVECTOR3 size)
{
	m_vSize = size;
}
D3DXMATRIX		c_Master_Primitive::GetMatrix(void)
{
	return m_mMatrix;
}
D3DXVECTOR3	c_Master_Primitive::GetPos(void)
{
	return m_vPos;
}
D3DXVECTOR3	c_Master_Primitive::GetSize(void)
{
	return m_vSize;
}

void c_Master_Primitive::SetOblique(D3DXVECTOR3* input)
{
	m_vOblique[0] = input[0];
	m_vOblique[1] = input[1];
}