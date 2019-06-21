#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define FACILITY_MES_MAX_FONT_LINE (6) //施設(兵舎、研究所)の必要素材&サイズメッセージの最大フォント行数
#define FACILITY_MAX_LV (3) //施設(兵舎、研究所)のMAXレベル
#define MAT_NAME_CHAR_DATA_STORE_NUM (7) //素材名の文字データ格納可能数

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

	int m_Mig_time;		//ホーム画面にシーン移行する際の時間管理変数
protected:
	int Allocation(int type_num, int up_down_check);//振り分け関数
	void Facility_message(int Facility_Level);//施設(兵舎、研究所)の必要素材&サイズメッセージ描画関数

	float m_mou_x;		 //マウスの位置X
	float m_mou_y;		 //マウスの位置Y
	bool  m_mou_r;		 //マウスプッシュ確認(右クリック)
	bool  m_mou_l;		 //マウスプッシュ確認(左クリック)
	bool  m_introduce_f; //施設紹介ウインドウ表示管理フラグ(true:表示 / false:非表示)
	bool  m_finalcheck_f;//最終確認ウインドウ表示管理フラグ(true:表示 / false:非表示)
	//bool  m_help_f;		 //ヘルプウインドウ表示管理フラグ  (true:表示/false:非表示)
	bool  m_key_lf;		 //左クリック用キーフラグ
	static bool m_key_rf;//右クリック用キーフラグ

	float m_Back_Button_color;	//戻るボタンカラー明度

	wchar_t m_message[18];		//マウスカーソル上部に描画する簡易メッセージ(エラーメッセージ、レベルUP表示等)のフォント用
	float	m_message_red_color;	//簡易メッセージカラー(Red)
	float	m_message_green_color;	//簡易メッセージカラー(Green)
	float	m_message_blue_color;	//簡易メッセージカラー(Blue)
	float	m_alpha;				//マウスカーソル上部に描画するグラフィックの透過度(アルファ値)

	float m_Yes_Button_color;		//最終確認[はい]ボタンカラー(Red)調節用
	float m_No_Button_color;		//最終確認[いいえ]ボタンカラー(Blue)調節用

	//▼施設(兵舎、研究所)LvUP処理等に使用する配列
	wchar_t m_Facility_message[FACILITY_MES_MAX_FONT_LINE][22];	//施設(兵舎、研究所)の必要素材&サイズメッセージのフォント用(素材名除く)
	wchar_t m_message_Mat_name[MAT_NAME_CHAR_DATA_STORE_NUM];	//各メッセージ(兵舎、研究所、武器ポッド)の素材名フォント用(現在ウインドウサイズ的に全角6文字分しか入らないようにしている)

	float  m_Facility_next_Size_num[FACILITY_MAX_LV - 1];	//施設(兵舎、研究所)の次のLVUPに必要なサイズ(HP)管理用
	wchar_t m_Facility_next_Mat_name[FACILITY_MAX_LV - 1][MAT_NAME_CHAR_DATA_STORE_NUM];//施設(兵舎、研究所)の次のLVUPに必要な素材の名前管理用
	int *m_Facility_next_Mat_type[FACILITY_MAX_LV - 1];		//施設(兵舎、研究所)の次のLVUPに必要な素材種類とその素材の所持数を管理するポインタ
	int  m_Facility_next_Mat_num[FACILITY_MAX_LV - 1];		//施設(兵舎、研究所)の次のLVUPに必要な素材数管理用(仮で必要素材1種類として考えている。2種類以上ならその分Mat_typeとMat_numを配列構造体に入れて増やす予定)


	static bool scene_change_start;	//シーン切り替え演出開始を伝えるフラグ
	static int  player_level;		//プレイヤー惑星レベル(ホワイトアウト処理判定で使う)
	static int  window_start_manage;//施設ウインドウの起動管理フラグ

	//▼各施設ウインドウ(戻るボタン含む)に列挙型で識別番号を割り振る
	enum window_id	
	{
		Default,	//デフォルト。どのウインドウも開いていない状態。
		BackButton,	//戻るボタンを押して、ホーム画面に戻ろうとしている状態。
		Barracks,	//兵舎ウインドウを開いている状態。
		Institute,	//研究所ウインドウを開いている状態。
		Missile,	//ミサイルウインドウを開いている状態。
		Equipment,	//武器ポッドウインドウを開いている状態。
		Warehouse,	//倉庫ウィンドウを開いている状態。
		Materials,	//資材ウィンドウを開いている状態。
		Residents,	//住民ウィンドウを開いている状態。
		Specialskill,//スペシャル技ウィンドウを開いている状態。
		Soubicheck,	//装備ウィンドウを開いている状態。
		//Help,		//ヘルプウィンドウを開いている状態。
	};
};