#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：スペシャル技ボタン
class CObjSpecialButton :public CObjFight //CObjFightを継承する
{
public:
	CObjSpecialButton(float x, float y, float h, float w);
	~CObjSpecialButton() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//スペシャル技ボタンの位置X
	float m_y;		//スペシャル技ボタンの位置Y
	float m_h;		//スペシャル技ボタンのheight(高さ)
	float m_w;		//スペシャル技ボタンのwidth(幅)
	float m_a;		//スペシャル技ボタンのalpha(透過度)

	bool m_is_used_special;	//スペシャル技が使用されたか(true:使用済　false:未使用)



	int m_get_line; //取得したライン(0～2)
	int m_cnt;		//カウント

	int Button_num; //パワーなどのボタン番号

	float m_create_x;	//プレイヤー惑星ポッド作成X位置調整用

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool m_mou_f;		//マウスフラグ
};