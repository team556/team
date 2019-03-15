#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjMissile :public CObj
{
public:
	CObjMissile(float x, float y);
	~CObjMissile() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//ミサイルの座標X
	float m_y;		//ミサイルの座標Y
	float m_vx;		//ベクトルX
	float m_vy;		//ベクトルY
	float m_size;	//ミサイルのサイズ
	bool  m_mou_f;

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	int m_get_line;		//取得したラインナンバー
	int m_cnt;			//カウント用
};