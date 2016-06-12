//-----------------------------------------------------------
//C_PARTICLE_QUARK_H
//-----------------------------------------------------------
#ifndef C_PARTICLE_QUARK_H
#define C_PARTICLE_QUARK_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define VALUE_PATRICLE_MAX_LIFE (4 * 60)
//--------------------------------------
//�\���̐錾
typedef enum
{
	QUARK_MOVE_MODE_KEEP_ORIGIN = 0,
	QUARK_MOVE_MODE_MOVE_A,
	QUARK_MOVE_MODE_KEEP_A,
	QUARK_MOVE_MODE_MOVE_B,
	QUARK_MOVE_MODE_KEEP_B,
	QUARK_MOVE_MODE_MOVE_RETURN,
	QUARK_MOVE_MODE_MAX,
}QUARK_MOVE_MODE;
typedef enum
{
	QUARK_STATS_POS = 0,
	QUARK_STATS_ROT,
	QUARK_STATS_SIZE,
	QUARK_STATS_SPEED,
	QUARK_STATS_MAX,

	QUARK_STATS_MAX_TIME,
	QUARK_STATS_STOP_TIME,
	QUARK_STATS_FRAMETIME,
	QUARK_STATS_MAX_FRAME,
	QUARK_STATS_MOVE_MODE,

	QUARK_STATS_USE,
	QUARK_STATS_RECYCLE,
	QUARK_STATS_WATCH,

	QUARK_STATS_ALPHA,
	QUARK_STATS_USIZE,
}QUARK_STATS;
//--------------------------------------
//�N���X�錾
class c_Quark
{
public:
	c_Quark();
	~c_Quark();
	void	InitQuarkStatus(void);
	HRESULT CreateQuarkTexBuff(void);
	void	UninitQuark(void);
	void	UpdateQuark(void);
	void	UpdateQuarkMatrix(void);

	void	Set_Quark_Stats(QUARK_STATS,D3DXVECTOR3 vInput);
	void	Set_Quark_Stats(QUARK_STATS,int vInput);
	void	Set_Quark_Stats(QUARK_STATS,bool bInput);
	void	Set_Quark_Stats(QUARK_STATS,float fInput);
	D3DXVECTOR3		m_vPos;			//
	D3DXVECTOR3		m_vOriginPos;	//�ŏ���POS
	D3DXVECTOR3		m_vRot;			//
	D3DXVECTOR3		m_vSize;		//
	D3DXVECTOR3		m_vSpeed;
	D3DXMATRIX		m_mMatrix;		//
	bool			m_bUse;
	bool			m_bWatchCamera;	//
	bool			m_bRecycle;		//�A�N�e�B�u�^�C�v(�������蓮
	float			m_fAlpha;
	float			m_fVerTexUSize;
	int				m_nVerTexFrame;
	int				m_nLife;
	int				m_nRecTime;		//���ݎ���
	int				m_nMaxTime;		//�ő厞��
	int				m_nStopTime;	//��~����
	int				m_nTimePerFrame;//TimeFrame Per AnimationFrame
	int				m_nMaxFrame;	//MAX Frame
	int				m_nRecFrame;	//Recent Frame
	int				m_nMoveMode;	//�ړ����̃��[�h
	
	int				m_nMoveStep[QUARK_STATS_MAX];
	D3DXVECTOR3		m_vDestPosAndSpeed[QUARK_STATS_MAX];		//�ڕWPos
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