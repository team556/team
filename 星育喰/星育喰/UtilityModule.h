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