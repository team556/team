#pragma once
#include "GameL\DrawTexture.h"
using namespace GameL;

//�v���g�^�C�v�錾
bool UnitVec(float* vx, float* vy);//�x�N�g���̐��K��

//�̈�������ׂ�֐�
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);

float GetAtan2Angle(float w, float h);//�����ƕ��Ŋp�x�����߂�

RECT_F GetBulletEffec(int* ani, int* ani_time, bool del, int tining);//del�Œe�ۂ�RECT�⒅�eeffect��RECT(�A�j���[�V������RECT)��Ԃ�

int Rand(int n_min, int n_max);//�󂯎���������Ń����_������Ԃ�(1,5)=(1�`5)

RECT_F GetPodEffec(int*ani, int* ani_time, bool del, int timing);