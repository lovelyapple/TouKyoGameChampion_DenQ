//-----------------------------------------------------------
//���f���}�X�^�[�N���Xcpp
//-----------------------------------------------------------
#ifndef _C_MODEL_H_
#define _C_MODEL_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Task.h"

//--------------------------------------
//�}�N����`

//--------------------------------------
//�\���̐錾
typedef struct
{
	LPD3DXMESH			pMesh;		//���b�V���I�u�W�F�N�g
	DWORD				dwNumMtrl;	//�}�e���A����
	D3DMATERIAL9*		pMtrl;		//�}�e���A���z��
	LPDIRECT3DTEXTURE9*	pTexture;	//�e�N�X�`���z��
	D3DXATTRIBUTERANGE*	pAttr;		//�����e�[�u��
	DWORD				dwNumAttr;	//������
	D3DXVECTOR3			vCenter;	//���E�����S���W
	float				fRadius;	//���E�����a
	D3DXVECTOR3			vBBox;		//���E�{�b�N�X�i�n�[�t�T�C�Y�j
}MODEL;
//--------------------------------------
//�N���X�錾
class c_Model: public c_Task
{
public:
	c_Model();
	c_Model(LPCSTR File , D3DXVECTOR3 pos);
	~c_Model();
	HRESULT LoadModel(void);

	void ReleaseModel(void);
	D3DXMATRIX* GetModelMatrix(void);
	D3DXVECTOR3* GetModelPos(void);
	virtual void UpdateModel(void);
	virtual void DrawModel(void);	
	virtual void UninitModel(void);

	virtual void UpdateTask(void);
	virtual void DrawTask(void);	
	virtual void UninitTask(void);
	D3DXVECTOR3	m_vPos;
private:
protected:

	MODEL*		m_pModel;
	LPCSTR		m_pszFName;

	D3DXMATRIX	m_matrix;

	
	D3DXVECTOR3	m_vAngle;
	D3DXVECTOR3	m_vScale;

};

#endif