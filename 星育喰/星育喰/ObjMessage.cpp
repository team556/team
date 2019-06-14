//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//デバッグ用
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//#include <string.h> 

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMessage::Init()
{
	//str = "";//初期化

	for (int i = 0; i < STR_MAX; i++)
	{
		str_column[i] = 0;
		str_line[i] = 0;
		str_draw_x[i] = 0;
		str_draw_y[i] = 0;
	}

	time = 0;
	text_count = 0;
	now_max = 0;


	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
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

	//半角文字＋登録されてない文字は使用不可
	//「＿」は空白、「￥」は改行、「；」で文章終了(文章終了入れないと永遠に読み込み続け、やがて読み取り違反が発生する)

	swprintf_s(str[0], L"あい＿うきく￥か３１２；");//メッセージ１
	
	//文字列長さ測定
	if (now_max == 0)
	{
		for (int i = 0; str[0][i] != L'；'; i++)
		{
			now_max = i;
		}
	}

	
	if (str[0][text_count] == L'；')
	{
		;//クリックで次の文章へ。
	}
	else if (time <= 0)//文章表示途中でクリックされたら、ここの値を30(何秒毎に表示の値と一緒にして瞬間表示させる)
	{
		if (str[0][text_count] == L'あ')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'い')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'う')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'か')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'き')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'く')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'１')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'２')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'３')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'＿')
		{
			str_column[text_count] = 0;
			str_line[text_count] = 0;
		}
		else if (str[0][text_count] == L'￥')
		{
			str_column[text_count] = 0;
			str_line[text_count] = 0;

			str_draw_x[text_count + 1] = 0;
			text_count++;
			time = 60;

			for (int i = text_count; i <= now_max; i++)
			{
				str_draw_y[i]++;
			}

			return;
		}

		str_draw_x[text_count + 1] = str_draw_x[text_count] + 1;
		text_count++;
		time = 60;
	}
	else
	{
		time--;
	}
}

//ドロー
void CObjMessage::Draw()
{
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

	if (now_max != 0)
	{
		for (int i = 0; i <= now_max; i++)
		{
			//▼フォント表示
			src.m_top = STR_SIZE * (str_line[i] - 1);
			src.m_left = STR_SIZE * (str_column[i] - 1);
			src.m_right = STR_SIZE * str_column[i];
			src.m_bottom = STR_SIZE * str_line[i];

			//行、列のどちらかに0が入力されていた場合、そのフォントを表示しない。
			if (src.m_right == 0.0f || src.m_bottom == 0.0f)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
			}

			dst.m_top = 500.0f + (STR_SIZE * str_draw_y[i]);
			dst.m_left = 50.0f + (STR_SIZE * str_draw_x[i]);
			dst.m_right = 50.0f + (STR_SIZE * (str_draw_x[i] + 1));
			dst.m_bottom = 500.0f + (STR_SIZE * (str_draw_y[i] + 1));

			Draw::Draw(3, &src, &dst, d, 0.0f);
		}
	}

	//デバッグ用仮マウス位置表示
	wchar_t mou[256];
	swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
