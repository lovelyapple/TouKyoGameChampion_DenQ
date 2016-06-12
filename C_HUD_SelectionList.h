//-----------------------------------------------------------
//���j���[�}�X�^�[�Y�N���X
//-----------------------------------------------------------
#ifndef	_C_SELECTIONLIST_H_
#define _C_SELECTIONLIST_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "Sys_Input.h"

//--------------------------------------
//�C���X�^���X�C���N���[�h
#include "C_HUD_Selection.h"
//--------------------------------------
//�}�N����`
#define CURSOR_SIZE				(D3DXVECTOR3(2.0f,0.5f,0.0f))
#define CURSOR_FILE_NAME		("data/Texture/MenuCursor.png")	
#define MAX_SELECTION			(8)
#define BACK_DEST_POS			(D3DXVECTOR3(-4.0f,0.0f,1.0f))
#define SELECTION_MOVE_TIME		(1*60)
#define	ALPHA_CHANGE_VALUE		(1.0f / SELECTION_MOVE_TIME)
//--------------------------------------
//�\���̐錾
typedef enum
{
	SELECTION_TYPE_MOVING = 0,			//�ړ����
	SELECTION_TYPE_FRONT,				//�t�����g��~���
	SELECTION_TYPE_BACK,				//�o�b�N��~���
	SELECTION_TYPE_MAX,					//����
}SELECTION_TYPE;
//--------------------------------------
//�N���X�錾
class c_SelectionList
{
public:
	c_SelectionList();
	void InitSelectionList(void);			//���X�g�̍��ڂ�NULL�ɏ�����
	void RunFadeList(void);					//���X�g�̃t�����g�o�b�N�ړ�
	void UpdateList(void);
	void DrawList(void);					//�т傮��
	void UninitSelectionList(void);			//���X�g���ڂ̊J������
	void CreatList(LPCSTR FileName[],					//�t�@�C������
					int MaxItem,						//�ő區�ڐ�
					D3DXVECTOR3 ListPos,				//���X�g�̃t�����g�ʒu
					D3DXVECTOR3 size);					//�傫��
	bool TypeCheck(void);								//�ړ��\�`�F�b�N
	void SetListPos(D3DXVECTOR3 pos);					//�ʒu�̎w��
	void SetListRot(D3DXVECTOR3 rot);					//��]�̎w��
	void ChangeType(int nType);							//�ړ��O����

	c_Selection*		m_pSelection[MAX_SELECTION];
private:
	
	LPCSTR*				m_pFileName;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vRot;

	D3DXVECTOR3			m_vBackPos;			//�o�b�N�ʒu
	D3DXVECTOR3			m_vFrontPos;		//�t�����g�ʒu
	D3DXVECTOR3			m_vSpeed;			//
	int					m_nRecType;			//���݂�Type
	int					m_nDesType;			//�ڕW��Type
	int					m_nTime;			//�ړ�����
	float				m_fAlpha;			//���݂̃A���t�@�l
	float				m_fHeight;			//����



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