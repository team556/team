#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define MES_MAX (10)			//メッセージ最大格納数
#define FONT_MAX (100)			//フォント格納最大数
#define FONT_DATA_X (33)		//フォントデータX
#define FONT_DATA_Y (22)		//フォントデータY
#define FONT_CLIP_SIZE (125.0f)	//フォント切り取りサイズ
#define FONT_DRAW_SIZE (36.0f)	//フォント描画サイズ

//オブジェクト：メッセージ
class CObjMessage :public CObj
{
public:
	CObjMessage(int id) { m_Scene_id = id; }
	~CObjMessage() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	wchar_t m_font_data[FONT_DATA_Y][FONT_DATA_X];	//フォントデータ(画像のどの位置にどの文字があるのか管理している)
	wchar_t m_font[MES_MAX][FONT_MAX];	//フォント情報管理配列[メッセージ格納数][フォントデータ格納数]
	int m_font_column[FONT_MAX];		//フォント切り取り位置(列)
	int m_font_line[FONT_MAX];			//フォント切り取り位置(行)
	int m_font_draw_x[FONT_MAX];		//フォント描画位置X
	int m_font_draw_y[FONT_MAX];		//フォント描画位置Y
	float m_font_color[FONT_MAX][4];	//フォントカラー

	int m_time;			//次のフォント描画までの時間管理
	int m_font_count;	//現在何文字目を描画中であるか管理
	int m_progress;		//メッセージ進行度の管理
	int m_length;		//文字列の長さを管理
	bool m_fast_f;		//メッセージ描画速度高速化フラグ[true:描画速度高速化　false:描画速度通常]
	bool m_skip_f;		//メッセージスキップフラグ[true:スキップ処理実行　false:未実行状態]
	
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	bool  m_key_f;		//キーフラグ

	int	  m_arrow_display_f;//矢印表示フラグ(0:非表示　1:表示)
	int	  m_arrow_angle_f;	//矢印角度フラグ(0:上向き　1:下向き　2:左向き　3:右向き)
	float m_arrow_x;		//矢印X位置
	float m_arrow_y;		//矢印Y位置

	float m_swing_vec;		//往復アニメーション用(矢印画像、クリック催促画像に使用)
	float m_swing_r;		//往復アニメーションさせるのに必要な角度の値保管用

	bool  m_black_out_f;		//画面全体やや暗転フラグ(true:暗転　false:明転)
	bool  m_reminder_f;			//クリック催促画像表示フラグ(true:表示　false:非表示)
	int   m_is_top_or_bottom;	//メッセージウインドウ位置変更用(0:下に表示　1:上に表示)

	int   m_message_window_num;	//メッセージウインドウ登録番号格納用
	

	//▼基本的にはtrue。メッセージ終了 or メッセージ途中にプレイヤーに何か操作させたい時にfalseにする。
	bool m_run_switch;	//メッセージ表示機能ON/OFF管理フラグ[true:動作させる　false:停止させる]
	
	//▼シーンID管理用
	int	m_Scene_id;//現状テストで割り振っているものを除き、何も割り振っていない。


	//▽メモ
	//シーンによっては初回に訪れた時だけでなく、２度目に訪れた時に発動するチュートリアルもあるので、
	//それに関しては、staticで訪れた数記憶させておき、それで判断させるべし！
};