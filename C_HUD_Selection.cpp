//-----------------------------------------------------------
//PasuMenu
//-----------------------------------------------------------

//--------------------------------------
//�V�X�e���C���N���[�h
#include "C_HUD_Selection.h"
c_Selection::c_Selection(LPCSTR fzName,D3DXVECTOR3 size)
{
	this->m_pszFName = fzName;
	m_vSize			 = size;
	m_fAlpha		  =1.0f;

}
c_Selection::~c_Selection()
{
}

void c_Selection::Update(void)
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

	this->SetVerTexBuff();
}
void c_Selection::SetAlpha(float fAlpha)
{
	m_fAlpha = fAlpha;
}

void c_Selection::SetVerTexBuff(void)
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

		VBuffer[0].nx =  0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;
		VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;
		VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;
		VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
	}
}