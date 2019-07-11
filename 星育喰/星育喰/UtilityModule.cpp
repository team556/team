//使用するヘッダー
#include <math.h>   //数学計算ヘッダー
#include <time.h>
#include "GameL\DrawTexture.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

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
		RECT_F ani_src[4] =
		{
			{ 0, 0, 32,29 },
			{ 0,32, 64,29 },
			{ 0,64, 96,29 },
			{ 0,96,128,29 },
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
		RECT_F bullet = { 0.0f,96.0f,126.0f,32.0f };
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




//▼以下はフォント表示を関数化して使いやすくしようと思ったものの、
//想定外の事態が重なり、関数化断念に至ったプログラムである。
//ただ、もしかすると余裕が出来た時に、このプログラムの続きをやる可能性は
//ゼロとは言い難いので、一旦コメントアウト状態として、残しておく事にする。

//フォント切り取り位置返す関数
//使いたい文字を入れたら、その文字の切り取り位置を返してくれる。
//※切り取り位置を受け取る配列を引数で用意してもらう。
//int入れられた場合、swscanf_s(%s)で文字化して、その後半角→全角してから
//通常処理に入れるように。
//int SetFont(wchar_t *str)
//{
//	int font_clip[2][FONT_MAX] = {};
//	int length = 0;
//	int font_count = 0;
//
//	//フォントデータ情報
//	//※配列位置がそのまま切り取り位置となる為、フォント画像の配置と同じように文字登録するように。
//	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
//	{
//		{ L'あ',L'い',L'う',L'え',L'お',L'ア',L'イ',L'ウ',L'エ',L'オ' },
//		{ L'か',L'き',L'く',L'け',L'こ',L'カ',L'キ',L'ク',L'ケ',L'コ',L'が',L'ぎ',L'ぐ',L'げ',L'ご',L'ガ',L'ギ',L'グ',L'ゲ',L'ゴ' },
//		{ L'さ',L'し',L'す',L'せ',L'そ',L'サ',L'シ',L'ス',L'セ',L'ソ',L'ざ',L'じ',L'ず',L'ぜ',L'ぞ',L'ザ',L'ジ',L'ズ',L'ゼ',L'ゾ' },
//		{ L'た',L'ち',L'つ',L'て',L'と',L'タ',L'チ',L'ツ',L'テ',L'ト',L'だ',L'ぢ',L'づ',L'で',L'ど',L'ダ',L'ヂ',L'ヅ',L'デ',L'ド' },
//		{ L'な',L'に',L'ぬ',L'ね',L'の',L'ナ',L'ニ',L'ヌ',L'ネ',L'ノ' },
//		{ L'は',L'ひ',L'ふ',L'へ',L'ほ',L'ハ',L'ヒ',L'フ',L'ヘ',L'ホ',L'ば',L'び',L'ぶ',L'べ',L'ぼ',L'バ',L'ビ',L'ブ',L'ベ',L'ボ' },
//		{ L'ま',L'み',L'む',L'め',L'も',L'マ',L'ミ',L'ム',L'メ',L'モ' },
//		{ L'や',L'ゆ',L'よ',L'ヤ',L'ユ',L'ヨ' },
//		{ L'ら',L'り',L'る',L'れ',L'ろ',L'ラ',L'リ',L'ル',L'レ',L'ロ' },
//		{ L'わ',L'を',L'ん',L'ワ',L'ヲ',L'ン' },
//		{ L'×',L'※',L'：',L'＋',L'－',L'…',L'。',L'！',L'？',L'、',L'０',L'１',L'２',L'３',L'４',L'５',L'６',L'７',L'８',L'９',L'一',L'二',L'三',L'四',L'五',L'六',L'七',L'八',L'九',L'零' },
//		{ L'今',L'日',L'人',L'類',L'統',L'括',L'山',L'田',L'先',L'敵',L'惑',L'星',L'情',L'報',L'不',L'意',L'打',L'喰',L'前',L'行' },
//		{ L'聞',L'強',L'来',L'思',L'準',L'備',L'越',L'手',L'入',L'見',L'攻',L'撃',L'傾',L'向',L'戦',L'闘',L'必',L'殺',L'技',L'持',L'捕',L'食',L'奪' },
//		{ L'直',L'結',L'負',L'無',L'気',L'仕',L'方',L'下',L'出',L'押',L'命',L'令',L'住',L'最',L'初',L'回',L'目',L'時',L'間',L'属',L'性' },
//		{ L'有',L'利',L'不',L'利',L'赤',L'青',L'緑',L'灰',L'色',L'対',L'等',L'察',L'簡',L'単',L'活',L'用',L'数',L'字',L'上',L'真',L'中',L'線' },
//		{ L'吸',L'寄',L'逆',L'自',L'分',L'同',L'士',L'引',L'力',L'衝',L'突',L'大',L'小',L'宇',L'宙',L'常',L'識',L'覚',L'習',L'慣',L'考' },
//		{ L'素',L'材',L'移',L'所',L'配',L'置',L'便',L'番',L'最',L'高',L'体',L'成',L'果',L'勝',L'昇',L'多',L'書',L'材',L'限',L'後' },
//		{ L'次',L'獲',L'得',L'集',L'切',L'札',L'乗',L'詳',L'内',L'容',L'説',L'明',L'欲',L'把',L'握',L'残',L'秘',L'訣',L'油',L'断',L'優' },
//		{ L'方',L'法',L'教',L'育',L'画',L'面',L'研',L'究',L'民',L'術',L'耐',L'久',L'増',L'員',L'割',L'振',L'再',L'産',L'早',L'武',L'器' },
//		{ L'製',L'作',L'実',L'際',L'度',L'当',L'滅',L'表',L'示',L'少',L'遅',L'戻',L'兵',L'舎',L'化',L'他',L'資',L'飛',L'相',L'的',L'込' },
//		{ L'参',L'加',L'割',L'振',L'分',L'中',L'色',L'出',L'撃',L'要',L'注',L'条',L'件',L'載',L'倉',L'庫',L'装',L'現',L'在',L'旦',L'定' },
//		{ L'発',L'展',L'黒',L'整',L'物',L'光',L'銀',L'河',L'盛',L'奇',L'跡',L'朗',L'報',L'帯',L'安',L'心',L'休',L'遊',L'暗' },
//	};
//
//	//▼現在メッセージの文字列の長さを取得
//	for (int i = 0; str[i] != L'；'; i++)
//	{
//		length = i;
//	}
//
//	while (font_count <= length)
//	{
//		//フォントデータ読み込み処理
//		for (int i = 0; i < FONT_DATA_Y; i++)
//		{
//			for (int j = 0; j < FONT_DATA_X; j++)
//			{
//				//フォントデータの端部に到達すると、次の行に移る処理
//				if (font_data[i][j] == NULL)
//				{
//					break;
//				}
//				//検索HITしたら、その切り取り位置を代入する
//				else if (str[font_count] == font_data[i][j])
//				{
//					font_clip[0][font_count] = j + 1;
//					font_clip[1][font_count] = i + 1;
//
//					break;
//				}
//			}
//
//			//検索終了していれば、フォントデータ読み込み処理から抜ける
//			if (font_clip[0][font_count] != 0 || font_clip[1][font_count] != 0)
//			{
//				break;
//			}
//		}
//
//		font_count++;
//	}
//
//	return font_clip[2][256];
//}
//
//
////フォント表示関数
////※切り取りデータ配列2つを入れたら、その文字を表示してくれる。
////Font::StrDrawと似た感じでx,y,x_size,y_size,color入れれるように
//void DrawFont()
//{
//
//}

