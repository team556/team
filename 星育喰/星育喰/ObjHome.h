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
	float m_Pvx;		//プレイヤー惑星の移動用ベクトルX
	float m_Pvy;		//プレイヤー惑星の移動用ベクトルY
	float m_boost;		//プレイヤー惑星のX移動速度上昇用
	float m_rx;			//サインカーブ用の角度(プレイヤー惑星x移動に使用)
	float m_ry;			//サインカーブ用の角度(プレイヤー惑星y移動に使用)
	float m_size;		//プレイヤー惑星のサイズ

	int m_Mig_time;		//シーン移行までの時間管理変数

	float m_Ey[3];		//敵惑星(背景)3つのY座標を管理
	int m_time[3];		//敵惑星(背景)3つの時間経過を管理
	int m_Enemy_id;		//各敵惑星の識別用変数
	int m_Planet_id;	//惑星データ読取用変数
	int	m_speed;		//敵惑星(背景)3つの移動速度変更用(デバッグ用 兼 隠し要素)

	float m_Tra_move;	//育アイコンの移動用ベクトル
	float m_Eat_move;	//喰アイコンの移動用ベクトル
	float m_Tra_color;	//育アイコンカラー明度
	float m_Eat_color;	//喰アイコンカラー明度
	float m_alpha;		//透過度(アルファ値)
	bool  m_Tra_flag;	//育アイコンクリック時trueフラグ
	bool  m_Eat_flag;	//喰アイコンクリック時trueフラグ
	bool  m_status_flag;//プレイヤー惑星ステータス表示フラグ(true:表示　false:非表示)

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool  m_key_f;		//キーフラグ
};