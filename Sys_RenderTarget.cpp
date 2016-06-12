// レンダリング ターゲット切り替え
#include "Sys_RenderTarget.h"

// 生成テクスチャ数
#define MAX_TARGET	2

// レンダリング ターゲット
static LPDIRECT3DTEXTURE9 g_pTexture[MAX_TARGET][2];
static LPDIRECT3DSURFACE9 g_pSurface[MAX_TARGET][2];
static LPDIRECT3DSURFACE9 g_pZBuffer[MAX_TARGET];

// バックバッファ退避
static LPDIRECT3DSURFACE9 g_pSaveBB;
static LPDIRECT3DSURFACE9 g_pSaveZB;

// 生成
HRESULT InitRenderTarget()
{
	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_TARGET && SUCCEEDED(hr); ++i) {
		// レンダリング用テクスチャ生成
		hr = g_pD3DDevice->CreateTexture(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN, 1,
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture[i][0], NULL);
		// レンダリング用サーフェス取得
		if (SUCCEEDED(hr)) {
			hr = g_pTexture[i][0]->GetSurfaceLevel(0, &g_pSurface[i][0]);
		}
		if (i == 0) {
			// マルチレンダーターゲット用テクスチャ生成
			hr = g_pD3DDevice->CreateTexture(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN, 1,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture[i][1], NULL);
			// マルチレンダーターゲット用サーフェス取得
			if (SUCCEEDED(hr)) {
				hr = g_pTexture[i][1]->GetSurfaceLevel(0, &g_pSurface[i][1]);
			}
		} else {
			g_pTexture[i][1] = NULL;
			g_pSurface[i][1] = NULL;
		}
		// レンダリング用Zバッファ生成
		if (SUCCEEDED(hr)) {
			hr = g_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN,
				D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &g_pZBuffer[i], NULL);
		}
	}
	return hr;
}

// 解放
void FinRenderTarget()
{
	for (int i = 0; i < MAX_TARGET; ++i) {
		SAFE_RELEASE(g_pZBuffer[i]);
		for (int j = 0; j < 2; ++j) {
			SAFE_RELEASE(g_pSurface[i][j]);
			SAFE_RELEASE(g_pTexture[i][j]);
		}
	}
}

// 参照
LPDIRECT3DTEXTURE9 GetRenderTexture(int nTarget, int nMulti)
{
	if (nTarget < 0 || nTarget >= MAX_TARGET ||
		nMulti < 0 || nMulti >= 2) {
		return NULL;
	}
	return g_pTexture[nTarget][nMulti];
}

// 現在のレンダリング ターゲットを退避
void SaveRenderTarget()
{
	// バックバッファ退避
	g_pD3DDevice->GetRenderTarget(0, &g_pSaveBB);
	// Zバッファ退避
	g_pD3DDevice->GetDepthStencilSurface(&g_pSaveZB);
}

// レンダリング ターゲット切り替え
void ChangeRenderTarget(int nTarget)
{
	if (nTarget < 0 || nTarget >= MAX_TARGET) {
		return;
	}
	// ターゲット テクスチャ設定
	g_pD3DDevice->SetRenderTarget(0, g_pSurface[nTarget][0]);
	g_pD3DDevice->SetRenderTarget(1, g_pSurface[nTarget][1]);
	// Zバッファ設定
	g_pD3DDevice->SetDepthStencilSurface(g_pZBuffer[nTarget]);
	// ビューポート内を消去
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}

// レンダリング ターゲットを元に戻す
void ResetRenderTarget()
{
	g_pD3DDevice->SetRenderTarget(0, g_pSaveBB);
	g_pD3DDevice->SetRenderTarget(1, NULL);
	g_pD3DDevice->SetDepthStencilSurface(g_pSaveZB);
}