#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：クリア画面
class CObjFightClear :public CObj
{
public:
	CObjFightClear(int p, int m, int s, int l);
	~CObjFightClear() {};
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

	float m_a;		//alpha 透明度
	float m_a_vec;	//m_aベクトル
	bool m_a_f;		//不透明化フラグ

	int m_people;	//住民
	int m_mrl;		//マテリアルズ(資材)
	int m_skill;	//スペシャル技
	int m_large;		//サイズ

	int m_cnt;		//カウント
};