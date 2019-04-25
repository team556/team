#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define ENEMY_PLANET_DETAIL_MES_MAX_FONT_LINE (3) //敵惑星詳細説明メッセージの最大フォント行数

//オブジェクト：戦闘準備画面
class CObjPreparation :public CObj
{
public:
	CObjPreparation() {};
	~CObjPreparation() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool  m_key_lf;		//左クリック用キーフラグ
	bool  m_key_rf;		//右クリック用キーフラグ

	float m_Pvx;		//プレイヤー惑星の移動用ベクトルX
	float m_PSvy;		//プレイヤー惑星、スペシャル技アイコン等の移動用ベクトルY(同じ移動距離の為、共有している)
	//float m_boost;		//プレイヤー惑星のX移動速度上昇用
	//float m_rx;			//サインカーブ用の角度(プレイヤー惑星x移動に使用)
	//float m_ry;			//サインカーブ用の角度(プレイヤー惑星y移動に使用)
	float m_Psize;		//プレイヤー惑星のサイズ

	float m_warning_message_x[2];//警告メッセージ移動用ベクトルX
	float m_warning_message_y[2];//警告メッセージ移動用ベクトルY
	float m_warning_message_size;//警告メッセージサイズ

	float m_Evx;		//敵惑星4つの移動用ベクトルX
						//ボス惑星のヤツは個別で用意予定
	float m_speed;		//開始演出で移動する各オブジェクト(プレイヤー惑星、各敵惑星等)の移動速度

	//int m_staging_time;		//演出時間管理変数
	bool m_is_operatable;	//操作可能か確認フラグ(true:操作可能　false;操作不可)

	float m_Back_Button_color;	//戻るボタンカラー明度
	float m_Yes_Button_color;	//最終確認[はい]ボタンカラー(Red)調節用
	float m_No_Button_color;	//最終確認[いいえ]ボタンカラー(Blue)調節用
	float m_alpha;				//透過度(アルファ値)

	wchar_t m_Enemy_detail_message[ENEMY_PLANET_DETAIL_MES_MAX_FONT_LINE][22];	//敵惑星詳細説明メッセージのフォント用
	float	m_Enemy_detail_message_window_x_size;	//敵惑星詳細説明ウインドウのサイズX
	float	m_Enemy_detail_message_window_y_size;	//敵惑星詳細説明ウインドウのサイズY

	int	  m_destroy_count;			//現在ステージでの敵惑星撃破数
	static bool destroy_progress[4];//現在ステージでの敵惑星撃破進行度(true:撃破　false:未撃破)
};