//============================================================================
//_CRAFT_HUD_.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_DATA.h"

S_BLOCK	g_Data_Blcok[BLOCK_TYPE_ACTIVE];
//-----------------------------------
//マスターズインクルード
//-----------------------------------
//インスタンスインクルード
//-----------------------------------
//プロトタイプ宣言
HRESULT Load_Block_Data(void);
void	Reset_Block_Data(void);

//-----------------------------------
HRESULT Load_Block_Data(void)
{
	FILE* fp;
	if((fp = fopen(FILE_NAME_BLOCK_DATA,"r")) == NULL)
	{
		if((fp = fopen(FILE_NAME_BLOCK_DATA,"w")) == NULL)
		{
			return S_FALSE;
		}
		else
		{
			Reset_Block_Data();
			for(int nCntBlock = 0;nCntBlock < BLOCK_TYPE_ACTIVE;nCntBlock++)
			{
				fprintf(fp,"%d,%d,%d,%d\n",	g_Data_Blcok[nCntBlock].nBoyance,
											g_Data_Blcok[nCntBlock].nHp,
											g_Data_Blcok[nCntBlock].nType,
											g_Data_Blcok[nCntBlock].nWeight);
			}
			fclose(fp);
			return S_OK;
		}
	}
	else
	{
			for(int nCntBlock = 0;nCntBlock < BLOCK_TYPE_ACTIVE;nCntBlock++)
			{
				fscanf(fp,"%d,%d,%d,%d\n",	&g_Data_Blcok[nCntBlock].nBoyance,
											&g_Data_Blcok[nCntBlock].nHp,
											&g_Data_Blcok[nCntBlock].nType,
											&g_Data_Blcok[nCntBlock].nWeight);
			}
	}
	return S_OK;
}
//-----------------------------------
void	Init_Data(void)
{
	for(int nCntBlock = 0;nCntBlock < BLOCK_TYPE_MAX;nCntBlock++)
	{
		g_Data_Blcok[nCntBlock].nBoyance	= 0;
		g_Data_Blcok[nCntBlock].nHp			= 0;
		g_Data_Blcok[nCntBlock].nType		= 0;
		g_Data_Blcok[nCntBlock].nWeight		= 0;
	}

}
void	Reset_Block_Data(void)
{
		g_Data_Blcok[BLOCK_TYPE_NORMAL].nBoyance	= 40;
		g_Data_Blcok[BLOCK_TYPE_NORMAL].nHp			= 30;
		g_Data_Blcok[BLOCK_TYPE_NORMAL].nType		= BLOCK_TYPE_NORMAL;
		g_Data_Blcok[BLOCK_TYPE_NORMAL].nWeight		= 50;

		g_Data_Blcok[BLOCK_TYPE_METAL].nBoyance		= 20;
		g_Data_Blcok[BLOCK_TYPE_METAL].nHp			= 50;
		g_Data_Blcok[BLOCK_TYPE_METAL].nType		= BLOCK_TYPE_METAL;
		g_Data_Blcok[BLOCK_TYPE_METAL].nWeight		= 90;

		g_Data_Blcok[BLOCK_TYPE_ENGINE].nBoyance	= 0;
		g_Data_Blcok[BLOCK_TYPE_ENGINE].nHp			= 40;
		g_Data_Blcok[BLOCK_TYPE_ENGINE].nType		= BLOCK_TYPE_ENGINE;
		g_Data_Blcok[BLOCK_TYPE_ENGINE].nWeight		= 70;

		g_Data_Blcok[BLOCK_TYPE_WOOD].nBoyance		= 80;
		g_Data_Blcok[BLOCK_TYPE_WOOD].nHp			= 20;
		g_Data_Blcok[BLOCK_TYPE_WOOD].nType			= BLOCK_TYPE_WOOD;
		g_Data_Blcok[BLOCK_TYPE_WOOD].nWeight		= 20;

		g_Data_Blcok[BLOCK_TYPE_ACTIVE].nBoyance	= 12;
		g_Data_Blcok[BLOCK_TYPE_ACTIVE].nHp			= 1;
		g_Data_Blcok[BLOCK_TYPE_ACTIVE].nType		= BLOCK_TYPE_ACTIVE;
		g_Data_Blcok[BLOCK_TYPE_ACTIVE].nWeight		= 1;
}
void SetBlockStats(c_Block* Block)
{
	Block->m_uBlock.nBoyance	= g_Data_Blcok[Block->m_uBlock.nType].nBoyance;
	Block->m_uBlock.nHp			= g_Data_Blcok[Block->m_uBlock.nType].nHp;
	Block->m_uBlock.nWeight		= g_Data_Blcok[Block->m_uBlock.nType].nWeight;
}
