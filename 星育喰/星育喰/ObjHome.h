#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ホーム
class CObjHome :public CObj
{
public:
	CObjHome() {};
	~CObjHome() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_Ey[3];		//敵惑星(背景)3つのY座標を管理
	int m_time[3];		//敵惑星(背景)3つの時間経過を管理
	int m_Enemy_id;		//各敵惑星の識別用変数
	int m_Planet_id;	//惑星データ読取用変数

	//bool  m_flag;		//true=クリックした　false=クリックしてない
	float m_alpha;		//透過度(アルファ値)
	float m_Tra_color;	//育アイコンカラー明度
	float m_Eat_color;	//喰アイコンカラー明度

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
};