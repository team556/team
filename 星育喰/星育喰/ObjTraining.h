#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define FACILITY_MAX_LV (3) //施設(兵舎、研究所)のMAXレベル
#define MAT_NAME_CHAR_DATA_STORE_NUM (7) //素材名の文字データ格納可能数
#define CON_PRE_TIME (30)	//連続振り分け前の次住民振り分け時間(0.5秒)
#define CON_MID_TIME (5)	//連続振り分け中の次住民振り分け時間(0.08秒)
#define MES_DRAW_TOP (-40.0f)	//簡易メッセージ画像描画位置top
#define MES_DRAW_BOTTOM (-10.0f)//簡易メッセージ画像描画位置bottom

//オブジェクト：育成画面
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_size;		//プレイヤー惑星のサイズ

	int   m_Mig_time;	//ホーム画面にシーン移行する際の時間管理変数

	float m_Eat_color;	//喰アイコンカラー明度
protected:
	int Allocation(int type_num, int up_down_check);//振り分け関数
	void Facility_message(int Facility_Level);//施設(兵舎、研究所)の必要素材&サイズメッセージ描画関数

	float m_mou_x;		 //マウスの位置X
	float m_mou_y;		 //マウスの位置Y
	bool  m_mou_r;		 //マウスプッシュ確認(右クリック)
	bool  m_mou_l;		 //マウスプッシュ確認(左クリック)
	bool  m_introduce_f; //施設紹介ウインドウ表示管理フラグ(true:表示 / false:非表示)
	bool  m_finalcheck_f;//最終確認ウインドウ表示管理フラグ(true:表示 / false:非表示)
	bool  m_key_lf;		 //左クリック用キーフラグ
	bool  m_key_rf;		 //右クリック用キーフラグ

	int   m_next_time;	//次の住民振り分けまでの時間管理変数
	bool  m_con_alo_f;	//住民連続振り分けフラグ[true:連続振り分け中(二回目以降)　false:連続振り分け前(初回)]

	float m_Back_Button_color;	//戻るボタンカラー明度

	//wchar_t m_message[18];		//マウスカーソル上部に描画する簡易メッセージ(エラーメッセージ、レベルUP表示等)のフォント用「画像で行うので、全て変更後不要なので消すべし。」
	float	m_message_clip_right;	//簡易メッセージ画像切り取り位置right
	float	m_message_clip_bottom;	//簡易メッセージ画像切り取り位置bottom
	float	m_message_draw_left;	//簡易メッセージ画像描画位置left
	float	m_message_draw_right;	//簡易メッセージ画像描画位置right
	float	m_message_red_color;	//簡易メッセージカラー(Red)
	float	m_message_green_color;	//簡易メッセージカラー(Green)
	float	m_message_blue_color;	//簡易メッセージカラー(Blue)
	float	m_alpha;				//マウスカーソル上部に描画するグラフィックの透過度(アルファ値)

	float m_Yes_Button_color;		//最終確認[はい]ボタンカラー(Red)調節用
	float m_No_Button_color;		//最終確認[いいえ]ボタンカラー(Blue)調節用

	//▼施設(兵舎、研究所)LvUP処理等に使用する配列
	//wchar_t m_Facility_message[20][22];	//施設(兵舎、研究所)の必要素材&サイズメッセージのフォント用(素材名除く)(フォント入れ替えしたのでこれは不要である。)
	//wchar_t m_message_Mat_name[MAT_NAME_CHAR_DATA_STORE_NUM];	//各メッセージ(兵舎、研究所、武器ポッド)の素材名フォント用(現在ウインドウサイズ的に全角6文字分しか入らないようにしている)

	float  m_Facility_next_Size_num[FACILITY_MAX_LV - 1];	//施設(兵舎、研究所)の次のLVUPに必要なサイズ(HP)管理用
	wchar_t m_Facility_next_Mat_name[FACILITY_MAX_LV - 1][MAT_NAME_CHAR_DATA_STORE_NUM];//施設(兵舎、研究所)の次のLVUPに必要な素材の名前管理用
	int *m_Facility_next_Mat_type[FACILITY_MAX_LV - 1];		//施設(兵舎、研究所)の次のLVUPに必要な素材種類とその素材の所持数を管理するポインタ
	int  m_Facility_next_Mat_num[FACILITY_MAX_LV - 1];		//施設(兵舎、研究所)の次のLVUPに必要な素材数管理用(仮で必要素材1種類として考えている。2種類以上ならその分Mat_typeとMat_numを配列構造体に入れて増やす予定)

	wchar_t m_mmmmm[50];

	static bool scene_change_start;	//シーン切り替え演出開始を伝えるフラグ
	static bool white_out_f;		//ホワイトアウト演出フラグ[true:ホワイトアウト演出実行中　false:ホワイトアウト演出を実行してない状態]
	static int  player_level;		//プレイヤー惑星レベル(この変数自体はプレイヤー惑星レベルUPチェック判定で使うだけで、それ以外では一切使用しない)
	static int  window_start_manage;//施設ウインドウの起動管理フラグ

	//▼各施設ウインドウ(戻るボタン含む)に列挙型で識別番号を割り振る
	enum window_id	
	{
		Default,	//デフォルト。どのウインドウも開いていない状態。
		BackButton,	//戻るボタンを押して、ホーム画面に戻ろうとしている状態。
		EatButton,	//喰ボタンを押して、戦闘準備画面に移行しようとしている状態。
		Barracks,	//兵舎ウインドウを開いている状態。
		Institute,	//研究所ウインドウを開いている状態。
		Missile,	//ミサイルウインドウを開いている状態。
		Equipment,	//武器ポッドウインドウを開いている状態。
		Warehouse,	//倉庫ウィンドウを開いている状態。
		Materials,	//資材ウィンドウを開いている状態。
		Residents,	//住民ウィンドウを開いている状態。
		Specialskill,//スペシャル技ウィンドウを開いている状態。
		Soubicheck,	//装備ウィンドウを開いている状態。
	};
};