// �����_�����O �^�[�Q�b�g�؂�ւ�
#pragma once

// �w�b�_
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"

// �֐��v���g�^�C�v
HRESULT InitRenderTarget();								// ����
void FinRenderTarget();									// ���
LPDIRECT3DTEXTURE9 GetRenderTexture(int nTarget = 0, int nMulti = 0);// �Q��
void SaveRenderTarget();								// �ޔ�
void ChangeRenderTarget(int nTarget = 0);				// �؂�ւ�
void ResetRenderTarget();								// ���ɖ߂�