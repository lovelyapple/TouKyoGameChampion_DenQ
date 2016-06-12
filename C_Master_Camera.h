//-----------------------------------------------------------
//�J�����}�X�^�[�N���Xh
//-----------------------------------------------------------
#ifndef _CLASS_CAMERA_MASTER_H_
#define _CLASS_CAMERA_MASTER_H_

#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
#include "Sys_Shader.h"

class c_Camera
{
public :
	c_Camera();
	HRESULT InitCamera(bool bWindow);
	virtual	void Update(void);
	virtual void Draw(void);
	void	UninitCamera(void);

	D3DXMATRIX	m_matProj;		// �v���W�F�N�V���� �}�g���b�N�X
	D3DXMATRIX	m_matView;		// �r���[ �}�g���b�N�X
	D3DXVECTOR3	m_vCamera;		// �J�����̎��ۂ̍��W
	D3DXVECTOR3 m_vRot;			// �J�����̉�]
	//D3DXVECTOR3	m_vAngle;		// �J�����̉�]�i�΁j
private:

};

#endif