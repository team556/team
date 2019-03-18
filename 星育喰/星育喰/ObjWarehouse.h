#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjWarehouse :public CObj
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
		int m_obx;//育成画面オブジェクトX軸
		int m_oby;//育成画面オブジェクトY軸

		int m_time;

		bool m_turn;
		bool m_turn0;
		bool m_key_f;

		bool m_obj;

};