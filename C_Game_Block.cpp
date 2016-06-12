//-----------------------------------------------------------
//ゲーム内のブロック
//-----------------------------------------------------------
//--------------------------------------
//システムブロック
#include "C_Game_Block.h"
const char* FileNameBlock[]={
	"data/model/Elec.x",
	"data/model/normal.x"
};
C_FIELDPLACE::C_FIELDPLACE()
{
	this->x = 0;
	this->y = 0;
}

C_FIELDPLACE::C_FIELDPLACE(int inputx,int inputy)
{
	this->x = inputx;
	this->y = inputy;
}
//***************************************************
//以下はブロッククラス解釈
c_Block::c_Block()
{
	m_uPlace = C_FIELDPLACE(0,0);
	m_uBlock.nType	= BLOCK_TYPE_NOMAL_ELE;
	this->InitArray();
	if(m_pModel)
	{
		ReleaseModel();
	}
}
c_Block::c_Block(int nType,C_FIELDPLACE* place)
{
	m_uPlace = *place;
	m_uBlock.nType	= nType;
	this->InitArray();
	if(m_pModel)
	{
		ReleaseModel();
	}
	SetModel();
}
c_Block::~c_Block()
{
}
void c_Block::FieldCheck(void)
{
	if(m_uPlace.x <= 0)		m_uPlace.x = 0;
	if(m_uPlace.x >= MAX_FIELD_WIDTH - 1)	m_uPlace.x = MAX_FIELD_WIDTH - 1;

	if(m_uPlace.y <= 0)		m_uPlace.y = 0;
	if(m_uPlace.y >= MAX_FIELD_HEIGHT - 1)	m_uPlace.y = MAX_FIELD_HEIGHT - 1;

	SetPosFromFeildPlace(&m_uPlace,&m_vPos);
	UpdateBlock();
}
HRESULT c_Block::SetModel(void)
{
	//---------------------------------
	//もし変更の場合なた一回開放する
	if(m_pModel)
		ReleaseModel();

	m_pszFName = FileNameBlock[m_uBlock.nType];
	
	HRESULT hr = (LoadModel());
	if(FAILED(hr))
	{
		delete m_pModel;
		SAFE_DELETE(m_pModel);

		m_pszFName = DEFAULT_MODEL_FILE;
		m_pModel = new MODEL;
		hr = (LoadModel());
		if(FAILED(hr))
		{
			delete m_pModel;
			SAFE_DELETE(m_pModel);
		}
	}
	return S_OK;
}
void c_Block::UpdateBlock(void)
{
	SetPosFromFeildPlace(&m_uPlace,&m_vPos);
	//D3DM_INIT(m_matrix);
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
void c_Block::DrawBlock(void)
{
	if(m_pModel)
	{
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_NONE);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_NONE);
		// ワールド変換設定
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matrix);

		// サブセット毎の描画
		for (DWORD i = 0; i < m_pModel->dwNumAttr; i++) 
		{
			DWORD id = m_pModel->pAttr[i].AttribId;
			g_pD3DDevice->SetMaterial(&m_pModel->pMtrl[id]);
			g_pD3DDevice->SetTexture(0, m_pModel->pTexture[id]);
			m_pModel->pMesh->DrawSubset(id);
		}
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);
	}
}
void c_Block::UpdateModel(void)
{
	UpdateBlock();
}

void c_Block::DrawModel(void)
{
	DrawBlock();
}

//---------------------------------------------
//その他の機能関数
void SetPosFromFeildPlace(C_FIELDPLACE* place,D3DXVECTOR3* pos)
{
	pos->x = (place->x) * BLOCK_SIZE;
	pos->y = (place->y) * BLOCK_SIZE;
}
