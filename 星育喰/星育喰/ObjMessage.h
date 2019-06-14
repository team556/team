#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define STR_MAX (50) //文字最大数
#define STR_SIZE (64.0f)//一文字の大きさ

//オブジェクト：メッセージ表示
class CObjMessage :public CObj
{
public:
	CObjMessage() {};
	~CObjMessage() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	wchar_t str[10][STR_MAX]; //文字管理配列[メッセージ数][文字]
	int str_column[STR_MAX];//フォント読み込み位置(列)
	int str_line[STR_MAX];//フォント読み込み位置(行)
	int str_draw_x[STR_MAX];//フォント表示位置X
	int str_draw_y[STR_MAX];//フォント表示位置Y
	int time;				//時間管理
	int text_count;			//現在何文字目か管理
	int page;				//ページ数管理
	int now_max;//文字列長さ管理


	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
};