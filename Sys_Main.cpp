//=========================================================================
//DirectX Base Main
//=========================================================================
#define STRICT					//��茵���ȃ`�F�b�N���s��
#define WIN32_LEAN_AND_MEAN		//�w�b�_�[���炠�܂�g��Ȃ��֐����ȗ�����
#define WINVER			0x501	//WXp�ȍ~
#define _WIN32_WINNT	0x501


#define D3D_DEBUG_INFO				//Direct3D�f�o�b�O���̗L����
#define D3DXFX_ARGEADRESS_HANDLE	//�������D3DXHANDLE�p�����[�^�ɓn��

#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Global_Variable.h"
#include "Sys_Graphics.h"
#include "Sys_Game.h"
#include "Sys_Input.h"
//---------------------------
//�A�v���P�[�V�����ϐ�
HINSTANCE		g_hInstance		= NULL;	// �C���X�^���X�E�n���h��
HWND			g_hWnd			= NULL;	// �E�C���h�E�E�n���h��
HMENU			g_hMenu			= NULL;	// ���j���[�E�n���h��

const char*		g_AppTitle	= "ShipCraft";
const char*		g_WndClass	= "D3D9GV01";

int				g_FPS;			//�@�t���[���J�E���g
RECT			g_rectWindow;	//�Ō�̃E�B���h�E����ۑ�����ϐ�
//�E�B���h�E�t���[�X�N���[���֘A
bool			g_bWindow		= false;

SIZE			g_sizeWindowMode		=	{SCREEN_WIDTH_WIN,SCREEN_HEIGHT_WIN};		//�E�C���h�E���[�h
SIZE			g_sizeFullScreenMode	=	{SCREEN_WIDTH_FULL,SCREEN_HEIGHT_FULL};		//�t���X�N���[�����[�h
D3DFORMAT		g_formatFull			= D3DFMT_X8R8G8B8;	//�f�B�X�v���C�i�o�b�N�o�b�t�@�t�H�[�}�b�g�j

//�A�v���P�[�V�����̓���t���O
bool			g_bActive				= false;//�A�N�e�B�u���
bool			g_bDeviceLost			= false;
int				g_MouseHoilu;

//�t���[���ϐ��錾
DWORD			g_dwExecLastTime;					// FPS�v���p
DWORD			g_dwFPSLastTime;					// �Ō�FPS�𑪂�������
DWORD			g_dwCurrentTime;					// ���݂̎���
DWORD			g_dwFrameCount;						// �t���[����
//-------------------------------------------------------
//�v���g�^�C�v�錾
LRESULT	CALLBACK MainWndProc(HWND hWnd,UINT msg,UINT wParam,LONG lparam);
HRESULT	InitApplication(HINSTANCE hInst);
bool CleanApplication(void);
bool AppIdle(void);
HRESULT ChangeWindowSize(void);
void ChangeDisplayMode(void);

//***********************************************************
//Main
//***********************************************************
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time (NULL));
	// �f�o�b�O �q�[�v �}�l�[�W���ɂ�郁�������蓖�Ă̒ǐՕ��@��ݒ�
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//�A�v���P�[�V�����Ɋւ��鏉����
	HRESULT hr = InitApplication(hInst);
	if(FAILED(hr))
	{
		MessageBox(g_hWnd, _T("�V�X�e�����������s"),
			_T("�A�v���P�[�V�������������s"), 
			MB_OK | MB_ICONERROR);	
	}
	else
	{
		hr = InitDXGraphics();
		if(FAILED(hr))
		{
			MessageBox(g_hWnd, _T("�V�X�e�����������s"),
				_T("D3D_3DGraphic���������s"), 
				MB_OK | MB_ICONERROR);
			DestroyWindow(g_hWnd);
		}


		//Direct�ȊO�̃I�u�W�F�N�g
		hr = Init3DObject();


		if(FAILED(hr))
		{
			MessageBox(g_hWnd, _T("�V�X�e�����������s"),
				_T("D3D_3D�I�u�W�F�N�g���������s"), 
				MB_OK | MB_ICONERROR);
			DestroyWindow(g_hWnd);
		}
	}

	//�t���[���Ɋւ��鏉����
	timeBeginPeriod(1);								// �^�C�}�̕���\���ŏ��ɃZ�b�g
	g_dwFPSLastTime = g_dwExecLastTime = timeGetTime();	// ���݂̃V�X�e���^�C�}���擾
	g_dwExecLastTime -= FRAME_RATE;					// Update()�����1��ȏ�Ă΂��悤��
	g_dwFrameCount = 0;
	g_FPS = 0;

	//���b�Z�[�W���[�v
	MSG msg;
	msg.message = WM_NULL;
	//Input������
	InitInput(g_hInstance,g_hWnd);
	while(WM_QUIT != msg.message)
	{
		//���b�Z�[�W�`�F�b�N
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{		// ���b�Z�[�W���`�F�b�N
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			// ���̕ӂŃt���[�����J�E���g
			g_dwCurrentTime = timeGetTime();					// ���݂̃^�C�}�l���擾
			if (g_dwCurrentTime - g_dwFPSLastTime >= 500)
			{		// 0.5�b���ƂɌv��
				// �t���[�������v�Z
				g_FPS = g_dwFrameCount * 1000 / (g_dwCurrentTime - g_dwFPSLastTime);
				g_dwFPSLastTime = g_dwCurrentTime;	// �^�C�}�l���X�V
				g_dwFrameCount = 0;				// �t���[���J�E���^�����Z�b�g
			}

			// ���̕ӂŎ��ԊǗ�
			while (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE)
			{	// ��莞�Ԃ��o�߂�����c
				g_dwExecLastTime += FRAME_RATE;						// �^�C�}�l���X�V
				g_MouseHoilu = GET_WHEEL_DELTA_WPARAM(msg.wParam);
				UpdateInput();
				Updategame();
			
			}
			if(!AppIdle())//���g�Ƀ����_�[�֐�������
				DestroyWindow(g_hWnd);
			//Render();		

			g_dwFrameCount++;										// �t���[���J�E���g��+1
		
		}
	}

	timeEndPeriod(1);//�^�C�}�[����\������
	//Input�I������
	UninitInput();
	//�O���t�B�b�N���̏I������
	UninitDXGraphics();//���g��UninitGame������
	return (int)msg.wParam;
	_CrtDumpMemoryLeaks();
}
//--------------------------------------
//�A�v���P�[�V�����̏�����
//--------------------------------------
HRESULT InitApplication(HINSTANCE hInst)
{
	//�A�v���P�[�V�����̃C���X�^���X�@�n���h����ۑ�
	g_hInstance = hInst;

	//IME���֎~����@���͗\���@�\��OFF
	//ImmDisableIME(-1);// ���̃X���b�h�ŋ֎~(imm32.lib�������N����)

	//�E�C���h�����W�X�^�ɓo�^
	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW;		//��{�����ݒ�
	wc.lpfnWndProc		= (WNDPROC)MainWndProc;			//���b�Z�[�W���󂯎��֐��̃|�C���^
	wc.cbClsExtra		= 0;							//1�ɂ���ƁA�A�v�����ʃ|�C���^��ݒ肷��ׂɓ��I���������m�ۂ���
	wc.cbWndExtra		= 0;							//��Ǝ��Ă���
	wc.hInstance		= hInst;						//�A�v���P�[�V�����̃C���X�^���X�n���h��
	wc.hIcon			= LoadIcon(hInst, IDI_APPLICATION);//�A�C�R�����ł����Ƃ��ۂɕ`��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);//�J�[�\���̐ݒ�
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);//�A�v���P�[�V��������ʂ��ĕ`�悷�鎞�̐F�u���V�n���h��
	wc.lpszMenuName		= NULL;//���j���[����邩
	//wc.lpszMenuName		= g_bWindow ? MAKEINTRESOURCE(IDR_MENU1) : NULL;
	wc.lpszClassName	= g_WndClass;//���̃E�B���h�E�̃N���X�̖��O�A�K��������
	if(!RegisterClass(&wc))
		return false;
	//�E�B���h�E�̍쐬
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;
	g_rectWindow.right	= g_sizeWindowMode.cx;
	g_rectWindow.bottom	= g_sizeWindowMode.cy;
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, TRUE);
	g_rectWindow.right	= g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom	= g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top	= 0;
	g_rectWindow.left	= 0;
	
	g_bWindow			= true;
	//if(IDYES == MessageBox(g_hWnd,_T("�܂��E�C���h�E���[�h�Ŏ��s���܂����H"),
	//	_T("��ʃ��[�h"), MB_YESNO))
	//	g_bWindow = true;

	RECT	rect;
	if(g_bWindow)
	{
		// (�E�C���h�E�E���[�h�p)
		rect.top	= CW_USEDEFAULT;
		rect.left	= CW_USEDEFAULT;
		rect.right	= g_rectWindow.right;
		rect.bottom	= g_rectWindow.bottom;
	}
	else
	{
		// (�t���X�N���[���E���[�h�p)
		rect.top	= 0;
		rect.left	= 0;
		rect.right	= g_sizeFullScreenMode.cx;
		rect.bottom	= g_sizeFullScreenMode.cy;
	}
	//-----------------------------------
	//�E�C���h�E�̍쐬
	g_hWnd = CreateWindow(
		g_WndClass,
		g_AppTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
		rect.left, 
		rect.top, 
		rect.right, 
		rect.bottom,
		NULL,
		NULL,
		hInst,
		NULL);
	if(g_hWnd == NULL)
	{
		return false;
	}
	//-------------------------------------
	//�E�C���h�E������x�\��
	ShowWindow(g_hWnd,SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);
	return S_OK;
}
//--------------------------------------
//�A�v���P�[�V�����̏I������
//--------------------------------------
bool CleanApplication(void)
{
	//�O�̂��߂ɏ����Ƃ�
	if(g_hMenu)
		DestroyMenu(g_hMenu);

	//�E�B���h�E�N���X�����W�X�^������
	UnregisterClass(g_WndClass,g_hInstance);
	return true;
}
//--------------------------------------
//�R�[���o�b�N�v���V�[�W���֐�
//--------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	HRESULT hr = S_OK;
	switch(msg)
	{
	case WM_ACTIVATE:
		g_bActive = (LOWORD(wParam)!= 0);
		break;

	case WM_DESTROY:
		// D3D�ɊǗ�����Ȃ��I�u�W�F�N�g�̏I������
		//CleanupD3DObject();
		// DirectX Graphics�̏I������
		//UninitDXGraphics();
		// �E�C���h�E�����
		PostQuitMessage(0);
		g_hWnd = NULL;
		return 0;

	// �E�C���h�E�E�T�C�Y�̕ύX����
	case WM_SIZE:
		if(g_D3DPP.Windowed != TRUE)
			break;
		if (!g_pD3DDevice || wParam == SIZE_MINIMIZED)
			break;
		g_D3DPP.BackBufferWidth  = LOWORD(lParam);
		g_D3DPP.BackBufferHeight = HIWORD(lParam);

		if(g_bDeviceLost)
			break;
		if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
			ChangeWindowSize();
		break;

	case WM_SETCURSOR://�J�[�\��������
		if (g_D3DPP.Windowed != TRUE)
		{
			SetCursor(NULL);
			return 1;
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE://[ESCAPE]�L�[�ŃE�C���h�E�����
			PostMessage(hWnd,WM_CLOSE,0,0);
			break;
		//case KEY_CHANGE_DISP://�Y���L�[����������A�f�B�X�v���C�̃��[�h��ύX
		//	ChangeDisplayMode();
		}
			break;
	case WM_COMMAND:
		//�I�����ꂽ���j���[�����s//���Ԃ�g��Ȃ�
		switch(LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			return 0;
		}
		break;
	}
	//�f�t�H���g����
	return DefWindowProc(hWnd,msg,wParam,lParam);

}
//--------------------------------------
//�A�C�h������
//--------------------------------------
bool AppIdle(void)
{
	if(!g_pD3D || !g_pD3DDevice)
		return false;
	if(!g_bActive)
		return true;

	//�f�o�C�X�����������̕�������
	HRESULT hr;
	if(g_bDeviceLost)
	{
		Sleep(100);//0.1�b��҂�
		//�f�o�C�X�̃`�F�b�N���s��
		hr = g_pD3DDevice->TestCooperativeLevel();
		
		if(FAILED(hr))
		{
			if(hr == D3DERR_DEVICELOST)
				return true;	//�f�o�C�X�͂܂������Ă���

			if(hr != D3DERR_DEVICENOTRESET)
				return false;

			//��������Direct�ŊǗ�����Ă��Ȃ��\�[�X���J��
			CleanupD3DObject();

			hr = g_pD3DDevice->Reset(&g_D3DPP);//�����������Ă݂�
			if(FAILED(hr))
			{
				if (hr == D3DERR_DEVICELOST)
					return true;  // �f�o�C�X�͂܂������Ă�
				MessageBox(g_hWnd, _T("��ʃ��[�h�ؑ֎��s"),
					_T("�f�o�C�X���܂�������"), 
					MB_OK | MB_ICONERROR);
				return false;
			}
			//��قǊJ�������\�[�X���Ď擾
			hr = Init3DObject();
			if(FAILED(hr))
			{
				MessageBox(g_hWnd, _T("��ʃ��[�h�ؑ֎��s"),
					_T("���\�[�X�̍Ď擾�����s���܂���"), 
					MB_OK | MB_ICONERROR);
				return false;
			}
		}
		//�f�o�C�X����������,�t���O��ύX
		g_bDeviceLost = false;
	}

	//��ʂ𕜌���̍X�V�����s��
	hr = Render();
	if(hr == D3DERR_DEVICELOST)
		g_bDeviceLost = true; //�f�o�C�X���񕜂���Ă��Ȃ�
	else if (FAILED(hr))
		return false;//�`�掸�s

	return true;
}
//-----------------------------------------
//�E�C���h�E�E�T�C�Y�̕ύX
HRESULT ChangeWindowSize(void)
{
	//�E�C���h�E�̃N���C�A���g�̈�ɍ��킹��
	CleanupD3DObject();
	
	HRESULT	hr = g_pD3DDevice->Reset(&g_D3DPP);//�f�o�C�X���܂����Z�b�g����

	if(FAILED(hr))
	{
		if(hr == D3DERR_DEVICELOST)
			g_bDeviceLost = true;
		else
			DestroyWindow(g_hWnd);

		return E_FAIL;
	}
	hr = Init3DObject();
	if(FAILED(hr))
	{
		DestroyWindow(g_hWnd);
		return E_FAIL;
	}

	// �r���[�|�[�g�̍Đݒ�
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= g_D3DPP.BackBufferWidth;
	vp.Height	= g_D3DPP.BackBufferHeight;
	vp.MinZ		= 0.0f;
	vp.MaxZ		= 1.0f;
	hr = g_pD3DDevice->SetViewport(&vp);
	if (FAILED(hr))
	{
		DestroyWindow(g_hWnd);
	}
	return hr;
	
}
//-----------------------------------------
//��ʃ��[�h�ύX
void ChangeDisplayMode(void)
{
	g_bWindow = !g_bWindow;//���݂̃��[�h�̔��΃��[�h�ɐ؂�ւ�

	CleanupD3DObject();
	if(g_bWindow)
	{
		g_D3DPP = g_D3DPPWindow;
	}
	else
	{
		g_D3DPP = g_D3DPPFull;
	}

	HRESULT hr = g_pD3DDevice->Reset(&g_D3DPP);
	if(FAILED(hr))
	{
		if(hr == D3DERR_DEVICELOST)
			g_bDeviceLost = true;
		else
			DestroyWindow(g_hWnd);
		MessageBox(g_hWnd, _T("��ʃ��[�h�̐؂�ւ��������s���܂���"),
			_T("�f�o�C�X�̃��Z�b�g���s"), 
			MB_OK | MB_ICONERROR);
		return ;
	}

	hr = Init3DObject();
	if(FAILED(hr))
	{
		DestroyWindow(g_hWnd);
		MessageBox(g_hWnd, _T("��ʃ��[�h�̐؂�ւ��������s���܂���"),
			_T("3D�I�u�W�F�N�g�̏��������s"), 
			MB_OK | MB_ICONERROR);
		return;
	}

	if(g_bWindow)
	{
		SetWindowLong(g_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		if(g_hMenu != NULL)//���Ԃ���v���ǁA�ꉞ�����Ƃ�
		{
			SetMenu(g_hWnd,g_hMenu);
				g_hMenu = NULL;
		}
		//�E�C���h�E�̈ʒu���Đݒ�
		SetWindowPos(g_hWnd, HWND_NOTOPMOST,
				g_rectWindow.left, g_rectWindow.top,
				g_rectWindow.right - g_rectWindow.left,
				g_rectWindow.bottom - g_rectWindow.top,
				SWP_SHOWWINDOW);

	}
	else
	{
		SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		if(g_hMenu == NULL)
		{
			g_hMenu = GetMenu(g_hWnd);
			SetMenu(g_hWnd, NULL);
		}
	}
}
