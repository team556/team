#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
#include "UtilityModule.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：惑星(プレイヤー & 敵)
class CObjPlanet :public CObjFight //CObjFightを継承する
{
public:
	CObjPlanet(float x, float y, float size, int type = g_Challenge_enemy);//座標+サイズ(HP)+敵ナンバー
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	//float GetHp() { return m_hp; }	
	float GetSiz() { return m_size; }		//現在サイズ(HP)取得関数
	float GetMaxSiz() { return m_siz_max; }	//最大サイズ(HP)取得関数
	float GetSiz_change_range() { return m_siz_change_range; }//星サイズの変更幅取得用
	float GetScale_down_move() { return m_scale_down_move; }//サイズ縮小分のX座標移動量を返す
	int   GetAni_frame() { return m_ani_frame[0]; }	//アニメーションフレーム取得用
	int  GetType() { return m_type; }
	int  GetLine() { return m_get_line; }
	bool GetInvincible() { return m_invincible_f; }//無敵であるかどうか返す
	float GetRank_size() { return m_rank_size; } //戦闘終了直後のＨＰ割合を返す(ランクを決める際に使用)
	void SetVX(float vector) { m_px += vector; }//X移動用
	void SetDamage() { m_size -= m_siz_max * 0.04f; }//呼び出すとダメージ処理を行う[スペシャル技:Explosion用]
	void SetScale_down_move(int Planet_id) //呼び出すとサイズ縮小分、X座標の移動を行う(Planet_id:プレイヤー or エネミー判別用)[スペシャル技:Explosion用]
	{
		Planet_id = Planet_id == 0 ? -1 : 1;//Planet_idが0なら-1を、それ以外なら1をPlanet_idに代入する
		m_scale_down_move = ((1 - (m_size / m_siz_max)) * 60) * Planet_id; 
	}
	void SetInvincible(bool is_Invincible) { m_invincible_f = is_Invincible; }//無敵フラグ設定用[スペシャル技:Immortality用]
	void SetRecastBuff(float buff) { m_enemy_recast_buff = buff; }//バフ倍率設定用[スペシャル技:リミットブレイク用]
	void SetEeatF() { m_eat_f = true; }//セット喰うフラグ
	void SetEmF() { m_eat_me = true; } //セット喰われるフラグ

	void SetDelF() { m_del_f = true; }//セット消すフラグ
	//void SetInjF(bool inject) { m_inject_f = inject; }//セットチュートリアル射出フラグ(trueで打つようになる)[どういう訳か、trueにしてもfalseになってしまい、原因がよく分からなかったので別の方法でチュートリアル惑星を撃つようにしました。(後庵)]
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_vy;			//モアイ用()
	float m_size;		//星サイズ(現在HP)
	float m_siz_max;	//サイズマックス(最大HP)
	float m_siz_change_range;	//星サイズの変更幅(最小サイズ＋この変数の値が最大サイズとなる)[例:最小サイズ:60,この変数:60 → 60〜120のサイズで変動する惑星となる]
	//float m_siz_vec;	//サイズ変更ベクトル
	//float m_siz_spd;	//サイズ変更スピード
	float m_get_siz;	//ゲット現在サイズ(HP)[敵の現在HP取得用]
	float m_get_max_siz;//ゲット最大サイズ(HP)[敵の最大HP取得用]
	float m_mov_spd;	//惑星移動スピード
	float m_scale_down_move;	//サイズ縮小分、X座標移動用(プレイヤーなら左に、エネミーなら右に移動)

	//float m_hp;			//ヒットポイント(m_sizeでHPも管理する事に変更。size = hp)
	//float m_get_hp;		//ゲットHP
	int m_cnt;			//カウント
	int m_type;		//惑星タイプ(主人公 == 0 != 敵)
	int m_img_nam;	//画像(image)ナンバー

	bool m_invincible_f;	//無敵フラグ(true:無敵　false:無敵ではない)[スペシャル技:Immortality用]
	float m_enemy_recast_buff;//エネミーミサイルポッドリキャストタイムのバフ倍率[スペシャル技:リミットブレイク用]	


	int m_time;
	int m_attackf;		//敵の攻撃タイプ

	int m_ani[4];
	int m_mani[6];		//モアイ
	int m_ani_time;
	int m_ani_frame[2];	//[0] = 通常ani用、[1] = 特殊ani用
	int m_vib_time;		//捕食後の振動時間管理用

	bool m_eat_f;		//喰うフラグ(true = 喰う)
	bool m_eat_me;		//食べられる
	float m_eat_spd;	//喰う速さ
	float m_r;			//モアイ用角度
	bool m_del_f;		//消すフラグ(true = 消す)

	bool m_win;			//敵惑星に勝利した時に流れる音楽のフラグ	
	bool m_failed;		//敵惑星に敗北した時に流れる音楽のフラグ

	int m_cntf;			//fightのm_cnt変数の値を格納する用
	int m_mov_stop;		//

	int Enemy_Attack_pattern_x;  //敵攻撃パターンの横軸読み込む用
	int Enemy_Attack_pattern_y;  //敵攻撃パターンの縦軸読み込む用

	int Enemy_Line_pattern_x;	////敵攻撃パターンの横軸読み込む用
	int Enemy_Line_pattern_y;	////敵攻撃パターンの縦軸読み込む用

	int m_get_line;				//取得したラインナンバー

	bool m_inject_f;	//チュートリアル惑星の攻撃制御用(true = 撃つ)

	float m_rank_size;		//戦闘終了直後のＨＰ割合保存用(ランクを決める際に使用)

	//メモ：↓m_rはモアイ用角度が使っており被っていたので、仮でm_r2としておきました。(後庵)
	float m_r2;			//体力減少時の汗の動き用変数
	float m_sweat_vy;	//上に同じ
	float m_subsize;	//汗表示に使うm_size保存用変数
};