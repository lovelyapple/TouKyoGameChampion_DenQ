//=============================================================================
//
// �^�C�g����ʏ���
//
//=============================================================================
#ifndef _C_TITLE_H_
#define _C_TITLE_H_

//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//-------------------------------------
#include "C_Master_Primitive.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//�}�N����`
//-------------------------------------
#define TEXTURE_HEIGHT (1)
#define TEXTURE_WIDTH (1)
#define TEXTURE_TITLE ("data/Texture/denkyu.png")
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class  c_Logo : public c_Master_Primitive
{
public:
	c_Logo();
	HRESULT	Init(void);
	void	Update(void);	
	void	SetVerTxBuff(void);	

private:
protected:
};

#endif