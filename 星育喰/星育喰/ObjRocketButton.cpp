//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRocketButton.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define UNIT_CONSUME_NUM (100)	//ユニット消費数
#define RECAST_COMPLETE_TIME (60.0f * g_Recast_time)//ミサイルのリキャスト完了タイム
#define RECAST_COMPLETE_POD_TIME (60.0f * 6)//ポッドのリキャスト完了タイム

//コンストラクタ
CObjRocketButton::CObjRocketButton(float x, float y, float h, float w, int n)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;

	Button_num = n;
}

//イニシャライズ
void CObjRocketButton::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	m_mou_f = false;//マウスフラグ

	m_a = 1.0f;		//透明度
	m_a2 = 1.0f;	//透明度

	m_cnt = 0;		//カウント

	m_player_recast_buff = 1.0f;
	m_is_empty = false;
	
	//ユニット数が空(0以下)かチェック処理
	if (Button_num == 1 && g_Power_num <= 0)
	{
		g_Power_num = 0;//0未満になっていた場合、0に戻す。
		m_is_empty = true;//空フラグON

		m_mou_f = true;
		m_a = 0.3f;		//透明化
	}
	else if (Button_num == 2 && g_Defense_num <= 0)
	{
		g_Defense_num = 0;//0未満になっていた場合、0に戻す。
		m_is_empty = true;//空フラグON

		m_mou_f = true;
		m_a = 0.3f;		//透明化
	}
	else if (Button_num == 3 && g_Speed_num <= 0)
	{
		g_Speed_num = 0;//0未満になっていた場合、0に戻す。
		m_is_empty = true;//空フラグON
	
		m_mou_f = true;
		m_a = 0.3f;		//透明化
	}
	else if (Button_num == 4 && g_Balance_num <= 0)
	{
		g_Balance_num = 0;//0未満になっていた場合、0に戻す。
		m_is_empty = true;//空フラグON

		m_mou_f = true;
		m_a = 0.3f;		//透明化
	}

	m_pow_f = false;		//powボタンのフラグ
	m_def_f = false;		//defボタンのフラグ
	m_spe_f = false;		//speボタンのフラグ
	m_bal_f = false;		//balボタンのフラグ
	m_mis_f = false;		//misボタンのフラグ

	m_key_push = 0;
	m_key_push_f = false;
}

//アクション
void CObjRocketButton::Action()
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


	//各押された時のボタンナンバーを設定と1～5が押されたフラグをtrueにする
	if (Input::GetVKey('2') == true || Input::GetVKey(VK_NUMPAD2) == true) {

		//powボタン
		m_key_push = 1;
		m_key_push_f = true;
	}
	if (Input::GetVKey('3') == true || Input::GetVKey(VK_NUMPAD3) == true) {

		//defボタン
		m_key_push = 2;
		m_key_push_f = true;
	}
	if (Input::GetVKey('4') == true || Input::GetVKey(VK_NUMPAD4) == true) {

		//speボタン
		m_key_push = 3;
		m_key_push_f = true;
	}
	if (Input::GetVKey('5') == true || Input::GetVKey(VK_NUMPAD5) == true) {

		//balボタン
		m_key_push = 4;
		m_key_push_f = true;
	}
	if (Input::GetVKey('1') == true || Input::GetVKey(VK_NUMPAD1) == true) {

		//misボタン
		m_key_push = 5;
		m_key_push_f = true;
	}

	//マウス座標がボタンの上かつ、クリックされているとき
	if (((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && (m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) && m_mou_l == true) ||	
		//ボタンが押されているかつ、その番号が自分のナンバーと同じとき
		((Button_num == m_key_push) && m_key_push_f == true))
		 {
		if (m_mou_f == false) {
			//自惑星の位置とサイズを取る
			CObjPlanet* objp = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (objp->GetType() == 0)
			{
				m_px = objp->GetX() + objp->GetScale_down_move();
				//m_py = objp->GetY();
				m_size = objp->GetSiz();
			}

			if ((Button_num == 1 && g_Power_num > 0))//パワーボタンかつ、パワーユニット数がある場合
			{
				//オブジェクト作成
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 1);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//オブジェクト登録

				g_Power_num -= UNIT_CONSUME_NUM;	//パワーユニット数消費

				//ユニット数が空(0以下)かチェック処理
				if (g_Power_num <= 0)
				{
					g_Power_num = 0;//0未満になっていた場合、0に戻す。
					m_is_empty = true;//空フラグON
				}
			}
			else if (Button_num == 2 && g_Defense_num > 0)//ディフェンスボタンかつ、ディフェンスユニット数がある場合
			{
				//オブジェクト作成
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 2);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//オブジェクト登録

				g_Defense_num -= UNIT_CONSUME_NUM;	//ディフェンスユニット数消費

				//ユニット数が空(0以下)かチェック処理
				if (g_Defense_num <= 0)
				{
					g_Defense_num = 0;//0未満になっていた場合、0に戻す。
					m_is_empty = true;//空フラグON
				}
			}
			else if (Button_num == 3 && g_Speed_num > 0)//スピードボタンかつ、スピードユニット数がある場合
			{
				//オブジェクト作成
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 3);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//オブジェクト登録

				g_Speed_num -= UNIT_CONSUME_NUM;	//スピードユニット数消費

				//ユニット数が空(0以下)かチェック処理
				if (g_Speed_num <= 0)
				{
					g_Speed_num = 0;//0未満になっていた場合、0に戻す。
					m_is_empty = true;//空フラグON
				}
			}
			else if (Button_num == 4 && g_Balance_num > 0)//バランスボタンかつ、バランスユニット数がある場合
			{
				//オブジェクト作成
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 4);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//オブジェクト登録

				g_Balance_num -= UNIT_CONSUME_NUM;	//バランスユニット数消費

				//ユニット数が空(0以下)かチェック処理
				if (g_Balance_num <= 0)
				{
					g_Balance_num = 0;//0未満になっていた場合、0に戻す。
					m_is_empty = true;//空フラグON
				}
			}
			else if (Button_num == 5)//ミサイルボタンの場合
			{
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 5);//オブジェクト作成
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//オブジェクト登録
			}

			m_mou_f = true;
			m_a = 0.3f;		//透明化

			//ポッド選択音
			Audio::Start(3);
		}
	}
	else{}//何もしない

	//ミサイルボタン以外のリキャストタイムの制御
	if (m_mou_f == true && m_is_empty == false && Button_num != 5) {	//クリックした後の処理(ユニット数が空の場合、実行されない)
		m_cnt++;			//カウントする
		if (m_cnt >= RECAST_COMPLETE_POD_TIME * m_player_recast_buff) {	//グローバル変数分カウントする
			m_mou_f = false;							//クリックできるようにする。
			m_cnt = 0;
			m_a = 1.0f;		//不透明化
		}
	}
	//ミサイルのリキャストタイム制御
	else if (m_mou_f == true && m_is_empty == false && Button_num == 5) {	//クリックした後の処理(ユニット数が空の場合、実行されない)
		m_cnt++;			//カウントする
		if (m_cnt >= RECAST_COMPLETE_TIME * m_player_recast_buff) {	//グローバル変数分カウントする
			m_mou_f = false;							//クリックできるようにする。
			m_cnt = 0;
			m_a = 1.0f;		//不透明化
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (battle_end == true) {	//時間切れで
		m_mou_f = true;			//マウス無効
		m_a -= 0.03f;				//透明化
		m_a2 -= 0.1f;		//透明化
		if (m_a > 0.0f && m_a2 > 0.0f)
			this->SetStatus(false);	//消滅
	}

}

//ドロー
void CObjRocketButton::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };//ポッドミサイルボタン用
	float d[4] = { 1.0f,1.0f, 1.0f, m_a2 };//人数不足アイコン、リキャストゲージ(現在値)用
	float b[4] = { 0.0f,0.0f, 0.0f, m_a2 };//リキャストゲージ(最大値)用

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	//ボタン入力が1～4の時の切り取り位置
	if (Button_num >= 1 && Button_num <= 4)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 156.0f;
		src.m_bottom = 156.0f;
	}
	//それ以外ならミサイルの切り取り位置
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 180.0f;
	}
		dst.m_top = m_y;
		dst.m_left = m_x;
		dst.m_right = m_x + m_w;
		dst.m_bottom = m_y + m_h;

	//ポッド・ミサイルの表示するためのswitch文
	switch (Button_num){
	case 1:                 //-------------------------赤色ボタン
		//11番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(11, &src, &dst, c, 0.0f);
		break;
	case 2:                 //-------------------------青色ボタン
		//12番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(12, &src, &dst, c, 0.0f);
		break;
	case 3:                 //-------------------------緑色ボタン
		//13番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(13, &src, &dst, c, 0.0f);
		break;
	case 4:                 //-------------------------灰色ボタン
		//14番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(14, &src, &dst, c, 0.0f);
		break;
	case 5:                 //-------------------------ミサイルボタン
		//15番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(15, &src, &dst, c, 0.0f);
		break;
	}

	//人数不足アイコン表示(ユニット数が空の時に表示される)
	if (m_is_empty == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 398.0f;
		src.m_bottom = 130.0f;

		dst.m_top = m_y + 25.0f;
		dst.m_left = m_x - 10.0f;
		dst.m_right = m_x + m_w + 10.0f;
		dst.m_bottom = m_y + m_h - 25.0f;
		Draw::Draw(31, &src, &dst, d, 0.0f);
	}

	//リキャストゲージ表示(満タンになる＝リキャスト完了)
	//※リキャスト中のみ表示される
	//ポッド関係の処理
	if (m_mou_f == true && m_is_empty == false && Button_num != 5)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_h - 15.0f;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_h - 5.0f;

		//▼最大値表示
		dst.m_right = m_x + m_w;
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//▼現在値表示		
		dst.m_right = m_x + (m_w * (m_cnt / (RECAST_COMPLETE_POD_TIME * m_player_recast_buff)));
		Draw::Draw(32, &src, &dst, d, 0.0f);
	}
	//ミサイルの処理
	else if (m_mou_f == true && m_is_empty == false &&Button_num==5)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_h - 15.0f;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_h - 5.0f;

		//▼最大値表示
		dst.m_right = m_x + m_w;
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//▼現在値表示		
		dst.m_right = m_x + (m_w * (m_cnt / (RECAST_COMPLETE_TIME * m_player_recast_buff)));
		Draw::Draw(32, &src, &dst, d, 0.0f);
	}

}