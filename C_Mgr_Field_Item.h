//-----------------------------------------------------------
//C_MGR_FIELD_ITEM
//-----------------------------------------------------------
#ifndef C_MGR_FIELD_ITEM_H
#define C_MGR_FIELD_ITEM_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Entity.h"
#include "C_Game_Player.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define MAX_ENTITY		(128)
//--------------------------------------
//�\���̐錾
//--------------------------------------
//�N���X�錾
class c_Mgr_Field_Item
{
public:
	c_Mgr_Field_Item(c_Player* pPlayer);
	void Init_MGR_Entity(void);
	void Uninit_MGR_Entity(void);
	void Update_MGR_Entity(void);
	void Draw_MGR_Entity(void);
	int  CreateEntity(C_FIELDPLACE place, 
							int nType,bool bUserTrigger,long lParam);
	c_Master_Entity*	m_pEntity[MAX_ENTITY];
private:
	c_Player*	m_pPlayer;

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