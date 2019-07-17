#pragma once
#include "GameL\DrawTexture.h"
using namespace GameL;


//プロトタイプ宣言
bool UnitVec(float* vx, float* vy);//ベクトルの正規化

//領域内か調べる関数
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);

float GetAtan2Angle(float w, float h);//高さと幅で角度を求める

RECT_F GetBulletEffec(int* ani, int* ani_time, bool del, int tining);//delで弾丸のRECTや着弾effectのRECT(アニメーションのRECT)を返す

int Rand(int n_min, int n_max);//受け取った数内でランダム数を返す(1,5)=(1～5)

RECT_F GetPodEffec(int*ani, int* ani_time, bool del, int timing);


//---FontDraw関数
//引数1　int id			:フォント登録番号[デフォルトでは32個登録可能。FONT_ID_MAXを変えれば増やす事が可能。]
//引数2　wchar_t *str	:出力したい文字入力場所
//引数3　float x		:フォント表示位置X
//引数4  float y		:フォント表示位置Y
//引数5  float x_size	:フォントのサイズX(横幅)
//引数6  float y_size	:フォントのサイズY(縦幅)
//引数7  float color[4]	:フォントカラー&透過度(RGBA)
//引数8  bool  right_alignment :[true:右詰め　false:左詰め]
//▼内容
//今回のフォントを登録(保存)する配列番号を決めた後、
//*strに入力された文字(wchar_t)をフリーフォント画像と照らし合わせ、フリーフォント化し、
//x,y,x_size,y_size,color[4]の情報に従い、フリーフォント化した文字を出力する関数。
//※入力する文字は必ず全角文字を用いる事。
//半角文字、フォントデータに登録されてない文字等は使用不可なので注意。(入力すると空白扱いとなる)
void FontDraw(wchar_t *str, float x, float y, float x_size, float y_size, float color[4], bool right_alignment);

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
//FontDraw(NumConversion(1234), 20, 50, 25, 50, d ,false);
//
//▽使用タイミング例
//武器ポッドウインドウの必要資材数、各施設のレベルアップに必要なHP等といった、
//数値が変動する部分のフリーフォント描画に使用すべし。
//※そもそもこの関数は、この部分のプログラムを楽にする為に作成したものである。
wchar_t* NumConversion(unsigned int conversion_num);