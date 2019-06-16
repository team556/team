//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//デバッグ用
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMessage::Init()
{
	for (int i = 0; i < FONT_MAX; i++)
	{
		m_font_column[i] = 0;
		m_font_line[i] = 0;
		m_font_draw_x[i] = 0;
		m_font_draw_y[i] = 0;
	}

	m_time = 0;
	m_font_count = 0;
	m_progress = 0;
	m_length = 0;
	m_fast_f = false;
	m_skip_f = false;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_run_switch = true;


	//-------------------------------------------------------------------------------
	//▼メッセージ文設定
	//以下のように「シーンID(if文)とメッセージ文(swprintf_s)」の２つで１セットとして設定する。
	//メッセージ文は必ず全角文字を用いる事。
	//半角文字、登録されてない文字等は使用不可なので注意。(入力すると空白扱いとなる)
	//▽特殊処理について
	//以下の全角文字を打ち込むと、それぞれ特殊処理が行われます。
	//「＿」……空白
	//「￥」……改行
	//「；」……メッセージ終了
	//※メッセージ終了を入れなければ永遠に読み込み続け、やがて読み取り違反が発生する)
	//「｜」……メッセージ表示機能停止
	//※全てのメッセージ終了後、
	//またはメッセージ途中にプレイヤーに
	//何か操作させたい時にこの全角文字を書いて下さい。

	//テスト
	if (Scene_id == 0)
	{
		swprintf_s(m_font[0], L"あかあかきくきく＿かうい￥１２３２１３２３１２１３１２１３２；");//メッセージ１
		swprintf_s(m_font[1], L"あいうかきく１２３；");//メッセージ２
		swprintf_s(m_font[2], L"うか１２２２３；");//メッセージ３
		swprintf_s(m_font[3], L"|");//メッセージ４
		swprintf_s(m_font[4], L"うか１２２２３；");//メッセージ５
		swprintf_s(m_font[5], L"|");//メッセージ４
	}
	//テスト
	if (Scene_id == 1)
	{

	}
}

//アクション
void CObjMessage::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//※再度起動させる場合、ページ増やしてm_run_switchをtrueにする
	//停止設定
	if (m_run_switch == false)
	{
		if (m_progress == 3)
		{
			if (Input::GetVKey('A') == true)
			{
				m_progress++;
				m_run_switch = true;
			}
		}

		return;
	}
	if (m_font[m_progress][m_font_count] == L'|')
	{
		m_run_switch = false;
		m_skip_f = false;
		return;
	}

	//文字列長さ測定
	if (m_length == 0)
	{
		for (int i = 0; m_font[m_progress][i] != L'；'; i++)
		{
			m_length = i;
		}
	}

	//キーフラグ
	if (m_mou_l == false)
	{
		m_key_f = false;
	}

	
	if (m_font[m_progress][m_font_count] == L'；' || m_skip_f == true)
	{
		//クリックで次の文章へ。
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			for (int i = 0; i < FONT_MAX; i++)
			{
				m_font_column[i] = 0;
				m_font_line[i] = 0;
				m_font_draw_x[i] = 0;
				m_font_draw_y[i] = 0;
			}

			m_time = 0;
			m_font_count = 0;
			m_progress++;
			m_length = 0;
			m_fast_f = false;

			m_key_f = true;
		}
	}
	else if (m_time <= 0 || m_fast_f == true)
	{
		//登録された文字から現在の文字に当てはまるものを探し、
		//見つかれば、適切な切り取り位置を返す。
		//※見つからなければ空白を返す。
		//※新たに文字を登録したい場合、
		//以下のようにif文で文字を登録し、適切な切り取り位置を設定すべし。
		//ちなみに、余裕があればこの部分は関数化する予定。
		if (m_font[m_progress][m_font_count] == L'あ')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'い')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'う')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'か')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'き')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'く')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'１')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'２')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'３')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'＿')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;
		}
		else if (m_font[m_progress][m_font_count] == L'￥')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;

			m_font_draw_x[m_font_count + 1] = 0;
			m_font_count++;

			for (int i = m_font_count; i <= m_length; i++)
			{
				m_font_draw_y[i]++;
			}

			return;
		}

		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count] + 1;
		m_font_count++;
		m_time = 5;
	}
	else
	{
		m_time--;
	}


	//左クリックされたらフォント高速表示
	if (m_mou_l == true && m_key_f == false)
	{
		m_fast_f = true;
		m_key_f = true;
	}
	//Zキーが入力されたらメッセージを全て飛ばす
	else if (Input::GetVKey('Z') == true)
	{
		m_skip_f = true;
	}
}

//ドロー
void CObjMessage::Draw()
{
	//▼メッセージ表示機能OFF時はドロー処理を実行しない処理
	if (m_run_switch == false)
	{
		return;
	}


	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼メッセージウインドウ表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = 630.0f;
	dst.m_left = 20.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = 680.0f;
	Draw::Draw(2, &src, &dst, d, 0.0f);

	if (m_length != 0)
	{
		for (int i = 0; i <= m_length; i++)
		{
			//▼フォント表示
			src.m_top = FONT_CLIP_SIZE * (m_font_line[i] - 1);
			src.m_left = FONT_CLIP_SIZE * (m_font_column[i] - 1);
			src.m_right = FONT_CLIP_SIZE * m_font_column[i];
			src.m_bottom = FONT_CLIP_SIZE * m_font_line[i];

			dst.m_top = 500.0f + (FONT_DRAW_SIZE * m_font_draw_y[i]);
			dst.m_left = 50.0f + (FONT_DRAW_SIZE * m_font_draw_x[i]);
			dst.m_right = 50.0f + (FONT_DRAW_SIZE * (m_font_draw_x[i] + 1));
			dst.m_bottom = 500.0f + (FONT_DRAW_SIZE * (m_font_draw_y[i] + 1));

			//以下はフォント切り取り位置(列、行)のどちらかに0が入力されていた場合、
			//そのフォントを表示しない処理。
			if (src.m_right == 0.0f || src.m_bottom == 0.0f)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 0.0f;
				src.m_bottom = 0.0f;

				dst.m_top = 0.0f;
				dst.m_left = 0.0f;
				dst.m_right = 0.0f;
				dst.m_bottom = 0.0f;
			}

			Draw::Draw(3, &src, &dst, d, 0.0f);
		}
	}

	//デバッグ用仮マウス位置表示
	wchar_t mou[256];
	swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
