//=======================================================================================
//
//	�V�F�[�_��`
//
//=======================================================================================
#ifndef _H_SHADER
#define _H_SHADER

//-------- �w�b�_
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"

//-------- �v���g�^�C�v�錾
HRESULT InitShader();	// ������
void BeginShader(int nTechnique = 0);	// �V�F�[�_�J�n
void SetCameraShader(LPD3DXVECTOR3 pCamera, LPD3DXMATRIX pView, LPD3DXMATRIX pProj);
void SetLightShader(LPD3DXVECTOR3 pLight);
void SetWorldMatrixShader(LPD3DXMATRIX pWorld);
void SetMaterialShader(D3DMATERIAL9* pMaterial, LPDIRECT3DTEXTURE9 pTexture);
void EndShader();		// �V�F�[�_�I��
void FinShader();		// ���
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture);

#endif

//=======================================================================================
//	End of File
//=======================================================================================