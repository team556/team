//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define PLAYER (0)	//プレイヤー(配列を分かりやすくする用)
#define ENEMY  (1)	//エネミー	(配列を分かりやすくする用)
#define RECAST_BUFF_MAGNIFICATION (0.5f)	//ミサイルポッドリキャストタイムのバフ倍率(リキャストタイムを0.5倍→リキャストタイムが半分で済む)
#define DAMAGE_BUFF_MAGNIFICATION (1.5f)	//与えるダメージのバフ倍率(与えるダメージが1.5倍になる)
#define INI_BUFF (1.0f)						//上記2つのバフ倍率初期値
#define INI_WIDTH (200.0f)					//[スペシャル技:Explosion / Fracture_Ray]エフェクト画像の初期幅
#define INI_ALPHA (1.0f)					//スペシャル技エフェクト画像の初期透過度

//コンストラクタ
CObjSpecialButton::CObjSpecialButton(float x, float y, float h, float w)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
}

//イニシャライズ
void CObjSpecialButton::Init()
{
	m_a = 1.0f;

	m_mou_x = 0.0f;	
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_staging_font_color = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_count[i] = 0;
		m_is_used_special[i] = false;
		m_is_invocating[i] = false;
		m_special_staging_f[i] = false;

		m_Explosion_size[i] = 0.0f;
		m_Explosion_width[i] = INI_WIDTH;
		m_Explosion_pos[i] = 0.0f;
		m_Explosion_target[i] = 0;
		m_Explosion_angle[i] = 0.0f;

		m_Fracture_Ray_pos[i] = 0.0f;
		m_Fracture_Ray_width[i] = INI_WIDTH;

		m_Immortality_size[i] = 0.0f;
		
		m_Special_effect_alpha[i] = INI_ALPHA;
		m_Special_effect_alpha_vec[i] = 0.0f;
	}

	m_Enemy_line = 0;

	for (int i = 0; i < 3; i++)
	{
		m_PodMissile_count[i] = 0;
	}

	m_enemy_special_equipment = 0;
	m_enemy_special_button = false;

	//▼実際にオブジェクト情報を取得する
	FightScene = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	Planet[PLAYER] = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	Planet[ENEMY] =  (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
	PodMissile[0] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON1);
	PodMissile[1] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON2);
	PodMissile[2] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON3);
	PodMissile[3] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON4);
	PodMissile[4] = (CObjRocketButton*)Objs::GetObj(OBJ_MISSILE_BUTTON);
}

//アクション
void CObjSpecialButton::Action()
{
	//▼戦闘開始前は操作不能にする処理
	//※スペシャル技発動演出中はこの影響を受けないようにする
	if (battle_start == false && m_special_staging_f[PLAYER] == false && m_special_staging_f[ENEMY] == false)
	{
		return;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//▼プレイヤー惑星スペシャル技処理
	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && 	//X軸範囲
		(m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) &&	//Y軸範囲
		(m_mou_l == true) &&							//左クリック
		(g_Special_equipment != 0) &&					//スペシャル技装備してるかチェック
		(m_is_used_special[PLAYER] == false) ||			//スペシャル技が未使用であれば実行
		(m_is_invocating[PLAYER] == true))				//また、現在スペシャル技発動中であっても実行
	{
		//エネミーがスペシャル技発動演出中である場合、
		//以下の処理を実行しないようにする。
		if (m_special_staging_f[ENEMY] == false)
		{
			Special_process(PLAYER, ENEMY, g_Special_equipment);	//スペシャル技処理関数を呼び出す
			m_a = 0.3f;		//スペシャル技ボタンを透明化
		}
	}

	//▼敵惑星スペシャル技処理
	if ((m_enemy_special_button == true) &&				//敵スペシャル技発動チェック
		(m_enemy_special_equipment != 0) &&				//スペシャル技装備してるかチェック
		(m_is_used_special[ENEMY] == false) ||			//スペシャル技が未使用であれば実行
		(m_is_invocating[ENEMY] == true))				//また、現在スペシャル技発動中であっても実行
	{
		//プレイヤーがスペシャル技発動演出中である場合、
		//以下の処理を実行しないようにする。
		if (m_special_staging_f[PLAYER] == false)
		{
			Special_process(ENEMY, PLAYER, m_enemy_special_equipment);//スペシャル技処理関数を呼び出す
		}
	}

	//▼時間切れの時の処理
	if (FightScene->GetCount() <= 60)
	{	
		//時間切れでスペシャル技発動不可にする
		m_is_used_special[PLAYER] = true;	
		m_is_invocating[PLAYER] = false;

		//同じく敵もスペシャル技発動不可にする
		m_is_used_special[ENEMY]  = true;	
		m_is_invocating[ENEMY] = false;

		m_a -= 0.03f;				//徐々に透明化する
		if (m_a > 0.0f)
			this->SetStatus(false);	//完全透明になった時点で消滅
	}
}

//ドロー
void CObjSpecialButton::Draw()
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float button[4] = { 1.0f,1.0f,1.0f,m_a };		//スペシャル技ボタン用
	float blackout[4] = { 1.0f,1.0f,1.0f,0.5f };	//画面全体やや暗転画像用

	//スペシャル技発動演出フォント用
	float staging_font[3][4] =
	{
		{ m_staging_font_color,0.0f,(1.0f - m_staging_font_color),1.0f },//1行目はプレイヤーなら青色、エネミーなら赤色
		{ 1.0f,1.0f,0.0f,1.0f },//2行目は黄色
		{ 1.0f,1.0f,1.0f,1.0f },//3行目は白色
	};

	float d[4] = { 1.0f,1.0f,1.0f,1.0f };	//その他画像用


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//スペシャル技未装備時はボタン非表示にする
	if (g_Special_equipment != 0)
	{
		//▼スペシャル技ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 175.0f;
		src.m_bottom = 114.0f;

		dst.m_top = m_y;
		dst.m_left = m_x;
		dst.m_right = m_x + m_w;
		dst.m_bottom = m_y + m_h;
		Draw::Draw(19, &src, &dst, button, 0.0f);
	}


	//スペシャル技演出(エフェクト)
	//▽プレイヤーの時の処理
	if ((m_is_invocating[PLAYER] == true) &&	//現在スペシャル技が発動中で、
		(m_is_used_special[PLAYER] == true))	//スペシャル技発動演出終了済みであれば描画
	{
		Special_effect(PLAYER, g_Special_equipment);//スペシャル技エフェクト描画関数を呼び出す
	}

	//▽エネミーの時の処理
	if ((m_is_invocating[ENEMY] == true) &&	//現在スペシャル技が発動中で、
		(m_is_used_special[ENEMY] == true))	//スペシャル技発動演出終了済みであれば描画
	{
		Special_effect(ENEMY, m_enemy_special_equipment);//スペシャル技エフェクト描画関数を呼び出す
	}


	//スペシャル技発動演出時、以下のものを描画する
	if (m_special_staging_f[PLAYER] == true || m_special_staging_f[ENEMY] == true)
	{
		//▼スペシャル技発動演出時の背景(画面全体やや暗転)表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 700.0f;
		Draw::Draw(20, &src, &dst, blackout, 0.0f);

		//▼スペシャル技発動演出フォント表示
		for (int i = 0; i < 2; i++)
		{
			Font::StrDraw(m_staging_message[i], 280.0f, 150.0f + i * 150.0f, 80.0f, staging_font[i]);
		}

		Font::StrDraw(L"発動！", 490.0f, 450.0f, 80.0f, staging_font[2]);
	}
}

//---Special_staging_message関数
//引数1　int Planet_id		:惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数2　int Special_equip	:装備中のスペシャル技(0:未装備　1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)
//▼内容
//スペシャル技を発動した惑星、現在装備中のスペシャル技を考慮した
//スペシャル技発動演出メッセージを設定する。
void CObjSpecialButton::Special_staging_message(int Planet_id, int Special_equip)
{
	if (Planet_id == 0)
	{
		swprintf_s(m_staging_message[0], L"   プレイヤー"); //文字配列に文字データを入れる
		m_staging_font_color = 0.0f;	//フォントのカラーを青色に設定する
	}
	else
	{
		swprintf_s(m_staging_message[0], L"　  エネミー"); //文字配列に文字データを入れる
		m_staging_font_color = 1.0f;	//フォントのカラーを赤色に設定する
	}

	if (Special_equip == 1)
	{
		swprintf_s(m_staging_message[1], L"   Explosion"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 2)
	{
		swprintf_s(m_staging_message[1], L"  Fracture Ray"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 3)
	{
		swprintf_s(m_staging_message[1], L"  Immortality"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 4)
	{
		swprintf_s(m_staging_message[1], L"リミットブレイク"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 5)
	{
		swprintf_s(m_staging_message[1], L" ステロイド投与"); //文字配列に文字データを入れる
	}
}

//---Special_process関数
//引数1　int Planet_id		:自分の惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数2　int Opponent_id	:相手の惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数3　int Special_equip	:装備中のスペシャル技(0:未装備　1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)
//▼内容
//スペシャル技発動演出、スペシャル技効果処理といった、
//スペシャル技処理を実行する。
void CObjSpecialButton::Special_process(int Planet_id, int Opponent_id, int Special_equip)
{
	m_is_invocating[Planet_id] = true;		//発動中管理フラグON


	//▼スペシャル技発動演出
	if (m_is_used_special[Planet_id] == false)
	{
		SetPrio(90);	//オブジェクト優先順位が変更されていた場合、元に戻す。
		Special_staging_message(Planet_id, Special_equip);//スペシャル技発動演出メッセージを設定する
		m_special_staging_f[Planet_id] = true;	//スペシャル技発動演出フラグON
		battle_start = false;			//戦闘開始フラグをfalseにする事で戦闘全体を一時停止させる


		//▽敵が[スペシャル技:Fracture_Ray]を発動時のみ実行
		//戦闘が一時停止している発動演出中に、
		//[スペシャル技:Fracture_Ray]を発射するラインを決定する処理を行う。
		//※決定処理には約0.07秒の時間を要する。
		//※発射するライン決定後は以下の処理は実行されない。
		//※戦闘一時停止中(他オブジェクトの処理停止中)なので
		//"ObjRocket"に[OBJ_FRACTURE_RAY]がHITしても、
		//"ObjRocket"の消滅処理は実行されない。
		if (Planet_id == ENEMY && Special_equip == 2 && m_Enemy_line == 0)
		{
			CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得

			//0秒時の処理
			if (m_count[ENEMY] == 0)
			{
				//中ラインの範囲にヒット相手数カウント用の当たり判定を設置
				Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);
			}
			//0.01～0.05秒時の処理
			else if (1 <= m_count[ENEMY] && m_count[ENEMY] <= 3)
			{
				//中ライン→下ライン→上ラインの順番で
				//HitBoxに当たっているヒット相手の数をカウントし、
				//その数を代入する。
				m_PodMissile_count[m_count[ENEMY] - 1] = hit->GetCount();

				//プレイヤー惑星、敵惑星が上記のカウント数に含まれていた場合、
				//その分を以下の処理で減らしておく。
				if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
				{
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}
				if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
				{
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}

				//発動演出終了後、ヒット相手数カウント用の当たり判定がそのまま存在していると、
				//"ObjRocket"の消滅処理が実行されてしまうので、
				//以下の処理で新しい当たり判定設置前に、現在の当たり判定を削除する。
				Hits::DeleteHitBox(this);

				//中ラインのヒット相手数カウント終了後、実行。
				if (m_count[ENEMY] == 1)
				{
					//次の処理の為に、
					//下ラインの範囲にヒット相手数カウント用の当たり判定を設置
					Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);

					//中ラインにのみ、
					//各惑星がライン上を通過しないようにする当たり判定が存在しており、
					//カウント数に含まれている為、その分を減らしておく。
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}
				else if (m_count[ENEMY] == 2)
				{
					//次の処理の為に、
					//上ラインの範囲にヒット相手数カウント用の当たり判定を設置
					Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);
				}
			}
			//0.06秒時の処理
			else if (m_count[ENEMY] == 4)
			{
				//▼選択ライン決定処理
				//上記の処理により、各ラインに存在する"プレイヤーのポッドミサイル数"が
				//配列それぞれに代入された状態である為、それらの数を比較し、
				//一番数が多いラインに[スペシャル技:Fracture_Ray]を発射するように設定する。
				//※数が同値である場合、以下の優先順位で選択ラインが決定する。
				//「中ライン＞下ライン＞上ライン」

				//中ラインと他ラインとの数比較
				if (m_PodMissile_count[0] >= m_PodMissile_count[1] && m_PodMissile_count[0] >= m_PodMissile_count[2])
				{
					m_Enemy_line = 1;//中ラインに決定
				}
				//下ラインと他ラインとの数比較
				else if (m_PodMissile_count[1] >= m_PodMissile_count[0] && m_PodMissile_count[1] >= m_PodMissile_count[2])
				{
					m_Enemy_line = 2;//下ラインに決定
				}
				else
				{
					m_Enemy_line = 3;//上ラインに決定
				}
			}
		}

		m_count[Planet_id]++;//演出時間計測

		//2秒経過後、スペシャル技発動演出を終了する
		if (m_count[Planet_id] > 60 * 2)
		{
			m_count[Planet_id] = 0;				//この後も使用するので0で初期化する
			m_special_staging_f[Planet_id] = false;	//スペシャル技発動演出フラグOFF
			battle_start = true;				//戦闘開始フラグをtrueにする事で一時停止を解除する
			m_is_used_special[Planet_id] = true;//スペシャル技使用済フラグ立て
		}

		return;
	}


	//現在装備中のスペシャル技を判別し、
	//そのスペシャル技の効果の処理を行う。

	//▼[Explosion]の処理
	if (Special_equip == 1)
	{
		//スペシャル技効果処理開始から約1.7秒後、
		//相手が無敵ではない、かつ相手のHPが0より上の時、
		//約0.1秒毎に相手のHPを減少させる。
		//※現状、計5ダメージ与える設定となっている。
		if (m_count[Planet_id] >= 100 && m_count[Planet_id] % 5 == 0 && Planet[Opponent_id]->GetInvincible() == false && Planet[Opponent_id]->GetSiz() > 0)
		{
			Planet[Opponent_id]->SetDamage();//サイズ(HP)減少
			Planet[Opponent_id]->SetScale_down_move(Opponent_id);//縮む分だけ移動

			//size30以下になる時のif文、ここにも用意。
		}
	
		m_count[Planet_id]++;//効果時間計測

		//[Explosion]の演出処理(下からの上の順番で徐々に実行される)
		if (m_Explosion_width[Planet_id] >= 860.0f)
		{
			//▽エフェクト画像の幅が狭まり、画面から非表示になると実行。
			//オブジェクト優先順位を元に戻し、演出終了。
			SetPrio(90);	//オブジェクト優先順位を元に戻す。
		}
		else if (m_Explosion_size[Planet_id] <= -860.0f)
		{
			//▽エフェクト画像サイズが画面外(下)に到達すると実行。
			//サイズ変更(下発射)をやめて、エフェクト画像の幅を徐々に狭めていく。
			SetPrio(2);//オブジェクト優先順位を変更し、エフェクト画像が相手惑星の後ろにいくようにする
			m_Explosion_width[Planet_id] += 10.0f;//エフェクト画像の幅を狭める
		}
		else if (m_Explosion_pos[Planet_id] == -1000.0f)
		{
			//▽演出準備終了後、実行。
			//エフェクト画像が画面外(相手惑星の真上)を起点に下へと発射し、相手惑星を貫く。
			SetPrio(2);//オブジェクト優先順位を変更し、エフェクト画像が相手惑星の後ろにいくようにする
			m_Explosion_size[Planet_id] -= 20.0f;//エフェクト画像サイズを変更し、下方向に画像を伸ばす
			m_Explosion_width[Planet_id] += 10.0f;//エフェクト画像の幅を狭める
		}
		else if (m_Explosion_width[Planet_id] + m_Explosion_size[Planet_id] <= 0)
		{
			//▽エフェクト画像の幅が狭まり、画面から非表示になると実行。
			//次の演出の為の準備を行う
			m_Explosion_size[Planet_id] = 0.0f;			//エフェクト画像サイズを初期値に戻す
			m_Explosion_width[Planet_id] = INI_WIDTH;	//エフェクト画像幅を初期値に戻す
			m_Explosion_pos[Planet_id] = -1000.0f;		//エフェクト画像位置を画面外(上)に移動させる
			m_Explosion_target[Planet_id] = Opponent_id;//エフェクト対象を相手に設定
			m_Explosion_angle[Planet_id] = 270.0f;		//エフェクト角度を下に向くように設定
		}
		else if (m_Explosion_size[Planet_id] > 200.0f && m_Explosion_width[Planet_id] + m_Explosion_size[Planet_id] > 0)
		{
			//▽エフェクト画像サイズが画面外(上)に到達すると実行。
			//サイズ変更(上発射)をやめて、エフェクト画像の幅を徐々に狭めていく。
			m_Explosion_width[Planet_id] -= 10.0f;//エフェクト画像の幅を狭める
		}
		else if (m_Explosion_size[Planet_id] <= 200.0f)
		{
			//▽最初に実行される。
			//エフェクト画像がプレイヤーを起点に上へと発射される
			m_Explosion_target[Planet_id] = Planet_id;//エフェクト対象を自分に設定
			m_Explosion_angle[Planet_id] = 90.0f;//エフェクト角度を上に向くように設定
			m_Explosion_size[Planet_id] += 20.0f;//エフェクト画像サイズを変更し、上方向に画像を伸ばす
		}
		
		//2秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 2)
		{
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
	}
	//▼[Fracture_Ray]の処理
	else if (Special_equip == 2)
	{
		//▽スペシャル技(FRACTURE_RAY)の当たり判定を設置する
		//この当たり判定にミサイルポッドがHITすると、消滅処理が実行される。
		//攻撃判定時間は0.05秒。
		//※エネミーの選択ライン決定処理は発動演出中に行っている。
		//決定方法：プレイヤーのミサイルポットが一番多い場所に発射する

		//選択ラインが中ラインの時(この処理は一度のみ実行される)
		if (FightScene->GetLine() == 1 && m_count[Planet_id] == 0 && Planet_id == PLAYER ||	//プレイヤーの時の条件式
			m_Enemy_line == 1 && m_count[Planet_id] == 0 && Planet_id == ENEMY)				//エネミーの時の条件式
		{
			Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//中ラインの範囲に当たり判定を設置
			m_Fracture_Ray_pos[Planet_id] = -5.0f;	//当たり判定設置ついでにエフェクト画像の位置を決める
		}
		//選択ラインが下ラインの時(この処理は一度のみ実行される)
		else if (FightScene->GetLine() == 2 && m_count[Planet_id] == 0 && Planet_id == PLAYER ||//プレイヤーの時の条件式
				 m_Enemy_line == 2 && m_count[Planet_id] == 0 && Planet_id == ENEMY)			//エネミーの時の条件式
		{
			Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//下ラインの範囲に当たり判定を設置
			m_Fracture_Ray_pos[Planet_id] = 100.0f;	//当たり判定設置ついでにエフェクト画像の位置を決める
		}
		//選択ラインが上ラインの時(この処理は一度のみ実行される)
		else if (m_count[Planet_id] == 0)
		{
			Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);		//上ラインの範囲に当たり判定を設置
			m_Fracture_Ray_pos[Planet_id] = -120.0f;//当たり判定設置ついでにエフェクト画像の位置を決める
		}

		//[Fracture_Ray]の演出処理(下からの上の順番で徐々に実行される)
		if (m_Fracture_Ray_width[Planet_id] <= 0.0f)
		{
			//▽エフェクト画像の幅が狭まり、画面から非表示になると演出終了
		}
		else
		{
			//▽最初に実行される。
			//エフェクト画像が自分惑星から相手惑星に対して発射される
			//その後、エフェクト画像の幅を徐々に狭めていく。
			m_Fracture_Ray_width[Planet_id] -= 10.0f;//エフェクト画像の幅狭める
		}

		m_count[Planet_id]++;//効果時間計測

		//0.35秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 0.35)
		{
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
		//0.05秒経過後、当たり判定を削除する
		else if (m_count[Planet_id] > 60 * 0.05)
		{
			Hits::DeleteHitBox(this);			//スペシャル技(FRACTURE_RAY)の当たり判定を削除
		}
	}
	//▼[Immortality]の処理
	else if (Special_equip == 3)
	{
		//▽エフェクト画像点滅処理
		//初期透過度は1.0f、切り替えポイントは0.75f。
		//1.0f→0.75fへ移動する際、0.003ずつベクトルが減算されていき、
		//同時に透過度も減少していく。
		//切り替えポイントの0.75fに到達時、0.003ずつベクトルが加算されていくが、
		//今まで移動したベクトル分が残っている為、すぐに透過度は上昇せず、
		//今まで移動したベクトル分が0.0fになるまで透過度は減少する。
		//透過度が上昇するのは、切り替えポイント的に透過度が0.5fになった時である。
		//その後は先程と全く真逆の処理が行われ、
		//結果的に透過度が1.0f⇔0.5fを行き来するプログラムとなっている。
		if (m_Special_effect_alpha[Planet_id] >= 0.75)
		{
			m_Special_effect_alpha_vec[Planet_id] -= 0.003f;	//ベクトルに減算
		}
		else
		{
			m_Special_effect_alpha_vec[Planet_id] += 0.003f;	//ベクトルに加算
		}
			
		m_Special_effect_alpha[Planet_id] += m_Special_effect_alpha_vec[Planet_id];	//ベクトルを反映

		m_count[Planet_id]++;//効果時間計測


		//[Immortality]の演出処理(下からの上の順番で徐々に実行される)

		//エフェクト画像が惑星中心に移動し、画面から非表示になると演出終了。
		//演出終了後、発動中管理フラグをOFFにする
		if (m_Immortality_size[Planet_id] <= 0.0f && m_count[Planet_id] > 60 * 10)
		{
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
		//10秒経過後、スペシャル技の効果を終了し、
		//終了演出を行う。
		else if (m_count[Planet_id] > 60 * 10)
		{
			Planet[Planet_id]->SetInvincible(false);	//プレイヤー無敵フラグをOFF
			m_Immortality_size[Planet_id] -= 1.5f;		//エフェクト画像サイズを変更し、惑星中心に徐々に移動させる
		}
		//スペシャル技効果終了まで自分惑星の周囲にエフェクト画像を出し、
		//無敵フラグをONにする
		else
		{
			m_Immortality_size[Planet_id] = 150.0f;	//エフェクト画像サイズを変更し、自分惑星の周囲にエフェクト画像を出す
			Planet[Planet_id]->SetInvincible(true);	//プレイヤー無敵フラグをON
		}
	}
	//▼[リミットブレイク]の処理
	else if (Special_equip == 4)
	{
		//ミサイルポッドリキャストタイムのバフ倍率を変更する
		//▽プレイヤーの時の処理
		if (Planet_id == PLAYER)
		{
			//それぞれのボタンを変更する
			for (int i = 0; i < 5; i++)
			{
				PodMissile[i]->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);//バフ倍率変更
			}
		}
		//▽エネミーの時の処理
		else //(Planet_id == ENEMY)
		{
			Planet[Planet_id]->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);//バフ倍率変更
		}

		m_count[Planet_id]++;//効果時間計測

		//20秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 20)
		{
			//ミサイルポッドリキャストタイムのバフ倍率を元に戻す
			//▽プレイヤーの時の処理
			if (Planet_id == PLAYER)
			{
				//それぞれのボタンを変更する
				for (int i = 0; i < 5; i++)
				{
					PodMissile[i]->SetRecastBuff(INI_BUFF);//バフ倍率元に戻す
				}
			}
			//▽エネミーの時の処理
			else //(Planet_id == ENEMY)
			{
				Planet[Planet_id]->SetRecastBuff(INI_BUFF);//バフ倍率元に戻す
			}

			m_is_invocating[Planet_id] = false;//発動中管理フラグOFF
		}
		//15秒経過後、エフェクト画像点滅処理
		//※点滅処理のプログラム内容は、
		//上記のImmortalityの処理と同じなので、
		//細かい説明は省略する。
		else if (m_count[Planet_id] > 60 * 15)
		{
			//初期透過度は1.0f、切り替えポイントは0.5f。
			if (m_Special_effect_alpha[Planet_id] >= 0.5)
			{
				m_Special_effect_alpha_vec[Planet_id] -= 0.003f;	//ベクトルに減算
			}
			else
			{
				m_Special_effect_alpha_vec[Planet_id] += 0.003f;	//ベクトルに加算
			}

			m_Special_effect_alpha[Planet_id] += m_Special_effect_alpha_vec[Planet_id];	//ベクトルを反映
		}
	}
	//▼[ステロイド投与]の処理
	else if (Special_equip == 5)
	{
		damage_buff[Planet_id] = DAMAGE_BUFF_MAGNIFICATION;	//ダメージバフ倍率を変更する

		//射出したポッドが破壊される度に
		//m_countが1ずつ増加するようにObjRocketで設定している

		//スペシャル技発動してからポッド5機全て破壊された後、
		//スペシャル技の効果を終了する
		if (m_count[Planet_id] >= 5)
		{
			damage_buff[Planet_id] = INI_BUFF;//ダメージバフ倍率を元に戻す
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
	}
}

//---Special_effect関数
//引数1　int Planet_id		:惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数2　int Special_equip	:装備中のスペシャル技(0:未装備　1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)
//▼内容
//スペシャル技発動中にエフェクトを描画する。
void CObjSpecialButton::Special_effect(int Planet_id, int Special_equip)
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//透過度変更が必要なスペシャル技エフェクト画像用
	float special_effect[2][4] =
	{
		{ 1.0f,1.0f,1.0f,m_Special_effect_alpha[PLAYER] },
		{ 1.0f,1.0f,1.0f,m_Special_effect_alpha[ENEMY] },
	};

	float d[4] = { 1.0f,1.0f,1.0f,1.0f };	//その他画像用


	//▽フォント準備
	wchar_t power_up_pod_count[2][2];	//強化状態のポッド数表示用


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼[Explosion]の描画処理
	if (Special_equip == 1)
	{
		//▼Explosion表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//▽メモ1：
		//画像を拡大縮小等と変形する際、
		//均等にtopとleftとrightとbottomを伸ばさなければ、
		//その誤差分、画像が引き伸ばされ、
		//欲しい画像とならないので
		//基本的にどんな状況でも均等に伸ばさないといけない。
		//ただ今回はtop方向に画像を伸ばし、bottomの位置は固定としたい為、
		//bottomを動かさない分、topを2倍動かす事でこれに対応している。
		//▽メモ2:
		//今回の画像は90度&270度回転させて使用している為、
		//topとbottomの値の差を変動させる事で、
		//欲しい画像である"左右から徐々に消えていく演出"を行っている。
		dst.m_top = Planet[m_Explosion_target[Planet_id]]->GetY() - m_Explosion_size[Planet_id] * 2 - m_Explosion_width[Planet_id] + m_Explosion_pos[Planet_id];
		dst.m_left = Planet[m_Explosion_target[Planet_id]]->GetX() - m_Explosion_size[Planet_id] + Planet[m_Explosion_target[Planet_id]]->GetScale_down_move();
		dst.m_right = Planet[m_Explosion_target[Planet_id]]->GetX() + m_Explosion_size[Planet_id] + Planet[m_Explosion_target[Planet_id]]->GetScale_down_move();
		dst.m_bottom = Planet[m_Explosion_target[Planet_id]]->GetY() + m_Explosion_width[Planet_id] + m_Explosion_pos[Planet_id];
		Draw::Draw(21, &src, &dst, d, m_Explosion_angle[Planet_id]);
	}

	//▼[Fracture_Ray]の描画処理
	else if (Special_equip == 2)
	{
		//▼Fracture_Ray表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = -64.0f + (Planet_id * 128.0f);//プレイヤーの時は左向き、エネミーの時は右向きになるように設定。
		src.m_bottom = 32.0f;

		dst.m_top = Planet[Planet_id]->GetY() - m_Fracture_Ray_width[Planet_id] + m_Fracture_Ray_pos[Planet_id];

		//leftとrightの描画処理はプレイヤーとエネミーで大きく違う為、別々で処理を行う。
		if (Planet_id == PLAYER)
		{
			dst.m_left = 0.0f;
			dst.m_right = Planet[Planet_id]->GetX() + Planet[Planet_id]->GetScale_down_move();
		}
		else //(Planet_id == ENEMY)
		{
			dst.m_left = Planet[Planet_id]->GetX() + Planet[Planet_id]->GetScale_down_move();
			dst.m_right = 1200.0f;
		}

		dst.m_bottom = Planet[Planet_id]->GetY() + m_Fracture_Ray_width[Planet_id] + m_Fracture_Ray_pos[Planet_id];
		Draw::Draw(22, &src, &dst, d, 0.0f);
	}

	//▼[Immortality]の描画処理
	else if (Special_equip == 3)
	{
		//▼Immortality表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = Planet[Planet_id]->GetY() - m_Immortality_size[Planet_id];
		dst.m_left = Planet[Planet_id]->GetX() - m_Immortality_size[Planet_id] + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + m_Immortality_size[Planet_id] + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() + m_Immortality_size[Planet_id];
		Draw::Draw(23, &src, &dst, special_effect[Planet_id], 0.0f);
	}

	//▼[リミットブレイク]の描画処理
	else if (Special_equip == 4)
	{
		//▼リミットブレイク表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//▽自分惑星の上に描画するように設定している
		dst.m_top = Planet[Planet_id]->GetY() - 190.0f;
		dst.m_left = Planet[Planet_id]->GetX() - 37.5f + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + 37.5f + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() - 115.0f;
		Draw::Draw(24, &src, &dst, special_effect[Planet_id], 0.0f);
	}

	//▼[ステロイド投与]の描画処理
	else if (Special_equip == 5)
	{
		//▼ステロイド投与表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//▽自分惑星の上に描画するように設定している
		dst.m_top = Planet[Planet_id]->GetY() - 190.0f;
		dst.m_left = Planet[Planet_id]->GetX() - 60.0f + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + 15.0f + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() - 115.0f;
		Draw::Draw(25, &src, &dst, d, 0.0f);

		//▼強化状態のポッド数表示
		swprintf_s(power_up_pod_count[Planet_id], L"%d", (5 - m_count[Planet_id]));
		Font::StrDraw(power_up_pod_count[Planet_id], Planet[Planet_id]->GetX() + 15.0f + Planet[Planet_id]->GetScale_down_move(), Planet[Planet_id]->GetY() - 190.0f, 75.0f, d);
	}
}
