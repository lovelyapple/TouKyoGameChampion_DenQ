//-----------------------------------------------------------
//カメラマスタークラスcpp
//-----------------------------------------------------------
#include "C_Master_Camera.h"
D3DXMATRIX*	g_matView;
c_Camera::c_Camera()
{
	D3DM_INIT(m_matProj);
	D3DM_INIT(m_matView);
	D3DV_INIT(m_vCamera);
	D3DV_INIT(m_vRot);
	//D3DV_INIT(m_vAngle);
	InitCamera(true);
}
HRESULT c_Camera::InitCamera(bool bWindow)
{
	float fAspect_ratio = ASPECT_RATIO_WIN;
	if(bWindow == false)
		fAspect_ratio = ASPECT_RATIO_FULL;
	//プロジェクション・マトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_matProj,
		D3DXToRadian(FOVY),
		fAspect_ratio,
		NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_matProj);

	//ビュー　マトリックス設定　//設定しなくてもよい
	m_vCamera = 
		D3DXVECTOR3(SCREEN_WIDTH_WIN * 0.5f,		// 視点座標(X)
					 0.0f,							// 視点座標(Y)
					 -SCREEN_HEIGHT_WIN * 0.5f / tanf(D3DXToRadian(FOVY) * 0.5f));	// 視点座標(Z)



	D3DXMatrixLookAtLH(&m_matView,
		&m_vCamera,	// 視点座標(Z)
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 注視点座標
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// アップベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	g_matView = &m_matView;
	return S_OK;
}
void c_Camera::Update(void)
{
	//D3DXVec3TransformCoord(&m_vCamera,
	//	&D3DXVECTOR3(0.0f,150.0f,-300.0f),
	//	&GetModelMatrix());

	//D3DXVECTOR3 vLook;
	//D3DXVec3TransformCoord(&vLook,
	//	&D3DXVECTOR3(0.0f,100.0f,0.0f),
	//	&GetModelMatrix());

	//D3DXVECTOR3 vUP;
	//D3DXVec3TransformNormal(&vUP,
	//	&D3DXVECTOR3(0.0f,1.0f,0.0f),
	//	&GetModelMatrix());

	//D3DXMatrixLookAtLH(&m_matView,
	//	&m_vCamera,&vLook,&vUP);
	//D3DM_INIT(m_matView);
	//D3DXMatrixTranslation(&m_matView,m_vCamera.x,m_vCamera.y,m_vCamera.z);
}
//---------------------------------------------------------------------------------------
// カメラ設定 (全ての描画より先に呼び出す必要がある)
//---------------------------------------------------------------------------------------
void c_Camera::Draw()
{
	// プロジェクション マトリックス設定
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	// ビュー マトリックス設定
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	SetCameraShader(&m_vCamera, &m_matView, &m_matProj);
}
void c_Camera::UninitCamera(void)
{
	//do Noth
}

