#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_nam = Scene_num; }//作成時に渡された値を、m_Scene_namに代入
	~CObjHelp() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;
	float m_y;
	bool  m_help_f;		//ヘルプ表示フラグ
	
	int m_page_nam;		//ページ数
	float m_a;			//alpha(透明度)
	float m_a2;			//alpha2(戻るボタン)

	int m_Scene_nam;	//現在表示中のシーン番号(1:ホーム ,2:育成 ,3:準備 ,4:戦闘)
	int m_Img_nam;		//画像の登録番号

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool m_key_f;		//マウスの連打制御
};