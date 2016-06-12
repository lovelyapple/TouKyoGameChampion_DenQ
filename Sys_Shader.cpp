//=======================================================================================
//
//	�V�F�[�_����
//
//=======================================================================================

//-------- �w�b�_
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Sys_Shader.h"


//-------- �萔
#define PATH_FXTEST		_T("data/Sys_File/Lighting.fx")
#define MAX_TECHNIQUE	4

//-------- �O���[�o���ϐ�
LPD3DXEFFECT	g_pFX;		// �G�t�F�N�g �I�u�W�F�N�g
D3DXHANDLE		g_hMatWVP;	// ���[���h�~�r���[�~�ˉe
D3DXHANDLE		g_hMatW;	// ���[���h �}�g���b�N�X
D3DXHANDLE		g_hCamera;	// ���_���W
D3DXHANDLE		g_hLight;	// �����x�N�g��
D3DXHANDLE		g_hDiffuse;	// (�}�e���A��)�g�U�F
D3DXHANDLE		g_hSpecular;// (�}�e���A��)���ʔ��ːF
D3DXHANDLE		g_hPower;	// (�}�e���A��)���ʔ��ˎw��
D3DXHANDLE		g_hAmbient;	// (�}�e���A��)���F
D3DXHANDLE		g_hTexture;	// �e�N�X�`��
D3DXHANDLE		g_hTexEnable;// �e�N�X�`���L��
D3DXHANDLE		g_hTech[MAX_TECHNIQUE];	// �e�N�j�b�N

static D3DXVECTOR3	g_vLight;
static D3DXVECTOR3	g_vCamera;
static D3DXMATRIX	g_mView;
static D3DXMATRIX	g_mProj;

//---------------------------------------------------------------------------------------
// �V�F�[�_������
//---------------------------------------------------------------------------------------
HRESULT InitShader()
{
	// �V�F�[�_�ǂݍ���
	HRESULT hr = D3DXCreateEffectFromFile(g_pD3DDevice,
		PATH_FXTEST, NULL, NULL, 0, NULL, &g_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("�V�F�[�_(%s)�ǂݍ��݃G���["),
			PATH_FXTEST);
		MessageBox(g_hWnd, szMsg, _T("error"), MB_OK);
		return hr;
	}
	// �n���h���擾
	struct _param {
		LPCSTR		pszName;
		D3DXHANDLE*	pHandle;
	} param[] = {
		{"WORLDVIEWPROJECTION", &g_hMatWVP},
		{"WORLD",				&g_hMatW},
		{"CAMERAPOSITION",		&g_hCamera},
		{"MATERIALDIFFUSE",		&g_hDiffuse},
		{"MATERIALSPECULAR",	&g_hSpecular},
		{"MATERIALPOWER",		&g_hPower},
		{"MATERIALAMBIENT",		&g_hAmbient},
		{"MATERIALTEXTURE",		&g_hTexture},
		{"MATERIALTEXTUREVALID", &g_hTexEnable},
	};
	for (int i = 0; i < _countof(param); i++) {
		*param[i].pHandle =
			g_pFX->GetParameterBySemantic(NULL,
									param[i].pszName);
	}
	g_hLight = g_pFX->GetParameterByName(NULL, "light");
	for (int i = 0; i < MAX_TECHNIQUE; ++i) {
		g_hTech[i] = g_pFX->GetTechnique(i);
	}

	return hr;
}

//---------------------------------------------------------------------------------------
// �J�������ݒ�
//---------------------------------------------------------------------------------------
void SetCameraShader(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	g_vCamera = *pCamera;
	g_mView = *pView;
	g_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// �����x�N�g���ݒ�
//---------------------------------------------------------------------------------------
void SetLightShader(LPD3DXVECTOR3 pLight)
{
	g_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// �V�F�[�_�J�n
//---------------------------------------------------------------------------------------
void BeginShader(int nTechnique)
{
	if (nTechnique < 0 || nTechnique >= MAX_TECHNIQUE) {
		nTechnique = 0;
	}
	// �e�N�j�b�N�ݒ�
	g_pFX->SetTechnique(g_hTech[nTechnique]);
	g_pFX->Begin(NULL, 0);
	// �p�X�J�n
	g_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ���[���h�ϊ��s��ݒ�(&�V�F�[�_�֐ݒ�)
//---------------------------------------------------------------------------------------
void SetWorldMatrixShader(LPD3DXMATRIX pWorld)
{
	g_pFX->SetMatrix(g_hMatWVP,
		&(*pWorld * g_mView * g_mProj));
	g_pFX->SetMatrix(g_hMatW, pWorld);
	g_pFX->SetFloatArray(g_hLight, &g_vLight.x, 4);
	g_pFX->SetFloatArray(g_hCamera, &g_vCamera.x, 3);
}

//---------------------------------------------------------------------------------------
// �}�e���A���ݒ�(&�R�~�b�g)
//---------------------------------------------------------------------------------------
void SetMaterialShader(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture)
{
	if (pMaterial) {
		g_pFX->SetVector(g_hDiffuse,
			(LPD3DXVECTOR4)&pMaterial->Diffuse);
		g_pFX->SetVector(g_hSpecular,
			(LPD3DXVECTOR4)&pMaterial->Specular);
		g_pFX->SetFloat(g_hPower, pMaterial->Power);
		g_pFX->SetVector(g_hAmbient,
			(LPD3DXVECTOR4)&pMaterial->Ambient);
	}
	if (pTexture) {
		g_pFX->SetTexture(g_hTexture, pTexture);
		g_pFX->SetBool(g_hTexEnable, TRUE);
	} else {
		g_pFX->SetBool(g_hTexEnable, FALSE);
	}
	g_pFX->CommitChanges();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_�I��
//---------------------------------------------------------------------------------------
void EndShader()
{
	// �p�X�I��
	g_pFX->EndPass();
	// �e�N�j�b�N�I��
	g_pFX->End();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_���
//---------------------------------------------------------------------------------------
void FinShader()
{
	SAFE_RELEASE(g_pFX);
}

// �e�N�X�`���ݒ�
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture)
{
	g_pFX->SetTexture(hTexture, pTexture);
}

//=======================================================================================
//	End of File
//=======================================================================================