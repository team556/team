#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：育成画面
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_Cloud_move;	//雲の移動用ベクトル

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool  m_key_f;		//キーフラグ

protected:
	static bool test_flag;//施設ウインドウの複数起動阻止フラグ(にする予定)
};