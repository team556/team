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
	float m_x;		//スペシャル技ボタンの座標X
	float m_y;		//スペシャル技ボタンの座標Y
	float m_h;		//スペシャル技ボタンのheight(高さ)
	float m_w;		//スペシャル技ボタンのwidth(幅)
	float m_a;		//スペシャル技ボタンのalpha(透過度)

	//▼配列数字の意味は以下の通り
	//0:プレイヤー惑星　1:敵惑星

	float m_hp[2];	//惑星のHP[敵に大ダメージ用]
	float m_size[2];//惑星のサイズ[敵に大ダメージ用]

	int m_line;		//選択中のライン(上から0,1,2)[一列殺し用]

	bool m_invincible[2];	//無敵フラグ[一定時間無敵用]

	int  m_recast_time[2];		//ミサイルポッドのリキャストタイム[生産性効率アップ]



	int m_time[2];	//スペシャル技効果時間管理用

	bool m_is_used_special[2];	//スペシャル技が使用されたか(true:使用済　false:未使用)

	int  m_enemy_special_equipment;//敵装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
	bool m_enemy_special_button;//敵用スペシャル技発動ボタン(true:発動　false:発動してない)





	int m_Planet_id; //敵orプレイヤー識別用

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
};