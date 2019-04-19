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

		float m_mou_x;		//マウスx座標
		float m_mou_y;		//マウスy座標

		bool m_mou_r;		//右クリックフラグ
		bool m_mou_l;		//左クリックフラグ

	private:
		int m_x;
		int m_y;

		bool m_key_wh;	//倉庫を開くフラグ
		bool m_key_ma;	//資材ボタンフラグ
		bool m_key_re;	//住民ボタンフラグ
		bool m_key_sp;	//スペシャル技ボタンフラグ
		bool m_key_eq;	//装備ボタンフラグ
		bool m_key_md;	//戻るボタンフラグ
		bool m_key_lf;  //左クリック用キーフラグ

		float m_Ware_color;			//倉庫カラー明度
		float m_Back_Button_color;	//戻るボタンカラー明度
		float m_object_ma;			//資材ボタンカラー明度
		float m_object_re;			//住民ボタンカラー明度
		float m_object_sp;			//スペシャル技ボタンカラー明度
		float m_object_eq;			//装備ボタンカラー明度

};