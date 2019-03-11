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
	float m_cnt;		//縮小用カウント
	
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y

	int m_pnam;			//画像ナンバー

	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	
};