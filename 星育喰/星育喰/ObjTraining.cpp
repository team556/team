//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

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
			Draw::LoadImage(L"TitleBackgroundTest.jpg", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);

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
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

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
		src.m_right = 62.0f;
		src.m_bottom = 62.0f;

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
		swprintf_s(m_message, L"残り住民数がいません");//文字配列に文字データを入れる
		
		//▼エラーメッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;
		
		m_alpha = 1.0f;		//エラーメッセージを表示するため、透過度を1.0fにする
	}
	else  //(Tmp_human < 0 || 999900 < Tmp_human) これ以上振り分けられない場合
	{
		swprintf_s(m_message, L"これ以上振り分けられません");//文字配列に文字データを入れる

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
	//▼施設(兵舎、研究所)必要素材&サイズフォント用
	float Facility_message_font[FACILITY_MES_MAX_FONT_LINE][4] =
	{
		{ 0.0f,0.0f,1.0f,1.0f },//1行目は青色
		{ 0.0f,0.0f,0.0f,1.0f },//2行目は黒色
		{ 0.0f,0.0f,0.0f,1.0f },//3行目は黒色
		{ 0.0f,0.0f,0.0f,1.0f },//4行目は赤色、または青色(以下の処理で変更する)
		{ 1.0f,0.0f,0.0f,1.0f },//5行目は赤色
		{ 1.0f,0.0f,0.0f,1.0f },//6行目は赤色
	};


	//▼施設レベルMAX時の処理
	if (Facility_Level == FACILITY_MAX_LV)
	{
		//施設必要素材&サイズメッセージ設定
		swprintf_s(m_Facility_message[0], L"LvUP条件  所持/  必要");	//文字配列に文字データを入れる
		swprintf_s(m_Facility_message[1], L"最大レベル到達！");			//文字配列に文字データを入れる
		swprintf_s(m_Facility_message[2], L"これ以上LVUP不可です。");	//文字配列に文字データを入れる
		swprintf_s(m_Facility_message[3], L"");							//文字データをクリアする
		swprintf_s(m_message_Mat_name, L"");							//文字データをクリアする
	}

	//▼施設レベルMAXではない時の処理
	else
	{
		//▽施設必要素材&サイズメッセージ設定(共通処理)
		swprintf_s(m_Facility_message[0], L"LvUP条件  所持/  必要");																						//文字配列に文字データを入れる
		swprintf_s(m_Facility_message[1], L"惑星HP  %6.0f/%6.0f", g_Player_max_size, m_Facility_next_Size_num[Facility_Level - 1]);							//文字配列に文字データを入れる
		swprintf_s(m_Facility_message[2], L"        %6d/%6d", *m_Facility_next_Mat_type[Facility_Level - 1], m_Facility_next_Mat_num[Facility_Level - 1]);	//文字配列に文字データを入れる
		swprintf_s(m_message_Mat_name, L"%s", m_Facility_next_Mat_name[Facility_Level - 1]);																//文字配列に文字データを入れる


		//▽レベルUP可能時の処理
		if (g_Player_max_size > m_Facility_next_Size_num[Facility_Level - 1] &&
			*m_Facility_next_Mat_type[Facility_Level - 1] >= m_Facility_next_Mat_num[Facility_Level - 1])
		{
			//施設必要素材&サイズメッセージ設定
			swprintf_s(m_Facility_message[3], L"      LvUP可能!");	//文字配列に文字データを入れる
			swprintf_s(m_Facility_message[4], L"");					//文字データをクリアする
			swprintf_s(m_Facility_message[5], L"");					//文字データをクリアする

			//施設必要素材&サイズメッセージ4行目のカラーを青色に設定
			Facility_message_font[3][0] = 0.0f;
			Facility_message_font[3][2] = 1.0f;
		}
		//▽レベルUP不可時の処理
		else
		{
			//施設必要素材&サイズメッセージ設定
			swprintf_s(m_Facility_message[3], L"      LvUP不可");	//文字配列に文字データを入れる
			
			//以下のメッセージは現在のサイズ(HP)がレベルUPに必要なサイズ(HP)以下だった場合のみ表示する
			if (g_Player_max_size <= m_Facility_next_Size_num[Facility_Level - 1])
			{
				swprintf_s(m_Facility_message[4], L"※惑星HPが0以下になる");	//文字配列に文字データを入れる
				swprintf_s(m_Facility_message[5], L"場合LvUPは出来ません");		//文字配列に文字データを入れる
			}
			else
			{
				swprintf_s(m_Facility_message[4], L"");	//文字データをクリアする
				swprintf_s(m_Facility_message[5], L"");	//文字データをクリアする
			}
		
			//施設必要素材&サイズメッセージ4行目のカラーを赤色に設定
			Facility_message_font[3][0] = 1.0f;
			Facility_message_font[3][2] = 0.0f;
		}
	}


	//▼描画処理
	//素材名を除いたフォント表示
	for (int i = 0; i < FACILITY_MES_MAX_FONT_LINE; i++)
	{
		Font::StrDraw(m_Facility_message[i], 167.5f, 440.0f + i * 35.0f, 25.0f, Facility_message_font[i]);
	}

	//素材名のフォント表示
	Font::StrDraw(m_message_Mat_name, 167.5f, 514.0f, 17.5f, Facility_message_font[2]);
}



//ここの関数説明、まだできてない。

//数字→文字化→フォント化→ついでに指定場所(x,y,size)に色決めて(color)表示してくれる関数

//武器ポッドウインドウの必要資材数、各施設のレベルアップに必要なHP等といった、
//数値が変動する部分のフリーフォント描画を楽にする為に作成した関数。
void CObjTraining::FontDraw(int id, int conversion, float x, float y, float x_size, float y_size, float color[4])
{
	#define WIDTH_DATA_NUM (10)//半角全角データ情報の数

	//数字の半角全角データ情報
	//※半角→全角に変換の際に使用。
	wchar_t halfwidth_data[WIDTH_DATA_NUM] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };
	wchar_t fullwidth_data[WIDTH_DATA_NUM] = { L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９' };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置



	//▼数字(int)→文字(wchar_t)化処理
	//※ついでに文字の終わり部分に印(；)をつける
	swprintf_s(font[id], L"%d；", conversion);

	//▼文字化した文字列の長さを取得	
	for (int i = 0; font[id][i] != L'；'; i++)
	{
		length = i + 1;
	}

	//▼半角→全角変換処理
	for (int i = 0; i <= length; i++)
	{
		for (int j = 0; j <= WIDTH_DATA_NUM; j++)
		{
			//文字化した数字と一致する半角データを探し、
			//それを見つけると、その配列部分に半角に対応する全角データを入れる。
			if (font[id][i] == halfwidth_data[j])
			{
				font[id][i] = fullwidth_data[j];
				
				break;//全角データ入ったので、半角→全角変換処理から抜ける
			}
		}
	}

	FontDraw(id, font[id], x, y, x_size, y_size, color);//文字化、全角化した為、通常のFontDrawの処理に入れる
}



//ここの関数説明、まだできてない。

//メッセージ文は必ず全角文字を用いる事。
//半角文字、フォントデータに登録されてない文字等は使用不可なので注意。(入力すると空白扱いとなる)
void CObjTraining::FontDraw(int id, wchar_t *conversion, float x, float y, float x_size, float y_size, float color[4])
{
	draw_x[id] = x;
	draw_y[id] = y;
	draw_x_size[id] = x_size;
	draw_y_size[id] = y_size;

	//フォントデータ情報
	//※配列位置がそのまま切り取り位置となる為、フォント画像の配置と同じように文字登録するように
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'あ',L'い',L'う',L'え',L'お',L'ア',L'イ',L'ウ',L'エ',L'オ' },
		{ L'か',L'き',L'く',L'け',L'こ',L'カ',L'キ',L'ク',L'ケ',L'コ',L'が',L'ぎ',L'ぐ',L'げ',L'ご',L'ガ',L'ギ',L'グ',L'ゲ',L'ゴ' },
		{ L'さ',L'し',L'す',L'せ',L'そ',L'サ',L'シ',L'ス',L'セ',L'ソ',L'ざ',L'じ',L'ず',L'ぜ',L'ぞ',L'ザ',L'ジ',L'ズ',L'ゼ',L'ゾ' },
		{ L'た',L'ち',L'つ',L'て',L'と',L'タ',L'チ',L'ツ',L'テ',L'ト',L'だ',L'ぢ',L'づ',L'で',L'ど',L'ダ',L'ヂ',L'ヅ',L'デ',L'ド' },
		{ L'な',L'に',L'ぬ',L'ね',L'の',L'ナ',L'ニ',L'ヌ',L'ネ',L'ノ' },
		{ L'は',L'ひ',L'ふ',L'へ',L'ほ',L'ハ',L'ヒ',L'フ',L'ヘ',L'ホ',L'ば',L'び',L'ぶ',L'べ',L'ぼ',L'バ',L'ビ',L'ブ',L'ベ',L'ボ' },
		{ L'ま',L'み',L'む',L'め',L'も',L'マ',L'ミ',L'ム',L'メ',L'モ' },
		{ L'や',L'ゆ',L'よ',L'ヤ',L'ユ',L'ヨ' },
		{ L'ら',L'り',L'る',L'れ',L'ろ',L'ラ',L'リ',L'ル',L'レ',L'ロ' },
		{ L'わ',L'を',L'ん',L'ワ',L'ヲ',L'ン' },
		{ L'×',L'※',L'：',L'＋',L'－',L'…',L'。',L'！',L'？',L'、',L'＆',L'．',L'＝',L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９',L'一',L'二',L'三',L'四',L'五',L'六',L'七',L'八',L'九',L'零' },
		{ L'今',L'日',L'人',L'類',L'統',L'括',L'山',L'田',L'先',L'敵',L'惑',L'星',L'情',L'報',L'不',L'意',L'打',L'喰',L'前',L'行' },
		{ L'聞',L'強',L'来',L'思',L'準',L'備',L'越',L'手',L'入',L'見',L'攻',L'撃',L'傾',L'向',L'戦',L'闘',L'必',L'殺',L'技',L'持',L'捕',L'食',L'奪' },
		{ L'直',L'結',L'負',L'無',L'気',L'仕',L'方',L'下',L'出',L'押',L'命',L'令',L'住',L'最',L'初',L'回',L'目',L'時',L'間',L'属',L'性' },
		{ L'有',L'利',L'不',L'利',L'赤',L'青',L'緑',L'灰',L'色',L'対',L'等',L'察',L'簡',L'単',L'活',L'用',L'数',L'字',L'上',L'真',L'中',L'線' },
		{ L'吸',L'寄',L'逆',L'自',L'分',L'同',L'士',L'引',L'力',L'衝',L'突',L'大',L'小',L'宇',L'宙',L'常',L'識',L'覚',L'習',L'慣',L'考' },
		{ L'素',L'材',L'移',L'所',L'配',L'置',L'便',L'番',L'最',L'高',L'体',L'成',L'果',L'勝',L'昇',L'多',L'書',L'材',L'限',L'後' },
		{ L'次',L'獲',L'得',L'集',L'切',L'札',L'乗',L'詳',L'内',L'容',L'説',L'明',L'欲',L'把',L'握',L'残',L'秘',L'訣',L'油',L'断',L'優' },
		{ L'方',L'法',L'教',L'育',L'画',L'面',L'研',L'究',L'民',L'術',L'耐',L'久',L'増',L'員',L'割',L'振',L'再',L'産',L'早',L'武',L'器' },
		{ L'製',L'作',L'実',L'際',L'度',L'当',L'滅',L'表',L'示',L'少',L'遅',L'戻',L'兵',L'舎',L'化',L'他',L'資',L'飛',L'相',L'的',L'込' },
		{ L'参',L'加',L'割',L'振',L'分',L'中',L'色',L'出',L'撃',L'要',L'注',L'条',L'件',L'載',L'倉',L'庫',L'装',L'現',L'在',L'旦',L'定' },
		{ L'発',L'展',L'黒',L'整',L'物',L'光',L'銀',L'河',L'盛',L'奇',L'跡',L'朗',L'報',L'帯',L'安',L'心',L'休',L'遊',L'暗' },
	};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼文字の終わり部分に印(；)をつける
	swprintf_s(font[id], L"%s；", conversion);

	//▼文字化した文字列の長さを取得	
	for (int i = 0; font[id][i] != L'；'; i++)
	{
		length = i + 1;
	}

	//▼フォント表示処理
	//文字列の長さ(文字の数)分、フォント表示処理を行う
	//※フォント１つ１つをfor文で文字の総数分回して、表示している。
	for (int i = 0; i <= length; i++)
	{
		//フォントデータ読み込み処理
		//※表示したい文字が白文字集.pngのどこにあるか検索
		for (int j = 0; j < FONT_DATA_Y; j++)
		{
			for (int k = 0; k < FONT_DATA_X; k++)
			{
				//フォントデータの端部に到達すると、次の行に移る処理
				if (font_data[j][k] == NULL)
				{
					break;
				}
				//検索HITしたら、その切り取り位置を代入する
				else if (font[id][i] == font_data[j][k])
				{
					font_column[id][i] = k + 1;
					font_line[id][i] = j + 1;

					break;//検索HITしたので、フォントデータ読み込み処理から抜ける
				}
			}

			//検索終了していれば、フォントデータ読み込み処理から抜ける
			if (font_column[i] != 0 || font_line[i] != 0)
			{
				break;
			}
		}

		//▼フォント表示
		src.m_top = FONT_CLIP_SIZE * (font_line[id][i] - 1);
		src.m_left = FONT_CLIP_SIZE * (font_column[id][i] - 1);
		src.m_right = FONT_CLIP_SIZE * font_column[id][i];
		src.m_bottom = FONT_CLIP_SIZE * font_line[id][i];

		dst.m_top = draw_y[id];
		dst.m_left = draw_x[id] + (draw_x_size[id] * i);
		dst.m_right = draw_x[id] + (draw_x_size[id] * (i + 1));
		dst.m_bottom = draw_y[id] + (draw_y_size[id]);

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

		//読み込み番号121番に白文字集.pngの画像が無ければ正常に動作しないので注意。
		Draw::Draw(121, &src, &dst, color, 0.0f);
	}
}
