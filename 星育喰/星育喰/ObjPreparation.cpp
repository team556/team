//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ENEMY_X_POS (1150.0f)	//敵惑星4つ全体の初期X位置
#define INI_ENEMY_Y_POS (190.0f)	//敵惑星4つ全体の初期Y位置
#define INI_WARNING_MESSAGE_X_POS (125.0f)	//警告メッセージ全体の初期X位置
#define INI_WARNING_MESSAGE_Y_POS (250.0f)	//警告メッセージ全体の初期Y位置
#define INI_WARNING_MESSAGE_SIZE  (100.0f)	//警告メッセージ全体のサイズ
#define INI_SPEED (50.0f)		//開始演出で移動する各オブジェクトの初期移動速度
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//static変数の定義
bool CObjPreparation::destroy_progress[4] = { false,false,false,false };

//グローバル変数の定義
int g_Stage_progress = 1;
int g_Special_equipment = 0;
bool g_Special_mastering[5] = { false,false,false,false,false };

//イニシャライズ
void CObjPreparation::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_lf = false;
	m_key_rf = false;

	m_Pvx = 0.0f;
	m_PSvy = 0.0f;
	//m_boost = 0.0f;
	//m_rx = 0.0f;
	//m_ry = 0.0f;
	m_Psize = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_warning_message_x[i] = INI_WARNING_MESSAGE_X_POS;
		m_warning_message_y[i] = INI_WARNING_MESSAGE_Y_POS;
	}

	m_warning_message_size = INI_WARNING_MESSAGE_SIZE;

	m_Evx = 0.0f;
	m_speed = INI_SPEED;

	//m_staging_time = 0;
	m_is_operatable = false;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = INI_COLOR;
	m_No_Button_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	m_Enemy_detail_message_window_x_size = 0.0f;
	m_Enemy_detail_message_window_y_size = 0.0f;

	m_destroy_count = 0;

	//現在の撃破数をカウント
	for (int i = 0; i < 4; i++)
	{
		if (destroy_progress[i] == true)
		{
			m_destroy_count++;
		}
	}
}

//アクション
void CObjPreparation::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//▼操作可能時の処理
	if (m_is_operatable == true)
	{
		return;
	}

	////育喰アイコン、敵惑星(背景)を徐々に表示させる
	//if (m_alpha < 1.0f)
	//{
	//	m_alpha += 0.01f;
	//}

	////育アイコン
	//if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680)
	//{
	//	//m_Tra_color = 1.0f;

	//	//左クリックされたらフラグを立て、育成画面へ演出を交えながらシーン移行
	//	if (m_mou_l == true)
	//	{
	//		//クリック押したままの状態では入力出来ないようにしている
	//		if (m_key_lf == true)
	//		{
	//			m_key_lf = false;

	//			//m_Tra_flag = true;
	//		}
	//	}
	//	else
	//	{
	//		m_key_lf = true;
	//	}
	//}
	//else
	//{
	//	//m_Tra_color = INI_COLOR;
	//}

	/*以下の戦闘準備画面開始演出のコメント結構適当なので、後でしっかり書き直す*/
	//▼戦闘準備画面開始演出
	//敵惑星が目的地に到達するまで以下の処理を実行
	//※プレイヤー惑星、スペシャル技変更ウインドウは敵惑星を基準にタイミング調整している
	if (m_warning_message_y[0] < 30.0f)
	{
		m_is_operatable = true;
	}
	else if (m_alpha >= 1.2f)
	{
		m_warning_message_x[0] += 1.5f;
		m_warning_message_y[0] -= 5.0f;
		m_warning_message_x[1] += 8.5f;
		m_warning_message_y[1] -= 7.9f;
		m_warning_message_size -= 1.0f;
	}
	else if (m_Evx <= -1000.0f)
	{
		//警告メッセージを徐々に表示させる
		//1.0f以上にする意味は、フォント移動までの時間管理もついでに行っている為。
		if (m_alpha < 1.2f)
		{
			m_alpha += 0.01f;
		}
	}
	else if (m_Evx > -1000.0f)
	{
		//移動速度を各惑星のベクトルに加算、もしくは減算し
		//惑星を所定の位置まで移動させる
		m_Evx -= m_speed;		//画面外の右から左の方へ移動
		m_Pvx += m_speed * 0.4;	//敵惑星ほど大きく移動する訳ではない為、0.4倍の値を加算。
		m_PSvy -= m_speed * 0.4;	

		//徐々にプレイヤー惑星、各敵惑星の移動速度を減少させる
		m_speed *= 0.951f;
	}
}

//ドロー
void CObjPreparation::Draw()
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//ボス出現警告メッセージ用
	float warning_message[4] = { 1.0f,0.0f,0.0f,m_alpha };

	//▽フォント準備
	//ボスと戦うまでのカウント
	wchar_t Until_fight_boss_count[6];							  //6文字分格納可能な文字配列を宣言
	swprintf_s(Until_fight_boss_count, L"あと %d体", 3 - m_destroy_count);//その文字配列に文字データを入れる


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼背景表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//▼敵惑星1表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS;
	dst.m_left = INI_ENEMY_X_POS + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 200.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 200.0f;
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//▼敵惑星2表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 30.0f;
	dst.m_left = INI_ENEMY_X_POS + 300.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 400.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 70.0f;
	Draw::Draw(2, &src, &dst, d, 0.0f);

	//▼敵惑星3表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 50.0f;
	dst.m_left = INI_ENEMY_X_POS + 600.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 800.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 150.0f;
	Draw::Draw(3, &src, &dst, d, 0.0f);

	//▼敵惑星4表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS + 250.0f;
	dst.m_left = INI_ENEMY_X_POS + 750.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 1000.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 500.0f;
	Draw::Draw(4, &src, &dst, d, 0.0f);

	//▼プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 62.0f;
	src.m_bottom = 62.0f;

	dst.m_top = 800.0f + m_PSvy - m_Psize;
	dst.m_left = -500.0f + m_Pvx - m_Psize;
	dst.m_right = -50.0f + m_Pvx + m_Psize;
	dst.m_bottom = 1250.0f + m_PSvy + m_Psize;
	Draw::Draw(63, &src, &dst, d, 0.0f);

	//▼スペシャル技選択ウインドウ表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 200.0f;

	dst.m_top = 900.0f + m_PSvy;
	dst.m_left = 360.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = 1100.0f + m_PSvy;
	Draw::Draw(62, &src, &dst, d, 0.0f);

	//▼スペシャル技アイコン集表示
	for (int i = 0; i < 5; i++)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 36.0f;
		src.m_bottom = 35.0f;

		dst.m_top = 985.0f + m_PSvy;
		dst.m_left = 380.0f + i * 95.0f;
		dst.m_right = 460.0f + i * 95.0f;
		dst.m_bottom = 1065.0f + m_PSvy;
		Draw::Draw(57 + i, &src, &dst, d, 0.0f);
	}



	//▼フォント表示
	//スペシャル技選択
	Font::StrDraw(L"スペシャル技選択", 445.0f, 915.0f + m_PSvy, 40.0f, black);

	//ボス出現警告メッセージ
	Font::StrDraw(L"強大な惑星 接近まで", m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);
	Font::StrDraw(Until_fight_boss_count, m_warning_message_x[1] + 250.0f, m_warning_message_y[1] + 130.0f, m_warning_message_size, warning_message);



	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
