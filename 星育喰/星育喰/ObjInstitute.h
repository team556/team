#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjInstitute :public CObj
{
	public:
		CObjInstitute() {};
		~CObjInstitute() {};
		void Init();     //イニシャライズ
		void Action();   //アクション
		void Draw();     //ドロー

		float m_mou_x;
		float m_mou_y;

		bool m_mou_r;
		bool m_mou_l;

	private:
		void InitScene();	//
		void Scene();		//
		int m_x;
		int m_y;

		int m_time;

		bool m_turn;
		bool m_turn0;
		bool m_key_f;

};