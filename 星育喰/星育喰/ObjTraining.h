#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：育成画面
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	int Allocation(int type_num, int up_down_check);//振り分け関数
private:
	float m_size;		//プレイヤー惑星のサイズ

	int m_Mig_time;		//ホーム画面にシーン移行する際の時間管理変数
protected:
	float m_mou_x;		 //マウスの位置X
	float m_mou_y;		 //マウスの位置Y
	bool  m_mou_r;		 //マウスプッシュ確認(右クリック)
	bool  m_mou_l;		 //マウスプッシュ確認(左クリック)
	bool  m_introduce_f; //施設紹介ウインドウ表示管理フラグ(true:表示 / false:非表示)
	bool  m_key_lf;		 //左クリック用キーフラグ
	static bool m_key_rf;//右クリック用キーフラグ

	float m_Back_Button_color;	//戻るボタンカラー明度

	wchar_t m_message[18];		//マウスカーソル上部に描画する簡易メッセージ(エラーメッセージ、レベルUP表示等)のフォント用
	float	m_message_red_color;	//簡易メッセージカラー(Red)
	float	m_message_green_color;	//簡易メッセージカラー(Green)
	float	m_message_blue_color;	//簡易メッセージカラー(Blue)
	float	m_alpha;				//マウスカーソル上部に描画するグラフィックの透過度(アルファ値)

	static bool scene_change_start;	//シーン切り替え演出開始を伝えるフラグ
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
		Finalcheck,	//最終確認ウインドウを開いている状態。
		Warehouse,	//倉庫ウィンドウを開いている状態。
		Materials,	//資材ウィンドウを開いている状態。
		Residents,	//住民ウィンドウを開いている状態。
		Specialskill,//スペシャル技ウィンドウを開いている状態。
	};
};