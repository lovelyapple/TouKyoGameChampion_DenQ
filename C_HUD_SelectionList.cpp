//-----------------------------------------------------------
//メニューマスターズクラス
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_HUD_SelectionList.h"
c_SelectionList::c_SelectionList()
{
	
}
void c_SelectionList::InitSelectionList(void)
{
	for(int nCntItem = 0; nCntItem < MAX_SELECTION;nCntItem++)
	{
		m_pSelection[nCntItem] = NULL;	
	}
	m_pFileName = NULL;
	D3DV_INIT(m_vPos);
	D3DV_INIT(m_vRot);
	m_nRecType = SELECTION_TYPE_FRONT;
	m_nRecType = SELECTION_TYPE_FRONT;
	m_fAlpha = 1.0f;
	m_fHeight = 0.0f;
}
void c_SelectionList::CreatList(LPCSTR FileName[],
								int MaxItem,
								D3DXVECTOR3 ListPos,
								D3DXVECTOR3 size)
{

	m_pFileName = FileName;
	m_vFrontPos = ListPos;
	m_vPos		= m_vFrontPos;
	m_vBackPos	= m_vFrontPos + BACK_DEST_POS;
	m_fHeight	= size.y;
	for(int nCntItem = 0; nCntItem < MaxItem;nCntItem++)
	{
		m_pSelection[nCntItem] = new c_Selection(m_pFileName[nCntItem],size);
		m_pSelection[nCntItem]->SetPos(D3DXVECTOR3( m_vPos.x,
													m_vPos.y - nCntItem * m_fHeight * 2,
													m_vPos.z));
		m_pSelection[nCntItem]->Init();
		m_pSelection[nCntItem]->SetVerTexBuff();
	}


}
void c_SelectionList::ChangeType(int nType)
{
	switch(nType)
	{
	case SELECTION_TYPE_FRONT:
		m_vSpeed	= (m_vFrontPos - m_vPos) / SELECTION_MOVE_TIME;
		m_nRecType	= SELECTION_TYPE_MOVING;
		m_nDesType	= nType;
		m_nTime		= SELECTION_MOVE_TIME;
		break;
	case SELECTION_TYPE_BACK:
		m_vSpeed	= (m_vBackPos - m_vPos) / SELECTION_MOVE_TIME;
		m_nRecType	= SELECTION_TYPE_MOVING;
		m_nDesType	= nType;
		m_nTime		= SELECTION_MOVE_TIME;
		break;
	}

}
void c_SelectionList::UninitSelectionList(void)
{
	for(int nCntItem = 0; nCntItem < MAX_SELECTION;nCntItem++)
	{
		if(!m_pSelection[nCntItem]) continue;
		m_pSelection[nCntItem]->Uninit();
		SAFE_DELETE(m_pSelection[nCntItem]);
	}

}
void c_SelectionList::SetListPos(D3DXVECTOR3 pos)
{
	m_vPos = pos;
	UpdateList();
}
void c_SelectionList::SetListRot(D3DXVECTOR3 rot)
{
	m_vRot = rot;
}

bool c_SelectionList::TypeCheck(void)
{
	if(m_nRecType == SELECTION_TYPE_MOVING)
		return false;
	else return true;
}
void c_SelectionList::UpdateList(void)
{
	if(m_nRecType = SELECTION_TYPE_FRONT)
	{
		//ここでメニュー―項目のエフェクトを書く
	}

	RunFadeList();
	for(int nCntItem = 0; nCntItem < MAX_SELECTION;nCntItem++)
	{
		if(!m_pSelection[nCntItem]) continue;
		m_pSelection[nCntItem]->SetPos(D3DXVECTOR3( m_vPos.x,
													m_vPos.y - nCntItem * m_fHeight * 2,
													m_vPos.z));
		m_pSelection[nCntItem]->SetRot(m_vRot);
		m_pSelection[nCntItem]->Update();
	}
}

void c_SelectionList::RunFadeList(void)
{
	switch(m_nRecType)
	{
	case SELECTION_TYPE_MOVING:

		m_vPos += m_vSpeed;
		if(m_nDesType == SELECTION_TYPE_FRONT)
		{
			m_fAlpha += ALPHA_CHANGE_VALUE;
		}
		else
		{
			m_fAlpha -= ALPHA_CHANGE_VALUE;
		}
		m_nTime--;
		if(m_nTime<= 0)
		{
			if(m_nDesType == SELECTION_TYPE_FRONT)
			{
				m_vPos = m_vFrontPos;
				m_fAlpha = 0.9f;
				
			}
			else if (m_nDesType == SELECTION_TYPE_BACK)
			{
				m_vPos = m_vBackPos;
				m_fAlpha = 0.0f;
			}
			m_nRecType	= m_nDesType;
			m_nTime		= SELECTION_MOVE_TIME;
		}

		break;
	case SELECTION_TYPE_FRONT:
		break;
	case SELECTION_TYPE_BACK:
		break;
	}
}
void c_SelectionList::DrawList(void)
{
	for(int nCntItem = 0; nCntItem < MAX_SELECTION;nCntItem++)
	{
		if(!m_pSelection[nCntItem]) continue;
		m_pSelection[nCntItem]->DrawPrimitive();
	}

}