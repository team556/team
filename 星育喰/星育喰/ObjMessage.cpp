//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//デバッグ用
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

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

		for (int j = 0; j < 4; j++)
		{
			m_font_color[i][j] = 1.0f;
		}
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

	m_arrow_display_f = 0;
	m_arrow_angle_f = 0;
	m_arrow_x = 0.0f;
	m_arrow_y = 0.0f;
	
	m_swing_vec = 0.0f;
	m_swing_r = 0.0f;

	m_black_out_f = false;
	m_reminder_f = false;
	m_is_top_or_bottom = 0;

	m_run_switch = true;


	//フォントデータ情報
	//※配列位置がそのまま切り取り位置となる為、フォント画像の配置と同じように文字登録するように。
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'あ',L'い',L'う',L'え',L'お',L'ア',L'イ',L'ウ',L'エ',L'オ' },
		{ L'か',L'き',L'く',L'け',L'こ',L'カ',L'キ',L'ク',L'ケ',L'コ',L'が',L'ぎ',L'ぐ',L'げ',L'ご',L'ガ',L'ギ',L'グ',L'ゲ',L'ゴ' },
		{ L'さ',L'し',L'す',L'せ',L'そ',L'サ',L'シ',L'ス',L'セ',L'ソ',L'ざ',L'じ',L'ず',L'ぜ',L'ぞ',L'ザ',L'ジ',L'ズ',L'ゼ',L'ゾ' },
		{ L'た',L'ち',L'つ',L'て',L'と',L'タ',L'チ',L'ツ',L'テ',L'ト',L'だ',L'ぢ',L'づ',L'で',L'ど',L'ダ',L'ヂ',L'ヅ',L'デ',L'ド' },
		{ L'な',L'に',L'ぬ',L'ね',L'の',L'ナ',L'ニ',L'ヌ',L'ネ',L'ノ' },
		{ L'は',L'ひ',L'ふ',L'へ',L'ほ',L'ハ',L'ヒ',L'フ',L'ヘ',L'ホ',L'ば',L'び',L'ぶ',L'べ',L'ぼ',L'バ',L'ビ',L'ブ',L'ベ',L'ボ' },
		{ L'ま',L'み',L'む',L'め',L'も',L'マ',L'ミ',L'ム',L'メ',L'モ' },
		{ L'や',L'ゆ',L'よ',L'ヤ',L'ユ',L'ヨ'},
		{ L'ら',L'り',L'る',L'れ',L'ろ',L'ラ',L'リ',L'ル',L'レ',L'ロ' },
		{ L'わ',L'を',L'ん',L'ワ',L'ヲ',L'ン',L'プ',L'ッ' },
		{ L'×',L'※',L'：',L'＋',L'−',L'…',L'。',L'！',L'？',L'、',L'＆',L'．',L'＝',L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９',L'一',L'二',L'三',L'四',L'五',L'六',L'七',L'八',L'九',L'零' },
		{ L'今',L'日',L'人',L'類',L'統',L'括',L'山',L'田',L'先',L'敵',L'惑',L'星',L'情',L'報',L'不',L'意',L'打',L'喰',L'前',L'行',L'鉄',L'木',L'／' },
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

	//フォントデータをコピー
	//※ヘッダーでm_font_data宣言後、普通にm_font_dataを定義しようとすると
	//上記のように宣言と同時に定義するやり方ができない為、
	//それを解決するために、一旦イニシャライズのみでしか使えない配列を
	//宣言と同時に定義し、そのデータをm_font_dataにコピーした。
	memcpy(m_font_data, font_data, sizeof(wchar_t)*(FONT_DATA_Y * FONT_DATA_X));


	//-------------------------------------------------------------------------------
	//▼メッセージ文設定
	//以下のように「シーンID(if文)とメッセージ文(swprintf_s)」の２つで１セットとして設定する。
	//メッセージ文は必ず全角文字を用いる事。
	//半角文字、フォントデータに登録されてない文字等は使用不可なので注意。(入力すると空白扱いとなる)
	//▽特殊処理について
	//以下の全角文字を打ち込むと、それぞれ特殊処理が行われます。
	//「Ｒ」……赤文字化
	//「Ｇ」……緑文字化
	//「Ｂ」……青文字化
	//「Ｗ」……白文字化
	//「＿」……空白
	//「￥」……改行
	//「〜」……文章途中のクリック要求
	//「｜」……メッセージ表示機能停止
	//※全てのメッセージ終了後、
	//またはメッセージ途中にプレイヤーに
	//何か操作させたい時にこの全角文字を書いて下さい。

	//テスト
	wchar_t strr[20] = L"きになあ";

	//テスト
	if (m_Scene_id == 0)
	{
		swprintf_s(m_font[0], L"ＲあかあかＢきくＧきく＿かうい〜かかかかかかかかきなきなにあ￥にあまむまむ￥テスト１２３￥２１３２３１２￥１３１２１３２");//メッセージ１
		swprintf_s(m_font[1], L"あいうかきく１２３今日人類発展");	//メッセージ２
		swprintf_s(m_font[2], L"テスト：%s：テスト",strr);		//メッセージ３
		swprintf_s(m_font[3], L"|");					//メッセージ４
		swprintf_s(m_font[4], L"うか１２２２３");		//メッセージ５
		swprintf_s(m_font[5], L"|");					//メッセージ６

		m_message_window_num = 2;
	}
	//テスト
	else if (m_Scene_id == 1)
	{
		m_message_window_num = 2;
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
		//▼文字の終わり部分に印(；)をつける
		swprintf_s(m_font[m_progress], L"%s；", m_font[m_progress]);

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


	//▼文章途中のクリック要求処理
	if (m_font[m_progress][m_font_count] == L'〜')
	{
		m_reminder_f = true;//クリック催促画像表示

		//現在のメッセージが最後まで表示されていなくとも、
		//'〜'を書けばクリックするまでメッセージを止める事が出来る。
		//この処理に入っている時に、左クリックする事でメッセージの続きが見れる。
		//※スキップフラグON時はクリックせずとも、勝手に処理が進む。
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			//現在のフォント描画位置Xをそのまま次のフォント描画位置Xに入れる
			//※'Ｒ'等の文字は内部処理の命令文であり、描画する訳ではないため。
			m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count];

			m_font_count++;	//表示しようとしている文字を次のフォント情報へ変更する


			m_key_f = true;//キーフラグを立てる
			m_reminder_f = false;//クリック催促画像非表示

			//選択音
			Audio::Start(1);
		}

		return;
	}

	//▼メッセージカラー変更処理
	if (m_font[m_progress][m_font_count] == L'Ｒ' || m_font[m_progress][m_font_count] == L'Ｇ' ||
		m_font[m_progress][m_font_count] == L'Ｂ' || m_font[m_progress][m_font_count] == L'Ｗ')
	{
		if (m_font[m_progress][m_font_count] == L'Ｒ')
		{
			//Ｒ宣言の後ろにあるフォント全てを赤色に変更する
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 0)
					{
						m_font_color[i][j] = 0.0f;
					}
					else
					{
						m_font_color[i][j] = 1.0f;
					}
				}
			}
		}
		else if (m_font[m_progress][m_font_count] == L'Ｇ')
		{
			//Ｇ宣言の後ろにあるフォント全てを緑色に変更する
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 1)
					{
						m_font_color[i][j] = 0.0f;
					}
					else
					{
						m_font_color[i][j] = 1.0f;
					}
				}
			}
		}
		else if (m_font[m_progress][m_font_count] == L'Ｂ')
		{
			//Ｂ宣言の後ろにあるフォント全てを青色に変更する
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 2)
					{
						m_font_color[i][j] = 0.0f;
					}
					else
					{
						m_font_color[i][j] = 1.0f;
					}
				}
			}
		}
		else  //(m_font[m_progress][m_font_count] == L'Ｗ')
		{
			//Ｗ宣言の後ろにあるフォント全てを白色に変更する
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m_font_color[i][j] = 1.0f;
				}
			}
		}

		//現在のフォント描画位置Xをそのまま次のフォント描画位置Xに入れる
		//※'Ｒ'等の文字は内部処理の命令文であり、描画する訳ではないため。
		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count];

		m_font_count++;	//表示しようとしている文字を次のフォント情報へ変更する

		return;
	}
	
	//▼メッセージ表示＆終了処理
	if (m_font[m_progress][m_font_count] == L'；' || m_skip_f == true)
	{
		m_reminder_f = true;//クリック催促画像表示

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

				for (int j = 0; j < 4; j++)
				{
					m_font_color[i][j] = 1.0f;
				}
			}

			m_time = 0;
			m_font_count = 0;
			m_length = 0;
			m_fast_f = false;

			m_key_f = true;//キーフラグを立てる
			m_reminder_f = false;//クリック催促画像非表示
			m_progress++;//メッセージ進行度を増加させ、次のメッセージへと移行。

			//選択音
			Audio::Start(1);
		}
	}
	else if (m_time <= 0 || m_fast_f == true)
	{
		//▽メッセージ表示処理
		//現在のメッセージが最後まで表示されていない場合、
		//m_timeにより、0.08秒毎にこの処理が実行される。
		//フォントデータに登録された文字から現在表示しようとしている文字に
		//当てはまるものを探し、見つかれば、適切な切り取り位置を返す。
		//※見つからなければ空白を返す。
		//※新たに文字を登録したい場合、
		//フォント画像を更新し、それに適応するようにフォントデータも更新すればOK。
		//※描画速度高速化フラグON時はm_time関係なしにこの処理に入る。


		//空白の処理
		if (m_font[m_progress][m_font_count] == L'＿')
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
		//フォントデータ読み込み処理
		//※空白でも改行でもない場合、フォントデータからの検索を開始する
		else
		{
			for (int i = 0; i < FONT_DATA_Y; i++)
			{
				for (int j = 0; j < FONT_DATA_X; j++)
				{
					//フォントデータの端部に到達すると、次の行に移る処理
					if (m_font_data[i][j] == NULL)
					{
						break;
					}
					//検索HITしたら、その切り取り位置を代入する
					else if (m_font[m_progress][m_font_count] == m_font_data[i][j])
					{
						m_font_column[m_font_count] = j + 1;
						m_font_line[m_font_count] = i + 1;

						break;
					}
				}

				//検索終了していれば、フォントデータ読み込み処理から抜ける
				if (m_font_column[m_font_count] != 0 || m_font_line[m_font_count] != 0)
				{
					break;
				}
			}
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

	//メッセージウインドウ描画位置情報配列
	float window_pos_y[2] = { 480.0f,20.0f };
	
	//矢印サイズ情報管理配列
	float arrow_size[2] = { 0.0f,64.0f };
	
	//矢印角度情報管理配列
	float arrow_angle[4] = { 0.0f,180.0f,90.0f,270.0f };


	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };//フォント画像用
	float blackout[4] = { 1.0f,1.0f,1.0f,0.5f };//画面全体やや暗転画像用
	float orange[4] = { 1.0f,0.5f,0.0f,1.0f };//山田文字画像用

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼m_swing_vecの値を増減させる処理
	//※常にこの処理は実行されている。
	//その為、この変数を描画位置等に組み込むと
	//往復アニメーションさせる事が出来るという訳である。

	//角度加算
	m_swing_r += 2.0f;

	//360°で初期値に戻す
	if (m_swing_r > 360.0f)
	{
		m_swing_r = 0.0f;
	}

	//移動方向
	m_swing_vec = sin(3.14f / 90 * m_swing_r);

	//速度付ける
	m_swing_vec *= 10.0f;



	//▼画面全体やや暗転画像
	if (m_black_out_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 700.0f;
		Draw::Draw(5, &src, &dst, blackout, 0.0f);
	}

	//▽ウインドウ表示左上 
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 790.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 230.0f;
	dst.m_right = 540.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▽ウインドウ表示左下
	src.m_top = 30.0f;
	src.m_left = 800.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 230.0f;
	dst.m_right = 540.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▽ウインドウ表示中央上 
	src.m_top = 0.0f;
	src.m_left = 1600.0f;
	src.m_right = 2400.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 530.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▽ウインドウ表示中央下 
	src.m_top = 5.0f;
	src.m_left = 2400.0f;
	src.m_right = 3200.0f;
	src.m_bottom = 800.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 540.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▼ウインドウ右上
	src.m_top = 0.0f;
	src.m_left = 4000.0f;
	src.m_right = 4800.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 860.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▼ウインドウ右下
	src.m_top = 5.0f;
	src.m_left = 4801.0f;
	src.m_right = 5600.0f;
	src.m_bottom = 800.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 850.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//▼山田ウインドウ表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 20.0f;
	dst.m_right = 220.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(3, &src, &dst, d, 0.0f);

	//▼山田表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 160.0f;
	src.m_bottom = 240.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 20.0f;
	dst.m_left = 40.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 180.0f;
	Draw::Draw(4, &src, &dst, d, 0.0f);

	//▼山田文字画像表示
	FontDraw(L"山田", 255.0f, window_pos_y[m_is_top_or_bottom] + 8.0f, 36.0f, 36.0f, orange, false);

	//▼クリック催促画像
	if (m_reminder_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 240.0f;

		dst.m_top = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * m_font_draw_y[m_font_count]) + m_swing_vec;
		dst.m_left = 255.0f + (FONT_DRAW_SIZE * m_font_draw_x[m_font_count]);
		dst.m_right = 255.0f + (FONT_DRAW_SIZE * (m_font_draw_x[m_font_count] + 1));
		dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * (m_font_draw_y[m_font_count] + 1)) + m_swing_vec;
		Draw::Draw(4, &src, &dst, d, 0.0f);
	}

	//▼矢印表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 64.0f;

	if (m_arrow_angle_f <= 1)//上、下向き
	{
		dst.m_top = m_arrow_y + m_swing_vec;
		dst.m_left = m_arrow_x;
		dst.m_right = arrow_size[m_arrow_display_f] + m_arrow_x;
		dst.m_bottom = arrow_size[m_arrow_display_f] * 2.0f + m_arrow_y + m_swing_vec;
	}
	else					 //左、右向き
	{
		dst.m_top = m_arrow_y;
		dst.m_left = m_arrow_x + m_swing_vec;
		dst.m_right = arrow_size[m_arrow_display_f] + m_arrow_x + m_swing_vec;
		dst.m_bottom = arrow_size[m_arrow_display_f] * 2.0f + m_arrow_y;
	}
	Draw::Draw(6, &src, &dst, d, arrow_angle[m_arrow_angle_f]);


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

			dst.m_top = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * m_font_draw_y[i]);
			dst.m_left = 255.0f + (FONT_DRAW_SIZE * m_font_draw_x[i]);
			dst.m_right = 255.0f + (FONT_DRAW_SIZE * (m_font_draw_x[i] + 1));
			dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * (m_font_draw_y[i] + 1));

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

			Draw::Draw(121, &src, &dst, m_font_color[i], 0.0f);
		}
	}

	//デバッグ用仮マウス位置表示
	wchar_t mou[256];
	swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
