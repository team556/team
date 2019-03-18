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
}

//アクション
void CObjBarracks::Action()
{
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	if (window_start_manage != Default)
	{
		return;
	}


	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//兵舎選択
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_Bar_color = 0.7f;

		//左クリックされたらフラグを立て、兵舎ウインドウを開く
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

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
	}
}