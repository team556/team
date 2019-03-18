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
private:
	float m_Bar_color;	//兵舎カラー明度
	bool m_f;
};