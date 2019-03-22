#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjWarehouse :public CObjTraining//CObjTrainingを継承する
{
	public:
		CObjWarehouse() {};
		~CObjWarehouse() {};
		void Init();     //イニシャライズ
		void Action();   //アクション
		void Draw();     //ドロー

		float m_mou_x;
		float m_mou_y;

		bool m_mou_r;
		bool m_mou_l;

	private:
		int m_x;
		int m_y;
		//int m_obx;//育成画面オブジェクトX軸
		//int m_oby;//育成画面オブジェクトY軸

		int m_time;

		bool m_key_f;

		bool m_key_ma;	//資材ボタンフラグ
		bool m_key_re;	//住民ボタンフラグ
		bool m_key_sp;	//スペシャル技ボタンフラグ
		bool m_key_eq;	//装備ボタンフラグ
		bool m_key_md;	//戻るボタンフラグ

		float m_Ware_color;	//倉庫カラー明度
		bool m_f;

};