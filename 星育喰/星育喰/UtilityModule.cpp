//使用するヘッダー
#include <math.h>   //数学計算ヘッダー
#include <time.h>
#include "GameL\DrawTexture.h"
#include "UtilityModule.h"

#include "Gamehead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define FONT_LENGTH_MAX (256)	//フォントにて表示可能な文字限界数(この値を越える文字数は正常に処理されない)
#define WIDTH_DATA_NUM (10)		//半角全角データ情報の数

//▼FontDraw、NumConversion関数で使用する変数
wchar_t con_num[FONT_LENGTH_MAX] = {};	//int→wchar_tに変換した情報管理配列
wchar_t font[FONT_LENGTH_MAX] = {};		//フォント情報管理配列
int font_column[FONT_LENGTH_MAX] = {};	//フォント切り取り位置(列)
int font_line[FONT_LENGTH_MAX] = {};	//フォント切り取り位置(行)
int length = 0;							//文字列の長さを管理


bool UnitVec(float* vx, float* vy)
{
	//ベクトルの長さを求める(三平方の定理)
	float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);

	//長さが0かどうか調べる
	if (r == 0.0f)
	{
		//0なら計算失敗
		return false;
	}
	else
	{
		//正規化しvxとvyに格納
		(*vx) = 1.0f / r*(*vx);
		(*vy) = 1.0f / r*(*vy);
	}
	//計算成功
	return true;
}

//---CheckWindow関数
//引数 float pos_x    :領域外か調べるx位置
//引数 float pos_y    :領域外か調べるy位置
//引数 float window_x :領域のtop位置
//引数 float window_y :領域のleft位置
//引数 float window_w  :領域のright位置
//引数 float window_h  :領域のbottom位置
//戻り値 bool
//領域内かどうか調べる位置pos_(x,y)がwindow_(xywh)の中か外か調べる
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//領域チェック
	if (pos_x < window_x)
	{
		return false;   //領域外
	}
	if (pos_x > window_w)
	{
		return false;   //領域外
	}
	if (pos_y < window_y)
	{
		return false;   //領域外
	}
	if (pos_y > window_h)
	{
		return false;   //領域外
	}

	return true;       //領域外
}

//---GetAtan2Angle関数
//引数1 float w　　：幅
//引数2 float h　　：高さ
//戻り値float 　　 ：角度(0°～　360°)
//内容
//高さと幅から直角三角形があると仮定し角度を求める。
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180° ～-0°　を　180°～360°に変換
	if (r < 0)
	{
		r = 360 - fabs(r);
	}
	return r;
}

//---GetPodEffec関数
//引数1 int*   ani;     爆発アニメーション
//引数1 int*   ani_time;爆発アニメーション間隔タイム
//引数1 bool   del;     削除チェック(true=着弾エフェクト false=普通の弾丸)
//引数1 int   timing    間隔区間RECT
//戻り値 RECT_F eff;    描画するRECT
//delで弾丸のRECTや着弾effectのRECT(アニメーションのRECT)を返す
RECT_F GetPodEffec(int* ani, int* ani_time, bool del, int timing)
{
	//返すRECT情報
	RECT_F rect;

	//ブラグで通常弾眼科着弾アニメーション処理分岐
	if (del == true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[20] =
		{
			{ 0,   0, 128,128 },
			{ 0, 128, 256,128 },
			{ 0, 256, 384,128 },
			{ 0 ,384, 512,128 },
			{ 0, 512, 640,128 },
			{ 0, 640, 768,128 },
			{ 0, 768, 896,128 },
			{ 0, 896,1024,128 },
			{ 0,1024,1152,128 },
			{ 0,1152,1280,128 },
			{ 0,1280,1408,128 },
			{ 0,1408,1536,128 },
			{ 0,1536,1664,128 },
			{ 0,1664,1792,128 },
			{ 0,1792,1920,128 },
			{ 0,1920,2048,128 },
			{ 0,2048,2176,128 },
			{ 0,2176,2304,128 },
			{ 0,2304,2432,128 },
			{ 0,2432,2560,128 },
		};
		//アニメーションのコマ間隔
		if (*ani_time > timing)
		{
			*ani += 1;     //アニメーションのコマを一つ進める
			*ani_time = 0;
		}
		else
		{
			*ani_time += 1;
		}

		rect = ani_src[*ani];//アニメーションのRECT配列からm_ani番目のRECT情報を渡す
	}
	else
	{
		//弾丸はアニメーション無し
		//リソース弾丸位置
		RECT_F bullet = { 0.0f,0.0f,0.0f,0.0f };
		rect = bullet;
	}

	return rect;
}

//n_min = 最小値
//n_max = 最大値
//最大と最小の差で、作られる乱数の幅を決める。
int Rand(int n_min, int n_max)
{
	n_max = (n_max + 1) - n_min;
	srand((unsigned int)time(NULL));
	return rand() % n_max + n_min;
}


//---FontDraw関数
//引数1　wchar_t *str	:出力したい文字入力場所
//引数2　float x		:フォント表示位置X
//引数3  float y		:フォント表示位置Y
//引数4  float x_size	:フォントのサイズX(横幅)
//引数5  float y_size	:フォントのサイズY(縦幅)
//引数6  float color[4]	:フォントカラー&透過度(RGBA)
//引数7  bool  right_alignment :[true:右詰め　false:左詰め]
//▼内容
//*strに入力された文字(wchar_t)をフリーフォント画像と照らし合わせ、フリーフォント化し、
//x,y,x_size,y_size,color[4]の情報に従い、フリーフォント化した文字を出力する関数。
//※入力する文字は必ず全角文字を用いる事。
//半角文字、フォントデータに登録されてない文字等は使用不可なので注意。(入力すると空白扱いとなる)
//また、読み込み番号121番に白文字集.pngの画像が無ければ正常に動作しないので注意。
void FontDraw(wchar_t *str, float x, float y, float x_size, float y_size, float color[4], bool right_alignment)
{
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
		{ L'わ',L'を',L'ん',L'ワ',L'ヲ',L'ン',L'プ',L'ッ' },
		{ L'×',L'※',L'：',L'＋',L'－',L'…',L'。',L'！',L'？',L'、',L'＆',L'．',L'＝',L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９',L'一',L'二',L'三',L'四',L'五',L'六',L'七',L'八',L'九',L'零' },
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

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼文字の終わり部分に印(；)をつける
	swprintf_s(font, L"%s；", str);

	//▼文字化した文字列の長さを取得	
	for (int i = 0; font[i] != L'；'; i++)
	{
		length = i + 1;
	}

	//▼フォント表示処理
	//文字列の長さ(文字の数)分、フォント表示処理を行う
	//※フォント１つ１つをfor文で文字の総数分回して、表示している。
	for (int i = 0; i <= length; i++)
	{
		//▼フォントデータ読み込み処理
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
				else if (font[i] == font_data[j][k])
				{
					font_column[i] = k + 1;
					font_line[i] = j + 1;

					break;//検索HITしたので、フォントデータ読み込み処理から抜ける
				}
			}

			//検索終了していれば、フォントデータ読み込み処理から抜ける
			if (font_column[i] != 0 || font_line[i] != 0)
			{
				break;
			}
		}

		//▼フォント表示処理
		src.m_top = FONT_CLIP_SIZE * (font_line[i] - 1);
		src.m_left = FONT_CLIP_SIZE * (font_column[i] - 1);
		src.m_right = FONT_CLIP_SIZE * font_column[i];
		src.m_bottom = FONT_CLIP_SIZE * font_line[i];

		dst.m_top = y;

		//右詰めの処理
		if (right_alignment == true)
		{
			dst.m_left = x + (x_size * i) - (x_size * (length - 1));
			dst.m_right = x + (x_size * (i + 1)) - (x_size * (length - 1));
		}
		//左詰めの処理
		else
		{
			dst.m_left = x + (x_size * i);
			dst.m_right = x + (x_size * (i + 1));
		}

		dst.m_bottom = y + (y_size);

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

	//フォント切り取り位置(列、行)を初期化する
	for (int i = 0; i <= length; i++)
	{
		font_column[i] = 0;
		font_line[i] = 0;
	}
}

//---NumConversion関数
//引数1　unsigned int 	:文字(wchar_t)化したい数値(int)の入力場所
//▼内容
//int型の数値をwchar_t型に変換、その後半角→全角化し、FontDrawで使えるようにする関数。
//※FontDrawと一緒に使う事を想定して作成した。
//
//▽使用する際の注意点
//数値はunsigned intの記憶範囲(0～4294967295)の値とする事。
//マイナス値だったり、少数であったりと、
//unsigned intが記憶できない値を入力すると、正常に処理されないので注意。
//
//▽実際の使用例
//FontDraw(NumConversion(1234), 20, 50, 25, 50, d, false);
//
//▽使用タイミング例
//武器ポッドウインドウの必要資材数、各施設のレベルアップに必要なHP等といった、
//数値が変動する部分のフリーフォント描画に使用すべし。
//※そもそもこの関数は、この部分のプログラムを楽にする為に作成したものである。
wchar_t* NumConversion(unsigned int conversion)
{
	//数字の半角全角データ情報
	//※半角→全角に変換の際に使用。
	wchar_t halfwidth_data[WIDTH_DATA_NUM] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };
	wchar_t fullwidth_data[WIDTH_DATA_NUM] = { L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９' };



	//▼数字(unsigned int)→文字(wchar_t)化処理
	//※ついでに文字の終わり部分に印(；)をつける
	swprintf_s(con_num, L"%u；", conversion);

	//▼文字化した文字列の長さを取得	
	for (int i = 0; con_num[i] != L'；'; i++)
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
			if (con_num[i] == halfwidth_data[j])
			{
				con_num[i] = fullwidth_data[j];

				break;//全角データ入ったので、半角→全角変換処理から抜ける
			}
		}
	}

	return con_num;
}