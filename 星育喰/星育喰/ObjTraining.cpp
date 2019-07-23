//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_PLAYER_SIZE (1500.0f) //プレイヤー惑星の初期サイズ
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//static変数の定義
bool CObjTraining::scene_change_start = false;
bool CObjTraining::white_out_f = false;
int  CObjTraining::player_level = 0;
int  CObjTraining::window_start_manage = Default;

//イニシャライズ
void CObjTraining::Init()
{
	m_size = INI_PLAYER_SIZE;
	m_Mig_time = 0;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_lf = false;
	m_key_rf = false;

	m_Back_Button_color = INI_COLOR;

	m_message_clip_right = 0.0f;
	m_message_clip_bottom = 0.0f;
	m_message_draw_left = 0.0f;
	m_message_draw_right = 0.0f;
	m_message_red_color = 0.0f;
	m_message_green_color = 0.0f;
	m_message_blue_color = 0.0f;
	m_alpha = 0.0f;

	//▼以下のstatic変数は他シーンから育成画面に入る度に初期化を行う
	scene_change_start = false;
	white_out_f = false;
	player_level = (int)((g_Bar_Level + g_Ins_Level) / 2);
	window_start_manage = Default;
}

//アクション
void CObjTraining::Action()
{
	//戻るボタンクリック、もしくは右クリック(どこでも)時実行
	if (window_start_manage == BackButton)
	{
		m_Mig_time++;

		//▼シーン切り替え演出
		//雲演出INが終了するまで(m_Mig_timeが120以上になるまで)待機。
		//終了すると背景をホーム画面のものに切り替え、
		//同じくオブジェクトもホーム画面のものに切り替えた後に
		//雲演出OUTを行い、画面を見せる。
		//プレイヤー惑星サイズがデフォルトの状態に戻った事を確認すると
		//ホーム画面へシーン移行を行う。
		if (scene_change_start == true)
		{
			m_size -= 20.0f;

			if (m_size <= 0.0f)
			{
				Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
			}
		}
		else if (m_Mig_time >= 120)
		{
			//ホーム画面の背景をプレイヤー惑星のレベルに合わせた読み込み番号部分に登録
			//Draw::LoadImage(L"TitleBackgroundTest.jpg", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);
			Draw::LoadImage(L"背景.png", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);

			//ObjHelpにシーン移行演出を伝える
			CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
			help->SetMig_stageF();

			//雲演出OUTを行う
			CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
			obj_cloud->SetCheck(false);

			//シーン切り替え演出にて不必要なオブジェクトを非表示、
			//また必要なオブジェクトを表示するフラグを立てる
			scene_change_start = true;
		}

		return;
	}
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default || g_help_f == true)
	{
		//他施設ウインドウ(ヘルプ画面も含む)の戻るボタンを左クリック(もしくは右クリック)時、
		//ホーム画面に戻るボタンも同時にクリックされないように、
		//以下のようにキーフラグをfalseにする事で制御している。
		m_key_lf = false;
		m_key_rf = false;

		return;
	}


	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼キーフラグ
	//※右クリックPush状態→右クリック未Push状態になるまで、
	//再度右クリックする事は出来ない処理。
	if (m_mou_r == false)	//右クリックOFF
	{
		m_key_rf = true;
	}

	//戻るボタン左クリック、もしくは右クリックする事でホーム画面に戻る
	if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
	{
		m_Back_Button_color = 1.0f;

		//▼移行フラグを立て、ホーム画面へ演出を交えながらシーン移行
		//右クリック入力時
		if (m_mou_r == true)
		{
			//前シーン(兵舎ウインドウ等)から右クリック押したままの状態では入力出来ないようにしている
			if (m_key_rf == true)
			{
				//雲演出INを行う
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//移行フラグ立て
				window_start_manage = BackButton;

				//戻るボタン音
				Audio::Start(2);
			}
		}
		//左クリック入力時
		else if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//雲演出INを行う
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//移行フラグ立て
				window_start_manage = BackButton;

				//戻るボタン音
				Audio::Start(2);
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_Back_Button_color = INI_COLOR;
	}
}

//ドロー
void CObjTraining::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//戻るボタン用
	float b[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼背景(地面)表示
	//シーン移行の演出処理的に、
	//この切り取り位置はホーム画面と同じが好ましい
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), &src, &dst, d, 0.0f);

	//▼シーン切り替え演出前に表示するグラフィック
	if (scene_change_start == false)
	{
		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 10.0f;
		dst.m_left = 10.0f;
		dst.m_right = 60.0f;
		dst.m_bottom = 60.0f;
		Draw::Draw(1, &src, &dst, b, 0.0f);
	}
	//▼シーン切り替え演出後に表示するグラフィック
	else
	{
		//▼プレイヤー惑星表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 448.0f;
		src.m_bottom = 448.0f;

		dst.m_top = 250.0f - m_size;
		dst.m_left = 450.0f - m_size;
		dst.m_right = 750.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(16 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	}



	//デバッグ用仮マウス位置表示
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Allocation関数
//引数1　int type_num		:住民タイプ決定
//引数2　int up_down_check	:振り分けUP / DOWNチェック(+1=振り分けUP / -1=振り分けDOWN)
//戻り値 int				:振り分け後の値
//▼内容
//住民タイプと振り分けUP or DOWNを引数で渡せば、
//以下の処理を行い、その住民タイプの振り分け後の値を返す。
//※同時にグローバル変数である"残り住民数(g_Remain_num)"の値も変化させている。
int CObjTraining::Allocation(int type_num, int up_down_check)
{
	//▼それぞれ仮の変数に代入
	int Tmp_human = type_num;
	int Tmp_remain = g_Remain_num;

	//▼仮の変数で変化させてみる
	Tmp_human += 100 * up_down_check;
	Tmp_remain -= 100 * up_down_check;

	//▼仮の変数が以下の条件を全て満たしていれば、実際の値を変化させる。
	//満たしていなければ、それに応じたエラーメッセージを出し、
	//実際の値を変化させずに関数を終了させる。
	if (0 <= Tmp_human && Tmp_human <= 999900 && Tmp_remain >= 0)
	{
		type_num += 100 * up_down_check;
		g_Remain_num -= 100 * up_down_check;
	}
	else if (Tmp_remain < 0) //残り住民数がいない場合
	{
		//残り住民数がいません文字画像を読み込み127番に登録
		Draw::LoadImage(L"残り住民数がいません.png", 127, TEX_SIZE_512);//簡易メッセージ画像読み込み番号に画像データを入れる

		//切り取り位置を設定する
		m_message_clip_right = 1192.0f;
		m_message_clip_bottom = 112.0f;

		//描画位置を設定する
		m_message_draw_left = -150.0f;
		m_message_draw_right = 150.0f;

		//▼エラーメッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;
		
		m_alpha = 1.0f;		//エラーメッセージを表示するため、透過度を1.0fにする
	}
	else  //(Tmp_human < 0 || 999900 < Tmp_human) これ以上振り分けられない場合
	{
		//これ以上振り分けられません文字画像を読み込み127番に登録
		Draw::LoadImage(L"これ以上振り分けられません.png", 127, TEX_SIZE_512);//簡易メッセージ画像読み込み番号に画像データを入れる

		//切り取り位置を設定する
		m_message_clip_right = 1552.0f;
		m_message_clip_bottom = 112.0f;

		//描画位置を設定する
		m_message_draw_left = -200.0f;
		m_message_draw_right = 200.0f;

		//▼エラーメッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//エラーメッセージを表示するため、透過度を1.0fにする
	}

	return type_num;
}

//---Facility_message関数
//引数1　int Facility_Level	:現在の施設(兵舎or研究所)レベル
//▼内容
//現在の施設(兵舎or研究所)レベルを考慮した
//必要素材&サイズメッセージを描画する。
void CObjTraining::Facility_message(int Facility_Level)
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//青色
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼LvUP条件　所持必要文字画像表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1335.0f;
	src.m_bottom = 112.0f;

	dst.m_top = 440.0f;
	dst.m_left = 165.0f;
	dst.m_right = 433.0f;
	dst.m_bottom = 465.0f;
	Draw::Draw(66, &src, &dst, blue, 0.0f);

	//▼施設レベルMAX時の処理
	if (Facility_Level == FACILITY_MAX_LV)
	{
		//▼最大Lv到達!文字画像表示
		src.m_top = 0.0f;
		src.m_left = 1.5f;//画像の左端に原因不明の黒い線があったので切り取り位置を調整し、その部分を映らなくしている。
		src.m_right = 907.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 167.5f;
		dst.m_right = 338.5f;
		dst.m_bottom = 500.0f;
		Draw::Draw(107, &src, &dst, black, 0.0f);

		//▼これ以上LVUP不可です。文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1350.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 510.0f;
		dst.m_left = 167.5f;
		dst.m_right = 433.0f;
		dst.m_bottom = 535.0f;
		Draw::Draw(108, &src, &dst, black, 0.0f);
	}

	//▼施設レベルMAXではない時の処理
	else
	{
		//▼惑星HP文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 412.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 165.0f;
		dst.m_right = 255.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(67, &src, &dst, black, 0.0f);

		//▼現在の惑星HPを表示
		FontDraw(NumConversion((unsigned int)g_Player_max_size), 338.0f, 475.0f, 15.0f, 25.0f, black, true);

		//▼施設(兵舎、研究所)の次のLVUPに必要なサイズ(HP)表示
		FontDraw(NumConversion((unsigned int)m_Facility_next_Size_num[Facility_Level - 1]), 420.0f, 475.0f, 15.0f, 25.0f, black, true);

		//▼施設(兵舎、研究所)の次のLVUPに必要な素材名表示
		FontDraw(m_Facility_next_Mat_name[Facility_Level - 1], 165.0f, 510.0f, 25.0f, 25.0f, black, false);

		//▼施設(兵舎、研究所)の次のLVUPに必要な現在の素材所持数を表示
		FontDraw(NumConversion(*m_Facility_next_Mat_type[Facility_Level - 1]), 338.0f, 510.0f, 15.0f, 25.0f, black, true);

		//▼施設(兵舎、研究所)の次のLVUPに必要な素材数を表示
		FontDraw(NumConversion(m_Facility_next_Mat_num[Facility_Level - 1]), 420.0f, 510.0f, 15.0f, 25.0f, black, true);

		//▼「所持 / 必要」の値を区切る仕切り表示
		FontDraw(L"／", 354.0f, 475.0f, 20.0f, 25.0f, black, false);
		FontDraw(L"／", 354.0f, 510.0f, 20.0f, 25.0f, black, false);

		//▽レベルUP可能時の処理
		if (g_Player_max_size > m_Facility_next_Size_num[Facility_Level - 1] &&
			*m_Facility_next_Mat_type[Facility_Level - 1] >= m_Facility_next_Mat_num[Facility_Level - 1])
		{
			//▼LvUP可能!文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 607.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 545.0f;
			dst.m_left = 245.0f;
			dst.m_right = 355.0f;
			dst.m_bottom = 570.0f;
			Draw::Draw(70, &src, &dst, blue, 0.0f);
		}
		//▽レベルUP不可時の処理
		else
		{
			//▼LvUP不可文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 577.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 545.0f;
			dst.m_left = 245.0f;
			dst.m_right = 345.0f;
			dst.m_bottom = 570.0f;
			Draw::Draw(71, &src, &dst, red, 0.0f);


			//以下のメッセージは現在のサイズ(HP)がレベルUPに必要なサイズ(HP)以下だった場合のみ表示する
			if (g_Player_max_size <= m_Facility_next_Size_num[Facility_Level - 1])
			{
				//▼"※惑星HPが0以下になる場合"文字画像表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 1577.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 580.0f;
				dst.m_left = 167.5f;
				dst.m_right = 433.0f;
				dst.m_bottom = 605.0f;
				Draw::Draw(106, &src, &dst, red, 0.0f);

				//▼"LvUPは出来ません"文字画像表示
				src.m_top = 0.0f;
				src.m_left = 1577.0f;
				src.m_right = 2639.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 615.0f;
				dst.m_left = 212.5f;
				dst.m_right = 398.0f;
				dst.m_bottom = 640.0f;
				Draw::Draw(106, &src, &dst, red, 0.0f);
			}
		}
	}
}