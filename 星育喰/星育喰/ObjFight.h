#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjFight :public CObj
{
public:
	CObjFight() {};
	~CObjFight() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	int GetLine() { return m_line_nam; }//選択ラインを返す
	int GetCount() { return m_cnt; }	//カウント数を返す
	void SetEndF() { m_end_f = true; }	//カウント数を返す

private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	
	float m_a;			//alpha(透明度)

	int m_line;			//選択前
	int m_line_nam;		//選択中ラインナンバー(上から0,1,2)

	int m_cnt;			//カウント用

	bool m_end_f;		//終わったフラグ

	float m_hp;
	float m_hp2;
	float m_ex;
	float m_ey;
};