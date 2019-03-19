//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_COLOR (1.0f) //全カラー明度の初期値

//イニシャライズ
void CObjBarracks::Init()
{
	m_Bar_color = INI_COLOR;
	Bar_Level_test = 1;
}

//アクション
void CObjBarracks::Action()
{
	//▼兵舎ウインドウ表示時の処理
	if (window_start_manage == Barracks)
	{

	}
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default)
	{
		return;
	}


	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//兵舎選択範囲
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_message_f = true;	//メッセージウインドウを表示させる
		m_Bar_color = 0.7f;

		//左クリックされたらフラグを立て、兵舎ウインドウを開く
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

				//m_message_f = false;//メッセージウインドウを非表示にしたい(兵舎ウインドウ表示時に後ろに出さない為に)

				//"兵舎ウインドウを開いている状態"フラグを立てる
				window_start_manage = Barracks;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_message_f = false;//メッセージウインドウを非表示にさせる
		m_Bar_color = 1.0f;
	}
}

//ドロー
void CObjBarracks::Draw()
{
	//▼シーン切り替え演出後に非表示にする処理
	if (scene_change_start == true)
	{
		return;
	}

	//兵舎画像用
	float b[4] = { m_Bar_color,m_Bar_color,m_Bar_color,1.0f };

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼テスト
	//Font::StrDraw(L"☆育喰", 425, 50, 120, d);

	//▼兵舎表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 245.0f;
	src.m_bottom = 206.0f;

	dst.m_top = 460.0f;
	dst.m_left = 810.0f;
	dst.m_right = 1190.0f;
	dst.m_bottom = 690.0f;
	Draw::Draw(2, &src, &dst, b, 0.0f);

	//メッセージウインドウ表示管理フラグがtrueの時、描画。
	if (m_message_f == true)
	{
		//▼メッセージウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = m_mou_y - 50.0f;
		dst.m_left = m_mou_x - 100.0f;
		dst.m_right = m_mou_x + 100.0f;
		dst.m_bottom = m_mou_y - 10.0f;
		Draw::Draw(21, &src, &dst, b, 0.0f);

		//▼フォント表示
		wchar_t str[9];											//9文字分格納可能な文字配列を宣言(99レベル以上はいかないと想定した文字分)
		swprintf_s(str, L"兵舎 Lv.%d", Bar_Level_test);			//その文字配列に文字データを入れる
		Font::StrDraw(str, m_mou_x - 75, m_mou_y - 45, 30, d);	//その文字配列をFontで描画
	}

	//▼兵舎ウインドウ開いている際に表示するグラフィック
	if (window_start_manage == Barracks)
	{
		//▼灰色ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, d, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, d, 0.0f);

		//▼フォント集
		//wchar_t str[9];											//9文字分格納可能な文字配列を宣言(99レベル以上はいかないと想定した文字分)
		//swprintf_s(str, L"兵舎 Lv.%d", Bar_Level_test);			//その文字配列に文字データを入れる
		//Font::StrDraw(str, m_mou_x - 75, m_mou_y - 45, 30, d);	//その文字配列をFontで描画

		//Font::StrDraw(L"兵舎レベルUP", 425, 50, 120, d);

		//Font::StrDraw(L"住民振り分け", 425, 50, 120, d);

		//Font::StrDraw(L"パワー", 425, 50, 120, d);

		//Font::StrDraw(L"ディフェンス", 425, 50, 120, d);

		//Font::StrDraw(L"スピード", 425, 50, 120, d);

		//Font::StrDraw(L"バランス", 425, 50, 120, d);
	}
}