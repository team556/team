#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

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
};