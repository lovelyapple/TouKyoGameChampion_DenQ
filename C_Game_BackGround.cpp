//-----------------------------------------------------------
//�X�e�[�W�N���X
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h"
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Game_BackGround.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
c_StageBG::c_StageBG(LPCSTR File,D3DXVECTOR3 pos):c_Model(File,pos)
{
	this->CleanArray();
}
c_StageBG::~c_StageBG()
{
}
void c_StageBG::Update(void)
{
	D3DXMATRIX matRot, matMove;
	D3DXMatrixRotationYawPitchRoll(&matRot, 
								m_vAngle.y, 
								m_vAngle.x,
								m_vAngle.z);
	D3DXMatrixRotationY(&matRot,m_vAngle.y);
	D3DXMatrixTranslation(&matMove, 
								m_vPos.x, 
								m_vPos.y, 
								m_vPos.z);
	D3DXMatrixMultiply(&m_matrix, &matRot, &matMove);
}
void c_StageBG::ShaderDraw(void)
{
	if(m_pModel)
	{
		// ���[���h�ϊ��ݒ�
		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matrix);

		SetWorldMatrixShader(&this->m_matrix);

		// �T�u�Z�b�g���̕`��
		for (DWORD i = 0; i < m_pModel->dwNumAttr; i++) 
		{
			DWORD id = m_pModel->pAttr[i].AttribId;
			//g_pD3DDevice->SetMaterial(&m_pModel->pMtrl[id]);
			//g_pD3DDevice->SetTexture(0, m_pModel->pTexture[id]);
			SetMaterialShader(&m_pModel->pMtrl[id],m_pModel->pTexture[id]);
			m_pModel->pMesh->DrawSubset(id);

		}
	}
}
