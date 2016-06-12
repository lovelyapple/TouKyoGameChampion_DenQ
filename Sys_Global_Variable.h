//------------------------------------------------------
//�O���[�o���ϐ��w�b�_�[
//------------------------------------------------------
#ifndef _SYS_G_VARIABLE_
#define _SYS_G_VARIABLE_

#include "Sys_Include.h"
//---------------------------
//�A�v���P�[�V�����ϐ�
extern HINSTANCE	g_hInstance;	// �C���X�^���X�E�n���h��
extern HWND			g_hWnd;			// �E�C���h�E�E�n���h��
extern HMENU		g_hMenu;		// ���j���[�E�n���h��

extern const char*	g_AppTitle;
extern const char*	g_WndClass;

extern  int			g_FPS;			//�@�t���[���J�E���g
extern DWORD		g_dwExecLastTime;					// FPS�v���p
extern DWORD		g_dwFPSLastTime;					// �Ō�FPS�𑪂�������
extern DWORD		g_dwCurrentTime;					// ���݂̎���
extern DWORD		g_dwFrameCount;						// �t���[����
extern RECT			g_rectWindow;	//�Ō�̃E�B���h�E����ۑ�����ϐ�
//�E�B���h�E�t���[�X�N���[���֘A
extern bool			g_bWindow;

extern SIZE			g_sizeWindowMode;		//�E�C���h�E���[�h
extern SIZE			g_sizeFullScreenMode;	//�t���X�N���[�����[�h
extern D3DFORMAT	g_formatFull;			//�f�B�X�v���C�i�o�b�N�o�b�t�@�t�H�[�}�b�g�j

//�A�v���P�[�V�����̓���t���O
extern bool			g_bActive;				//�A�N�e�B�u���

//---------------------------
//DirectX�֘A�ϐ�

//�C���^�[�t�F�C�X
extern LPDIRECT3D9				g_pD3D;			// Direct3D�C���^�[�t�F�C�X
extern LPDIRECT3DDEVICE9		g_pD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern D3DPRESENT_PARAMETERS	g_D3DPP;		// D3DDevice�̐ݒ�(����)

extern D3DPRESENT_PARAMETERS	g_D3DPPWindow;	// D3DDevice�̐ݒ�(�E�C���h�E�E���[�h�p)
extern D3DPRESENT_PARAMETERS	g_D3DPPFull;	// D3DDevice�̐ݒ�(�t���X�N���[���E���[�h�p)

extern D3DXMATRIX*				g_matView;
extern bool	g_bDeviceLost;						//�f�o�C�X�̏����t���O


extern int						g_MouseHoilu;	//
//2D�`��p�̃X�v���C�g�@�\-->>>>>>>.�����ɂ͂���Ȃ�
//LPD3DXSPRITE			g_pD3DXSprite = NULL;	// �X�v���C�g
//LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;	// �X�v���C�g�Ɏg���e�N�X�`��
//WCHAR g_szSpriteFile[] = L"..\\Media\\canvas.dds";	// �X�v���C�g�Ɏg���摜�t�@�C��

#endif