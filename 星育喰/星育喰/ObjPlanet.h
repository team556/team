#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, bool type);//座標+タイプを受け取る
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_size;		//星サイズ
	float m_siz_vec;	//サイズ変更ベクトル
	float m_mov_spd;	//惑星移動スピード
	float m_siz_spd;	//サイズ変更スピード

	float m_hp;			//ヒットポイント

	bool m_type;		//惑星タイプ(true主人公)
	bool m_cnt_f;		//カウントフラグ
	
};