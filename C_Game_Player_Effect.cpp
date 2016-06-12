//-----------------------------------------------------------
//プレイヤークラス
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_Global_Variable.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
#include "C_Game_Player_Effect.h"

c_PlayerLight::c_PlayerLight(c_Player* pPlayer)
{

	m_pszFName	= FILE_NAME_PLAYERLIGHT;
	m_pPlayer	= NULL;
	m_fAlpha	= 0.1f;
	m_pPlayer	= pPlayer;
}
c_PlayerLight::~c_PlayerLight()
{
	m_pPlayer = NULL;
}
void c_PlayerLight::Update(void)
{

	this->m_vPos = m_pPlayer->GetPos();
	m_vPos.z -= PLAYER_EFFECT_LIGHT_NEAR_POS;//ブロックの前に置く
	if(m_bUse)
	{
		m_fAlpha += PLAYER_EFFECT_LIGHT_ALPH_CHANGE;
		if(m_fAlpha >= PLAYER_EFFECT_LIGHT_MAX_ALPH)
			m_fAlpha = PLAYER_EFFECT_LIGHT_MAX_ALPH;

		this->m_vSize.x += PLAYER_EFFECT_LIGHT_SIZE_CHANGE;	
		if(m_vSize.x > PLAYER_EFFECT_LIGHT_MAX_SIZE) 
			m_vSize.x = PLAYER_EFFECT_LIGHT_MAX_SIZE;

		this->m_vSize.y += PLAYER_EFFECT_LIGHT_SIZE_CHANGE;	
		if(m_vSize.y > PLAYER_EFFECT_LIGHT_MAX_SIZE) 
			m_vSize.y = PLAYER_EFFECT_LIGHT_MAX_SIZE;
		
	}
	else
	{
		m_fAlpha -= PLAYER_EFFECT_LIGHT_ALPH_CHANGE * 1.4f;
		m_vSize.x *= 0.99f;
		m_vSize.y *= 0.99f;
		if(m_fAlpha <= 0)
		{
			m_fAlpha = 0.0f;
			m_vSize.x = PLAYER_EFFECT_LIGHT_MIN_SIZE;
			m_vSize.y = PLAYER_EFFECT_LIGHT_MIN_SIZE;
		}
	}

	D3DXMATRIX	matRotate;		// 回転マトリックス
	D3DXMATRIX	matTrans;		// 平行移動マトリックス
	D3DXMATRIX*	pmatInv;
	D3DXVECTOR3 vDir;

	D3DXMatrixRotationYawPitchRoll(&matRotate,m_vRot.y,m_vRot.x,m_vRot.z);	// 回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);	// 平行移動マトリックスを生成

	m_mMatrix = matRotate * matTrans;
	if(m_bWatchCamera)
	{
		pmatInv = &m_mMatrix;
		float _41 = m_mMatrix._41;
		float _42 = m_mMatrix._42;
		float _43 = m_mMatrix._43;
		D3DXMatrixInverse(pmatInv, NULL, g_matView);
		pmatInv->_41 = _41;  //オフセットを切る（回転行列だけにして）
		pmatInv->_42 = _42;
		pmatInv->_43 = _43;
	}
	SetVerTexBuff();
	
}
void c_PlayerLight::GetPlayerLight(bool light)
{
	m_bUse = light;
}

void c_PlayerLight::SetVerTexBuff(void)
{
	DVERTEX_PRIMITIVE*	VBuffer;								// 頂点バッファへのポインタ	// 頂点バッファに値をセット
	if (FAILED(m_pD3DVertexBuffer->Lock(0, 0, (LPVOID*)&VBuffer, 0))) 
	{		
		MessageBox(NULL, _T("頂点バッファのロックに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
	} 
	else 
	{
		
		
		VBuffer[0].x  =	 -(float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.x; // 頂点０
		VBuffer[0].y  =   (float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.y;		
		VBuffer[0].z  =   0.0f;	

		VBuffer[1].x  =   (float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.x; // 頂点１
		VBuffer[1].y  =   (float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.y;
		VBuffer[1].z  =   0.0f;

		VBuffer[2].x  =  -(float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.x; // 頂点3
		VBuffer[2].y  =  -(float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.y;	
		VBuffer[2].z  =   0.0f;

		VBuffer[3].x  =   (float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.x; // 頂点２	
		VBuffer[3].y  =  -(float)PLAYER_EFFECT_LIGHT_MIN_SIZE * m_vSize.y;	
		VBuffer[3].z  =   0.0f;

		VBuffer[0].nx =   0.0f;	VBuffer[0].ny =   0.0f;	VBuffer[0].nz =  -1.0f;	
		VBuffer[1].nx =   0.0f;	VBuffer[1].ny =   0.0f;	VBuffer[1].nz =  -1.0f;	
		VBuffer[2].nx =   0.0f;	VBuffer[2].ny =   0.0f;	VBuffer[2].nz =  -1.0f;	
		VBuffer[3].nx =   0.0f;	VBuffer[3].ny =   0.0f;	VBuffer[3].nz =  -1.0f;
		
		VBuffer[0].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[1].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[2].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		VBuffer[3].color = D3DCOLOR_RGBA(255,255,255,(int)(m_fAlpha * 255));
		m_pD3DVertexBuffer->Unlock();					// バッファをアンロック
	}
	
}
