#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：ミサイルボタン
class CObjPushMissile :public CObjFight //CObjFightを継承する
{
public:
	CObjPushMissile(float x, float y, float h, float w);
	~CObjPushMissile() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//座標X
	float m_y;		//座標Y
	float m_h;		//height高
	float m_w;		//width幅
	float m_a;		//alpha

	int m_get_line; //取得したライン(0～2)
	int m_cnt;		//カウント
	int m_re_time;	//リキャストタイム

	float m_create_x;	//プレイヤー惑星ミサイル作成X位置調整用

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool m_mou_f;		//マウスフラグ
};
