//-----------------------------------------------------------
//エンティティ　マスターズクラスH
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_Master_Entity.h"
c_Master_Entity::c_Master_Entity()
{
	ResetMasterStats();
}
c_Master_Entity::~c_Master_Entity()
{
}
void c_Master_Entity::ResetMasterStats(void)
{

	m_nTime				= 0;
	m_nMaxTime			= 0;
	m_nMoveMode			= ENTITY_MOVE_MODE_KEEP_A;
	m_nTriggerType		= TRIGGER_TYPE_MANUAL;
	m_bUse				= false;
	m_bTriggered		= false;
	m_bHitBox			= false;
	m_bMove				= false;
	m_bAnimated			= false;
	m_bActive			= false;

	m_uPlace			= C_FIELDPLACE(0,0);
	D3DV_INIT(m_vSize);
	D3DV_INIT(m_vSpeed);
	D3DV_INIT(m_vDriection);
	D3DV_INIT(m_vDestPos);


	m_pMum = NULL;
	m_pTargetEntity	= NULL;
	m_pPlayer	= NULL;
}
void c_Master_Entity::UninitEntity(void)
{
	D3DV_INIT(m_vSize);
	D3DV_INIT(m_vSpeed);
	D3DV_INIT(m_vDriection);
	D3DV_INIT(m_vDestPos);
	if(m_pMum)
	{
		m_pMum = NULL;
	}
	if(m_pTargetEntity)
	{
		m_pTargetEntity	= NULL;
	}
	if(m_pPlayer)
	m_pPlayer	= NULL;
}
bool c_Master_Entity::Entity_HitPlayerChecker(void)
{
	bool res = false;
		res = HitBoxWorld_2D(m_pPlayer->GetPos(),PLAYER_HEIGHT ,PLAYER_WIDTH,
							this->GetPos(),this->m_vSize.y,this->m_vSize.x,3.0f);
	return res;
}
void c_Master_Entity::Entity_PlayerExclusion(void)
{
	D3DXVECTOR3 vSizeD = this->GetSize();
	this->HitExclusion2D(*m_pPlayer->GetPlayerPosAdress(),PLAYER_WIDTH,PLAYER_HEIGHT,
		this->m_vPos,vSizeD.x,vSizeD.y,*m_pPlayer->GetPlayerSpeed(),0.01);
}
void c_Master_Entity::UpdateEntity(void)
{
	if(this->m_bUse)
	{
		switch(m_nTriggerType)
		{
		case TRIGGER_TYPE_AUTO:	
			m_bTriggered = true;
			break;
		case TRIGGER_TYPE_SEMI:
			m_bTriggered = Entity_HitPlayerChecker();
			break;
		case TRIGGER_TYPE_MANUAL:
			break;
		}
		if(this->m_uTypeName == ENTITY_NAME_TRIGGER)
		{
			if(this->m_bTriggered)
				this->m_pTargetEntity->m_bTriggered = true;
			else
				this->m_pTargetEntity->m_bTriggered = false;
		}
		if(this->m_bMove)
			this->Entity_Move();
	}

	if(m_bHitBox && Entity_HitPlayerChecker())
		this->Entity_PlayerExclusion();
	this->UpdatePrimitive();		
}
void c_Master_Entity::Entity_Draw(void)
{
		DrawPrimitive();
}
void c_Master_Entity::Entity_Move(void)
{
	if(m_nTriggerType != TRIGGER_TYPE_AUTO)
		if(m_bTriggered)
		{
 			m_nMoveMode = ENTITY_MOVE_MODE_MOVE_A;
			m_bActive	= true;
		}

	switch(m_nMoveMode)
	{
	case ENTITY_MOVE_MODE_KEEP_A:
		//全自動ドアー場合
		if(m_nTriggerType == TRIGGER_TYPE_AUTO)
		{
			m_bActive = true;
			this->m_nTime --;
			if(this->m_nTime <= 0)
			{
				m_nMoveMode = ENTITY_MOVE_MODE_MOVE_A;
				m_nTime	= m_nMaxTime;
			}
		}
		else
		{
			m_bTriggered = false;
			m_bActive = false;
		}

		break;
	case ENTITY_MOVE_MODE_MOVE_A:
		this->m_vPos += this->m_vSpeed;
		this->m_nTime --;
		if(this->m_nTime <= 0)
		{
			m_nMoveMode = ENTITY_MOVE_MODE_KEEP_B;
			m_nTime	= m_nMaxTime;
		}
		break;
	case ENTITY_MOVE_MODE_KEEP_B:

		this->m_nTime --;
		if(this->m_nTime <= 0)
		{
			m_nMoveMode = ENTITY_MOVE_MODE_MOVE_B;
			m_nTime	= m_nMaxTime;
		}
		break;
	case ENTITY_MOVE_MODE_MOVE_B:
		this->m_vPos -= this->m_vSpeed;
		this->m_nTime --;
		if(this->m_nTime <= 0)
		{
			this->m_vPos = this->m_vDestPos;
			m_nMoveMode = ENTITY_MOVE_MODE_KEEP_A;
			m_nTime	= m_nMaxTime;
		}
		break;
	}
}
void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, bool bInput)
{
	switch(state)
	{
	case ENTITY_STATE_USE: m_bUse = bInput;
		break;
	case ENTITY_STATE_HITBOX: m_bHitBox	= bInput;
		break;
	case ENTITY_STATE_MOVE:m_bMove = bInput;
		break;
	case ENTITY_STATE_ANIMATED:m_bAnimated = bInput;
		break;
	}
}
void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, int nInput)
{
	switch(state)
	{
	case ENTITY_STATE_TIME:	m_nMaxTime  = nInput; m_nTime = nInput;
		break;
	case ENTITY_STATE_TYPENAME:	m_uTypeName	= (ENTITY_TYPE_NAME)nInput;
		break;
	case ENTITY_STATE_TRIGGER_TYPE: m_nTriggerType = (TRIGGER_TYPE)nInput;
		break;
	}
}

void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, D3DXVECTOR3 vInput)
{
	switch(state)
	{
	case ENTITY_STATE_POS:		m_vPos	= vInput;
		break;
	case ENTITY_STATE_SIZE:		m_vSize = vInput;
		break;
	case ENTITY_STATE_SPEED:		m_vSpeed = vInput;
		break;
	case ENTITY_STATE_DIRECTOIN:	m_vDriection = vInput;
		break;
	case ENTITY_STATE_DESTPOS:		m_vDestPos	= vInput;
		break;
	}
}
void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, c_Master_Entity* pInput)
{
	switch(state)
	{
	case ENTITY_STATE_MOTHER:	m_pMum  = pInput;
		break;
	case ENTITY_STATE_TARGET:	m_pTargetEntity	= pInput;
		break;
	}
}
void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, C_FIELDPLACE place)
{
	switch(state)
	{
	case ENTITY_STATE_PLACE:
		m_uPlace = place;
		break;
	}
}
void c_Master_Entity::SetEntityBaseState(ENTITY_BASE_STATS state, c_Player* pPlayer)
{
	switch(state)
	{
	case ENTITY_STATE_PLAYER_P:
		this->m_pPlayer = pPlayer;
		break;
	}

}
c_Master_Entity* c_Master_Entity::GetThisEntity(void)
{
	return this;
}