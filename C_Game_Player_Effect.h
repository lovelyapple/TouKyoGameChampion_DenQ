//-----------------------------------------------------------
//�v���C���[�N���X
//-----------------------------------------------------------
#ifndef _C_PLAYERLIGHT_H_
#define _C_PLAYERLIGHT_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Global_Variable.h"

//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Primitive.h"


#include "C_Game_Player.h"

//--------------------------------------
//�C���X�^���X�C���N���[�h
//--------------------------------------
//�}�N����`
#define START_ALPHA		(0.3)
#define PLAYER_EFFECT_LIGHT_MIN_SIZE	(1.0f)
#define PLAYER_EFFECT_LIGHT_MAX_SIZE	(6.0f)
#define PLAYER_EFFECT_LIGHT_SIZE_CHANGE	(0.05f)


#define PLAYER_EFFECT_LIGHT_MIN_ALPH	(0.1f)
#define PLAYER_EFFECT_LIGHT_MAX_ALPH	(0.3f)
#define PLAYER_EFFECT_LIGHT_ALPH_CHANGE	(0.01f)

#define PLAYER_EFFECT_LIGHT_NEAR_POS	(1.0f)
#define FILE_NAME_PLAYERLIGHT	("data/Texture/PlayerLight.png")
//--------------------------------------
//�\���̐錾

//--------------------------------------
//�N���X�錾
class c_PlayerLight : public c_Master_Primitive
{
public:
	c_PlayerLight(c_Player* pPlayer);
	~c_PlayerLight();
	//HRESULT	Init(void);
	void	Update(void);								// �X�V
	void	GetPlayerLight(bool light);					//
	void	SetVerTexBuff(void);							// �o�b�t�@�X�V
	/*void	SetPlayerPos(c_Player* pPlayer);*/
private:
	bool	m_bUse;
	float	m_fAlpha;

	c_Player* m_pPlayer;
};
#endif