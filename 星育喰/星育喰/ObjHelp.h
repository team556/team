#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ヘルプボタン
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_num = Scene_num; }//作成時に渡された値を、m_Scene_numに代入
	~CObjHelp() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	void SetMig_stageF() { m_mig_staging_f = true; }//シーン移行演出フラグON用
	void SetTra_EatF(bool staging) { m_Tra_Eat_f = staging; }//育成or戦闘判断フラグ設定用
	void SetOperatable(bool operatable) { m_is_operatable = operatable; }//ヘルプボタン操作可否設定用
	void SetAlpha(float alpha) { m_Help_Button_alpha = alpha; }//ヘルプボタン透過度設定用
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	bool  m_key_f;		//マウスの連打制御(キーフラグ)

	float m_px;			//ヘルプボタンの座標X
	float m_py;			//ヘルプボタンの座標Y
	float m_vec;		//ヘルプボタンの移動ベクトル

	float m_Help_Button_color;	//ヘルプボタンのカラー明度
	float m_Back_Button_color;	//戻るボタンのカラー明度
	float m_Page_Back_Button_color;	//ページ戻すボタンのカラー明度
	float m_Page_Next_Button_color;	//ページ進めるボタンのカラー明度

	float m_Help_Button_alpha;	//ヘルプボタンの透過度

	bool  m_mig_staging_f;	//シーン移行演出フラグ(true:移行演出中　false:移行演出前)
	bool  m_Tra_Eat_f;		//育成or戦闘判断フラグ(true:育成画面移行　false:戦闘準備画面移行)[ホーム画面シーン移行演出でのみ使用]
	bool  m_is_operatable;	//ヘルプボタン操作可能か確認フラグ(true:操作可能　false;操作不可)

	int m_page_num;		//現在表示中のヘルプ画像番号(ページ)
	int m_page_max;		//現在シーンで表示するヘルプ画像(ページ)の最大数
	int m_help_reg_num;	//ヘルプボタン、ヘルプ画像の登録番号[この値にはヘルプボタンの登録番号を代入し、ヘルプ画像は枚数分ヘルプボタンの値の後に続くように順番通りに登録する](シーン毎にヘルプ画像登録番号が違うためm_Scene_numを考慮して値を決定)
	int m_Back_reg_num;	//戻るボタン画像の登録番号(シーン毎に戻るボタン画像登録番号が違うためm_Scene_numを考慮して値を決定)

	int m_Scene_num;	//現在表示中のシーン番号(1:ホーム ,2:育成 ,3:準備)
};