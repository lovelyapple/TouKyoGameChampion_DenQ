//-----------------------------------------------------------
//�X�e�[�W�N���X
//-----------------------------------------------------------
#ifndef _C_GAME_SATGE_BACKGOUNRD_H
#define _C_GAME_SATGE_BACKGOUNRD_H
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Shader.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Model.h"
//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define FILENAME_STAGEBG	("data/model/Box.x")
//--------------------------------------
//�N���X�錾
class c_StageBG : public c_Model
{
public:
	c_StageBG(LPCSTR File,D3DXVECTOR3 pos);
	~c_StageBG();
	void Update(void);
	void ShaderDraw(void);
private:
};

#endif