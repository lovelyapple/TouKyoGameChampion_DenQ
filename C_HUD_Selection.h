//-----------------------------------------------------------
//PauseMenu
//-----------------------------------------------------------
#ifndef _C_SELECTION_H
#define _C_SELECTION_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Primitive.h"
//--------------------------------------
//�}�N���錾


//-------------------------------------
//�N���X�錾
class c_Selection: public c_Master_Primitive
{
public:
	c_Selection(LPCSTR fzName,D3DXVECTOR3 size);
	~c_Selection();
	void Update(void);
	void SetVerTexBuff(void);
	void SetAlpha(float fAlpha);


private:

	float				m_fAlpha;			//�����x
};

#endif