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
	int m_del_cnt;	//削除までのカウント用

	bool m_atk_f;	//交戦用(true = 戦闘中)
	bool m_type;	//タイプ(true = 敵)
	bool m_del_f;	//削除フラグ(true = 削除)
	bool m_ppod_f;	//プレイヤーポッドと接触中フラグ(true = 接触中)
	bool m_epod_f;	//エネミーポッドと接触中フラグ(true = 接触中)
};