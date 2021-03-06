
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
	int m_word_w[50];
	int click_cut;
	float click_win[5];
	int m_tex_discri[6];
	bool m_tex_clar;
	bool m_f;
	int m_cut;
	bool m_finalcheck_f;
	bool m_finalcheck_f_yes;	//
	bool m_scene_move;//trueでホーム画面にシーン移行
	int m_Yes_Button_color;
	int m_No_Button_color;
	bool m_key_f;
	int m_num_cnt;
	bool m_check_f;

	float m_alpha;

	int m_c_cut; 

	wchar_t  m_c[6];
};
