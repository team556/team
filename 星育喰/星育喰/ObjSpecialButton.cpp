//使用するヘッダーファイル
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

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
	if (battle_start == false)
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
		m_is_used_special[PLAYER] = true;	//スペシャル技使用済フラグ立て
		m_is_invocating[PLAYER] = true;		//発動中管理フラグON


		//▼スペシャル技発動演出(敵惑星でも使うので関数化必須)


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
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

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
		Draw::Draw(19, &src, &dst, c, 0.0f);
	}

	////▼スペシャル技発動演出時の背景表示
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 175.0f;
	//src.m_bottom = 114.0f;

	//dst.m_top = m_y;
	//dst.m_left = m_x;
	//dst.m_right = m_x + m_w;
	//dst.m_bottom = m_y + m_h;
	//Draw::Draw(20, &src, &dst, c, 0.0f);
}