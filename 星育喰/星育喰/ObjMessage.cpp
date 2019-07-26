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

	m_count = 0;

	m_arrow_display_f = 0;
	m_arrow_angle_f = 0;
	m_arrow_x = 0.0f;
	m_arrow_y = 0.0f;
	
	m_swing_vec = 0.0f;
	m_swing_r = 0.0f;

	m_black_out_a = 0.0f;
	m_black_out_f = false;
	m_reminder_f = false;
	m_is_top_or_bottom = 0;

	m_message_window_num = 0;
	m_yamada_window_num = 0;
	m_black_out_num = 0;

	m_run_switch = false;


	//フォントデータ情報
	//※配列位置がそのまま切り取り位置となる為、フォント画像の配置と同じように文字登録するように。
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'あ',L'い',L'う',L'え',L'お',L'ア',L'イ',L'ウ',L'エ',L'オ',L'蓄',L'積',L'パ',L'動',L'源',L'弾',L'話',L'理',L'由',L'原' },
		{ L'か',L'き',L'く',L'け',L'こ',L'カ',L'キ',L'ク',L'ケ',L'コ',L'が',L'ぎ',L'ぐ',L'げ',L'ご',L'ガ',L'ギ',L'グ',L'ゲ',L'ゴ' },
		{ L'さ',L'し',L'す',L'せ',L'そ',L'サ',L'シ',L'ス',L'セ',L'ソ',L'ざ',L'じ',L'ず',L'ぜ',L'ぞ',L'ザ',L'ジ',L'ズ',L'ゼ',L'ゾ' },
		{ L'た',L'ち',L'つ',L'て',L'と',L'タ',L'チ',L'ツ',L'テ',L'ト',L'だ',L'ぢ',L'づ',L'で',L'ど',L'ダ',L'ヂ',L'ヅ',L'デ',L'ド' },
		{ L'な',L'に',L'ぬ',L'ね',L'の',L'ナ',L'ニ',L'ヌ',L'ネ',L'ノ',L'因',L'量',L'追',L'語',L'抗',L'乱',L'搭',L'効',L'抜',L'群' },
		{ L'は',L'ひ',L'ふ',L'へ',L'ほ',L'ハ',L'ヒ',L'フ',L'ヘ',L'ホ',L'ば',L'び',L'ぶ',L'べ',L'ぼ',L'バ',L'ビ',L'ブ',L'ベ',L'ボ' },
		{ L'ま',L'み',L'む',L'め',L'も',L'マ',L'ミ',L'ム',L'メ',L'モ',L'熱',L'本',L'題',L'味',L'制',L'減',L'甲',L'質',L'訓',L'練' },
		{ L'や',L'ゆ',L'よ',L'ヤ',L'ユ',L'ヨ',L'取',L'補',L'足',L'基',L'凄',L'長',L'近',L'尽' },
		{ L'ら',L'り',L'る',L'れ',L'ろ',L'ラ',L'リ',L'ル',L'レ',L'ロ' },
		{ L'わ',L'を',L'ん',L'ワ',L'ヲ',L'ン',L'プ',L'ッ',L'確',L'認' },
		{ L'×',L'※',L'：',L'＋',L'－',L'…',L'。',L'！',L'？',L'、',L'＆',L'．',L'＝',L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９',L'一',L'二',L'三',L'四',L'五',L'六',L'七',L'八',L'九',L'零' },
		{ L'今',L'日',L'人',L'類',L'統',L'括',L'山',L'田',L'先',L'敵',L'惑',L'星',L'情',L'報',L'不',L'意',L'打',L'喰',L'前',L'行',L'鉄',L'木',L'／',L'達',L'互',L'生',L'存',L'合',L'弱',L'肉',L'名',L'─' },
		{ L'聞',L'強',L'来',L'思',L'準',L'備',L'越',L'手',L'入',L'見',L'攻',L'撃',L'傾',L'向',L'戦',L'闘',L'必',L'殺',L'技',L'持',L'捕',L'食',L'奪',L'両',L'Ｈ',L'Ｐ',L'何',L'ポ',L'受',L'与' },
		{ L'直',L'結',L'負',L'無',L'気',L'仕',L'方',L'下',L'出',L'押',L'命',L'令',L'住',L'最',L'初',L'回',L'目',L'時',L'間',L'属',L'性',L'消',L'去',L'完',L'了',L'以',L'降' },
		{ L'有',L'利',L'不',L'利',L'赤',L'青',L'緑',L'灰',L'色',L'対',L'等',L'察',L'簡',L'単',L'活',L'用',L'数',L'字',L'上',L'真',L'中',L'線' },
		{ L'吸',L'寄',L'逆',L'自',L'分',L'同',L'士',L'引',L'力',L'衝',L'突',L'大',L'小',L'宇',L'宙',L'常',L'識',L'覚',L'習',L'慣',L'考' },
		{ L'素',L'材',L'移',L'所',L'配',L'置',L'便',L'番',L'最',L'高',L'体',L'成',L'果',L'勝',L'昇',L'多',L'書',L'材',L'限',L'後' },
		{ L'次',L'獲',L'得',L'集',L'切',L'札',L'乗',L'詳',L'内',L'容',L'説',L'明',L'欲',L'把',L'握',L'残',L'秘',L'訣',L'油',L'断',L'優',L'始',L'っ',L'例',L'ー',L'ペ',L'ェ',L'ャ' },
		{ L'方',L'法',L'教',L'育',L'画',L'面',L'研',L'究',L'民',L'術',L'耐',L'久',L'増',L'員',L'割',L'振',L'再',L'産',L'早',L'武',L'器',L'ゃ',L'使',L'左',L'右',L'通' },
		{ L'製',L'作',L'実',L'際',L'度',L'当',L'滅',L'表',L'示',L'少',L'遅',L'戻',L'兵',L'舎',L'化',L'他',L'資',L'飛',L'相',L'的',L'込',L'文',L'射',L'言',L'低',L'代',L'可',L'視' },
		{ L'参',L'加',L'割',L'振',L'分',L'中',L'色',L'出',L'撃',L'要',L'注',L'条',L'件',L'載',L'倉',L'庫',L'装',L'現',L'在',L'旦',L'定',L'呼',L'白',L'選',L'択',L'状',L'態',L'況' },
		{ L'発',L'展',L'黒',L'整',L'物',L'光',L'銀',L'河',L'盛',L'奇',L'跡',L'朗',L'報',L'帯',L'安',L'心',L'休',L'遊',L'暗',L'奴',L'ピ',L'応',L'防',L'御',L'第',L'操',L'削',L'能' },
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
	//「～」……文章途中のクリック要求
	//「｜」……メッセージ表示機能停止
	//※全てのメッセージ終了後、
	//またはメッセージ途中にプレイヤーに
	//何か操作させたい時にこの全角文字を書いて下さい。

	//自分の惑星名(テスト用)
	wchar_t strr[20] = L"でふおると";

	//○○画面メッセージ文設定＆画像登録番号設定
	//if (m_Scene_id == 30)
	//{
	//	swprintf_s(m_font[1], L"");
	//	swprintf_s(m_font[2], L"", strr);
	//	swprintf_s(m_font[3], L"");
	//	swprintf_s(m_font[4], L"");
	//	swprintf_s(m_font[5], L"");
	//	swprintf_s(m_font[6], L"");
	//	swprintf_s(m_font[7], L"");
	//	swprintf_s(m_font[8], L"");
	//	swprintf_s(m_font[9], L"");
	//	swprintf_s(m_font[10], L"");
	//	swprintf_s(m_font[11], L"");
	//	swprintf_s(m_font[12], L"");
	//	swprintf_s(m_font[13], L"");


	//	swprintf_s(m_font[0], L"ＲあかあかＢきくＧきく＿かうい～かかかかかかかかきなきなにあ￥にあまむまむ￥テスト１２３￥２１３２３１２￥１３１２１３２");//メッセージ１
	//	swprintf_s(m_font[1], L"あいうかきく１２３今日人類発展");	//メッセージ２
	//	swprintf_s(m_font[2], L"テスト：%s：テスト",strr);		//メッセージ３
	//	swprintf_s(m_font[3], L"｜");					//メッセージ４
	//	swprintf_s(m_font[4], L"うか１２２２３");		//メッセージ５
	//	swprintf_s(m_font[5], L"｜");					//メッセージ６

	//	m_message_window_num = 2;
	//	m_yamada_window_num = 3;
	//	m_black_out_num = 5;
	//}
	//ホーム画面1回目メッセージ文設定＆画像登録番号、グローバル変数設定
	if (m_Scene_id == 0)
	{
		swprintf_s(m_font[0], L"よう。￥今日から%s星、人類統括になった山田だ。", strr);
		swprintf_s(m_font[1], L"%s、生まれたてでいきなりなんだが￥敵惑星が攻めてくるって情報が入ったぜ。", strr);
		swprintf_s(m_font[2], L"不意打ち食らう前に戦いに行こうぜ！");
		swprintf_s(m_font[3], L"｜");

		m_message_window_num = 6;
		m_yamada_window_num = 7;
		m_black_out_num = 8;

		g_is_operatable = false;//操作不能に(ObjMessageしか動かない)
		m_black_out_f = true;//徐々に暗転
	}
	//戦闘準備画面1回目メッセージ文設定＆画像登録番号、グローバル変数設定
	else if (m_Scene_id == 1)
	{
		swprintf_s(m_font[1], L"これが例の敵惑星か。～￥攻めてくるって聞いたから、￥強いのが来るかと思ったけど￥思ってたよりもだいぶ弱そうだな！");
		swprintf_s(m_font[2], L"まあ弱そうだけど準備するに越したことはねえ！￥%s！￥敵惑星にマウスカーソルを合わせてみな！", strr);
		swprintf_s(m_font[3], L"｜");
		swprintf_s(m_font[4], L"よし、カーソルを合わせたな！～￥敵にカーソルを合わせると敵の情報が見れるぜ！￥手に入る資材や敵の攻撃傾向がわかるから￥戦う前にしっかりチェックしておけよ！");
		swprintf_s(m_font[5], L"あ、そうそう。￥敵の情報にオーバーワークって書いてあるだろ？～￥あれはスペシャル技といって、￥要は敵が持っている必殺技みたいなもんだ。");
		swprintf_s(m_font[6], L"今%sはスペシャル技を持ってはいないが￥敵を捕食すると敵が持っているスペシャル技を￥奪って使えるようになるからな。～￥じゃあ戦闘にいってみるか。",strr);
		swprintf_s(m_font[7], L"｜");

		m_message_window_num = 55;
		m_yamada_window_num = 89;
		m_black_out_num = 91;

		g_is_operatable = true;//操作可能に
		m_black_out_f = false;//明転状態から始める
	}
	//戦闘画面1回目メッセージ文設定＆画像登録番号、グローバル変数設定
	else if (m_Scene_id == 2)
	{
		swprintf_s(m_font[1], L"戦闘が始まったな。");
		swprintf_s(m_font[2], L"右が見てわかる通り%sだな。",strr);	
		swprintf_s(m_font[3], L"それで左が敵の惑星だ。");
		swprintf_s(m_font[4], L"両方の惑星の下に緑色のバーがあるだろ？～￥この下のバーが惑星のＨＰゲージになってるぜ。");
		swprintf_s(m_font[5], L"ＨＰゲージは惑星のサイズに直結していて、￥このゲージがゼロになると￥戦いに負けてしまうからな。～￥ＨＰゲージが無くならないように気をつけろよ。");
		swprintf_s(m_font[6], L"次は戦闘の仕方についてだな。");
		swprintf_s(m_font[7], L"下に五つのボタンがあるだろ？");
		swprintf_s(m_font[8], L"この内の右の四つのボタンのどれかを押してみろ。");
		swprintf_s(m_font[9], L"｜");
		swprintf_s(m_font[10], L"ボタンを押したら何か出てきたろ？￥これがポッドだぜ。～￥ボタンを押すと１００人の住人が命令を受けて、￥ポッドに乗り込み、攻撃しに行っているんだ。");
		swprintf_s(m_font[11], L"最初は準備しているから￥すぐに出撃することができるが、￥二回目以降は準備に時間がかかるから気をつけろよ。");
		swprintf_s(m_font[12], L"ポッドには属性があって有利不利があるんだ。～￥赤色は緑色に強く緑は青に強いそして青は赤に強い、￥灰色はすべての色に対して少し強いが￥ミサイルに対してはすごく弱い……ってかんじでな。");
		swprintf_s(m_font[13], L"ポッドは惑星に当たるとダメージを与えて、￥惑星のサイズをちっさくできるぜ。～￥敵も攻撃をしてくるから敵の攻撃に合わせて￥ポッドを出撃させるのも手だな。");				
		swprintf_s(m_font[14], L"次はミサイルについての説明だ。");
		swprintf_s(m_font[15], L"このボタンを押してみな。");
		swprintf_s(m_font[16], L"｜");
		swprintf_s(m_font[17], L"察しの通り、ミサイルが発射されるぜ。");
		swprintf_s(m_font[18], L"ミサイルは簡単に言うとジャブみたいなもんだ。～￥ポッドと同じでダメージを与えることができるが￥攻撃力が低い。");
		swprintf_s(m_font[19], L"ただその代わりに、￥ポッドよりも準備する時間が早いから￥うまいこと活用してくれ！");
		swprintf_s(m_font[20], L"ちなみにポッドもミサイルも￥ボタンの下に書いている数字を押しても￥命令できるぜ。");
		swprintf_s(m_font[21], L"真ん中に三つの線があるだろ？～￥この線はポッドやミサイルの￥発射線を可視化したものだぜ。～￥オレ達はこの線のことをレーンって呼んでる。");
		swprintf_s(m_font[22], L"んで、このレーンの一番上をクリックしてくれ。");
		swprintf_s(m_font[23], L"｜");
		swprintf_s(m_font[24], L"クリックしたレーンが他よりも白くなっているだろ？～￥これがレーン選択ができた状態だ。");
		swprintf_s(m_font[25], L"さっきのポッドやミサイルは￥選択レーン上に射出されるから￥状況に応じてレーンを選んで戦っていけよ。");
		swprintf_s(m_font[26], L"ただし同じレーンで、￥ミサイルやポッドを撃ちすぎると￥ポッドの防御力が下がっちまうデメリットがある。");
		swprintf_s(m_font[27], L"ポッドやミサイルを撃つ度に￥レーンの色が赤くなってるだろ？～￥それはこのデメリット度合いを表してるってわけだ。");
		swprintf_s(m_font[28], L"要は赤くなればなるほど￥ポッドの防御力が下がってヤバいってことだな。");
		swprintf_s(m_font[29], L"このデメリットは￥他のレーンにポッドやミサイルを出撃させていけば￥次第にそのレーンでの￥ポッド防御力がもとに戻るぜ。");
		swprintf_s(m_font[30], L"要は同じレーンに撃ちつづけるのは￥やめた方がいいってことだぜ。");
		swprintf_s(m_font[31], L"あ、ちなみにレーン選択は￥方向キーの上下でも操作できるからな。");
		swprintf_s(m_font[32], L"さて、これが戦闘最後の説明だ。");
		swprintf_s(m_font[33], L"画面上に時間が表示されてるだろ？～￥この時間は惑星同士が引力で引き合って￥衝突するまでの大体の時間だぜ。");
		swprintf_s(m_font[34], L"時間切れになって衝突したら、￥惑星のサイズが大きい方が小さい方を捕食するぜ。～￥これがこの宇宙の常識だから覚えとけよ。");
		swprintf_s(m_font[35], L"まあ習うより慣れろだな。～￥ここからは自分で考えて戦ってみな。￥Ｒ※クリックで戦闘が始まります。");
		swprintf_s(m_font[36], L"｜");
		swprintf_s(m_font[38], L"時間切れにならなくても￥敵惑星の体力を削りきると￥惑星が吸い寄せられて捕食できるぜ。～￥逆に削りきられると自分が食われちまうからな。");
		swprintf_s(m_font[39], L"｜");
		swprintf_s(m_font[42], L"よし！戦いに勝って捕食することができたな。～￥捕食すると能力や素材を奪うことができるんだ。￥最高だろ？～￥さて今回の成果を見ていこうぜ。");
		swprintf_s(m_font[43], L"一番上が%sに移住した住人の数だな。～￥こいつらは兵士や研究員にしたりと￥色んな所に配置できるから便利だぜ。",strr);
		swprintf_s(m_font[44], L"二番目に書いているのは惑星を食べたことで￥どれだけ%sの最大ＨＰが￥上昇したかを表す数字だな。",strr);
		swprintf_s(m_font[45], L"ＨＰがあればあるほど￥戦いは負けにくくなるから、￥多いに越したことはねえな。");
		swprintf_s(m_font[46], L"その下は獲得した資材のことを書いてあるぜ。～￥まあ今回は資材を獲得できなかったみたいだけどな。～￥次からの戦いからは集められる資材のことも考えろよ。￥資材は有限だからな。");
		swprintf_s(m_font[47], L"これが最後だな。￥スペシャル技ってやつだ。￥名前がダサいのは気にすんな。");
		swprintf_s(m_font[48], L"これは戦闘においての切り札みたいなもんで￥ピンチを乗り切ったりすることができるぜ。～￥またあとで詳しく説明してやるよ。");
		swprintf_s(m_font[49], L"説明はこんなもんだな。～￥自分が何が欲しいかをしっかり把握して￥どの敵と戦うかを考えていくのが￥これから生き残っていく秘訣だぜ。");
		swprintf_s(m_font[50], L"｜");

		m_message_window_num = 33;
		m_yamada_window_num = 79;
		m_black_out_num = 20;

		g_is_operatable = true;//操作可能に
		m_black_out_f = false;//明転状態から始める
	}
	//ホーム画面2回目メッセージ文設定＆画像登録番号、グローバル変数設定
	if (m_Scene_id == 7)
	{
		swprintf_s(m_font[0], L"戦いに勝ててよかったぜ。￥……だけど油断はするなよ。￥この宇宙は弱い奴には優しくないからな。");
		swprintf_s(m_font[1], L"これからも戦いに勝っていくためには、￥自分を強くすることも大切だぜ！～￥……ってことで強くなる方法を教えてやるぜ！");
		swprintf_s(m_font[2], L"｜");

		m_message_window_num = 6;
		m_yamada_window_num = 7;
		m_black_out_num = 8;

		g_is_operatable = false;//操作不能に(ObjMessageしか動かない)
		m_black_out_f = true;//徐々に暗転
	}
	//育成画面メッセージ文設定＆画像登録番号、グローバル変数設定
	else if (m_Scene_id == 8)
	{
		swprintf_s(m_font[0], L"んじゃ、さっそく説明していくぜ。");
		swprintf_s(m_font[1], L"まずはここをクリックしてみな。");
		swprintf_s(m_font[2], L"｜");
		swprintf_s(m_font[3], L"テスト");
		swprintf_s(m_font[4], L"");
		swprintf_s(m_font[5], L"");
		swprintf_s(m_font[6], L"");
		swprintf_s(m_font[7], L"");

		m_message_window_num = 21;
		m_yamada_window_num = 20;
		m_black_out_num = 135;

		g_is_operatable = false;//操作不能に(ObjMessageしか動かない)
		m_black_out_f = false;//明転状態から始める

		//メッセージウインドウ位置変更
		m_is_top_or_bottom = 1;
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

	//メッセージ表示機能動作中の処理
	if (m_run_switch == true)
	{
		//▼戦闘画面1回目
		if (m_Scene_id == 2 && m_progress == 2)
		{
			m_black_out_f = false;//徐々に明転

			//戦闘処理を一時停止させる
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(false);

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 915.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 3)
		{
			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 225.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 4 || m_progress == 5))
		{
			//メッセージウインドウ位置変更
			m_is_top_or_bottom = 1;

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_y = 480.0f;

			m_count++;//時間計測

			if (m_count >= 240)
			{
				m_count = 0;//m_countを初期化
			}
			else if (m_count >= 120)
			{
				m_arrow_x = 225.0f;
			}
			else
			{
				m_arrow_x = 915.0f;
			}
		}
		else if (m_Scene_id == 2 && m_progress == 6)
		{
			m_black_out_f = true;//徐々に暗転

			//矢印非表示
			m_arrow_display_f = 0;
			m_arrow_angle_f = 0;
			m_arrow_x = 0.0f;
			m_arrow_y = 0.0f;
			
			m_count = 0;//m_countを初期化
		}
		else if (m_Scene_id == 2 && m_progress == 8)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 455.0f + m_swing_r * 1.5;
			m_arrow_y = 410.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 12)
		{
			m_black_out_f = false;//徐々に明転

			//メッセージウインドウ位置変更
			m_is_top_or_bottom = 0;

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 250.0f;
			m_arrow_y = 50.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 13)
		{
			m_black_out_f = true;//徐々に暗転

			//矢印非表示
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 14)
		{
			//メッセージウインドウ位置変更
			m_is_top_or_bottom = 1;
		}
		else if (m_Scene_id == 2 && m_progress == 15)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 220.0f;
			m_arrow_y = 410.0f;

			g_is_operatable = true;//操作可能にする
		}
		else if (m_Scene_id == 2 && m_progress == 21)
		{
			//メッセージウインドウ位置変更
			m_is_top_or_bottom = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 22)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 557.5f;
			m_arrow_y = 80.0f;

			g_is_operatable = true;//操作可能にする
		}
		else if (m_Scene_id == 2 && m_progress == 33)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 553.5f;
			m_arrow_y = 100.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 34)
		{
			m_black_out_f = true;//徐々に暗転

			//矢印非表示
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 43)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 880.0f;
			m_arrow_y = 185.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 44 || m_progress == 45))
		{
			//矢印表示
			m_arrow_y = 235.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 46)
		{
			//矢印表示
			m_arrow_x = 550.0f;
			m_arrow_y = 310.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 47 || m_progress == 48))
		{
			//メッセージウインドウ位置変更
			m_is_top_or_bottom = 1;

			//矢印表示
			m_arrow_x = 1030.0f;
			m_arrow_y = 435.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 49)
		{
			m_black_out_f = true;//徐々に暗転

			//矢印非表示
			m_arrow_display_f = 0;
		}


		//▼育成画面
		else if (m_Scene_id == 8 && m_progress == 1)
		{
			m_black_out_f = false;//徐々に明転

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 140.0f;
			m_arrow_y = 520.0f;

			g_is_operatable = true;//操作可能に
		}
	}
	//▼メッセージ表示機能が停止した時の処理
	//※メッセージ表示機能停止時はこの処理の中に入り、
	//この処理以降の処理は実行されない。
	//特にこの処理の中に何か書き込まなければ、
	//メッセージ表示機能が再び動作状態になる事はない。
	//再び動作状態にしたい場合、条件を満たした時に
	//「m_progress++」「m_run_switch = true」する事で動作させる事が出来る。
	//※「m_progress++」する意味は、メッセージ進行度を次に進めないと、
	//また「｜」が読み込まれてしまうため。
	else if (m_run_switch == false)
	{
		//▼ホーム画面1回目
		if (m_Scene_id == 0 && m_progress == 0)
		{
			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
			}
		}
		else if (m_Scene_id == 0 && m_progress == 3)
		{
			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 1050.0f;
			m_arrow_y = 340.0f;

			g_is_operatable = true;//操作可能に
			m_black_out_f = false;//画面明転
			g_tutorial_progress = 1;//チュートリアル進行度を1にする

			if (980 < m_mou_x && m_mou_x < 1180 && 480 < m_mou_y && m_mou_y < 680 && m_mou_l == true)
			{
				m_arrow_display_f = 0;//喰ボタンクリックされたら矢印非表示
				m_progress = 4;//進行度上昇させてこの処理から抜ける
			}
		}


		//▼戦闘準備画面1回目
		else if (m_Scene_id == 1 && m_progress == 1)
		{
			m_black_out_f = true;//徐々に暗転
			
			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
			}
		}
		else if (m_Scene_id == 1 && m_progress == 3)
		{
			if (426 < m_mou_x && m_mou_x < 767 && 123 < m_mou_y && m_mou_y < 460 || m_arrow_display_f == 0 && m_arrow_angle_f == 2)
			{
				m_arrow_display_f = 0;//マウスカーソル合わさったら矢印非表示
				g_is_operatable = false;//操作不可に
				m_black_out_f = true;//画面暗転

				//完全暗転後、メッセージ処理開始
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//メッセージ表示機能動作開始
					m_progress = 4;//進行度上昇させてこの処理から抜ける
				}

				return;
			}

			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 800.0f;
			m_arrow_y = 250.0f;

			g_is_operatable = true;//操作可能に
			m_black_out_f = false;//画面明転
		}
		else if (m_Scene_id == 1 && m_progress == 7)
		{
			g_tutorial_progress = 2;//チュートリアル進行度を2にする
		}


		//▼戦闘画面1回目
		else if (m_Scene_id == 2 && m_progress == 1)
		{
			m_count++;//時間計測開始

			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
				m_count = 0;//m_countを初期化
			}
			//戦闘開始1秒後、画面暗転処理開始
			else if (m_count >= 60 * 1)
			{
				m_black_out_f = true;//画面暗転
			}
		}
		else if (m_Scene_id == 2 && m_progress == 9)
		{			
			//ポッドが何かしら１つ出れば、この処理に入る
			if (m_arrow_display_f == 0)
			{
				m_count++;//時間計測開始

				//完全暗転後、メッセージ処理開始
				if (m_black_out_a >= 0.5f)
				{
					//戦闘処理を一時停止させる
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//メッセージ表示機能動作開始
					m_count = 0;//m_countを初期化
					m_progress = 10;//進行度上昇させてこの処理から抜ける
				}
				//1秒後、画面暗転処理開始
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//画面暗転
				}

				return;
			}

			//ポッドボタンの範囲でクリックしたら処理に入る
			if (550 <= m_mou_y && m_mou_y <= 650)
			{
				if (500 <= m_mou_x && m_mou_x <= 600 || 650 <= m_mou_x && m_mou_x <= 750 || 800 <= m_mou_x && m_mou_x <= 900 || 950 <= m_mou_x && m_mou_x <= 1050)
				{
					if (m_mou_l == true)
					{
						g_is_operatable = false;//操作不能にする

						m_arrow_display_f = 0;//矢印非表示
					}
				}
			}

			//ポッド射出ボタンを押したら処理に入る
			if (Input::GetVKey('2') == true || Input::GetVKey(VK_NUMPAD2) == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}
			else if (Input::GetVKey('3') == true || Input::GetVKey(VK_NUMPAD3) == true) 
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}
			else if (Input::GetVKey('4') == true || Input::GetVKey(VK_NUMPAD4) == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}
			else if (Input::GetVKey('5') == true || Input::GetVKey(VK_NUMPAD5) == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}

			//矢印表示
			m_arrow_x = 455.0f + m_swing_r * 1.5;
			m_arrow_y = 410.0f;

			//戦闘処理を再開させる
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 3;//チュートリアル進行度を3に設定	
		}
		else if (m_Scene_id == 2 && m_progress == 16)
		{
			//ミサイルが１つ出れば、この処理に入る
			if (m_arrow_display_f == 0)
			{
				m_count++;//時間計測開始

				//完全暗転後、メッセージ処理開始
				if (m_black_out_a >= 0.5f)
				{
					//戦闘処理を一時停止させる
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//メッセージ表示機能動作開始
					m_count = 0;//m_countを初期化
					m_progress = 17;//進行度上昇させてこの処理から抜ける
				}
				//1秒後、画面暗転処理開始
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//画面暗転
				}

				return;
			}

			if (150 <= m_mou_x && m_mou_x <= 350 && 550 <= m_mou_y && m_mou_y <= 650 && m_mou_l == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}

			if (Input::GetVKey('1') == true || Input::GetVKey(VK_NUMPAD1) == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}

			//矢印表示
			m_arrow_x = 220.0f;
			m_arrow_y = 410.0f;

			//戦闘処理を再開させる
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 4;//チュートリアル進行度を4に設定	
		}
		else if (m_Scene_id == 2 && m_progress == 23)
		{
			//レーン選択出来れば、この処理に入る
			if (m_arrow_display_f == 0)
			{
				m_count++;//時間計測開始

				//完全暗転後、メッセージ処理開始
				if (m_black_out_a >= 0.5f)
				{
					//戦闘処理を一時停止させる
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//メッセージ表示機能動作開始
					m_count = 0;//m_countを初期化
					m_progress = 24;//進行度上昇させてこの処理から抜ける
				}
				//1秒後、画面暗転処理開始
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//画面暗転
				}
			}

			if (400 <= m_mou_x && m_mou_x <= 800 && 200 <= m_mou_y && m_mou_y <= 250 && m_mou_l == true)
			{
				g_is_operatable = false;//操作不能にする

				m_arrow_display_f = 0;//矢印非表示
			}

			//矢印表示
			m_arrow_x = 557.5f;
			m_arrow_y = 80.0f;

			//戦闘処理を再開させる
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 5;//チュートリアル進行度を5に設定	
		}
		else if (m_Scene_id == 2 && m_progress == 36)
		{
			m_black_out_f = false;//画面明転

			g_is_operatable = true;//操作可能にする

			//戦闘処理を再開させる
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 6;//チュートリアル進行度を6に設定	
		}
		else if (m_Scene_id == 2 && m_progress == 37)
		{
			m_black_out_f = true;//徐々に暗転

			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
				m_progress = 38;//進行度上昇させてこの処理から抜ける
			}
		}
		else if (m_Scene_id == 2 && m_progress == 39)
		{
			m_black_out_f = false;//画面明転

			//クリア画面表示
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetEnd();

			//戦闘音楽を破棄し勝利音楽再生
			Audio::Stop(0);
			Audio::Start(4);

			m_progress = 40;//進行度上昇させてこの処理から抜ける
		}
		else if (m_Scene_id == 2 && m_progress == 41)
		{
			m_black_out_f = true;//徐々に暗転

			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
				m_progress = 42;//進行度上昇させてこの処理から抜ける
			}
		}
		else if (m_Scene_id == 2 && m_progress == 50)
		{
			m_black_out_f = false;//徐々に明転

			g_tutorial_progress = 7;//チュートリアル進行度を7にする。
		}


		//▼ホーム画面2回目
		else if (m_Scene_id == 7 && m_progress == 0)
		{
			//完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
			}
		}
		else if (m_Scene_id == 7 && m_progress == 2)
		{
			//矢印表示
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 90.0f;
			m_arrow_y = 340.0f;

			g_is_operatable = true;//操作可能に
			m_black_out_f = false;//画面明転
			g_tutorial_progress = 8;//チュートリアル進行度を8にする

			if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680 && m_mou_l == true)
			{
				m_arrow_display_f = 0;//育ボタンクリックされたら矢印非表示
				m_progress = 3;//進行度上昇させてこの処理から抜ける
			}
		}


		//▼育成画面
		else if (m_Scene_id == 8 && m_progress == 0)
		{
			m_count++;//時間計測開始

			 //完全暗転後、メッセージ処理開始
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//メッセージ表示機能動作開始
				m_count = 0;//m_countを初期化
			}
			//1秒後、画面暗転処理開始
			else if (m_count >= 60 * 1)
			{
				m_black_out_f = true;//画面暗転
			}
		}
		else if (m_Scene_id == 8 && m_progress == 2)
		{
			if (120 < m_mou_x && m_mou_x <= 220 && 340 < m_mou_y && m_mou_y < 550 && m_mou_l == true || m_arrow_display_f == 0)
			{
				m_arrow_display_f = 0;//クリックされたら矢印非表示
				
				g_is_operatable = false;//操作不能に

				m_count++;//時間計測開始

				//完全暗転後、メッセージ処理開始
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//メッセージ表示機能動作開始
					m_count = 0;//m_countを初期化
					m_progress = 3;//進行度上昇させてこの処理から抜ける
				}
				//0.5秒後、画面暗転処理開始
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//画面暗転
				}

				return;
			}
		}


		//else if (m_Scene_id == 30 && m_progress == 3)
		//{
		//	if (Input::GetVKey('A') == true)
		//	{
		//		m_progress++;
		//		m_run_switch = true;
		//	}
		//}
		//else if (m_Scene_id == 1 && m_progress == 0)
		//{

		//}

		return;
	}

	//▼メッセージ表示機能停止処理
	//※「｜(メッセージ表示機能停止)」が書かれていれば、
	//この処理が実行される。
	if (m_font[m_progress][m_font_count] == L'｜')
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
	if (m_font[m_progress][m_font_count] == L'～')
	{
		m_reminder_f = true;//クリック催促画像表示

		//現在のメッセージが最後まで表示されていなくとも、
		//'～'を書けばクリックするまでメッセージを止める事が出来る。
		//この処理に入っている時に、左クリックする事でメッセージの続きが見れる。
		//※スキップフラグON時はクリックせずとも、勝手に処理が進む。
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			//現在のフォント描画位置Xをそのまま次のフォント描画位置Xに入れる
			//※'Ｒ'等の文字は内部処理の命令文であり、描画する訳ではないため。
			m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count];

			m_font_count++;	//表示しようとしている文字を次のフォント情報へ変更する


			m_fast_f = false;//描画速度高速化停止
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
			//※m_length + 1の理由は、クリック催促画像も下にずらしたいため。
			for (int i = m_font_count; i <= m_length + 1; i++)
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
	//メッセージウインドウ描画位置情報配列
	float window_pos_y[2] = { 480.0f,20.0f };
	
	//矢印サイズ情報管理配列
	float arrow_size[2] = { 0.0f,64.0f };
	
	//矢印角度情報管理配列
	float arrow_angle[4] = { 0.0f,180.0f,90.0f,270.0f };


	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };//フォント画像用
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };//画面全体やや暗転画像用
	float orange[4] = { 1.0f,0.5f,0.0f,1.0f };//山田文字画像用

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼画面徐々に暗転＆徐々に明転処理
	if (m_black_out_f == true)
	{
		if (m_black_out_a < 0.5f)
		{
			m_black_out_a += 0.01f;
		}
	}
	else
	{
		if (m_black_out_a > 0.0f)
		{
			m_black_out_a -= 0.01f;
		}
	}

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
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(m_black_out_num, &src, &dst, blackout, 0.0f);

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
	Draw::Draw(191, &src, &dst, d, arrow_angle[m_arrow_angle_f]);


	//▼メッセージ表示機能OFF時は以下のドロー処理を実行しない処理
	if (m_run_switch == false)
	{
		return;
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
	Draw::Draw(m_yamada_window_num, &src, &dst, d, 0.0f);

	//▼山田表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 160.0f;
	src.m_bottom = 240.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 20.0f;
	dst.m_left = 40.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 180.0f;
	Draw::Draw(190, &src, &dst, d, 0.0f);

	//▼山田文字画像表示
	FontDraw(L"山田", 255.0f, window_pos_y[m_is_top_or_bottom] + 8.0f, 36.0f, 36.0f, orange, false);

	//▼クリック催促画像
	if (m_reminder_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 36.0f;
		src.m_bottom = 35.0f;

		dst.m_top = window_pos_y[m_is_top_or_bottom] + 57.0f + (FONT_DRAW_SIZE * m_font_draw_y[m_font_count]) + m_swing_vec;
		dst.m_left = 264.0f + (FONT_DRAW_SIZE * m_font_draw_x[m_font_count]);
		dst.m_right = 246.0f + (FONT_DRAW_SIZE * (m_font_draw_x[m_font_count] + 1));
		dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 39.0f + (FONT_DRAW_SIZE * (m_font_draw_y[m_font_count] + 1)) + m_swing_vec;
		Draw::Draw(189, &src, &dst, d, 0.0f);
	}


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
	//wchar_t mou[256];
	//swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
