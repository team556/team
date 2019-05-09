#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：惑星(プレイヤー & 敵)
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, float hp, bool type, float siz = 0);//座標+HP+タイプ+サイズ
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_px; }
	float GetHp() { return m_hp; }	//カウント数を返す
	float GetSiz() { return (m_siz_vec + m_size); }
	void SetEeatF() { m_eat_f = true; }//セット喰うフラグ

	void SetDelF() { m_del_f = true; }//セット消すフラグ
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_size;		//星サイズ
	float m_siz_max;	//サイズマックス
	float m_siz_vec;	//サイズ変更ベクトル
	float m_siz_spd;	//サイズ変更スピード
	float m_get_siz;	//ゲットサイズ
	float m_mov_spd;	//惑星移動スピード

	float m_hp;			//ヒットポイント
	float m_get_hp;		//ゲットHP
	int m_cnt;			//カウント
	bool m_type;		//惑星タイプ(true主人公)

	int m_time;
	int m_attackf;
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//喰うフラグ(true = 喰う)
	float m_eat_spd;
	bool m_del_f;		//消すフラグ(true = 消す)
};