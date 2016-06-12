#include "C_Master_Model.h"

c_Model::c_Model()
{
	D3DM_INIT(m_matrix);
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vAngle);

	m_pModel = new MODEL;
	ZeroMemory(m_pModel,sizeof(m_pModel));
	m_pszFName = DEFAULT_MODEL_FILE;
	
	HRESULT hr = (LoadModel());
	if(FAILED(hr))
	{
		delete m_pModel;
		SAFE_DELETE(m_pModel);

	}
}
c_Model::c_Model(LPCSTR File,D3DXVECTOR3 pos)
{
	D3DM_INIT(m_matrix);
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vAngle);
	m_pszFName	= File;
	m_vPos		= pos;
	m_pModel = new MODEL;
	ZeroMemory(m_pModel,sizeof(m_pModel));
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
}
c_Model::~c_Model()
{
	if(m_pModel)
	{
		ReleaseModel();
	}
}

HRESULT c_Model:: LoadModel(void)
{
	LPD3DXBUFFER	pMtrlBuff = NULL;
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szSaveDir[_MAX_DIR];

	HRESULT hr = D3DXLoadMeshFromX(m_pszFName,	// �t�@�C����
		D3DXMESH_SYSTEMMEM,						// ��ɓ����w��
		g_pD3DDevice,							// Direct3D�f�o�C�X
		NULL,									// ���NULL
		&pMtrlBuff,								// �}�e���A���o�b�t�@
		NULL,									// ���NULL
		&m_pModel->dwNumMtrl,					// �}�e���A����
		&m_pModel->pMesh);						// ���b�V���I�u�W�F�N�g
	if (FAILED(hr)) 
	{
		if (hr == D3DERR_INVALIDCALL) {
			hr = D3DERR_INVALIDCALL;
		} else if (hr == E_OUTOFMEMORY) {
			hr = D3DERR_INVALIDCALL;
		}
		MessageBox(g_hWnd, _T("���f�����[�h���s"),
			_T("�O���t�B�b�N�X���������s"), 
			MB_OK | MB_ICONERROR);
		ReleaseModel();
		return hr;
	}
	// �@���������ꍇ�͋����I�ɒǉ�
	LPD3DXMESH pMeshWk;
	DWORD dwFVF = m_pModel->pMesh->GetFVF();
	if ((dwFVF & D3DFVF_NORMAL) == 0) 
	{
		hr = m_pModel->pMesh->CloneMeshFVF(m_pModel->pMesh->GetOptions(),
			dwFVF | D3DFVF_NORMAL, g_pD3DDevice, &pMeshWk);

		if (SUCCEEDED(hr))
		{
			D3DXComputeNormals(pMeshWk, NULL);
			m_pModel->pMesh->Release();
			m_pModel->pMesh = pMeshWk;
		}
	}
// �����e�[�u���擾
	hr = m_pModel->pMesh->GetAttributeTable(NULL, &m_pModel->dwNumAttr);
	if (FAILED(hr)) {
		SAFE_RELEASE(pMtrlBuff);
		SAFE_RELEASE(m_pModel->pMesh);
		return hr;
	}
	m_pModel->pAttr = new D3DXATTRIBUTERANGE[m_pModel->dwNumAttr];
	hr = m_pModel->pMesh->GetAttributeTable(m_pModel->pAttr, &m_pModel->dwNumAttr);

	// ���_�o�b�t�@�Œ�
	LPD3DXVECTOR3 pVtx;
	m_pModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVtx);
	// ���E�{�b�N�X����
	D3DXVECTOR3 vMin = *pVtx;
	D3DXVECTOR3 vMax = vMin;
	DWORD dwVtx = m_pModel->pMesh->GetNumVertices();
	DWORD dwStroke = m_pModel->pMesh->GetNumBytesPerVertex();
	LPD3DXVECTOR3 pV = pVtx;
	for (DWORD i = 0; i < dwVtx; i++) {
		if (vMin.x > pV->x) vMin.x = pV->x;
		if (vMin.y > pV->y) vMin.y = pV->y;
		if (vMin.z > pV->z) vMin.z = pV->z;
		if (vMax.x < pV->x) vMax.x = pV->x;
		if (vMax.y < pV->y) vMax.y = pV->y;
		if (vMax.z < pV->z) vMax.z = pV->z;
		pV = (LPD3DXVECTOR3)((LPBYTE)pV + dwStroke);
	}
	m_pModel->vBBox = (vMax - vMin) / 2.0f;
	m_pModel->vCenter = (vMax + vMin) / 2.0f;
	// ���E������
	m_pModel->fRadius = 0.0f;
	float fR;
	pV = pVtx;
	for (DWORD i = 0; i < dwVtx; i++)
	{
		fR = D3DXVec3Length(&(*pV - m_pModel->vCenter));
		if (m_pModel->fRadius < fR)
			m_pModel->fRadius = fR;
		pV = (LPD3DXVECTOR3)((LPBYTE)pV + dwStroke);
	}
	// ���_�o�b�t�@���
	m_pModel->pMesh->UnlockVertexBuffer();

	// �J�����g�f�B���N�g����X�t�@�C���̂���t�H���_�Ɉړ�
	_tsplitpath(m_pszFName, NULL, szDir, NULL, NULL);
	if (szDir[0])
	{	// �t�H���_���Ύw�肠��?
		GetCurrentDirectory(_countof(szSaveDir), szSaveDir);
		SetCurrentDirectory(szDir);
	}

	// �}�e���A���̒��o
	D3DXMATERIAL* pMtrl = (D3DXMATERIAL*)pMtrlBuff->GetBufferPointer();
	m_pModel->pMtrl = new D3DMATERIAL9[m_pModel->dwNumMtrl];
	m_pModel->pTexture = new LPDIRECT3DTEXTURE9[m_pModel->dwNumMtrl];

	for (DWORD i = 0; i < m_pModel->dwNumMtrl; i++) 
	{
		m_pModel->pMtrl[i] = pMtrl[i].MatD3D;
		// X�t�@�C���ɂ͊��F�������A�g�U�F�ŏ㏑�����Ă���.
		m_pModel->pMtrl[i].Ambient = m_pModel->pMtrl[i].Diffuse;

		m_pModel->pTexture[i] = NULL;
		if (pMtrl[i].pTextureFilename && pMtrl[i].pTextureFilename[0]) 
		{
			hr = D3DXCreateTextureFromFileA(g_pD3DDevice, pMtrl[i].pTextureFilename, &m_pModel->pTexture[i]);
			if (FAILED(hr)) 
			{
				break;
			}
		}
	}

	// �J�����g�f�B���N�g�������ɖ߂�
	if (szDir[0]) 
	{	// �t�H���_���Ύw�肠��?
		SetCurrentDirectory(szSaveDir);
	}

	pMtrlBuff->Release();
	return hr;
}
void c_Model::ReleaseModel(void)
{
	if (m_pModel->pTexture) 
	{
		for (DWORD i = 0; i < m_pModel->dwNumMtrl; i++)
		{
			SAFE_RELEASE(m_pModel->pTexture[i]);
		}
	}
	SAFE_DELETE_ARRAY(m_pModel->pTexture);
	SAFE_DELETE_ARRAY(m_pModel->pMtrl);
	SAFE_RELEASE(m_pModel->pMesh);
}
void c_Model::UpdateModel(void)
{
}
void c_Model:: DrawModel(void)
{
	if(m_pModel)
	{
		// ���[���h�ϊ��ݒ�
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matrix);

		// �T�u�Z�b�g���̕`��
		for (DWORD i = 0; i < m_pModel->dwNumAttr; i++) 
		{
			DWORD id = m_pModel->pAttr[i].AttribId;
			g_pD3DDevice->SetMaterial(&m_pModel->pMtrl[id]);
			g_pD3DDevice->SetTexture(0, m_pModel->pTexture[id]);
			m_pModel->pMesh->DrawSubset(id);
		}
	}
}
void c_Model::UninitModel(void)
{
	ReleaseModel();
}

void c_Model::UpdateTask(void)
{
	UpdateModel();
}
void c_Model::DrawTask(void)
{
	DrawModel();
}
void c_Model::UninitTask(void)
{
	UninitModel();
}

D3DXMATRIX* c_Model::GetModelMatrix(void)
{
	return &m_matrix;
}
D3DXVECTOR3* c_Model::GetModelPos(void)
{
	return &m_vPos;
}

