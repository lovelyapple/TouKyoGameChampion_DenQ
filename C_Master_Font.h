//============================================================================
//C_Font.h
//============================================================================
#ifndef _CLASS_FONT_H_
#define _CLASS_FONT_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
//-----------------------------------
//�}�N����`
#define FONT_SIZE	(18)
//�N���X�錾
class c_Font
{
public:
	c_Font();	//�R���X�g
	~c_Font();	//�f�X�R��
	void CreatFont(LPCSTR style,float fsize);	//�t�H���g�̎�ށA�T�C�Y�ݒ�
	void SetFontPos(D3DXVECTOR3 pos);	//�t�H���g�̕\���ʒu�ݒ�
	virtual void Draw();			//�t�H���g�`��
	void DrawCord(LPCSTR style,int message,D3DXVECTOR3 pos);	//�t�H���g��ށA�`��(int)�ݒ�
	void DrawCord(LPCSTR style,float number,D3DXVECTOR3 pos);	//�t�H���g��ށA�`��(float)�ݒ�

private:
	LPD3DXFONT		m_pFont;
	D3DXVECTOR3		m_vPos;
	float m_fsize;
	LPCSTR m_lFontStyle;

protected:
};


#endif