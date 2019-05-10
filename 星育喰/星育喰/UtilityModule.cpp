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
//戻り値float 　　 ：角度(0°〜　360°)
//内容
//高さと幅から直角三角形があると仮定し角度を求める。
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180° 〜-0°　を　180°〜360°に変換
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

