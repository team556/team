#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjGameClear :public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;
	float m_y;
	bool  m_f;

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	float m_y_vec;	//y軸ベクトル
	float m_cy[100];	//charのy軸
	int m_c_nam;		//charのナンバー

	int	m_speed;		//エンドロール速度をはやくする

	float m_alpha;		//透過度(アルファ値)
	float m_right_alpha;		//スクロール速度の説明文を透過する

	bool  m_flag;		//true=クリックした　false=クリックしてない
	bool  m_end_f;		//スクロール終了フラグ
};
