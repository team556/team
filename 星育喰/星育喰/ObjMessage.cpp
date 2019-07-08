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


	//テスト
	wchar_t font_data[22][30] =
	{
		{ L'あ',L'い',L'う',L'え',L'お',L'ア',L'イ',L'ウ',L'エ',L'オ' },
		{ L'か',L'き',L'く',L'け',L'こ',L'カ',L'キ',L'ク',L'ケ',L'コ',L'が',L'ぎ',L'ぐ',L'げ',L'ご',L'ガ',L'ギ',L'グ',L'ゲ',L'ゴ' },
		{ L'さ',L'し',L'す',L'せ',L'そ',L'サ',L'シ',L'ス',L'セ',L'ソ',L'ざ',L'じ',L'ず',L'ぜ',L'ぞ',L'ザ',L'ジ',L'ズ',L'ゼ',L'ゾ' },
		{ L'た',L'ち',L'つ',L'て',L'と',L'タ',L'チ',L'ツ',L'テ',L'ト',L'だ',L'ぢ',L'づ',L'で',L'ど',L'ダ',L'ヂ',L'ヅ',L'デ',L'ド' },

		//仮でここまでにしてテストしたい。
	};

	//フォントデータをコピー
	memcpy(m_font_data, font_data, sizeof(wchar_t)*(22 * 30));


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
	if (m_Scene_id == 0)
	{
		swprintf_s(m_font[0], L"あかあかきくきく＿かうい￥１２３２１３２３１２１３１２１３２；");//メッセージ１
		swprintf_s(m_font[1], L"あいうかきく１２３；");	//メッセージ２
		swprintf_s(m_font[2], L"うか１２２２３；");		//メッセージ３
		swprintf_s(m_font[3], L"|");					//メッセージ４
		swprintf_s(m_font[4], L"うか１２２２３；");		//メッセージ５
		swprintf_s(m_font[5], L"|");					//メッセージ６
	}
	//テスト
	else if (m_Scene_id == 1)
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

	//▼メッセージ表示機能が停止した時の処理
	//※メッセージ表示機能停止時はこの処理の中に入り、
	//この処理以降の処理は実行されない。
	//特にこの処理の中に何か書き込まなければ、
	//メッセージ表示機能が再び動作状態になる事はない。
	//再び動作状態にしたい場合、条件を満たした時に
	//「m_progress++」「m_run_switch = true」する事で動作させる事が出来る。
	//※「m_progress++」する意味は、メッセージ進行度を次に進めないと、
	//また「｜」が読み込まれてしまうため。
	if (m_run_switch == false)
	{
		if (m_Scene_id == 0 && m_progress == 3)
		{
			if (Input::GetVKey('A') == true)
			{
				m_progress++;
				m_run_switch = true;
			}
		}
		else if (m_Scene_id == 1 && m_progress == 0)
		{

		}

		return;
	}

	//▼メッセージ表示機能停止処理
	//※「｜(メッセージ表示機能停止)」が書かれていれば、
	//この処理が実行される。
	else if (m_font[m_progress][m_font_count] == L'|')
	{
		m_run_switch = false;
		m_skip_f = false;//スキップフラグOFF(再び動作状態となった時、スキップされるのを防ぐため)

		return;
	}


	//▼現在メッセージの文字列の長さを取得
	//※新たなメッセージ取得毎に１回だけ実行される。
	if (m_length == 0)
	{
		for (int i = 0; m_font[m_progress][i] != L'；'; i++)
		{
			m_length = i;
		}
	}

	//▼キーフラグ
	//※左クリックPush状態→左クリック未Push状態になるまで、
	//再度左クリックする事は出来ない処理。
	if (m_mou_l == false)
	{
		m_key_f = false;
	}

	
	//▼メッセージ表示＆終了処理
	if (m_font[m_progress][m_font_count] == L'；' || m_skip_f == true)
	{
		//▽メッセージ終了の処理
		//現在のメッセージが最後まで表示されると、この処理が実行される。
		//この状態の時に、左クリックする事で次のメッセージへと移行する。
		//※スキップフラグON時はメッセージ終了してなくてもこの処理に入る。
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			//次のメッセージへ移行する前に、
			//メッセージ表示に必要な変数等を元に戻す
			for (int i = 0; i < FONT_MAX; i++)
			{
				m_font_column[i] = 0;
				m_font_line[i] = 0;
				m_font_draw_x[i] = 0;
				m_font_draw_y[i] = 0;
			}

			m_time = 0;
			m_font_count = 0;
			m_length = 0;
			m_fast_f = false;

			m_key_f = true;//キーフラグを立てる
			m_progress++;//メッセージ進行度を増加させ、次のメッセージへと移行。
		}
	}
	else if (m_time <= 0 || m_fast_f == true)
	{
		//▽メッセージ表示処理
		//現在のメッセージが最後まで表示されていない場合、
		//m_timeにより、0.08秒毎にこの処理が実行される。
		//登録された文字から現在表示しようとしている文字に
		//当てはまるものを探し、見つかれば、適切な切り取り位置を返す。
		//※見つからなければ空白を返す。
		//※新たに文字を登録したい場合、
		//以下のようにif文で文字を登録し、適切な切り取り位置を設定すべし。
		//ちなみに、余裕があればこの部分は関数化する予定。
		//※描画速度高速化フラグON時はm_time関係なしにこの処理に入る。


		////テスト
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{

		//	}
		//}


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
		//空白の処理
		else if (m_font[m_progress][m_font_count] == L'＿')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;
		}
		//改行の処理
		else if (m_font[m_progress][m_font_count] == L'￥')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;

			m_font_draw_x[m_font_count + 1] = 0;//フォント描画位置Xを初期地点に戻す
			m_font_count++;	//表示しようとしている文字を次のフォント情報へ変更する

			//改行以降のフォント描画位置Yを下にずらす
			for (int i = m_font_count; i <= m_length; i++)
			{
				m_font_draw_y[i]++;
			}

			return;
		}

		//次のフォント描画位置Xを現在のフォント描画位置Xを基に右にずらす
		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count] + 1;

		m_font_count++;//表示しようとしている文字を次のフォント情報へ変更する
		m_time = 5;//次のフォント描画までの時間を0.08秒に設定
	}
	else
	{
		//▽次のフォント描画までの時間減少処理
		m_time--;
	}


	//メッセージ表示中に左クリックされたら
	//メッセージ描画速度を高速化するフラグを立てる
	if (m_mou_l == true && m_key_f == false)
	{
		m_fast_f = true;
		m_key_f = true;//キーフラグを立てる
	}
	//メッセージ表示中にCTRLキーが入力されたら
	//メッセージ表示機能停止までのメッセージを全て飛ばすフラグを立てる
	else if (Input::GetVKey(VK_CONTROL) == true)
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


	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };//フォント画像用

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

	//現在メッセージの文字列の長さが取得出来ていれば実行される
	if (m_length != 0)
	{
		//文字列の長さ(文字の数)分、フォント表示処理を行う
		//※フォント１つ１つをfor文で文字の総数分回して、表示している。
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
