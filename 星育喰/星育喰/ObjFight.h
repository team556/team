#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：戦闘画面
class CObjFight :public CObj
{
public:
	CObjFight(int c = 0, int e_n = 0);	//c = cnt(戦闘時間),e_n = m_ene_nam(敵ナンバー)
	~CObjFight() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	int GetLine() { return m_line_nam; }//選択ラインを返す
	int GetCount() { return m_cnt; }	//カウント数を返す
	void SetEndF(int win_lose) { m_end_f = win_lose; }	//勝敗結果をもらう
	void SetStart_Count() { m_start_count_f = true; }//戦闘開始カウントを動作させる
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	
	float m_a;			//alpha(透明度)

	int m_line;			//選択前
	int m_line_nam;		//選択中ラインナンバー(上から0,1,2)

	int m_cnt;			//カウント用
	int m_ene_nam;		//敵ナンバー

	int m_end_f;		//勝敗確定フラグ(0:戦闘中　1:プレイヤー勝利確定　-1:エネミー勝利確定)

	float m_ex;
	float m_ey;

	float m_scale_down_cnt;		//縮小比カウント(背景)
	float m_scale_down_speed;	//縮小スピード(背景)

	float m_font_a;				//透明度(戦闘開始時表示される"スタート"の文字用)

	int	  m_start_count;		//戦闘開始カウント用
	bool  m_start_count_f;		//「戦闘開始カウント」開始フラグ(trueの時、動作を開始する)
protected:
	static bool battle_start;	//戦闘開始フラグ(true:戦闘開始　false:戦闘前 or 一時停止中)
	static bool battle_end;		//戦闘終了フラグ(true:戦闘終了　false:戦闘中)
};