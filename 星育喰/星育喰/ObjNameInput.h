
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjNameInput :public CObj
{
public:
	CObjNameInput() {};
	~CObjNameInput() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	int word_x[100];
	int word_y[100];
	int word[100][100];
	bool word_w[50][50];
	int click_cut;
	float click_win[50];
	bool m_f;
};
