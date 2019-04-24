#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, float hp,bool type);//座標+タイプを受け取る
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_px; }
	float GetHp() { return m_hp; }	//カウント数を返す
	void SetEeatF() { m_eat_f = true; }
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_size;		//星サイズ
	float m_siz_max;	//サイズマックス
	float m_siz_vec;	//サイズ変更ベクトル
	float m_siz_spd;	//サイズ変更スピード
	float m_mov_spd;	//惑星移動スピード

	float m_hp;			//ヒットポイント
	float m_get_hp;		//ゲットHP
	int m_cnt;			//カウント
	bool m_type;		//惑星タイプ(true主人公)
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;
};