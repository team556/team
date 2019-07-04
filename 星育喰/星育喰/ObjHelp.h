#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ヘルプボタン
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_num = Scene_num; }//作成時に渡された値を、m_Scene_numに代入
	~CObjHelp() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	bool GetHelpF() { return m_help_f; }//ヘルプ画面表示状態取得用
	//void SetHelpF() { m_help_f = true; }//ヘルプ画面表示状態設定用
	
	//シーン移行した事をこのヘルプオブジェクトに伝える為のセッターいるかも。
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	bool  m_key_f;		//マウスの連打制御(キーフラグ)

	float m_Help_Button_color;	//ヘルプボタンのカラー明度
	float m_Back_Button_color;	//戻るボタンのカラー明度

	bool  m_help_f;		//ヘルプ画面表示フラグ(true:ヘルプ画面表示　false:ヘルプ画面非表示)

	int m_page_num;		//現在表示中のヘルプ画像番号(ページ)
	int m_page_max;		//現在シーンで表示するヘルプ画像(ページ)の最大数
	int m_Img_num;		//画像の登録番号(シーン毎にヘルプ画像登録番号が違うためm_Scene_numを考慮して値を決定)[これ使わなくとも出来るように全画像番号(ヘルプで使うの)統一する？]

	int m_Scene_num;	//現在表示中のシーン番号(1:ホーム ,2:育成 ,3:準備)

	//static int  window_start_manage;//施設ウインドウの起動管理フラグ

	////▼各施設ウインドウ(戻るボタン含む)に列挙型で識別番号を割り振る
	//enum window_id
	//{
	//	Default,	//デフォルト。どのウインドウも開いていない状態。
	//	BackButton,	//戻るボタンを押して、ホーム画面に戻ろうとしている状態。
	//	Barracks,	//兵舎ウインドウを開いている状態。
	//	Institute,	//研究所ウインドウを開いている状態。
	//	Warehouse,	//倉庫ウィンドウを開いている状態。
	//	Help,		//ヘルプウィンドウを開いている状態。
	//};

};