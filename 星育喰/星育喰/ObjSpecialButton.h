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

	bool GetEnemy_Used_Special() { return m_is_used_special[1]; }//敵がスペシャル技を使用したかどうかを返す
	void SetSpecial_Equip(int equip) { m_enemy_special_equipment = equip; }//敵の発動するスペシャル技を決める用
	void SetSpecial_Start() { m_enemy_special_button = true; }	//敵のスペシャル技を発動させる用
private:
	void Special_staging_message(int Planet_id, int Special_equip);	//スペシャル技発動演出メッセージ設定関数

	float m_x;		//スペシャル技ボタンの座標X
	float m_y;		//スペシャル技ボタンの座標Y
	float m_h;		//スペシャル技ボタンのheight(高さ)
	float m_w;		//スペシャル技ボタンのwidth(幅)
	float m_a;		//スペシャル技ボタンのalpha(透過度)

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	bool  m_special_staging_f;			//スペシャル技発動演出フラグ[true:演出中　false:演出してない]
	wchar_t m_staging_message[2][13];	//スペシャル技発動演出フォント用([フォント行数][文字データ格納可能数])
	float m_staging_font_color;			//スペシャル技発動演出フォントカラー変更用

	//▼配列数字の意味は以下の通り
	//0:プレイヤー惑星　1:敵惑星
	int m_count[2];				//スペシャル技効果時間、効果回数、発動演出時間管理用
	bool m_is_used_special[2];	//スペシャル技が使用されたか[スペシャル技発動演出終了時点で使用したとみなされる](true:使用済　false:未使用)
	bool m_is_invocating[2];	//現在スペシャル技が発動中であるか(true:発動中　false:発動済 or 未発動)

	//▼以下はObjPlanet(Enemy)から送られてくる情報を取得する
	int  m_enemy_special_equipment;//敵装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
	bool m_enemy_special_button;//敵用スペシャル技発動ボタン(true:発動　false:発動してない)


	//▼オブジェクト情報取得用のポインタをそれぞれ宣言
	//※スペシャル技ボタンの処理を各オブジェクトに送ったり、逆に取得したりする為のもの。
	CObjFight *FightScene;
	CObjPlanet *Player;
	CObjPlanet *Enemy;
	CObjRocketButton *Pod1;
	CObjRocketButton *Pod2;
	CObjRocketButton *Pod3;
	CObjRocketButton *Pod4;
	CObjRocketButton *Missile;
};