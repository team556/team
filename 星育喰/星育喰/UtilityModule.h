#pragma once
#include "GameL\DrawTexture.h"
using namespace GameL;

//�}�N��
//#define FONT_MAX (256)			//�t�H���g�i�[�ő吔
//#define FONT_DATA_X (30)		//�t�H���g�f�[�^X
//#define FONT_DATA_Y (22)		//�t�H���g�f�[�^Y
//#define FONT_CLIP_SIZE (125.0f)	//�t�H���g�؂���T�C�Y

//�v���g�^�C�v�錾
bool UnitVec(float* vx, float* vy);//�x�N�g���̐��K��

//�̈�������ׂ�֐�
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);

float GetAtan2Angle(float w, float h);//�����ƕ��Ŋp�x�����߂�

RECT_F GetBulletEffec(int* ani, int* ani_time, bool del, int tining);//del�Œe�ۂ�RECT�⒅�eeffect��RECT(�A�j���[�V������RECT)��Ԃ�

int Rand(int n_min, int n_max);//�󂯎���������Ń����_������Ԃ�(1,5)=(1�`5)

RECT_F GetPodEffec(int*ani, int* ani_time, bool del, int timing);

//int SetFont(wchar_t *str);