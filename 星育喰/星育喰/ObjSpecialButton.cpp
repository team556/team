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
#define DAMAGE_BUFF_MAGNIFICATION (1.5f)	//与えるダメージのバフ倍率(与えるダメージが1.5倍になる)
#define INI_BUFF (1.0f) //上記2つのバフ倍率初期値

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

		m_damage_buff[i] = INI_BUFF;
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
			Special_process(PLAYER, g_Special_equipment);	//スペシャル技処理関数を呼び出す
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
			Special_process(ENEMY, m_enemy_special_equipment);//スペシャル技処理関数を呼び出す
		}
	}

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
	float staging_font[3][4] =
	{
		{ m_staging_font_color,0.0f,(1.0f - m_staging_font_color),1.0f },//1行目はプレイヤーなら青色、エネミーなら赤色
		{ 1.0f,1.0f,0.0f,1.0f },//2行目は黄色
		{ 1.0f,1.0f,1.0f,1.0f },//3行目は白色
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
//引数2　int Special_equip	:装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
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
//引数1　int Planet_id		:惑星識別番号(0:プレイヤー惑星　1:敵惑星)
//引数2　int Special_equip	:装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
//▼内容
//スペシャル技発動演出、スペシャル技効果処理といった、
//スペシャル技処理を実行する。
void CObjSpecialButton::Special_process(int Planet_id, int Special_equip)
{
	m_is_invocating[Planet_id] = true;		//発動中管理フラグON


	//▼スペシャル技発動演出
	if (m_is_used_special[Planet_id] == false)
	{
		Special_staging_message(Planet_id, Special_equip);//スペシャル技発動演出メッセージを設定する
		m_special_staging_f[Planet_id] = true;	//スペシャル技発動演出フラグON
		battle_start = false;			//戦闘開始フラグをfalseにする事で戦闘全体を一時停止させる

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

	//▼[敵に大ダメージ]の処理
	if (Special_equip == 1)
	{
		//相手が無敵ではない、かつ相手のHPが0より上の時、
		//0.5秒毎に相手のHPを減少させる。
		//▽プレイヤーの時の処理
		if (Planet_id == PLAYER)
		{
			if (m_count[Planet_id] % 30 == 0 && Enemy->GetInvincible() == false && (Enemy->GetHp() > 0))
			{
				Enemy->SetDamage();		//HP-1
				Enemy->SetScale_down();	//サイズ減少
			}
		}
		//▽エネミーの時の処理
		else //(Planet_id == ENEMY)
		{
			if (m_count[Planet_id] % 30 == 0 && Player->GetInvincible() == false && (Player->GetHp() > 0))
			{
				Player->SetDamage();		//HP-1
				Player->SetScale_down();	//サイズ減少
			}
		}

		m_count[Planet_id]++;//効果時間計測

		//2秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 2)
		{
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
	}
	//▼[一列殺し]の処理
	else if (Special_equip == 2)
	{
		//▽メモ
		//現在敵選択ラインを決めるプログラムを作っていない。
		//その為、現状プレイヤーが選択しているラインにFRACTURE_RAYを撃つようになっている。
		//[5/18～5/19中に一番ポッド多い場所に撃つように変更予定]


		//▽スペシャル技(FRACTURE_RAY)の当たり判定を設置する
		//この当たり判定にミサイルポッドがHITすると、消滅処理が実行される。
		//攻撃判定時間は0.05秒。

		//選択ラインが中ラインの時(この処理は一度のみ実行される)
		if (FightScene->GetLine() == 1 && m_count[Planet_id] == 0)
		{
			Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//中ラインの範囲に当たり判定を設置
		}
		//選択ラインが下ラインの時(この処理は一度のみ実行される)
		else if (FightScene->GetLine() == 2 && m_count[Planet_id] == 0)
		{
			Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//下ラインの範囲に当たり判定を設置
		}
		//選択ラインが上ラインの時(この処理は一度のみ実行される)
		else if (m_count[Planet_id] == 0)
		{
			Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);		//上ラインの範囲に当たり判定を設置
		}

		m_count[Planet_id]++;//効果時間計測

		//0.05秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 0.05)
		{
			Hits::DeleteHitBox(this);			//スペシャル技(FRACTURE_RAY)の当たり判定を削除
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
	}
	//▼[一定時間無敵]の処理
	else if (Special_equip == 3)
	{
		//▽プレイヤーの時の処理
		if (Planet_id == PLAYER)
		{
			Player->SetInvincible(true);	//プレイヤー無敵フラグをON
		}
		//▽エネミーの時の処理
		else //(Planet_id == ENEMY)
		{
			Enemy->SetInvincible(true);		//エネミー無敵フラグをON
		}

		m_count[Planet_id]++;//効果時間計測

		//10秒経過後、スペシャル技の効果を終了する
		if (m_count[Planet_id] > 60 * 10)
		{
			//▽プレイヤーの時の処理
			if (Planet_id == PLAYER)
			{
				Player->SetInvincible(false);	//プレイヤー無敵フラグをOFF
			}
			//▽エネミーの時の処理
			else //(Planet_id == ENEMY)
			{
				Enemy->SetInvincible(false);	//エネミー無敵フラグをOFF
			}

			m_is_invocating[Planet_id] = false;//発動中管理フラグOFF
		}
	}
	//▼[生産性効率アップ]の処理
	else if (Special_equip == 4)
	{
		//ミサイルポッドリキャストタイムのバフ倍率を変更する
		//▽プレイヤーの時の処理
		if (Planet_id == PLAYER)
		{
			//それぞれのボタンを変更する
			Pod1->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod2->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod3->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod4->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Missile->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
		}
		//▽エネミーの時の処理
		else //(Planet_id == ENEMY)
		{
			Enemy->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
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
				Pod1->SetRecastBuff(INI_BUFF);
				Pod2->SetRecastBuff(INI_BUFF);
				Pod3->SetRecastBuff(INI_BUFF);
				Pod4->SetRecastBuff(INI_BUFF);
				Missile->SetRecastBuff(INI_BUFF);
			}
			//▽エネミーの時の処理
			else //(Planet_id == ENEMY)
			{
				Enemy->SetRecastBuff(INI_BUFF);
			}

			m_is_invocating[Planet_id] = false;//発動中管理フラグOFF
		}
	}
	//▼[住民の士気がアップ]の処理
	else if (Special_equip == 5)
	{
		m_damage_buff[Planet_id] = DAMAGE_BUFF_MAGNIFICATION;	//ダメージバフ倍率を変更する

		//ポッド射出毎にm_countが1ずつ増加するようにObjRocketButton(敵の場合はObjPlanet)で設定している

		//スペシャル技発動してからポッドを5回射出後、スペシャル技の効果を終了する
		//※正確に言えば6回目のポッドを射出した瞬間に以下の処理が実行される
		if (m_count[Planet_id] > 5)
		{
			m_damage_buff[Planet_id] = INI_BUFF;//ダメージバフ倍率を元に戻す
			m_is_invocating[Planet_id] = false;	//発動中管理フラグOFF
		}
	}
}
