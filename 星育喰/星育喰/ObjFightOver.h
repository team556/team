#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲームオーバー画面
class CObjFightOver :public CObj
{
public:
	CObjFightOver() {};
	~CObjFightOver() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	//float m_x;
	//float m_y;
	//bool  m_f;

	//float m_mou_x;		//マウスの位置X
	//float m_mou_y;		//マウスの位置Y
	//bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	float m_a;		//透明度
	float m_a_vec;	//透明度ベクトル
	bool  m_a_f;	//透明度フラグ
	float m_black_out_a;	//画面暗転透過度
	float m_gameover_a;	//ゲームオーバーフォント用透過度(アルファ値)

	//int m_cnt;		//カウント
};