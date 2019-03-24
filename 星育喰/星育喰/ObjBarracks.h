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
	
		int Allocation(int type_num, int up_down_check);//振り分け関数
	private:
		float m_Bar_color;			//兵舎カラー明度
		float m_Human_up_color[4];	//住民振り分けUPカラー明度
		float m_Human_down_color[4];//住民振り分けDOWNカラー明度
};