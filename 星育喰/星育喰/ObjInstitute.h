#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//マクロ
#define MIS_MAX_LV (5) //ミサイルリキャストのMAXレベル(仮決めで"5"としている)

//オブジェクト：研究所
class CObjInstitute :public CObjTraining //CObjTrainingを継承する
{
public:
	CObjInstitute() {};
	~CObjInstitute() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_Ins_color;			//研究所カラー明度
	float m_Ins_Lvup_color;		//研究所レベルUPカラー明度
	float m_Human_up_color;		//住民振り分けUPカラー明度
	float m_Human_down_color;	//住民振り分けDOWNカラー明度
	float m_Mis_Button_color;	//ミサイルボタンカラー明度
	float m_Equ_Button_color;	//武器ポッドボタンカラー明度

	float m_Mis_recast_time[MIS_MAX_LV];			//ミサイルリキャストタイム
	int m_Mis_recast_next_Ins_Lv[MIS_MAX_LV - 1];	//ミサイルリキャストの次のLVUPに必要な研究所レベル管理用
	int m_Mis_recast_next_Hum_num[MIS_MAX_LV - 1];	//ミサイルリキャストの次のLVUPに必要な研究員の住民数管理用
};