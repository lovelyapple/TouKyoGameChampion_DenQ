// �����_�����O �^�[�Q�b�g�؂�ւ�
#include "Sys_RenderTarget.h"

// �����e�N�X�`����
#define MAX_TARGET	2

// �����_�����O �^�[�Q�b�g
static LPDIRECT3DTEXTURE9 g_pTexture[MAX_TARGET][2];
static LPDIRECT3DSURFACE9 g_pSurface[MAX_TARGET][2];
static LPDIRECT3DSURFACE9 g_pZBuffer[MAX_TARGET];

// �o�b�N�o�b�t�@�ޔ�
static LPDIRECT3DSURFACE9 g_pSaveBB;
static LPDIRECT3DSURFACE9 g_pSaveZB;

// ����
HRESULT InitRenderTarget()
{
	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_TARGET && SUCCEEDED(hr); ++i) {
		// �����_�����O�p�e�N�X�`������
		hr = g_pD3DDevice->CreateTexture(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN, 1,
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture[i][0], NULL);
		// �����_�����O�p�T�[�t�F�X�擾
		if (SUCCEEDED(hr)) {
			hr = g_pTexture[i][0]->GetSurfaceLevel(0, &g_pSurface[i][0]);
		}
		if (i == 0) {
			// �}���`�����_�[�^�[�Q�b�g�p�e�N�X�`������
			hr = g_pD3DDevice->CreateTexture(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN, 1,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture[i][1], NULL);
			// �}���`�����_�[�^�[�Q�b�g�p�T�[�t�F�X�擾
			if (SUCCEEDED(hr)) {
				hr = g_pTexture[i][1]->GetSurfaceLevel(0, &g_pSurface[i][1]);
			}
		} else {
			g_pTexture[i][1] = NULL;
			g_pSurface[i][1] = NULL;
		}
		// �����_�����O�pZ�o�b�t�@����
		if (SUCCEEDED(hr)) {
			hr = g_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH_WIN, SCREEN_HEIGHT_WIN,
				D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &g_pZBuffer[i], NULL);
		}
	}
	return hr;
}

// ���
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

// �Q��
LPDIRECT3DTEXTURE9 GetRenderTexture(int nTarget, int nMulti)
{
	if (nTarget < 0 || nTarget >= MAX_TARGET ||
		nMulti < 0 || nMulti >= 2) {
		return NULL;
	}
	return g_pTexture[nTarget][nMulti];
}

// ���݂̃����_�����O �^�[�Q�b�g��ޔ�
void SaveRenderTarget()
{
	// �o�b�N�o�b�t�@�ޔ�
	g_pD3DDevice->GetRenderTarget(0, &g_pSaveBB);
	// Z�o�b�t�@�ޔ�
	g_pD3DDevice->GetDepthStencilSurface(&g_pSaveZB);
}

// �����_�����O �^�[�Q�b�g�؂�ւ�
void ChangeRenderTarget(int nTarget)
{
	if (nTarget < 0 || nTarget >= MAX_TARGET) {
		return;
	}
	// �^�[�Q�b�g �e�N�X�`���ݒ�
	g_pD3DDevice->SetRenderTarget(0, g_pSurface[nTarget][0]);
	g_pD3DDevice->SetRenderTarget(1, g_pSurface[nTarget][1]);
	// Z�o�b�t�@�ݒ�
	g_pD3DDevice->SetDepthStencilSurface(g_pZBuffer[nTarget]);
	// �r���[�|�[�g��������
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}

// �����_�����O �^�[�Q�b�g�����ɖ߂�
void ResetRenderTarget()
{
	g_pD3DDevice->SetRenderTarget(0, g_pSaveBB);
	g_pD3DDevice->SetRenderTarget(1, NULL);
	g_pD3DDevice->SetDepthStencilSurface(g_pSaveZB);
}