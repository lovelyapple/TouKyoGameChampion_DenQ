//============================================================================
//Ship.h
//============================================================================
#ifndef _CLASS_MASTER_PRIMITIVE_H_
#define _CLASS_MASTER_PRIMITIVE_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
//-----------------------------------
//�C���X�^���X�C���N���[�h
//-----------------------------------
//�}�N����`
#define FILE_NAME_DEAULT_PRIMITIVE		("data/Texture/denkyu.png")
//-----------------------------------
//�\���̐錾
#ifndef DVERTEX_PRIMITIVE_3D
#define DVERTEX_PRIMITIVE_3D
typedef struct  
{	
	float		x, y, z;		// ���_
	float		nx, ny, nz;		// �@���x�N�g��
	D3DCOLOR	color;			// �f�B�t���[�Y�J���[
	float		tu, tv;			// �e�N�X�`�����W
}DVERTEX_PRIMITIVE;
#endif
//-----------------------------------
//�N���X�錾
class c_Master_Primitive
{
public:
	c_Master_Primitive();
	c_Master_Primitive(LPCSTR fzName);	// �R���X�g���N�^
	~c_Master_Primitive();				// �f�X�g���N�^
	void	SetFileName(LPCSTR fzName);
	void	ResetPrimitive(void);
	virtual HRESULT Init(void);			// ������
	virtual	void	Uninit(void);		// �I������
	virtual void	Release(void);		// �J��

	virtual void	SetPos(D3DXVECTOR3 Pos);				// Pos�̕ύX
	virtual void	SetSize(D3DXVECTOR3 size);
	virtual void	SetRot(D3DXVECTOR3 Ros);				// Rot�̕ύX
	virtual void	SetVerTexBuff(void);					// �o�b�t�@�ύX
	virtual void	SetVerTexBuffUV(void);					//
			void	SetVerTexBuffAlpha(float Alpha);		// 	
	virtual	void	UpdatePrimitive(void);					// �X�V
	virtual void	UpdateCageStyle(void);					// �P�[�W�X�^�C���^�X�V
	virtual void	SetVerTexBuffCageStylePos(void);		// �P�[�W�X�^�C���`��ݒ�
			void	SetOblique(D3DXVECTOR3* input);			//�΂ߓx���̐ݒ�
			void	SetTexUV(D3DXVECTOR3 UV);				//UV�T�C�Y�̐ݒ�
			void	SetTexRecUVFrame(int nFrameX,int nFrameY);	//UV�t���[���̐ݒ�
	void			SetWatchCamera(bool input);				//�J���������ݒ�
	virtual void	DrawPrimitive();						// �`��
			void	DrawAntialiasing(void);//�A���`�G���A�V���O�`��
			void	DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture);

	D3DXMATRIX		GetMatrix(void);
	D3DXVECTOR3		GetPos(void);
	D3DXVECTOR3		GetSize(void);
protected:
	D3DXVECTOR3						m_vPos;			// 
	D3DXVECTOR3						m_vRot;			//
	D3DXMATRIX						m_mMatrix;		//
	LPDIRECT3DVERTEXBUFFER9			m_pD3DVertexBuffer;
	LPDIRECT3DTEXTURE9				m_pD3DTexture;

	bool							m_bWatchCamera;	//�v����v��
	LPCSTR							m_pszFName;

	D3DXVECTOR3						m_vSize;
	D3DXVECTOR3						m_vOblique[2];	//�X�΂̓x��

	D3DXVECTOR3						m_vSizeUV;		//UV�̍��W
	int								m_nMaxUVFrame;	//�ő�UVFrame
	int								m_nRecUVFrameX; //����UV_X�̃t���[����
	int								m_nRecUVFrameY;	//����UV_Y�̃t���[����

	
};


#endif