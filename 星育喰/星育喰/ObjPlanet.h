#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：惑星(プレイヤー & 敵)
class CObjPlanet :public CObjFight //CObjFightを継承する
{
public:
	CObjPlanet(float x, float y, float hp, int type, float siz = 0);//座標+HP+タイプ+サイズ
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	//float GetY() { return m_py; }
	float GetHp() { return m_hp; }	//HP取得関数
	//float GetSiz() { return m_size; }
	bool GetInvincible() { return m_invincible_f; }//無敵であるかどうか返す
	void SetDamage() { m_hp -= 1; }//呼び出すとダメージ処理(HP)を行う[スペシャル技:敵に大ダメージ用]
	void SetScale_down() { m_size -= m_size / 20; }////呼び出すとダメージ処理(SIZE)を行う[スペシャル技:敵に大ダメージ用]
	void SetInvincible(bool is_Invincible) { m_invincible_f = is_Invincible; }//無敵フラグ設定用[スペシャル技:一定時間無敵用]
	void SetRecastBuff(float buff) { m_enemy_recast_buff = buff; }//バフ倍率設定用[スペシャル技:生産性効率アップ用]
	void SetDamageBuff(float buff) { m_damage_buff = buff; }//バフ倍率設定用[スペシャル技:住民の士気がアップ用]
	void SetEeatF() { m_eat_f = true; }//セット喰うフラグ

	void SetDelF() { m_del_f = true; }//セット消すフラグ
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_size;		//星サイズ
	float m_siz_max;	//サイズマックス
	float m_siz_vec;	//サイズ変更ベクトル
	float m_siz_spd;	//サイズ変更スピード
	float m_get_siz;	//ゲットサイズ
	float m_mov_spd;	//惑星移動スピード

	float m_hp;			//ヒットポイント
	float m_get_hp;		//ゲットHP
	int m_cnt;			//カウント
	int m_type;		//惑星タイプ(主人公 == 0 != 敵)
	int m_img_nam;	//画像(image)ナンバー

	bool m_invincible_f;	//無敵フラグ(true:無敵　false:無敵ではない)[スペシャル技:一定時間無敵用]
	float m_enemy_recast_buff;//エネミーミサイルポッドリキャストタイムのバフ倍率[スペシャル技:生産性効率アップ用]
	float m_damage_buff;		//ダメージのバフ倍率[スペシャル技:住民の士気がアップ用]


	int m_time;
	int m_attackf;		//敵の攻撃タイプ

	float m_create_x;	//敵惑星ミサイルポッド作成X位置調整用
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//喰うフラグ(true = 喰う)
	float m_eat_spd;
	bool m_del_f;		//消すフラグ(true = 消す)

	int m_cntf;			//fightのm_cnt変数の値を格納する用
	int m_mov_stop;		//

	int Enemy_Attack_pattern_x;  //敵攻撃パターンの横軸読み込む用
	int Enemy_Attack_pattern_y;  //敵攻撃パターンの縦軸読み込む用
};