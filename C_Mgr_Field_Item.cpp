//-----------------------------------------------------------
//C_MGR_FIELD_ITEM
//-----------------------------------------------------------

//--------------------------------------
//システムインクルード
#include "C_Mgr_Field_Item.h"
const char* FileName[ENTITY_NAME_MAX]={
	"data/Texture/Items/Item_test.png",
	"data/Texture/Items/Item_test.png",
	"data/Texture/Items/Item_test.png",
	"data/Texture/Items/Item_test.png"
};
c_Mgr_Field_Item::c_Mgr_Field_Item(c_Player* pPlayer)
{
	m_pPlayer = pPlayer;
}
void c_Mgr_Field_Item::Init_MGR_Entity(void)
{
	for(int nCntEntity = 0;nCntEntity < MAX_ENTITY;nCntEntity++)
	{
		m_pEntity[nCntEntity] = NULL;
	}
	CreateEntity(C_FIELDPLACE(86,3),ENTITY_NAME_FINISH_POINT,true,NULL);
	CreateEntity(C_FIELDPLACE(8,3),ENTITY_NAME_DOOR_AUTO_UP,false,NULL);
	int DoorDown	= CreateEntity(C_FIELDPLACE(9,1),ENTITY_NAME_DOOR_AUTO_DOWN,false,NULL);
	int trigger		= CreateEntity(C_FIELDPLACE(3,3),ENTITY_NAME_TRIGGER,true,NULL);
	m_pEntity[trigger]->SetEntityBaseState(ENTITY_STATE_TARGET,m_pEntity[DoorDown]->GetThisEntity());
}
void c_Mgr_Field_Item::Uninit_MGR_Entity(void)
{
	m_pPlayer=NULL;
	for(int nCntEntity = 0;nCntEntity < MAX_ENTITY;nCntEntity++)
	{
		if(!m_pEntity[nCntEntity]) continue;
		m_pEntity[nCntEntity]->UninitEntity();
		SAFE_DELETE(m_pEntity[nCntEntity]);
	}
}
void c_Mgr_Field_Item::Update_MGR_Entity(void)
{
	for(int nCntEntity = 0;nCntEntity < MAX_ENTITY;nCntEntity++)
	{
		if(!m_pEntity[nCntEntity]) continue;
		m_pEntity[nCntEntity]->UpdateEntity();
	}
}
void c_Mgr_Field_Item::Draw_MGR_Entity(void)
{
	for(int nCntEntity = 0;nCntEntity < MAX_ENTITY;nCntEntity++)
	{
		if(!m_pEntity[nCntEntity]) continue;
		m_pEntity[nCntEntity]->Entity_Draw();
	}
}
int c_Mgr_Field_Item::CreateEntity(C_FIELDPLACE place, int nType,bool bUserTrigger,long lParam)
{
	int Num = 9999;
	c_Master_Entity* pEntity;
	for(int nCntEntity = 0;nCntEntity < MAX_ENTITY;nCntEntity++)
	{
		if(m_pEntity[nCntEntity]) continue;
		if(nCntEntity == MAX_ENTITY-1)
		{
			return Num;
			break;
		}
		m_pEntity[nCntEntity] = new c_Master_Entity;
		pEntity = m_pEntity[nCntEntity];
		Num = nCntEntity;
		break;
	}


	//---------------------------------------------
	//プリミティブに関する設定
	pEntity->SetFileName(FileName[nType]);
	D3DXVECTOR3	pos;
	D3DV_INIT(pos);
	SetPosFromFeildPlace(&place,&pos);
	pEntity->SetPos(pos);
	pEntity->SetEntityBaseState(ENTITY_STATE_TYPENAME,nType);
	pEntity->SetEntityBaseState(ENTITY_STATE_PLACE,place);
	
	switch(nType)
	{
	case ENTITY_NAME_TRIGGER:
		pEntity->SetEntityBaseState(ENTITY_STATE_USE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_HITBOX,false);
		pEntity->SetEntityBaseState(ENTITY_STATE_TRIGGER_TYPE,TRIGGER_TYPE_SEMI);
		pEntity->SetEntityBaseState(ENTITY_STATE_PLAYER_P,m_pPlayer);
		pEntity->SetSize(D3DXVECTOR3(BLOCK_SIZE*0.5f,BLOCK_SIZE*0.5f,0.0f));
		

		break;
	case ENTITY_NAME_FINISH_POINT:
		pEntity->SetEntityBaseState(ENTITY_STATE_USE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_TRIGGER_TYPE,TRIGGER_TYPE_SEMI);
		pEntity->SetEntityBaseState(ENTITY_STATE_PLAYER_P,m_pPlayer);
		pEntity->SetSize(D3DXVECTOR3(BLOCK_SIZE*0.5f,BLOCK_SIZE*0.5f,0.0f));
		break;
	case ENTITY_NAME_DOOR_AUTO_UP:
		pEntity->SetEntityBaseState(ENTITY_STATE_USE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_HITBOX,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_MOVE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_TRIGGER_TYPE,TRIGGER_TYPE_SEMI);
		pEntity->SetEntityBaseState(ENTITY_STATE_SIZE,
									D3DXVECTOR3(BLOCK_SIZE * 0.2f,BLOCK_SIZE * 0.5f,0.0f));
		pEntity->SetEntityBaseState(ENTITY_STATE_DIRECTOIN,
									D3DXVECTOR3(0,BLOCK_SIZE,0));
		pEntity->SetEntityBaseState(ENTITY_STATE_SPEED,
									D3DXVECTOR3(0,ENTITY_DOOR_SPEED,0.0f));
		pEntity->SetEntityBaseState(ENTITY_STATE_DESTPOS,
									pos);
		pEntity->SetEntityBaseState(ENTITY_STATE_TIME,60);
		pEntity->SetEntityBaseState(ENTITY_STATE_PLAYER_P,m_pPlayer);
		break;
	case ENTITY_NAME_DOOR_AUTO_DOWN:
		pEntity->SetEntityBaseState(ENTITY_STATE_USE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_HITBOX,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_MOVE,true);
		pEntity->SetEntityBaseState(ENTITY_STATE_TRIGGER_TYPE,TRIGGER_TYPE_MANUAL);
		pEntity->SetEntityBaseState(ENTITY_STATE_SIZE,
									D3DXVECTOR3(BLOCK_SIZE * 0.2f,BLOCK_SIZE * 0.5f,0.0f));
		pEntity->SetEntityBaseState(ENTITY_STATE_DIRECTOIN,
									D3DXVECTOR3(0,BLOCK_SIZE,0));
		pEntity->SetEntityBaseState(ENTITY_STATE_SPEED,
									D3DXVECTOR3(0,-ENTITY_DOOR_SPEED,0.0f));
		pEntity->SetEntityBaseState(ENTITY_STATE_DESTPOS,
									pos);
		pEntity->SetEntityBaseState(ENTITY_STATE_TIME,60);
		pEntity->SetEntityBaseState(ENTITY_STATE_PLAYER_P,m_pPlayer);
		break;
	//case ENTITY_NAME_FINISH_POINT:
	//	break;
	case ENTITY_NAME_MAX:						
		break;
	}
	pEntity->Init();
	return Num;


}
