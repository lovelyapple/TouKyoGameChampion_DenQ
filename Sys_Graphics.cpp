//=========================================================================
//DirectX Base Graphics.cpp
//=========================================================================

#include "Sys_Graphics.h"
#include "Sys_RenderTarget.h"


//�C���^�[�t�F�C�X
LPDIRECT3D9				g_pD3D			= NULL; // Direct3D�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9		g_pD3DDevice	= NULL; // Direct3DDevice�C���^�[�t�F�C�X
D3DPRESENT_PARAMETERS	g_D3DPP;				// D3DDevice�̐ݒ�(����)

D3DPRESENT_PARAMETERS	g_D3DPPWindow;			// D3DDevice�̐ݒ�(�E�C���h�E�E���[�h�p)
D3DPRESENT_PARAMETERS	g_D3DPPFull;			// D3DDevice�̐ݒ�(�t���X�N���[���E���[�h�p)


//-----------------------------------------
//�O���t�B�b�N�X�֘A������
HRESULT	InitDXGraphics(void)
{
	//Drecit3D�I�u�W�F�N�g���쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
		return E_FAIL;

	//D3DDevice�I�u�W�F�N�g�̃p�����[�^�[��ݒ�----window mode
	ZeroMemory(&g_D3DPPWindow,sizeof(g_D3DPPWindow));

	
	g_D3DPPWindow.BackBufferWidth			= 0;
	g_D3DPPWindow.BackBufferHeight			= 0;
	g_D3DPPWindow.BackBufferFormat			= D3DFMT_UNKNOWN;
	g_D3DPPWindow.BackBufferCount			= 1;
	g_D3DPPWindow.MultiSampleType			= D3DMULTISAMPLE_NONE;
	g_D3DPPWindow.MultiSampleQuality		= 0;
	g_D3DPPWindow.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	g_D3DPPWindow.hDeviceWindow				= g_hWnd;
	g_D3DPPWindow.Windowed					= TRUE;
	g_D3DPPWindow.EnableAutoDepthStencil	= TRUE;
	g_D3DPPWindow.AutoDepthStencilFormat	= D3DFMT_D24S8;
	g_D3DPPWindow.Flags						= 0;
	g_D3DPPWindow.FullScreen_RefreshRateInHz= 0;
	g_D3DPPWindow.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	// D3DDevice�I�u�W�F�N�g�̐ݒ�(�t���X�N���[���E���[�h)
	ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));

	g_D3DPPFull.BackBufferWidth				= g_sizeFullScreenMode.cx;
	g_D3DPPFull.BackBufferHeight			= g_sizeFullScreenMode.cy;
	g_D3DPPFull.BackBufferFormat			= g_formatFull;
	g_D3DPPFull.BackBufferCount				= 1;
	g_D3DPPFull.MultiSampleType				= D3DMULTISAMPLE_NONE;
	g_D3DPPFull.MultiSampleQuality			= 0;
	g_D3DPPFull.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	g_D3DPPFull.hDeviceWindow				= g_hWnd;
	g_D3DPPFull.Windowed					= FALSE;
	g_D3DPPFull.EnableAutoDepthStencil		= TRUE;
	g_D3DPPFull.AutoDepthStencilFormat		= D3DFMT_D24S8;
	g_D3DPPFull.Flags						= 0;
	g_D3DPPFull.FullScreen_RefreshRateInHz	= 0;
	g_D3DPPFull.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	
	//--------------------------------
	//Device���쐬

	//if (IDYES == MessageBox(g_hWnd, _T("�E�B���h�E���[�h�Ŏ��s���܂����H"), _T("��ʃ��[�h"), MB_YESNO))
	//	g_bWindow = true;

	if (g_bWindow)
		g_D3DPP = g_D3DPPWindow;
	else
		g_D3DPP = g_D3DPPFull;



	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
		if (FAILED(hr))
		{
			hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, g_hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
			if (FAILED(hr))
				return E_FAIL;
		}
	}




	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O���� �}�e���A����A�Ɗ֌W�Ȃ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	//�A���`�G�C���A�V���O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);


	//--------------------------------
	//�r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 vp;
	vp.X			= 0;
	vp.Y			= 0;
	vp.Width		= g_D3DPP.BackBufferWidth;
	vp.Height		= g_D3DPP.BackBufferHeight;
	vp.MinZ			= 0.0f;
	vp.MaxZ			= 1.0f;
	hr = g_pD3DDevice->SetViewport(&vp);
	if(FAILED(hr))
		return E_FAIL;
	return S_OK;

}

//-----------------------------------------
//�I�u�W�F�N�g�Ɋւ���ݒ�
HRESULT	Init3DObject(void)
{
	HRESULT hr = Initgame();
	if (SUCCEEDED(hr)) {
		hr = InitShader();		// �V�F�[�_������
	}
	if (SUCCEEDED(hr)) {
		//hr = InitRenderTarget();// �����_�����O �^�[�Q�b�g������
	}
	return S_OK;
}
//-----------------------------------------
//�I�u�W�F�N�g�̃N���[���A�b�v
HRESULT CleanupD3DObject(void)
{
	return S_OK;
}
//-----------------------------------------
//�`�揈��
HRESULT Render(void)
{

	//�o�b�N�o�b�t�@�N���A
	g_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,BACKCOLOR,1.0f,0);

	//�`��J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//SaveRenderTarget();		// �����_�����O���ޔ�
		//ChangeRenderTarget(0);	// �����_�����O����e�N�X�`����
		//BeginShader(0);
		//���g�ŗl�X�̕`����s��
		Drawgame();
		//EndShader();
		//ResetRenderTarget();	// �����_�����O���ʏ�ɖ߂�
		//�V�[���I��
		g_pD3DDevice->EndScene();
	}

	//�V�[����\��
	return g_pD3DDevice->Present(NULL,NULL,NULL,NULL);

				// �V�F�[�_�I��
	return S_OK;
}
//-----------------------------------------
//�O���t�B�b�N�X�̏I������
bool UninitDXGraphics(void)
{
	//FinRenderTarget();
	FinShader();				// �V�F�[�_���	
	Uninitgame();				// �Q�[���̏I������
	SAFE_RELEASE(g_pD3DDevice);//�f�o�C�X������
	SAFE_RELEASE(g_pD3D);		//�C���^�t�F�[�X������
	return true;
}
