//-----------------------------------------------------------
//�G���e�B�e�B�@�}�X�^�[�Y�N���XH
//-----------------------------------------------------------
#ifndef C_ENTITY_MASTER_H
#define C_ENTITY_MASTER_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "C_SYS_STAGE.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Primitive.h"
#include "Sys_C_Physic.h"
#include "C_Game_Player.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define ENTITY_DOOR_SPEED		(0.02f)
const	int FinishPointNum	= 0;
//--------------------------------------
//�\���̐錾
typedef enum
{
	ENTITY_STATE_USE = 0,			//�g�p�\��
	ENTITY_STATE_TYPENAME,			//���̎��̂̃^�C�v���O
	ENTITY_STATE_TRIGGER_TYPE,		//�����^�C�v
	ENTITY_STATE_HITBOX,			//�q�b�g�{�b�N�X
	ENTITY_STATE_MOVE,				//�ړ��\��
	ENTITY_STATE_ANIMATED,			//�A�j���[�V����
	ENTITY_STATE_TIME,				//���݂̃t���[������
	ENTITY_STATE_PLACE,				//�t�B�[���h���W
	ENTITY_STATE_POS,				//D3D���W(Primitive_SetPos���l)
	ENTITY_STATE_SIZE,				//�傫��(Primitive_SetSize���l)
	ENTITY_STATE_SPEED,				//���x�̎w��(������)
	ENTITY_STATE_DIRECTOIN,			//����
	ENTITY_STATE_DESTPOS,			//�ŏI�ړ��ʒu(�Ⴆ�΃h�A�̏ꍇ�A�܂��Ă����Ԃ͍ŏI�ʒu)
	ENTITY_STATE_MOTHER,			//��e�̃A�h���X
	ENTITY_STATE_TARGET,			//�q���̃A�h���X
	ENTITY_STATE_PLAYER_P,			//�v���C���[�|�C���^
	ENTITY_STATE_MAX,				//����
}ENTITY_BASE_STATS;
typedef enum
{
	ENTITY_NAME_TRIGGER = 0,
	ENTITY_NAME_FINISH_POINT,
	ENTITY_NAME_DOOR_AUTO_UP,
	ENTITY_NAME_DOOR_AUTO_DOWN,
	ENTITY_NAME_DOOR_TRIGGER_UP,
	ENTITY_NAME_DOOR_TRIGGER_DOWN,
	ENTITY_NAME_MAX,

}ENTITY_TYPE_NAME;
typedef enum
{
	ENTITY_MOVE_MODE_KEEP_A	= 0,
	ENTITY_MOVE_MODE_MOVE_A,
	ENTITY_MOVE_MODE_KEEP_B,
	ENTITY_MOVE_MODE_MOVE_B,
	ENTITY_MOVE_MODE_RESET,
	ENTITY_MOVE_MODE_MAX,
}ENTITY_MOVE_MODE;
typedef enum
{
	TRIGGER_TYPE_AUTO = 0,		//�S����
	TRIGGER_TYPE_SEMI,			//������
	TRIGGER_TYPE_MANUAL,		//�蓮
	TRIGGER_TYPE_MAX,
}TRIGGER_TYPE;
typedef struct
{
	C_FIELDPLACE	s_uPlace;				
}ENTITY_STRUCT;
//--------------------------------------
//�N���X�錾
class c_Master_Entity : public c_Master_Primitive ,public  c_Physic
{

public:
	c_Master_Entity();
	~c_Master_Entity();
	void ResetMasterStats(void);
	void UninitEntity(void);
	bool Entity_HitPlayerChecker(void);
	void Entity_PlayerExclusion(void);
	void Entity_Draw(void);
	virtual void UpdateEntity(void);

	void Entity_Move(void);

	void SetEntityBaseState(ENTITY_BASE_STATS, bool bInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, int	 nInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, D3DXVECTOR3 vInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, c_Master_Entity* pInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, c_Player* pPlayer);
	void SetEntityBaseState(ENTITY_BASE_STATS, C_FIELDPLACE place);

	c_Master_Entity* GetThisEntity(void);

protected:

	
	int				m_nTime;
	int				m_nMaxTime;
	int				m_nMoveMode;
	D3DXVECTOR3		m_vSpeed;
	D3DXVECTOR3		m_vDriection;
	D3DXVECTOR3		m_vDestPos;
	//primitive �̒��Ɂ@�K�v�Ȋ�{�ݒ� size pos ������
	//�A�b�v�f�[�^�[
	bool			m_bUse;			//�g�p�\
	TRIGGER_TYPE	m_nTriggerType;		//�������@
	bool			m_bTriggered;	//�U���t���O
	bool			m_bHitBox;		//���E�{�b�N�X
	bool			m_bMove;		//�ړ�
	bool			m_bAnimated;	//�A�j���[�V������
	bool			m_bActive;		//������
private:
	
	C_FIELDPLACE			m_uPlace;
	ENTITY_TYPE_NAME		m_uTypeName;

	c_Master_Entity*		m_pMum;
	c_Master_Entity*		m_pTargetEntity;
	c_Player*				m_pPlayer;
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