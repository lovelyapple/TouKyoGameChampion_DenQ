//============================================================================
//C_2D_Master.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "C_Master_2DBase.h"
#include "Sys_Macro.h"
c_2DMaster::c_2DMaster()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vMove);

	m_bAnimation	= false;
	m_nRecFrame		= 0;
	m_nMaxFrame		= 0;
	m_fFrameSize	= 1.0f;

	m_fTexSizeNor.x	= 0.0f;
	m_fTexSizeNor.y	= 0.0f;

	m_fTexSizePro.x	= 0.0f;
	m_fTexSizePro.y	= 0.0f;

	m_nAlphaPeriod  = 0;
	m_nAlphaTime	= 0;
	m_fAlpha		= 0.0f;

}
c_2DMaster::~c_2DMaster()
{
}
void c_2DMaster::SetpTexture(LPDIRECT3DTEXTURE9 *pTexture)
{
	m_pTexture = *pTexture;
}

HRESULT c_2DMaster::MakeVertex(void)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_2D,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}
{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos.x = m_vPos.x - m_fTexSizePro.x;
		pVtx[0].pos.y = m_vPos.y - m_fTexSizePro.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_vPos.x;
		pVtx[1].pos.y = m_vPos.y - m_fTexSizePro.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_vPos.x;
		pVtx[2].pos.y = m_vPos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_vPos.x + m_fTexSizePro.x;
		pVtx[3].pos.y = m_vPos.y;
		pVtx[3].pos.z = 0.0f;
		// rhwの設定
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}
	return S_OK;
}
void c_2DMaster::SetVerTex(void)
{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_vPos.x - m_fTexSizePro.x;
	pVtx[0].pos.y = m_vPos.y - m_fTexSizePro.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_vPos.x;
	pVtx[1].pos.y = m_vPos.y - m_fTexSizePro.y;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_vPos.x;
	pVtx[2].pos.y = m_vPos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_vPos.x + m_fTexSizePro.x;
	pVtx[3].pos.y = m_vPos.y;
	pVtx[3].pos.z = 0.0f;
	// rhwの設定
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f,1.0f);

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}
void c_2DMaster::Update(void)
{
	SetVerTex();
}
void c_2DMaster::Uninit(void)
{
	if(m_pTexture != NULL)
	{// テクスチャの開放
		m_pTexture = NULL;
	}

	if(m_pVtxBuff != NULL)
	{// 頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
void c_2DMaster::Draw(void)
{
	// 頂点バッファをデバイスのデータストリームにバインド
	g_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	g_pD3DDevice->SetTexture(0,m_pTexture);

	// ポリゴンの描画
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//set
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//in
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//set
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// out

}

//============================================================================
//End of  File
//============================================================================