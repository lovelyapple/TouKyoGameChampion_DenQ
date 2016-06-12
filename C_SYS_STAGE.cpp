//-----------------------------------------------------------
//ステージクラス
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "C_SYS_Stage.h"
//--------------------------------------
//マスターズインクルード

c_Stage::c_Stage(c_TaskList* List,C_FIELDPLACE player)
{
	m_uTaskList		= List;
	m_uPlayerPlace	= player;
}
c_Stage::~c_Stage()
{
}
void c_Stage::CreatBlockSingle(C_FIELDPLACE Place,int nType)
{
	if(!m_uBlock[Place.y][Place.x])
	{
		m_uBlock[Place.y][Place.x] = new c_Block(nType,&Place);
		SetPosFromFeildPlace(&Place,&m_uBlock[Place.y][Place.x]->m_vPos);
		m_uBlock[Place.y][Place.x]->SetModel();
		m_uBlock[Place.y][Place.x]->SetList(m_uTaskList->m_pActive,
											m_uTaskList->m_pRecycle);
		m_uBlock[Place.y][Place.x]->AddTask();
		m_uBlock[Place.y][Place.x]->UpdateBlock();
	}
}
void c_Stage::SetStageName(LPCSTR Name)
{
	m_lpzStageName = Name;
}
void c_Stage::InitAllBlock(void)
{
	for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
		for(int x = 0;x < MAX_FIELD_WIDTH; x++)
		{
			m_uBlock[y][x] = NULL;
		}
}

void c_Stage::ClearBlockSingle(C_FIELDPLACE Place)
{
	if(m_uBlock[Place.y][Place.x])
	{
		m_uBlock[Place.y][Place.x]->MoveOutFromActive();
		m_uBlock[Place.y][Place.x]->CleanArray();
		m_uBlock[Place.y][Place.x]->UninitModel();
		m_uBlock[Place.y][Place.x] = NULL;
	}

}

void c_Stage::ClearAllBlock(void)
{
	for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
		for(int x = 0;x < MAX_FIELD_WIDTH; x++)
		{
			ClearBlockSingle(C_FIELDPLACE(x,y));
		}
}
HRESULT c_Stage::SaveStage(void)
{
	FILE* fp;

	if((fp = fopen(m_lpzStageName,"w")) == NULL)
	{
		return 1;
	}
	else
	{
		for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
			for(int x = 0;x < MAX_FIELD_WIDTH; x++)
				{
					if(m_uBlock[y][x] == NULL)
					{
						fprintf(fp,"%d,",99);
					}
					else
					{	
						fprintf(fp,"%d,",m_uBlock[y][x]->m_uBlock.nType);
					}
					if(x == MAX_FIELD_WIDTH-1)
					{
						fprintf(fp,"\n",99);
					}

				}		
	}
	fclose(fp);
	return S_OK;
}
HRESULT c_Stage::LoadStage(void)
{

	for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
		for(int x = 0;x < MAX_FIELD_WIDTH; x++)
			{
				if(m_uBlock[y][x])
				{
					C_FIELDPLACE place;
					place.x = x;
					place.y = y;
					ClearBlockSingle(place);
				}

			}

	FILE* fpc;
	if((fpc = fopen(m_lpzStageName,"r")) == NULL)
	{
		return 1;
	}
	else
	{
		for(int y = 0;y < MAX_FIELD_HEIGHT; y++)
			for(int x = 0;x < MAX_FIELD_WIDTH; x++)
			{
				int Block = 99;
				fscanf(fpc,"%d,",&Block);
				if( Block != 99)
				{
					
					this->CreatBlockSingle(C_FIELDPLACE(x,y),Block);
				}
			}
	}
		fclose(fpc);
		return S_OK;
}
