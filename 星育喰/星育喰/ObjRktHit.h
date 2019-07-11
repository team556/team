#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjRktHit :public CObj

{
public:
	CObjRktHit(float x, float y, bool t);//座標、タイプ、
	~CObjRktHit() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//座標X
	float m_y;		//座標Y
	float m_vx;		//X移動用vec
	float m_vy;		//Y移動用vec
	float m_mov;	//Y変則移動用
	float m_mov_spd;//動くスピード
	float m_size;	//縦横サイズ(50)

	int m_get_line;	//戦闘シーンからGetしたline

	bool  m_atk_f;	//交戦用(false = OFF, true = ON)
	bool  m_type;	//タイプ(false 味方 , true 敵)
};