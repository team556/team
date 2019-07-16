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


//---FontDraw�֐�
//����1�@int id			:�t�H���g�o�^�ԍ�[�f�t�H���g�ł�32�o�^�\�BFONT_ID_MAX��ς���Α��₷�����\�B]
//����2�@wchar_t *str	:�o�͂������������͏ꏊ
//����3�@float x		:�t�H���g�\���ʒuX
//����4  float y		:�t�H���g�\���ʒuY
//����5  float x_size	:�t�H���g�̃T�C�YX(����)
//����6  float y_size	:�t�H���g�̃T�C�YY(�c��)
//����7  float color[4]	:�t�H���g�J���[&���ߓx(RGBA)
//����8  bool  right_alignment :[true:�E�l�߁@false:���l��]
//�����e
//����̃t�H���g��o�^(�ۑ�)����z��ԍ������߂���A
//*str�ɓ��͂��ꂽ����(wchar_t)���t���[�t�H���g�摜�ƏƂ炵���킹�A�t���[�t�H���g�����A
//x,y,x_size,y_size,color[4]�̏��ɏ]���A�t���[�t�H���g�������������o�͂���֐��B
//�����͂��镶���͕K���S�p������p���鎖�B
//���p�����A�t�H���g�f�[�^�ɓo�^����ĂȂ��������͎g�p�s�Ȃ̂Œ��ӁB(���͂���Ƌ󔒈����ƂȂ�)
void FontDraw(wchar_t *str, float x, float y, float x_size, float y_size, float color[4], bool right_alignment);

//---NumConversion�֐�
//����1�@unsigned int 	:����(wchar_t)�����������l(int)�̓��͏ꏊ
//�����e
//int�^�̐��l��wchar_t�^�ɕϊ��A���̌㔼�p���S�p�����AFontDraw�Ŏg����悤�ɂ���֐��B
//��FontDraw�ƈꏏ�Ɏg������z�肵�č쐬�����B
//
//���g�p����ۂ̒��ӓ_
//���l��unsigned int�̋L���͈�(0�`4294967295)�̒l�Ƃ��鎖�B
//�}�C�i�X�l��������A�����ł�������ƁA
//unsigned int���L���ł��Ȃ��l����͂���ƁA����ɏ�������Ȃ��̂Œ��ӁB
//
//�����ۂ̎g�p��
//FontDraw(NumConversion(1234), 20, 50, 25, 50, d ,false);
//
//���g�p�^�C�~���O��
//����|�b�h�E�C���h�E�̕K�v���ސ��A�e�{�݂̃��x���A�b�v�ɕK�v��HP���Ƃ������A
//���l���ϓ����镔���̃t���[�t�H���g�`��Ɏg�p���ׂ��B
//�������������̊֐��́A���̕����̃v���O�������y�ɂ���ׂɍ쐬�������̂ł���B
wchar_t* NumConversion(unsigned int conversion_num);