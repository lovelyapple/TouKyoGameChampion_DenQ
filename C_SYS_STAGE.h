//-----------------------------------------------------------
//ステージクラス
//-----------------------------------------------------------
#ifndef _C_STAGE_H_
#define _C_STAGE_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
#include "C_Game_Block.h"
#include "C_Master_Task_List.h"
//--------------------------------------
//マクロ定義
#ifndef _FIELD_SIZE_			//たぶんSysMacroの中に設定しておる

#define MAX_FIELD_WIDTH		(50)
#define MAX_FIELD_HEIGHT	(20)

#endif
#define DEFAULT_FILE_NAME_STAGE		("data/Sys_Data/DefaultStage.csv")
#define MAX_STAGE		(3)

//--------------------------------------
//クラス宣言
class c_Stage
{
public:
	c_Stage(c_TaskList* List,C_FIELDPLACE player);		//コンストラクタ
	~c_Stage();											//デストラクタ
	void CreatBlockSingle(C_FIELDPLACE Place,int nType);//ブロックの生成
	void ClearBlockSingle(C_FIELDPLACE Place);			//単体のブロック削除
	HRESULT SaveStage(void);							//ステージの保存
	HRESULT LoadStage(void);							//ステージのロード
	void	SetStageName(LPCSTR Name);					//ステージ名の設定
	void	ClearAllBlock(void);						//前ブロッククリア
	void	InitAllBlock(void);
	c_Block*		m_uBlock[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH];
private:
	
	c_TaskList*		m_uTaskList;
	LPCSTR			m_lpzStageName;
	C_FIELDPLACE	m_uPlayerPlace;
protected:
	

};
#endif