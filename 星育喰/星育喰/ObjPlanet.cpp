//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "ObjPlanet.h"
#include <stdlib.h>
#include <time.h>

//使用するネームスペース
using namespace GameL;

//マクロ
/*DELAYのマクロは敵のポッド発射速度です
DELAYの値を増やすと発射速度が遅くなり、
値を減らすと発射速度が速くなります*/
#define ONE_DELAY (170)//たこ焼き
#define SEC_DELAY (140)//モアイ
#define THI_DELAY (180)//コワモーテ
#define FOU_DELAY (140)//再星
#define FIV_DELAY (140)//アマテラス
#define SIX_DELAY (200)//ボロボロン
#define MIN_SIZE (60.0f)//各惑星の最小サイズ(これ以上は小さくならない)

#define MOAI_NAM (2)	//モアイの番号type設定(仮

//コンストラクタ
CObjPlanet::CObjPlanet(float x, float y, float size, int type)
{
	//作成時に渡された値を、各ステータスに代入
	m_px = x;
	m_py = y;
	m_size = size;
	m_siz_max = size;
	m_type = type + 1;
	//m_get_siz = siz;
}

//イニシャライズ
void CObjPlanet::Init()
{
	//各ステータス初期化
	//m_size = 50.0f;//サイズ
	//m_siz_max= 50.0f;
	//m_siz_vec=  0.0f;
	m_siz_change_range = 60.0f;
	m_scale_down_move = 0.0f;
	m_r = 0.0f;

	m_cnt = 0;		//カウント

	//m_get_hp = 0;	//取得HP

	m_invincible_f = false;
	m_enemy_recast_buff = 1.0f;

	m_time = 0; //タイムカウント初期化
	m_attackf = 0;

	Enemy_Attack_pattern_x = 0;

	srand(time(NULL));
	Enemy_Attack_pattern_y = rand() % 5;//初期行動パターンをランダムで決める(この処理ないと初期行動パターンが必ず0のものになる)

	Enemy_Line_pattern_x = 0;

	srand(time(NULL));
	Enemy_Line_pattern_y = rand() % 3;//初期行動パターンをランダムで決める(この処理ないと初期行動パターンが必ず0のものになる)

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (fit->GetCount() / 70);//動く速度
	//*m_siz_spd*/ = 0.07f * 30 / (fit->GetCount() / 40);//拡大速度

	if (m_type == 0)
		m_px += 0.0f;
	else
		m_px -= 0.0f;

	m_mani[0] = 4;
	m_mani[1] = 0;
	m_mani[2] = 1;
	m_mani[3] = 0;
	m_mani[4] = 2;
	m_mani[5] = 3;

	m_ani[0] = 0;//アニメーションデータの初期化
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;

	m_ani_frame[0] = 0;
	m_ani_frame[1] = 0;
	m_ani_time = 0;
	m_vib_time = 0;
	m_cntf = 0;
	m_eat_f = false;	//喰うフラグ(true = 喰う)
	m_eat_me = false;
	m_eat_spd = fit->GetCount();
	m_del_f = false;	//消すフラグ(true = 消す)

	m_r2 = 0.0f;		
	m_vy = 0.0f;
	m_sweat_vy = 0.0f;

	m_subsize = 0.0f;

	m_inject_f = true;
	if(m_type == 6)//チュートリアル惑星のみ(最初から打てない設定にするとき用)
		m_inject_f = false;
	//m_img_nam = 0;

	m_rank_size = 0.0f;
	
	//当たり判定用HitBoxを作成(アクション中に更新される為、幅と高さはこの時点では0.0fでOK。)
	//それに加え各惑星のHP、画像番号等も設定している。
	if (m_type == 0)//プレイヤー惑星
	{		
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_PLAYER, OBJ_PLANET, 1);
		m_img_nam = 3 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1;
	}
	//60以下に設定すると汗が出なくなるので調節が必要
	else if (m_type == 1)//左から1番目の敵惑星(たこ焼き)
	{	
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 26;
		m_size = 100;
		m_siz_max = 100;
	}
	else if (m_type == 2)//左から2番目の敵惑星(モアイ)
	{	
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 27;
		m_size = 270;
		m_siz_max = 270;
	}
	else if (m_type == 3)//左から3番目の敵惑星(コワモーテ)
	{ 
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 28;
		m_size = 500;
		m_siz_max = 500;
	}
	else if (m_type == 4)//左から4番目の敵惑星(再星)
	{ 
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 29;
		m_size = 200;
		m_siz_max = 200;
	}
	else  if(m_type == 5)   //ボス惑星(アマテラス)
	{
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 30;
		m_size = 600;
		m_siz_max = 600;
	}
	else if(m_type == 6)	//チュートリアル惑星
	{
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 122;
		m_size = 80;
		m_siz_max = 80;
	}
}

//アクション
void CObjPlanet::Action()
{
	if (g_tutorial_progress == 6)
	{
		m_inject_f = true;//チュートリアル惑星も攻撃してくるようにする処理
	}

	CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);

	//▼戦闘開始前は戦闘処理(敵惑星の行動等)を実行しないようにする
	if (battle_start == false)
	{
		return;
	}

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	//if (fit->GetCount() != 0)		//対戦時間が0でない場合
	//	/*m_siz_vec += m_siz_spd*/; //拡大非をベクトルに加算


	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	if (((hit->CheckElementHit(ELEMENT_ENEMY) == true)
		|| (hit->CheckElementHit(ELEMENT_PLAYER) == true))	//お互い当たっているかつ
		&& (m_cnt < (2.5 * 60) * m_mov_spd)) {		//2.5秒カウントしてない場合
		m_cnt++;
	}

	//-------------------------------------------------アニメーション、星の動き
	if (m_ani_time == 60 || m_vib_time >= 1) {	//フレーム切り替え時間(捕食後の振動処理中は関係なくこの処理に入る)
		
		//惑星振動＆巨大化処理(相手惑星を喰うとこの処理に入る)
		if (m_ani_frame[0] == 3)
		{
			//vib_time加算処理(惑星捕食後から開始)
			if (m_vib_time >= 1)
			{
				m_vib_time++;		//vib_time 加算
			}

			//約0.6〜1.6秒中、左右に振動する処理
			if (40 < m_vib_time && m_vib_time < 100)
			{
				if (m_vib_time % 5 == 0)
				{
					if (m_vib_time % 2 == 0)
					{
						m_px += 10.0f;
					}
					else
					{
						m_px -= 10.0f;
					}

				}
			}

			//約2.8秒後リザルト画面に移行できるように
			//フレームを４に切り替える。
			if (m_vib_time == 170)
			{
				m_ani_frame[0] = 4;
				m_ani_frame[1] = 4;
			}
			//1.6秒後、惑星サイズを大きくする。
			//ＳＥも鳴らす。
			else if (m_vib_time == 100)
			{
				//▼演出用サイズ変更処理
				m_size = m_siz_max;//m_size(HP)を満タンに設定
				m_siz_change_range *= 1.5f;//その後、1.5倍化する
				Audio::Start(12);
			}
		}
		//相手惑星を喰っていない時は以下の処理を実行
		else
		{
			m_ani_time = 0;		//タイムリセット

			m_ani_frame[0]++;		//フレーム切り替え
			m_ani_frame[1]++;
		}
		

		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		/*if(pla != nullptr && )
			pla->SetEmF();*/
		if (m_ani_frame[0] == 4) {			//最終初期フレームにする前
			m_eat_f = false;	//食べるフラグ★OFF
			m_ani_time = -1;							//ループ制御☆
			m_vib_time = 0;								//ループ制御☆
			if (m_type == 0) {		//主人公の場合
				//CObjFightClear* crer = new CObjFightClear(100,50,0,20);	//(住人,資材,スキル,大きさ)
				//Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);	//クリア画面

				//勝利惑星の口(背面)を非表示にする
				CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
				fight->SetPrey_f(-1);

				if (g_tutorial_progress == 6)
				{
					//ObjMessageのメッセージ進行度を増加させる
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setprogress(39);
				}

				if (g_tutorial_progress != 6)
				{
					fit->SetEnd();

					//戦闘音楽を破棄し勝利音楽再生
					Audio::Stop(0);
					Audio::Start(4);
				}
			}
			else {
				CObjFightOver* over = new CObjFightOver();	//敵の場合
				Objs::InsertObj(over, OBJ_FIGHT_CLEAR, 15);	//ゲームオーバー画面

				//戦闘音楽を破棄し敗北音楽再生
				Audio::Stop(0);
				Audio::Start(2);
			}
		}
	}
	else if (m_ani_time == 30) {
		m_ani_frame[1]++;		//特殊aniフレーム切り替え
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		if (m_type == MOAI_NAM && m_ani_frame[1] == 3 && pla != nullptr) {
			pla->SetEmF();
		}
	}
	if (m_ani_frame[1] == 6) {
		m_ani_frame[1] = 0;
	}
	//2.5秒
	if (m_cnt < (2.5 * 60) * m_mov_spd)	//カウントし終わってない場合
		if (m_type == 0)//------(戦闘中)
		{
			if (hit->CheckElementHit(ELEMENT_LINE) != true)
				m_px -= m_mov_spd;	//自星の動き
			else
			{

			}
		}
		else
		{
			if (m_type >= 1)
			{
				if (hit->CheckElementHit(ELEMENT_LINE) != true)
					m_px += m_mov_spd;	//敵星の動き
				else
				{
				}
			}
		}
	else { 						//カウントし終わった後 (停止後)
		if (m_ani_time == 0) {					//timeでループ制御☆

			//▼戦闘終了時処理
			//プレイヤー惑星、敵惑星のサイズ(現在HPと最大HP)をそれぞれ取得し、勝敗判定を行う
			//※惑星サイズが大きい方の勝利。
			//また、サイズ(HP)が高い方の惑星画像が手前に来るようにする
			//※同HPならプレイヤーの勝利となる。
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				if (ene != nullptr)
				{
					m_get_siz = ene->GetSiz();
					m_get_max_siz = ene->GetMaxSiz();
				}
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				if (pla != nullptr)
				{
					m_get_siz = pla->GetSiz();
					m_get_max_siz = pla->GetMaxSiz();
				}
			}
			if (m_type == 0) {
				if ((m_size / m_siz_max) >= (m_get_siz / m_get_max_siz))
				{
					m_eat_f = true;		//喰うフラグ有効

					//勝利惑星の口(背面)を描画させる
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetPrey_f(m_type);

					m_rank_size = m_size / m_siz_max;//戦闘終了直後のＨＰ割合を保存する(ランクを決める際に使用)
				}
			}

			else {
				if ((m_size / m_siz_max) > (m_get_siz / m_get_max_siz))
				{
					m_eat_f = true;		//喰うフラグ有効
					m_r = 20.0f;		//モアイ角度変更

					CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
					ene->SetPrio(11);	//オブジェクトの優先順位変更し、敵惑星が手前に来るようにする

					//勝利惑星の口(背面)を描画させる
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetPrey_f(m_type);
				}
			}
		}
	}

	if (m_eat_f == true) {	//食べるフラグ★処理
		m_ani_time++;		//ani_time 加算
		if ((m_ani_frame[0] == 3) && (m_ani_time == 1) && (m_vib_time == 0)) {//口閉じた瞬間

			m_vib_time = 1;		//vib_time加算処理を開始
			m_r = 0.0f;

			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				ene->SetDelF();
				Audio::Start(9);

			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				pla->SetDelF();
				Audio::Start(9);

			}
		}
	}
	else
	{
		m_ani_frame[0] = 0;	//初期フレーム
		m_ani_frame[1] = 0;
	}

	if (m_ani_frame[0] == 2)		//喰うフレームの移動
	{

		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		if (m_type != MOAI_NAM) {
			if (m_type == 0)
			{
				if (m_px > ene->GetX() + ene->GetScale_down_move() - pla->GetScale_down_move())		//敵のX座標より自惑星が大きくなると移動を止める
				{
					m_px -= 4.0f;
				}
			}
			else
			{
				if (m_px < pla->GetX() + pla->GetScale_down_move() - ene->GetScale_down_move())		//自分のX座標より敵惑星が小さくなると移動を止める
				{
					m_px += 4.0f;
				}
			}
		}
	}
	else if (m_eat_me == true && m_eat_f != true)
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		if (ene != nullptr) {
			if (m_px > ene->GetX() + ene->GetScale_down_move() - pla->GetScale_down_move())		//敵のX座標より自惑星が大きくなると移動を止める
			{
				m_px -= 2.3f;
				if(m_size >= -120.0f)
					m_size -= 1.8f;
				if (m_py < 365)
					m_vy += 0.1f;
				else
					m_vy -= 0.1f;
				m_py += m_vy;
			}
		}
	}

	//-------------------------------------------------------------


	hit->SetPos(m_px + m_scale_down_move - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range),	//HitBox更新
		m_py - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range),
		(MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range)) * 2,
		(MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range)) * 2);

	//▼ダメージ処理
	//▽プレイヤーのダメージ処理(ミサイルポッドHIT時)
	if ((hit->CheckElementHit(ELEMENT_ENEMYPOD) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD1) || hit->CheckElementHit(ELEMENT_ENEMYPOD2) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD3) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD4) == true
		|| hit->CheckElementHit(ELEMENT_ENEMYPOD5) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD6) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD7) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD8) == true || hit->CheckElementHit(ELEMENT_ENEMYPOD9) == true || hit->CheckElementHit(ELEMENT_ENEMYRKT) == true) 
		&& (m_type == 0) && (m_size > 0))
	{
		//無敵フラグがtrueの時は以下のダメージ処理を飛ばす
		if (m_invincible_f == false)
		{
			CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
			//敵がチュートリアル惑星以外の時
			if (ene->GetType() != 6) {
				//ポッドが与えれるダメージ量をRocket.cppからグローバル変数で引っ張ってきた
				//ダメージ量は「(敵攻撃力 * 3.6 [リミットブレイクすれば更に1.5倍]」
				if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)//パワーポッドHIT時の処理
				{
					m_size -= g_P_Planet_damage * 3.6f * damage_buff[1];	//サイズ(HP)減少
				}
				else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//スピードポッドHIT時の処理
				{
					m_size -= g_P_Planet_damage * 3.6f * damage_buff[1];	//サイズ(HP)減少
				}
				else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//ディフェンスポッドHIT時の処理
				{
					m_size -= g_P_Planet_damage * 3.6f * damage_buff[1];	//サイズ(HP)減少
				}
				else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//バランスポッドHIT時の処理
				{
					m_size -= g_P_Planet_damage * 3.6f * damage_buff[1];	//サイズ(HP)減少
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//ミサイルHIT時の処理
				{
					m_size -= 3;	//サイズ(HP)減少
				}


				m_scale_down_move = -((1 - (m_size / m_siz_max)) * m_siz_change_range);	//縮む分だけ左に移動
			}
		}
	}
	//▽エネミーのダメージ処理(ミサイルポッドHIT時)
	else if ((hit->CheckElementHit(ELEMENT_POD) == true || hit->CheckElementHit(ELEMENT_POD1) == true || hit->CheckElementHit(ELEMENT_POD2) == true || hit->CheckElementHit(ELEMENT_POD3) == true || hit->CheckElementHit(ELEMENT_POD4) == true
		|| hit->CheckElementHit(ELEMENT_POD5) == true || hit->CheckElementHit(ELEMENT_POD6) == true || hit->CheckElementHit(ELEMENT_POD7) == true || hit->CheckElementHit(ELEMENT_POD8) == true || hit->CheckElementHit(ELEMENT_POD9) == true || hit->CheckElementHit(ELEMENT_RKT) == true)
		&& (m_type != 0) && (m_size > 0))
	{
		//無敵フラグがtrueの時は以下のダメージ処理を飛ばす
		if (m_invincible_f == false)
		{
			//ダメージ量は「(2 + コアのレベル + 兵舎のレベル - 1) * 3.6 [リミットブレイクすれば更に1.5倍]」
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//パワーポッドHIT時の処理
			{
				m_size -= (2.0f + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1)) * 3.6f * damage_buff[0];	//サイズ(HP)減少
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//スピードポッドHIT時の処理
			{
				m_size -= (2.0f + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1)) * 3.6f * damage_buff[0];	//サイズ(HP)減少
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//ディフェンスポッドHIT時の処理
			{
				m_size -= (2.0f + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1)) * 3.6f * damage_buff[0];	//サイズ(HP)減少
			}
			else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//バランスポッドHIT時の処理
			{
				m_size -= (2.0f + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1)) * 3.6f * damage_buff[0];	//サイズ(HP)減少
			}
			else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//ミサイルHIT時の処理
			{
				m_size -= 3;	//サイズ(HP)減少
			}


			m_scale_down_move = ((1 - (m_size / m_siz_max)) * m_siz_change_range);//縮む分だけ右に移動
		}
	}

	//どちらかの惑星がHP0以下に達した時、
	//制限時間が余っていても戦闘終了処理を行う
	if (m_size <= 0.0f && battle_end == false)
	{
		m_size = 0.0f;		//0未満の値になっている場合、0に設定する

		if (m_type == 0)//プレイヤーの時
		{
			m_scale_down_move = -((1 - (m_size / m_siz_max)) * m_siz_change_range);	//縮む分だけ左に移動
		}
		else if (m_type != 0)//敵惑星の時
		{
			m_scale_down_move = ((1 - (m_size / m_siz_max)) * m_siz_change_range);	//縮む分だけ右に移動
		}

		battle_end = true;	//戦闘終了フラグを立てる
		fit->SetEndCount();	//戦闘時間を残り1秒に設定する
	}

	if (m_del_f == true) {				//消すフラグ判定＆処理
		this->SetStatus(false);	 //オブジェクト削除
		Hits::DeleteHitBox(this);//HitBox削除
	}

	if (m_inject_f == true) {
		//▼敵惑星攻撃パターン
		if (m_type >= 1 && battle_end == false)//惑星が敵の時のみ弾を発射し、戦闘終了時に弾を打たないようにする。
		{
			//▼敵行動パターン決め
			if (m_time <= 0)
			{
				int Enemy_Fight_type[7][5][6] =   //敵攻撃用の配列作成
				{
					//m_type==0 これは呼び出されない
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 2,3,2,2,5,0 }, //0番目
						{ 2,2,2,4,2,0 }, //1番目
						{ 2,5,3,2,4,0 }, //2番目
						{ 5,2,3,2,2,0 }, //3番目
						{ 2,1,2,5,6,0 }, //4番目
					},
					//m_type==1たこ焼き
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 2,3,2,2,5,0 }, //0番目
						{ 1,2,2,4,2,0 }, //1番目
						{ 2,5,3,2,4,0 }, //2番目
						{ 5,2,3,2,2,0 }, //3番目
						{ 2,1,2,5,2,0 }, //4番目
					},
					//m_type==2モアイ
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 1,3,1,1,5,0 }, //0番目
						{ 2,1,1,4,1,0 }, //1番目
						{ 1,5,3,1,4,0 }, //2番目
						{ 5,1,3,1,1,0 }, //3番目
						{ 1,2,1,5,1,0 }, //4番目
					},
					//m_type==3コワモーテ
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 4,3,4,4,5,0 }, //0番目
						{ 2,4,4,2,4,0 }, //1番目
						{ 4,5,3,4,2,0 }, //2番目
						{ 5,4,3,4,4,0 }, //3番目
						{ 4,1,4,5,4,0 }, //4番目
					},
					//m_type==4再星
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 3,2,3,3,5,0 }, //0番目
						{ 2,3,3,4,3,0 }, //1番目
						{ 3,5,2,3,4,0 }, //2番目
						{ 5,3,2,3,3,0 }, //3番目
						{ 3,1,3,5,3,0 }, //4番目
					},
					//m_type==5アマテラス
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 1,5,2,1,1,0 }, //0番目
						{ 2,6,3,2,2,0 }, //1番目
						{ 3,5,4,3,3,0 }, //2番目
						{ 4,2,5,4,4,0 }, //3番目
						{ 5,1,1,5,5,0 }, //4番目
					},
					//m_type == 6(チュートリアル惑星)
					{
						//1=赤,2=青,3=緑,4=灰色,5=ミサイル,6=スペシャル技
						{ 1,2,3,4,5,0 }, //0番目
						{ 1,2,3,4,5,0 }, //1番目
						{ 1,2,3,4,5,0 }, //2番目
						{ 1,2,3,4,5,0 }, //3番目
						{ 1,2,3,4,5,0 }, //4番目
					},
					/*
					　攻撃パターン追加する際は、上の配列の数字を変え
					  下のコメントアウトを取って、出したい種類の数字をカンマごとに順番に入れてください。
					{,,,,,}, //5番目
					{,,,,,}, //6番目
					{,,,,,}, //7番目
					{,,,,,}, //8番目
					*/
				};

				m_attackf = Enemy_Fight_type[m_type][Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
				if (m_attackf == 0)//--------配列が最後に行ったとき(0の時)
				{
					Enemy_Attack_pattern_x = 0;//配列一番左の状態に戻す
					//↓行動パターンを決める,ランダムを割っている数字と配列の種類を増やすと攻撃パターンが増える	
					srand(time(NULL));
					Enemy_Attack_pattern_y = rand() % 5;
					//↓m_attackに攻撃パターンを入れる処理
					m_attackf = Enemy_Fight_type[m_type][Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
					Enemy_Attack_pattern_x++;
				}
				else
				{
					Enemy_Attack_pattern_x++;
				}
			}


			CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (m_type != 0 && Special->GetEnemy_Used_Special() == false) {
				switch (m_type) {
				case 1://大阪のフラクチャーレイ
					//自惑星のＨＰが60％以下
					if (m_size / m_siz_max <= 0.6) {
						m_attackf = 6;
					}
					break;
				case 2://アモイのエクスプロージョン
					//自惑星のＨＰが30％以下且つ敵のHPが70％以上で無敵でないとき
					if ((m_size / m_siz_max <= 0.5) && (pla->GetSiz() / pla->GetMaxSiz() >= 0.7)
						&& (pla->GetInvincible() != true)) {
						m_attackf = 6;
					}
					//敵惑星のＨＰが50％以下になった時
					if (pla->GetSiz() / pla->GetMaxSiz() <= 0.5) {
						m_attackf = 6;
					}
					break;
				case 3://コワモーテのリミットブレイク
					//自惑星のＨＰが70％以下になった時
					if (m_size / m_siz_max <= 0.7) {
						m_attackf = 6;
					}
					//敵惑星のＨＰが40％以下になった時
					if (pla->GetSiz() / pla->GetMaxSiz() <= 0.4) {
						m_attackf = 6;
					}
					break;
				case 4://再星のイモータリティ
					//敵はエクスプロージョンを打った時
					if (g_Special_equipment == 1 && Special->GetPlayer_Used_Special() == true) {
						m_attackf = 6;
					}
					//自惑星のＨＰが30％以下になった時
					if (m_size / m_siz_max <= 0.3) {
						m_attackf = 6;
					}
					break;
				case 5://アマテラスのオーバーワーク
					//無条件で速攻使う
					m_attackf = 6;
					break;
				}
			}

			//▼敵惑星攻撃パターン
			if (m_type >= 1 && battle_end == false)//惑星が敵の時のみ弾を発射し、戦闘終了時に弾を打たないようにする。
			{
				//敵の発動するスペシャル技を決める(0:未装備　1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)
				switch (m_type) {
				case 1:
					Special->SetSpecial_Equip(2);
					break;
				case 2:
					Special->SetSpecial_Equip(1);
					break;
				case 3:
					Special->SetSpecial_Equip(5);
					break;
				case 4:
					Special->SetSpecial_Equip(3);
					break;
				case 5:
					Special->SetSpecial_Equip(4);
					break;
				}

				//▼敵レーン選択パターン決め
				if (m_time <= 0)
				{
					int Enemy_Fight_line[5][6] =   //敵攻撃用の配列作成
					{
						//0,3:上レーン　1:中レーン　2:下レーン
							{ 3,2,1,3,2,0 }, //0番目
							{ 2,3,2,3,1,0 }, //1番目
							{ 1,2,3,2,3,0 }, //2番目
							{ 2,1,1,2,3,0 }, //3番目
							{ 1,3,2,3,1,0 }, //4番目

						/*
						レーン選択パターン追加する際は、上の配列の数字を変え
						下のコメントアウトを取って、出したい種類の数字をカンマごとに順番に入れてください。
						{,,,,,}, //5番目
						{,,,,,}, //6番目
						{,,,,,}, //7番目
						{,,,,,}, //8番目
						*/
					};

					m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
					if (m_get_line == 0)//--------配列が最後に行ったとき(0の時)
					{
						Enemy_Line_pattern_x = 0;//配列一番左の状態に戻す
												 //↓行動パターンを決める,ランダムを割っている数字と配列の種類を増やすと攻撃パターンが増える	
						srand(time(NULL));
						//↓m_attackに攻撃パターンを入れる処理
						m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
						if (Enemy_Line_pattern_y <= 3) {
							Enemy_Line_pattern_y++;
						}
						else {
							Enemy_Line_pattern_y = rand() % 5;
						}
					}
					else
					{
						Enemy_Line_pattern_x++;
					}
				}
			}

			//▼ミサイル、ポッド作成X位置を設定
			if (m_attackf == 1 && m_time <= 0 && m_type != 0)//赤色ポッド
			{
				CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 1);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 20);		//オブジェクト登録
				switch (m_type)//敵の種類によって攻撃のリキャストタイム変更
				{
				case 1:
					m_time = ONE_DELAY * m_enemy_recast_buff;//たこ焼き
					break;
				case 2:
					m_time = SEC_DELAY * m_enemy_recast_buff;//モアイ
					break;
				case 3:
					m_time = THI_DELAY * m_enemy_recast_buff;//コワモーテ
					break;
				case 4:
					m_time = FOU_DELAY * m_enemy_recast_buff;//再星
					break;
				case 5:
					m_time = FIV_DELAY * m_enemy_recast_buff;//アマテラス
					break;
				case 6:
					m_time = SIX_DELAY * m_enemy_recast_buff;//ボロボロン
					break;
				}
			}
			else if (m_attackf == 2 && m_time <= 0 && m_type != 0)//青色ポッド
			{
				CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 2);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 20);		//オブジェクト登録
				/*m_time = 100 * m_enemy_recast_buff;*/
				switch (m_type)//敵の種類によって攻撃のリキャストタイム変更
				{
				case 1:
					m_time = ONE_DELAY * m_enemy_recast_buff;//たこ焼き
					break;
				case 2:
					m_time = SEC_DELAY * m_enemy_recast_buff;//モアイ
					break;
				case 3:
					m_time = THI_DELAY * m_enemy_recast_buff;//コワモーテ
					break;
				case 4:
					m_time = FOU_DELAY * m_enemy_recast_buff;//再星
					break;
				case 5:
					m_time = FIV_DELAY * m_enemy_recast_buff;//アマテラス
					break;
				case 6:
					m_time = SIX_DELAY * m_enemy_recast_buff;//ボロボロン
					break;
				}
			}
			else if (m_attackf == 3 && m_time <= 0 && m_type != 0)//緑色ポッド
			{
				CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 3);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 20);		//オブジェクト登録
			/*	m_time = 100 * m_enemy_recast_buff;*/
				switch (m_type)
				{
				case 1:
					m_time = ONE_DELAY * m_enemy_recast_buff;//たこ焼き
					break;
				case 2:
					m_time = SEC_DELAY * m_enemy_recast_buff;//モアイ
					break;
				case 3:
					m_time = THI_DELAY * m_enemy_recast_buff;//コワモーテ
					break;
				case 4:
					m_time = FOU_DELAY * m_enemy_recast_buff;//再星
					break;
				case 5:
					m_time = FIV_DELAY * m_enemy_recast_buff;//アマテラス
					break;
				case 6:
					m_time = SIX_DELAY * m_enemy_recast_buff;//ボロボロン
					break;
				}
			}
			else if (m_attackf == 4 && m_time <= 0 && m_type != 0)//灰色ポッド(今は黄色)
			{
				CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 4);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 20);		//オブジェクト登録
				//m_time = 100 * m_enemy_recast_buff;
				switch (m_type)
				{
				case 1:
					m_time = ONE_DELAY * m_enemy_recast_buff;//たこ焼き
					break;
				case 2:
					m_time = SEC_DELAY * m_enemy_recast_buff;//モアイ
					break;
				case 3:
					m_time = THI_DELAY * m_enemy_recast_buff;//コワモーテ
					break;
				case 4:
					m_time = FOU_DELAY * m_enemy_recast_buff;//再星
					break;
				case 5:
					m_time = FIV_DELAY * m_enemy_recast_buff;//アマテラス
					break;
				case 6:
					m_time = SIX_DELAY * m_enemy_recast_buff;//ボロボロン
					break;
				}
			}
			else if (m_attackf == 5 && m_time <= 0 && m_type != 0)//ミサイル
			{
				CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 5);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 20);		//オブジェクト登録
				//m_time = 100 * m_enemy_recast_buff;
				switch (m_type)
				{
				case 1:
					m_time = ONE_DELAY * m_enemy_recast_buff;//たこ焼き
					break;
				case 2:
					m_time = SEC_DELAY * m_enemy_recast_buff;//モアイ
					break;
				case 3:
					m_time = THI_DELAY * m_enemy_recast_buff;//コワモーテ
					break;
				case 4:
					m_time = FOU_DELAY * m_enemy_recast_buff;//再星
					break;
				case 5:
					m_time = FIV_DELAY * m_enemy_recast_buff;//アマテラス
					break;
				case 6:
					m_time = SIX_DELAY * m_enemy_recast_buff;//ボロボロン
					break;
				}
			}
			else if (m_attackf == 6 && m_time <= 0 && m_type != 0)//スペシャル技
			{
				//敵がスペシャル技を使用済(true)である場合、
				//リキャストタイムを元に戻さず、再度行動パターン決めを行う
				//未使用(false)であれば、以下の処理を行う
				if (Special->GetEnemy_Used_Special() == false)
				{
					Special->SetSpecial_Start();	//スペシャル技を発動させる
					m_time = 100 * m_enemy_recast_buff;
				}
			}
			m_time--;
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_cntf = obj->GetCount();	//CObjFightのカウント数を持ってくる

	if (m_cntf <= 0)			//カウント数が0以下になったら
	{
		if (m_cnt < m_mov_spd)	//惑星同士が重なっていないとき
		{
			if (m_type == 0)
				m_px -= 1.0f;
				
			else
				m_px += 1.0f;
		}
	}

	if (battle_end == false)	//バトル終了時、処理しない
	{
		if (m_size >= (MIN_SIZE * (m_siz_max / 100)) * 0.7f) {
			m_subsize = m_size;	
		}
		else if (m_subsize <= (MIN_SIZE * (m_siz_max / 100)) * 0.7f) {	//subsizeの最小の値を決める
			m_subsize = MIN_SIZE * (m_siz_max / 100)  * 0.7f;	//汗表示の際に使う式の分母の数が惑星によって変動するので仕方なくこうしている
		}
	}
}

//ドロー
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };//惑星画像&HPゲージ(現在値)用
	float g[4] = { 0.0f,1.0f, 0.0f, 1.0f };//緑HPゲージ(現在値)用
	float r[4] = { 1.0f,0.0f, 0.0f, 1.0f };//赤HPゲージ(現在値)用
	float b[4] = { 0.0f,0.0f, 0.0f, 1.0f };//HPゲージ(最大値)用
	RECT_F src;
	RECT_F dst;
	//切り取り位置
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame[0]] * 448.0f * 2;
	src.m_right = m_ani[m_ani_frame[0]] * 448.0f * 2 + 448.0f;
	src.m_bottom= 448.0f;
	//表示位置
	dst.m_top	= m_py - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range);
	dst.m_left	= m_px - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range) + m_scale_down_move;
	dst.m_right = m_px + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range) + m_scale_down_move;
	dst.m_bottom= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range);

	
	if (m_type != 0)//敵のみ切り取りサイズ変更
	{
		src.m_top	= 0.0f;
		src.m_left	= m_ani[m_ani_frame[0]] * 300.0f;
		src.m_right	= m_ani[m_ani_frame[0]] * 300.0f + 300.0f;
		src.m_bottom= 300.0f;
	}

	if (m_type == MOAI_NAM)//モアイは,m_mani[ani_frame[1]]を使う
	{
		src.m_top   = 0.0f;
		src.m_left  = m_mani[m_ani_frame[1]] * 300.0f;
		src.m_right = m_mani[m_ani_frame[1]] * 300.0f + 300.0f;
		src.m_bottom= 300.0f;
		Draw::Draw(m_img_nam, &src, &dst, c, m_r);
	}
	else {
		//m_img_namの数で、登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(m_img_nam, &src, &dst, c, 0.0f);
	}


	//▽HPゲージ表示(戦闘終了後は表示しない)
	if (battle_end == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top	= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range) - 5.0f;
		dst.m_left	= m_px - MIN_SIZE + m_scale_down_move;
		dst.m_bottom= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range);

		//▼最大値表示
		dst.m_right = m_px - MIN_SIZE + m_scale_down_move + (MIN_SIZE * 2);
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//▼現在値表示		
		dst.m_right = m_px - MIN_SIZE + m_scale_down_move + ((MIN_SIZE * 2) * (m_size / m_siz_max));

		
		if(m_size/m_siz_max >= 0.25f)				//HPが20%以上の時HPバーを緑色にする
			Draw::Draw(32, &src, &dst, g, 0.0f);
		else {										//HPが20%以下の時汗を出してHPバーを赤くする
			Draw::Draw(32, &src, &dst, r, 0.0f);

			//▼戦闘が続いているとき(止まっていないとき)上下する"汗"を表示
			if (battle_start == true) {
				//角度加算
				m_r2 += 10.0f;

				//360°で初期値に戻す
				if (m_r2 > 360.0f)
					m_r2 = 0.0f;

				//移動方向
				m_sweat_vy = sin(3.14f / 90 * m_r2);

				//速度付ける。
				m_sweat_vy *= 10.0f;
			}

			//汗を表示
			src.m_top	= 0.0f;
			src.m_left	= 0.0f;
			src.m_right = 128.0f;
			src.m_bottom= 128.0f;

			dst.m_top	= m_py - ((m_subsize / m_siz_max) * m_siz_change_range) + m_sweat_vy - ((m_subsize / m_siz_max) * 150);
			dst.m_left	= m_px - ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + ((m_subsize / m_siz_max) * 150);
			dst.m_right = m_px + ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + ((m_subsize / m_siz_max) * 150);
			dst.m_bottom= m_py + ((m_subsize / m_siz_max) * m_siz_change_range) + m_sweat_vy - ((m_subsize / m_siz_max) * 150);

			if (m_type != 0)//惑星がプレイヤー以外の時、汗の位置を左上に表示して反転させる
			{
				dst.m_left  = m_px + ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + ((m_subsize / m_siz_max) * 150) * -1;
				dst.m_right = m_px - ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + ((m_subsize / m_siz_max) * 150) * -1;
			}
			
			//汗
			Draw::Draw(34, &src, &dst, c, 1.0f);
		}
	}

}
