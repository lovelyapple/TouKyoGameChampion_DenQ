//============================================================================
//C_2D_Master.h
//============================================================================
#ifndef _C_2D_MASTER_H_
#define _C_2D_MASTER_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�N����`
#define NUM_VERTEX	(4)					//���_��
#define NUM_POLYGON	(2)					//�|���S����

#define VALUE_BIG_ALPHA		(0.8f)
#define VALUE_LIGHT_ALPHA	(0.4f)

#define ALPHA_PERIOD		(2 * 60)
//----------------------------------
//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;
typedef struct
{
	float x,y;
}TEX_SIZE;//-----------------------------------
//�\���̐錾
typedef enum
{
	ALPHA_TYPE_SINWAVE = 0,
	ALPHA_TYPE_BIG,
	ALPHA_TYPE_LIGHT,
	ALPHA_TYPE_MAX,
}ALPHA_TYPE;
//----------------------------------
//�N���X�錾
class c_2DMaster
{
public:
	c_2DMaster();
	~c_2DMaster();
	HRESULT MakeVertex(void);		
	void SetpTexture(LPDIRECT3DTEXTURE9 *pTexture);
	virtual void SetVerTex(void);
	virtual void Update(void);
	virtual void Uninit(void);
	virtual void Draw(void);
private:
protected:
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`��������
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;				//�o�b�t�@
	D3DXVECTOR3				m_vPos;					//��ʏ�̐�΍��W
	D3DXVECTOR3				m_vMove;				//�ړ�


	bool					m_bAnimation;			//�A�j���[�V�����ł��邩
	int						m_nRecFrame;			//���݂̃t���[����
	int						m_nMaxFrame;			//�}�b�N�X�t���[����
	float					m_fFrameSize;			//�t���[���e�N�X�`���T�C�Y
	TEX_SIZE				m_fTexSizeNor;			//�{��
	TEX_SIZE				m_fTexSizePro;			//��Ώ����_
	int						m_nAlphaTime;			//���݂̃A���t�@����
	int						m_nAlphaPeriod;			//�A���t�@����
	float					m_fAlpha;
};

//------------------------------------
//�v���g�^�C�v�錾

#endif
//============================================================================
//End of  File
//============================================================================