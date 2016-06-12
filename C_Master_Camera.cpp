//-----------------------------------------------------------
//�J�����}�X�^�[�N���Xcpp
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
	//�v���W�F�N�V�����E�}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_matProj,
		D3DXToRadian(FOVY),
		fAspect_ratio,
		NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_matProj);

	//�r���[�@�}�g���b�N�X�ݒ�@//�ݒ肵�Ȃ��Ă��悢
	m_vCamera = 
		D3DXVECTOR3(SCREEN_WIDTH_WIN * 0.5f,		// ���_���W(X)
					 0.0f,							// ���_���W(Y)
					 -SCREEN_HEIGHT_WIN * 0.5f / tanf(D3DXToRadian(FOVY) * 0.5f));	// ���_���W(Z)



	D3DXMatrixLookAtLH(&m_matView,
		&m_vCamera,	// ���_���W(Z)
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// �����_���W
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// �A�b�v�x�N�g��
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
// �J�����ݒ� (�S�Ă̕`�����ɌĂяo���K�v������)
//---------------------------------------------------------------------------------------
void c_Camera::Draw()
{
	// �v���W�F�N�V���� �}�g���b�N�X�ݒ�
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	// �r���[ �}�g���b�N�X�ݒ�
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	SetCameraShader(&m_vCamera, &m_matView, &m_matProj);
}
void c_Camera::UninitCamera(void)
{
	//do Noth
}

