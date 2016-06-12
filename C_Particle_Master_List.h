//-----------------------------------------------------------
//C_PARTICLE_MASTER_LIST
//-----------------------------------------------------------
#ifndef C_PARTICLE_MASTER_LIST
#define C_PARTICLE_MASTER_LIST
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Input.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Patricle_Quark.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define MAX_PARTICLE_QUARK	(128)
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Particle_Master
{
public:
	c_Particle_Master();
	~c_Particle_Master();
	virtual void Init_Particle(LPCSTR FileName);
	virtual void Init_Particle(LPCSTR FileName,int nMaxFrame,int TimePerFrame);
	HRESULT CreateTexBuff_Particle(void);
	virtual void Uninit_Particle(void);
	virtual void Update_Particle(void);
	virtual void Draw_Particle(D3DBLEND Effect);
	virtual void SetVerTexBuff_Particle(void);
	virtual void CreateQuarkSingle(void);

private:
	LPDIRECT3DTEXTURE9		m_pD3DTexture;
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVertexBuffer;
	D3DXVECTOR3				m_vParticlePos;
	LPCSTR					m_lpzFileName;
	c_Quark*				m_pQuark[MAX_PARTICLE_QUARK];
	int						m_nMaxQuark;
	int						m_nMaxQuarkLife;
	int						m_nPatricleMaxFrame;
	int						m_nPatricleTimePerFrame;
	float					m_fPatricleAlpha;
	
};
//--------------------------------------
//�I�u�W�F�N�g�O���[�o���ϐ��錾
//--------------------------------------
//�W���O���[�o���ϐ��錾
//--------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------
//����������
//--------------------------------------
//�I������
//--------------------------------------
//�X�V����
//--------------------------------------
//�`�揈��
#endif
