#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_click_vy;	//"クリックでスタート"の移動用ベクトルＹ
	float m_r;			//サインカーブ用の角度("クリックでスタート"上下ふわふわに使用)

	float m_Ey[3];		//敵惑星(背景)3つのY座標を管理
	int m_time[3];		//敵惑星(背景)3つの時間経過を管理
	int m_Enemy_id;		//各敵惑星の識別用変数
	int m_Planet_id;	//惑星データ読取用変数
	int	m_speed;		//敵惑星(背景)3つの移動速度変更用(デバッグ用 兼 隠し要素)

	float m_Yes_Button_color;	//最終確認[はい]ボタンカラー(Red)調節用
	float m_No_Button_color;	//最終確認[いいえ]ボタンカラー(Blue)調節用
	float m_del_color;	//データ消去ボタンカラー明度
	float m_del_alpha;	//データ消去完了通知画像の透過度
	bool  m_del_f;		//データ消去最終確認ウインドウ表示管理フラグ(true:表示中　false:非表示)

	bool  m_flag;		//true=クリックした　false=クリックしてない
	bool  m_key_f;		//キーフラグ
	float m_alpha;		//透過度(アルファ値)
	float m_malpha;		//透過度0.0～1.0に変える
	float m_black_out_a;//画面暗転透過度
	float m_des_y;		//世界観説明画像の位置Y
	float m_des_vec;	//世界観説明画像のベクトル
	float m_des_a;		//世界観説明画像の透過度

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	static bool after_once;	//タイトル画面→ホーム画面移行時にtrue(二回目以降訪れた時の演出用に使用)
};