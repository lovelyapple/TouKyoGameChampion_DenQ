//-----------------------------------------------------------
//�����G���W��
//-----------------------------------------------------------
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_C_Physic.h"
c_Physic::c_Physic()
{
}
c_Physic::~c_Physic()
{
}
bool c_Physic::HitBoxWorld_2D(D3DXVECTOR3 Apos,float Ah, float Aw, 
							  D3DXVECTOR3 Bpos,float Bh, float Bw,
							  float fCheckRange)
{
	float fRange = sqrtf((Apos.x - Bpos.x)*(Apos.x - Bpos.x) + (Apos.y - Bpos.y)*(Apos.y - Bpos.y));
	if(fRange > fCheckRange) return false;
	else
	{
		D3DXVECTOR3 AC = D3DXVECTOR3(Apos.x + Aw,Apos.y + Ah,0.0f);
		D3DXVECTOR3 BC = D3DXVECTOR3(Bpos.x + Bw,Bpos.y + Bh,0.0f);
		
		if(AC.x >= (BC.x - Bw*2) && BC.x >= (AC.x - Aw*2) &&
			AC.y >= (BC.y - Bh*2) && BC.y >= (AC.y - Ah*2))
			return true;
		else 
			return false;
	}
}
void c_Physic::HitExclusion2D(D3DXVECTOR3 &BodyPos, float BodySizeX, float BodySizeY,
							D3DXVECTOR3 &BoxPos,	float BoxSizeX,	 float BoxSizeY,
							D3DXVECTOR3 &BodySpeed, float ExclusionRange)
{
	D3DXVECTOR3 MoveRes;
	D3DV_INIT(MoveRes);
	float Ix = BodySizeX - (abs(BodyPos.x - BoxPos.x) - BoxSizeX);
	float Iy = BodySizeY - (abs(BodyPos.y - BoxPos.y) - BoxSizeY);
	if(Ix < Iy)
	{
		if(BodyPos.x < BoxPos.x)
		{
			MoveRes.x = BoxPos.x - BodyPos.x - (BoxSizeX + BodySizeX +  ExclusionRange);
			BodySpeed.x = 0;
			BodyPos.x  += MoveRes.x;
		}
		else
		{
			MoveRes.x = BoxPos.x - BodyPos.x + (BoxSizeX + BodySizeX +  ExclusionRange);
			BodySpeed.x = 0;
			BodyPos.x  += MoveRes.x;
		}
	}
	else
	{

		if(BodyPos.y < BoxPos.y)
		{
			MoveRes.y = BoxPos.y - BodyPos.y - (BoxSizeY + BodySizeY +  ExclusionRange);
			BodySpeed.y = 0;
			BodyPos.y  += MoveRes.y;
		}
		else
		{
			MoveRes.y = BoxPos.y - BodyPos.y + (BoxSizeY + BodySizeY +  ExclusionRange);
			BodySpeed.y = 0;
			BodyPos.y  += MoveRes.y;
		}
	}

}
bool c_Physic::HitCheckDirection2D(D3DXVECTOR3 BodyPos, float BodySizeX,float BodySizeY,
						D3DXVECTOR3 BoxPos, float BoxSizeX,float BoxSizeY,
						D3DXVECTOR3 BodySpeed,HIT_DIR Direction,float checkRange)
{
	BodyPos += BodySpeed;
	bool hr;
	hr = HitBoxWorld_2D(BodyPos,BodySizeY,BodySizeX,
						BoxPos,BoxSizeY,BoxSizeX,
						checkRange);
	if(!hr) 
	{
		hr = false;
	}
	else
	{
		float Ix = BodySizeX - (abs(BodyPos.x - BoxPos.x) - BoxSizeX);
		float Iy = BodySizeY - (abs(BodyPos.y - BoxPos.y) - BoxSizeY);
		hr = false;
		switch(Direction)
		{
			
		case HIT_DIR_UP:
			if(Ix > Iy)
				if(BodyPos.y < BoxPos.y)
					hr = true;
			break;
		case HIT_DIR_DOWN:
			if(Ix > Iy)
				if(BodyPos.y >= BoxPos.y)
					hr = true;
			break;
		case HIT_DIR_LEFT:
			if(Ix <= Iy)
				if(BodyPos.x < BoxPos.x)
					hr = true;
			break;
		case HIT_DIR_RIGHT:
			if(Ix <= Iy)
				if(BodyPos.x >= BoxPos.x)
					hr = true;
			break;
		}
	}
	return hr;
}

void c_Physic::FreeFallRealTime(D3DXVECTOR3* speed)
{
	speed->y -= PHYSIC_G_VALUE / FOVY;
}
			//touched = HitCheckDirection2D(Wkpos,PLAYER_WIDTH,PLAYER_HEIGHT,
			//								m_pStage->m_uBlock[y][x]->m_vPos,BLOCK_SIZE*0.5f,BLOCK_SIZE*0.5f,
			//								WkSpeed,HIT_DIR_DOWN,5);