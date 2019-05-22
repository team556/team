#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：ミサイル&ポッドボタン
class CObjRocketButton :public CObjFight //CObjFightを継承する
{
public:
	CObjRocketButton(float x, float y, float h, float w, int n);
	~CObjRocketButton() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	void SetRecastBuff(float buff) { m_player_recast_buff = buff; }//バフ倍率設定用[スペシャル技:リミットブレイク用]
private:
	float m_x;		//座標X
	float m_y;		//座標Y
	float m_h;		//height高
	float m_w;		//width幅
	float m_a;		//alpha

	int m_get_line; //取得したライン(0～2)
	int m_cnt;		//カウント

	int Button_num; //パワーなどのボタン番号

	float m_player_recast_buff;	//プレイヤーミサイルポッドリキャストタイムのバフ倍率[スペシャル技:リミットブレイク用]

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool m_mou_f;		//マウスフラグ

	float m_px;			//惑星のX座標代入用
	float m_py;			//惑星のY座標代入用
	float m_size;		//惑星のSize代入用
};