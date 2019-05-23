#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define DETAIL_MES_MAX_FONT_LINE (4) //詳細説明の最大フォント行数

//オブジェクト：戦闘準備画面
class CObjPreparation :public CObj
{
public:
	CObjPreparation() {};
	~CObjPreparation() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	void Enemy_message(int enemy_id);		//敵惑星詳細説明表示関数
	void Special_message(int special_id);	//スペシャル技詳細説明表示関数
private:
	float m_mou_x;	//マウスの位置X
	float m_mou_y;	//マウスの位置Y
	bool  m_mou_r;	//マウスプッシュ確認(右クリック)
	bool  m_mou_l;	//マウスプッシュ確認(左クリック)

	bool  m_key_lf;	//左クリック用キーフラグ
	bool  m_key_rf;	//右クリック用キーフラグ

	float m_Pvx;	//プレイヤー惑星の移動用ベクトルX
	float m_Pvy;	//プレイヤー惑星の移動用ベクトルY
	float m_Pr;		//サインカーブ用の角度(プレイヤー惑星y移動に使用)
	float m_Psize;	//プレイヤー惑星のサイズ

	float m_Svy;	//スペシャル技ウインドウ、アイコンの移動用ベクトルY

	float m_Bvx;	//戻るボタンの移動用ベクトルX
	float m_Bvy;	//戻るボタンの移動用ベクトルY

	float m_Evx;	//敵惑星4つの移動用ベクトルX

	float m_warning_message_x[2];	//ボス出現警告メッセージ移動用ベクトルX
	float m_warning_message_y[2];	//ボス出現警告メッセージ移動用ベクトルY
	float m_warning_message_size;	//ボス出現警告メッセージサイズ
	float m_warning_message_alpha;	//ボス出現警告メッセージ透過度(アルファ値)

	float m_Boss_vx[3];		//ボス惑星(演出用も含む)の移動用ベクトルX
	float m_Boss_vy[3];		//ボス惑星(演出用も含む)の移動用ベクトルY
	float m_Boss_clip_pos;	//ボス惑星描画元切り取り位置変更用

	float m_speed;		//各演出で移動する各オブジェクト(プレイヤー惑星、各敵惑星、ボス惑星等)の移動速度
	float m_save_speed;	//移動速度保存用変数

	float m_black_star_effect_size;	//戦闘画面移行演出(黒星)のサイズ
	int	  m_staging_time;			//演出時間管理変数
	bool  m_is_operatable;			//操作可能か確認フラグ(true:操作可能　false;操作不可)

	float m_Back_Button_color;		//戻るボタンカラー明度
	float m_Special_icon_color[5];	//スペシャル技アイコンカラー明度
	float m_Yes_Button_color;		//最終確認[はい]ボタンカラー(Red)調節用
	float m_No_Button_color;		//最終確認[いいえ]ボタンカラー(Blue)調節用

	bool  m_Back_flag;				//「戦闘準備画面→ホーム画面」移行開始フラグ
	bool  m_Go_flag;				//「戦闘準備画面→戦闘画面」移行開始フラグ
	bool  m_boss_emerge_staging_f;	//ボス惑星出現演出開始フラグ
	bool  m_finalcheck_f;			//最終確認ウインドウ表示管理フラグ(true:表示 / false:非表示)

	wchar_t m_detail_message[DETAIL_MES_MAX_FONT_LINE][13];	//詳細説明(敵惑星、スペシャル技)のフォント用
	wchar_t m_Enemy_detail_message[3][5][DETAIL_MES_MAX_FONT_LINE][13];//各敵惑星の詳細説明文管理用([ステージ数][敵惑星ナンバー][最大フォント行数][文字データ格納可能数])
	float	m_detail_message_window_top;	//詳細説明(敵惑星、スペシャル技)ウインドウの描画先表示位置(top)
	float	m_detail_message_window_left;	//詳細説明(敵惑星、スペシャル技)ウインドウの描画先表示位置(left)
	float	m_detail_message_window_right;	//詳細説明(敵惑星、スペシャル技)ウインドウの描画先表示位置(right)
	float	m_detail_message_window_bottom;	//詳細説明(敵惑星、スペシャル技)ウインドウの描画先表示位置(bottom)
	float	m_detail_message_font_x;		//詳細説明(敵惑星、スペシャル技)フォント位置X
	float	m_detail_message_font_y;		//詳細説明(敵惑星、スペシャル技)フォント位置Y
	float	m_detail_message_alpha;			//詳細説明(敵惑星、スペシャル技)の透過度(アルファ値)

	//int	  m_destroy_count;			//現在ステージでの敵惑星撃破数
	//static bool destroy_progress[4];//現在ステージでの敵惑星撃破進行度(true:撃破　false:未撃破)
};