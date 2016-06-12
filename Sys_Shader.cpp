//=======================================================================================
//
//	シェーダ処理
//
//=======================================================================================

//-------- ヘッダ
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Sys_Shader.h"


//-------- 定数
#define PATH_FXTEST		_T("data/Sys_File/Lighting.fx")
#define MAX_TECHNIQUE	4

//-------- グローバル変数
LPD3DXEFFECT	g_pFX;		// エフェクト オブジェクト
D3DXHANDLE		g_hMatWVP;	// ワールド×ビュー×射影
D3DXHANDLE		g_hMatW;	// ワールド マトリックス
D3DXHANDLE		g_hCamera;	// 視点座標
D3DXHANDLE		g_hLight;	// 光源ベクトル
D3DXHANDLE		g_hDiffuse;	// (マテリアル)拡散色
D3DXHANDLE		g_hSpecular;// (マテリアル)鏡面反射色
D3DXHANDLE		g_hPower;	// (マテリアル)鏡面反射指数
D3DXHANDLE		g_hAmbient;	// (マテリアル)環境色
D3DXHANDLE		g_hTexture;	// テクスチャ
D3DXHANDLE		g_hTexEnable;// テクスチャ有無
D3DXHANDLE		g_hTech[MAX_TECHNIQUE];	// テクニック

static D3DXVECTOR3	g_vLight;
static D3DXVECTOR3	g_vCamera;
static D3DXMATRIX	g_mView;
static D3DXMATRIX	g_mProj;

//---------------------------------------------------------------------------------------
// シェーダ初期化
//---------------------------------------------------------------------------------------
HRESULT InitShader()
{
	// シェーダ読み込み
	HRESULT hr = D3DXCreateEffectFromFile(g_pD3DDevice,
		PATH_FXTEST, NULL, NULL, 0, NULL, &g_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("シェーダ(%s)読み込みエラー"),
			PATH_FXTEST);
		MessageBox(g_hWnd, szMsg, _T("error"), MB_OK);
		return hr;
	}
	// ハンドル取得
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
// カメラ情報設定
//---------------------------------------------------------------------------------------
void SetCameraShader(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	g_vCamera = *pCamera;
	g_mView = *pView;
	g_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// 光源ベクトル設定
//---------------------------------------------------------------------------------------
void SetLightShader(LPD3DXVECTOR3 pLight)
{
	g_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// シェーダ開始
//---------------------------------------------------------------------------------------
void BeginShader(int nTechnique)
{
	if (nTechnique < 0 || nTechnique >= MAX_TECHNIQUE) {
		nTechnique = 0;
	}
	// テクニック設定
	g_pFX->SetTechnique(g_hTech[nTechnique]);
	g_pFX->Begin(NULL, 0);
	// パス開始
	g_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ワールド変換行列設定(&シェーダへ設定)
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
// マテリアル設定(&コミット)
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
// シェーダ終了
//---------------------------------------------------------------------------------------
void EndShader()
{
	// パス終了
	g_pFX->EndPass();
	// テクニック終了
	g_pFX->End();
}

//---------------------------------------------------------------------------------------
// シェーダ解放
//---------------------------------------------------------------------------------------
void FinShader()
{
	SAFE_RELEASE(g_pFX);
}

// テクスチャ設定
void SetTexture(D3DXHANDLE hTexture, LPDIRECT3DTEXTURE9 pTexture)
{
	g_pFX->SetTexture(hTexture, pTexture);
}

//=======================================================================================
//	End of File
//=======================================================================================