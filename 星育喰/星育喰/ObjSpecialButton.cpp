//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define PLAYER (0)	//プレイヤー(配列を分かりやすくする用)
#define ENEMY  (1)	//エネミー	(配列を分かりやすくする用)
#define RECAST_BUFF_MAGNIFICATION (0.5f)	//ミサイルポッドリキャストタイムのバフ倍率(リキャストタイムを0.5倍→リキャストタイムが半分で済む)

#define INI_BUFF (1.0f) //上記2つのバフ倍率初期値(現状1つしかないが……)

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

	m_special_staging_f = false;
	m_staging_font_color = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_count[i] = 0;
		m_is_used_special[i] = false;
		m_is_invocating[i] = false;
	}

	m_enemy_special_equipment = 0;
	m_enemy_special_button = false;

	//▼実際にオブジェクト情報を取得する
	FightScene = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	Player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	Enemy =  (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
	Pod1 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON1);
	Pod2 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON2);
	Pod3 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON3);
	Pod4 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON4);
	Missile = (CObjRocketButton*)Objs::GetObj(OBJ_MISSILE_BUTTON);
}

//アクション
void CObjSpecialButton::Action()
{
	//▼戦闘開始前は操作不能にする処理
	//※スペシャル技発動演出中はこの影響を受けないようにする
	if (battle_start == false && m_special_staging_f == false)
	{
		return;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//▼プレイヤー惑星スペシャル技処理(↓の敵惑星verとほとんど被るようであれば後で関数化)
	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && 	//X軸範囲
		(m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) &&	//Y軸範囲
		(m_mou_l == true) &&							//左クリック
		(g_Special_equipment != 0) &&					//スペシャル技装備してるかチェック
		(m_is_used_special[PLAYER] == false) ||			//スペシャル技が未使用であれば実行
		(m_is_invocating[PLAYER] == true))				//また、現在スペシャル技発動中であっても実行
	{
		m_is_invocating[PLAYER] = true;		//発動中管理フラグON
		Special_staging_message(PLAYER, g_Special_equipment);//スペシャル技発動演出メッセージを設定する


		//▼スペシャル技発動演出(敵惑星でも使うので関数化必須)
		if (m_is_used_special[PLAYER] == false)
		{
			m_special_staging_f = true;		//スペシャル技発動演出フラグON
			battle_start = false;			//戦闘開始フラグをfalseにする事で戦闘全体を一時停止させる

			m_count[PLAYER]++;//演出時間計測

			//2秒経過後、スペシャル技発動演出を終了する
			if (m_count[PLAYER] > 60 * 2)
			{
				m_count[PLAYER] = 0;				//この後も使用するので0で初期化する
				m_special_staging_f = false;		//スペシャル技発動演出フラグOFF
				battle_start = true;				//戦闘開始フラグをtrueにする事で一時停止を解除する
				m_is_used_special[PLAYER] = true;	//スペシャル技使用済フラグ立て
			}

			return;
		}
			
		//現在装備中のスペシャル技を判別後、
		//そのスペシャル技の効果を実際に発動する


		//▼[敵に大ダメージ]の処理
		if (g_Special_equipment == 1)
		{
			//エネミーが無敵ではない、かつエネミーのHPが0より上の時、
			//0.5秒毎にエネミーのHPを減少させる。
			if (m_count[PLAYER] % 30 == 0 && Enemy->GetInvincible() == false && (Enemy->GetHp() > 0))
			{
				Enemy->SetDamage();		//HP-1
				Enemy->SetScale_down();	//サイズ減少
			}

			m_count[PLAYER]++;//効果時間計測

			//2秒経過後、スペシャル技の効果を終了する
			if (m_count[PLAYER] > 60 * 2)
			{
				m_is_invocating[PLAYER] = false;	//発動中管理フラグOFF
			}
		}
		//▼[一列殺し]の処理
		else if (g_Special_equipment == 2)
		{
			//▽スペシャル技(FRACTURE_RAY)の当たり判定を設置する
			//この当たり判定にミサイルポッドがHITすると、消滅処理が実行される。
			//攻撃判定時間は0.05秒。

			//選択ラインが中ラインの時(この処理は一度のみ実行される)
			if (FightScene->GetLine() == 1 && m_count[PLAYER] == 0)	
			{
				Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);	//中ラインの範囲に当たり判定を設置
			}
			//選択ラインが下ラインの時(この処理は一度のみ実行される)
			else if (FightScene->GetLine() == 2 && m_count[PLAYER] == 0)
			{
				Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);	//下ラインの範囲に当たり判定を設置
			}
			//選択ラインが上ラインの時(この処理は一度のみ実行される)
			else if (m_count[PLAYER] == 0)
			{
				Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);		//上ラインの範囲に当たり判定を設置
			}

			m_count[PLAYER]++;//効果時間計測

			//0.05秒経過後、スペシャル技の効果を終了する
			if (m_count[PLAYER] > 60 * 0.05)
			{
				Hits::DeleteHitBox(this);			//スペシャル技(FRACTURE_RAY)の当たり判定を削除
				m_is_invocating[PLAYER] = false;	//発動中管理フラグOFF
			}
		}
		//▼[一定時間無敵]の処理
		else if (g_Special_equipment == 3)
		{
			Player->SetInvincible(true);	//プレイヤー無敵フラグをON
			
			m_count[PLAYER]++;//効果時間計測

			//10秒経過後、スペシャル技の効果を終了する
			if (m_count[PLAYER] > 60 * 10)
			{
				Player->SetInvincible(false);	//プレイヤー無敵フラグをOFF
				m_is_invocating[PLAYER] = false;//発動中管理フラグOFF
			}
		}
		//▼[生産性効率アップ]の処理
		else if (g_Special_equipment == 4)
		{
			//▽ミサイルポッドのリキャストタイムを0.5倍、
			//つまり、リキャストタイムが半分の時間で済むように
			//それぞれのボタンに設定。
			Pod1->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod2->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod3->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod4->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Missile->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			
			m_count[PLAYER]++;//効果時間計測

			//20秒経過後、スペシャル技の効果を終了する
			if (m_count[PLAYER] > 60 * 20)
			{
				//▽ミサイルポッドのリキャストタイムを元に戻す
				Pod1->SetRecastBuff(INI_BUFF);
				Pod2->SetRecastBuff(INI_BUFF);
				Pod3->SetRecastBuff(INI_BUFF);
				Pod4->SetRecastBuff(INI_BUFF);
				Missile->SetRecastBuff(INI_BUFF);

				m_is_invocating[PLAYER] = false;//発動中管理フラグOFF
			}
		}
		//▼[住民の士気がアップ]の処理
		else if (g_Special_equipment == 5)
		{
			//Player->SetDamageBuff()
		}


		//▼テスト用
		//Player->SetDamage();
		//Player->SetScale_down();
		//Enemy->SetDamage();
		//Enemy->SetScale_down();



		//if (m_count[0] == 0)
		//{
		//	Enemy->SetInvincible(true);
		//	m_count[0] = 1;
		//}
		//else
		//{
		//	Player->SetInvincible(false);
		//	m_count[0] = 0;
		//}




		////▽エネミーのダメージ処理
		//if (m_special_1[ENEMY] == true && (m_hp > 0))
		//{
		//	m_special_count[ENEMY]++;

		//	//無敵フラグがtrueの時は以下のダメージ処理を飛ばす+1秒毎に実行
		//	if (m_special_count[ENEMY] % 60 && m_invincible_f[ENEMY] == false)
		//	{
		//		m_hp -= 1;				//HP-1
		//		m_size -= m_size / 20;	//サイズ減少
		//	}

		//	if (m_special_count[ENEMY] >= 300)
		//	{
		//		m_special_1[ENEMY] = false;
		//	}
		//}





		//m_is_invocating[PLAYER] = false;	//発動中管理フラグOFF
		
		m_a = 0.3f;		//透明化
	}

	//▼敵惑星スペシャル技処理
	//if (*m_enemy_special_button == true &&				//敵スペシャル技発動チェック
	//	m_is_used_special[ENEMY] == false)				//スペシャル技未使用かチェック
	//{
	//	m_is_used_special[ENEMY] == true;	//スペシャル技使用済フラグ立て
	//}

	//▼時間切れの時の処理
	if (FightScene->GetCount() <= 60)
	{	
		m_is_used_special[PLAYER] = true;	//時間切れでスペシャル技発動不可にする
		m_is_used_special[ENEMY]  = true;	//同じく敵もスペシャル技発動不可にする
		m_a -= 0.03f;				//徐々に透明化する
		if (m_a > 0.0f)
			this->SetStatus(false);	//完全透明になった時点で消滅
	}
}

//ドロー
void CObjSpecialButton::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float button[4] = { 1.0f,1.0f,1.0f,m_a };		//スペシャル技ボタン用
	float blackout[4] = { 1.0f,1.0f,1.0f,0.5f };	//画面全体やや暗転画像用

	//スペシャル技発動演出フォント用
	float staging_font[2][4] =
	{
		{ m_staging_font_color,0.0f,(1.0f - m_staging_font_color),1.0f },//1行目はプレイヤーなら青色、エネミーなら赤色
		{ 1.0f,1.0f,0.0f,1.0f },//2行目は黄色
	};

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

	//スペシャル技発動演出時、以下のものを描画する
	if (m_special_staging_f == true)
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
			Font::StrDraw(m_staging_message[i], 50.0f, 50.0f + i * 40.0f, 25.0f, staging_font[i]);
		}
	}
}

//---Special_staging_message関数
//引数1　int Planet_id		:惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数2　int Special_equip	:装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
//▼内容
//スペシャル技を発動した惑星、現在装備中のスペシャル技を考慮した
//スペシャル技発動演出メッセージを設定する。
void CObjSpecialButton::Special_staging_message(int Planet_id, int Special_equip)
{
	if (Planet_id == 0)
	{
		swprintf_s(m_staging_message[0], L"プレイヤー"); //文字配列に文字データを入れる
		m_staging_font_color = 0.0f;	//フォントのカラーを青色に設定する
	}
	else
	{
		swprintf_s(m_staging_message[0], L"エネミー"); //文字配列に文字データを入れる
		m_staging_font_color = 1.0f;	//フォントのカラーを赤色に設定する
	}

	if (Special_equip == 1)
	{
		swprintf_s(m_staging_message[1], L"Explosion"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 2)
	{
		swprintf_s(m_staging_message[1], L"Fracture Ray"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 3)
	{
		swprintf_s(m_staging_message[1], L"Immortality"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 4)
	{
		swprintf_s(m_staging_message[1], L"リミットブレイク"); //文字配列に文字データを入れる
	}
	else if (Special_equip == 5)
	{
		swprintf_s(m_staging_message[1], L"ステロイド投与"); //文字配列に文字データを入れる
	}
}
