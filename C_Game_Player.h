//-----------------------------------------------------------
//�v���C���[�N���X
//-----------------------------------------------------------
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Input.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Primitive.h"
#include "C_SYS_STAGE.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
#include "C_Game_Block.h"
//--------------------------------------
//�}�N����`
#define PLAYER_HEIGHT	(BLOCK_SIZE * 1.5 * 0.5f)
#define PLAYER_WIDTH	(BLOCK_SIZE * 1.0 * 0.5f)
#define FILE_NAME_PLAYER	("data/Texture/DenQ_Animation.png")
#define MAX_FRAME			(12)
#define FRAME_PER_TIME		(6)
#define VALUE_WALK_SPEED			(0.005f)
#define VALUE_WALK_MAX_SPEED		(0.06f)
#define VALUE_SPEED_ATTENUSUION		(0.92f)
#define VALUE_SPPED_RESET			(0.01f)
#define VALUE_DUSH_TIMES			(2)
#define VALUE_DUSH_FRAMETIMES		(6)
#define	VALUE_DUSH_SPEED			(VALUE_WALK_SPEED * VALUE_DUSH_TIMES)
#define VALUE_DUSH_MAX_SPEED		(VALUE_WALK_MAX_SPEED * VALUE_DUSH_TIMES)
#define VALUE_JUMP_MOVE_SPEED	(0.01)
#define VALUE_JUMP_MAX_MOVE_SPEED	(0.1)
#define VALUE_JUMP_SPEED	(0.33f)
#define PLAYER_MAX_HEAT			(100)
#define PLAYER_MAX_HEAT_TIME	(10 * 60)
#define PLAYER_HEAT_PER_TIME	((float)PLAYER_MAX_HEAT / (float)PLAYER_MAX_HEAT_TIME)
#define PLAYER_COOL_PER_TIME	((float)PLAYER_HEAT_PER_TIME * 0.7f)
const int g_FrameDislight[4] = {3,10,14,21};
//--------------------------------------
//�\���̐錾
typedef enum
{
	MOVE_TYPE_WALK = 0,
	MOVE_TYPE_JUMP,
	//MOVE_TYPE_DUSH,
	//MOVE_TYPE_SLIDE,
	//MOVE_TYPE_DROPING,
	MOVE_TYPE_MAX,
}MOVE_TYPE;						//�v���C���[�̍s�����
typedef struct{
	bool  bRTouch;
	bool  bLTouch;
	float fRDist;  
	float fLDist;
}PLAYER_WALK_STATE;
const PLAYER_WALK_STATE g_WalkState[MAX_FRAME / 2] = {{true, true, 0.2f, 0.2f},// �E�����A�������A�E���������A����������
													 {true, true, 0.2f, 0.2f},// �i��0�`5�̃A�j���[�V�����͍��E�Ώۂł��邱�Ɓj
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f}};

//--------------------------------------
//�N���X�錾
class c_Player : public c_Master_Primitive,public c_Physic
{
typedef struct{
bool  bTouched;
int	  nNearBox_X;
int   nNearBox_Y;
float nNearBoxDist;
}FOOT_STATS;
public:
	c_Player();
	c_Player(C_FIELDPLACE place);
	HRESULT	Init(void);
	void	Reset(void);								// �f�[�^������
	void	Update(void);								// �X�V
	void	GronudTouchedCheck(void);					//
	int		MoveCheck(void);							//
	void	SetMoveTypeFrame(int nType,int MaxFrame);	//
	void	SetVerTxBuff(void);							// �o�b�t�@�X�V
	void	SetStage(c_Stage* pStage);					// 
	bool	GetLightSwitch(void);						// �_�ŊǗ�
	int		GetPlayerFrame(void);						// �t���[���擾
	int		GetPlayerHeat(void);
	D3DXVECTOR3* GetPlayerSpeed(void);

	void    InitFootState(FOOT_STATS *Foot);
	bool	GetFootRTorF(void);
	bool	GetFootLTorF(void);
	D3DXVECTOR3* GetPlayerPosAdress(void);
private:
	D3DXVECTOR3			m_vAcceleration;	//�����x
	D3DXVECTOR3			m_vRecSpeed;		//���݂̑��x
	FOOT_STATS			m_uLeftFoot;		//�����^�b�`
	FOOT_STATS			m_uRightFoot;		//�E���^�b�`
	//bool				m_bGravitCheck;		//�d��
	bool				m_bDirection;		//���E�̔���
	bool				m_bLighted;			//�d���t���O
	int					m_nMaxFrame[MOVE_TYPE_MAX];
	int					m_nRecFrame;
	int					m_nTimeFrame;
	int					m_uMoveType;		//�ړ����
	float				m_fHeat;			//���x
	float				m_vVerTexSizeH;
	float				m_vVerTexSizeW[MOVE_TYPE_MAX];	//�v���C���[�t���[���T�C�Y


	c_Stage*			m_pStage;
	bool				m_bAllTouched;		//�A���t�@�o�[�W������Ԃł̂�����ڒn����
};
#endif