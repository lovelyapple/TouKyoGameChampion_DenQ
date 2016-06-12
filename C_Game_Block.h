//-----------------------------------------------------------
//�Q�[�����̃u���b�N
//-----------------------------------------------------------
#ifndef _C_BLOCK_H_
#define _C_BLOCK_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Model.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define BLOCK_SIZE			(1.0f)
//--------------------------------------
//�\���̐錾
typedef struct 
{
	int		nType;
}S_BLOCK;
typedef enum
{
	BLOCK_TYPE_NOMAL_ELE = 0,
	BLOCK_TYPE_HEIGH_ELE,
	BLOCK_TYPE_MAX,
}BLOCK_TYPE;
//--------------------------------------
//�N���X�錾
class C_FIELDPLACE
{
public:
	C_FIELDPLACE();
	C_FIELDPLACE(int inputx,int inputy);
	int x,y;
};
class c_Block :public c_Model
{
public:	
	c_Block();						//�R���X�g���N�^
	c_Block(int,C_FIELDPLACE*);		//�R���X�g���N�^�I�[�o�[���[�h
	~c_Block();						//�f�X�g���N�^
	HRESULT	SetModel(void);			//
	void UpdateBlock(void);
	void FieldCheck(void);		//�t�B�[���h�͈̔̓`�F�b�N(�I���u���b�N�p)
	void DrawBlock(void);	

	C_FIELDPLACE	m_uPlace;		//�t�B�[���h���W
	S_BLOCK			m_uBlock;		//�u���b�N�\����
	void UpdateModel(void);
	void DrawModel(void);	



private:
protected:

};
//----------------------------------------
//���̑��̋@�\�֐�
void SetPosFromFeildPlace(C_FIELDPLACE*,D3DXVECTOR3*);
#endif
