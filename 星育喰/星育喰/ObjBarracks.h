#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：兵舎
class CObjBarracks :public CObjTraining	//CObjTrainingを継承する
{
public:
	CObjBarracks() {};
	~CObjBarracks() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	
	int Allocation(int human_num, int updown_flag);//
private:
	float m_Bar_color;			//兵舎カラー明度
	float m_Human_up_color[4];	//住民振り分けUPカラー明度
	float m_Human_down_color[4];//住民振り分けDOWNカラー明度

	int m_Bar_Level_test;	//兵舎レベル管理変数(後にグローバル変数にする予定)
	int m_power_num;	//パワー住民数(後にグローバル変数にする予定)
	int m_defense_num;	//ディフェンス住民数(後にグローバル変数にする予定)
	int m_speed_num;	//スピード住民数(後にグローバル変数にする予定)
	int m_balance_num;	//バランス住民数(後にグローバル変数にする予定)
	int m_remain_num;	//残り住民数(後にグローバル変数にする予定)
};