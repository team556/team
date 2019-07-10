//�g�p����w�b�_�[
#include <math.h>   //���w�v�Z�w�b�_�[
#include <time.h>
#include "GameL\DrawTexture.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�(�O�����̒藝)
	float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);

	//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		//0�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K����vx��vy�Ɋi�[
		(*vx) = 1.0f / r*(*vx);
		(*vy) = 1.0f / r*(*vy);
	}
	//�v�Z����
	return true;
}

//---CheckWindow�֐�
//���� float pos_x    :�̈�O�����ׂ�x�ʒu
//���� float pos_y    :�̈�O�����ׂ�y�ʒu
//���� float window_x :�̈��top�ʒu
//���� float window_y :�̈��left�ʒu
//���� float window_w  :�̈��right�ʒu
//���� float window_h  :�̈��bottom�ʒu
//�߂�l bool
//�̈�����ǂ������ׂ�ʒupos_(x,y)��window_(xywh)�̒����O�����ׂ�
bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h)
{
	//�̈�`�F�b�N
	if (pos_x < window_x)
	{
		return false;   //�̈�O
	}
	if (pos_x > window_w)
	{
		return false;   //�̈�O
	}
	if (pos_y < window_y)
	{
		return false;   //�̈�O
	}
	if (pos_y > window_h)
	{
		return false;   //�̈�O
	}

	return true;       //�̈�O
}

//---GetAtan2Angle�֐�
//����1 float w�@�@�F��
//����2 float h�@�@�F����
//�߂�lfloat �@�@ �F�p�x(0���`�@360��)
//���e
//�����ƕ����璼�p�O�p�`������Ɖ��肵�p�x�����߂�B
float GetAtan2Angle(float w, float h)
{
	//atan2�Ŋp�x�����߂�
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180�� �`-0���@���@180���`360���ɕϊ�
	if (r < 0)
	{
		r = 360 - fabs(r);
	}
	return r;
}

//---GetPodEffec�֐�
//����1 int*   ani;     �����A�j���[�V����
//����1 int*   ani_time;�����A�j���[�V�����Ԋu�^�C��
//����1 bool   del;     �폜�`�F�b�N(true=���e�G�t�F�N�g false=���ʂ̒e��)
//����1 int   timing    �Ԋu���RECT
//�߂�l RECT_F eff;    �`�悷��RECT
//del�Œe�ۂ�RECT�⒅�eeffect��RECT(�A�j���[�V������RECT)��Ԃ�
RECT_F GetPodEffec(int* ani, int* ani_time, bool del, int timing)
{
	//�Ԃ�RECT���
	RECT_F rect;

	//�u���O�Œʏ�e��Ȓ��e�A�j���[�V������������
	if (del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[4] =
		{
			{ 0, 0, 32,29 },
			{ 0,32, 64,29 },
			{ 0,64, 96,29 },
			{ 0,96,128,29 },
		};
		//�A�j���[�V�����̃R�}�Ԋu
		if (*ani_time > timing)
		{
			*ani += 1;     //�A�j���[�V�����̃R�}����i�߂�
			*ani_time = 0;
		}
		else
		{
			*ani_time += 1;
		}

		rect = ani_src[*ani];//�A�j���[�V������RECT�z�񂩂�m_ani�Ԗڂ�RECT����n��
	}
	else
	{
		//�e�ۂ̓A�j���[�V��������
		//���\�[�X�e�ۈʒu
		RECT_F bullet = { 0.0f,96.0f,126.0f,32.0f };
		rect = bullet;
	}

	return rect;
}

//n_min = �ŏ��l
//n_max = �ő�l
//�ő�ƍŏ��̍��ŁA����闐���̕������߂�B
int Rand(int n_min, int n_max)
{
	n_max = (n_max + 1) - n_min;
	srand((unsigned int)time(NULL));
	return rand() % n_max + n_min;
}




//���ȉ��̓t�H���g�\�����֐������Ďg���₷�����悤�Ǝv�������̂́A
//�z��O�̎��Ԃ��d�Ȃ�A�֐����f�O�Ɏ������v���O�����ł���B
//�����A����������Ɨ]�T���o�������ɁA���̃v���O�����̑��������\����
//�[���Ƃ͌�����̂ŁA��U�R�����g�A�E�g��ԂƂ��āA�c���Ă������ɂ���B

//�t�H���g�؂���ʒu�Ԃ��֐�
//�g��������������ꂽ��A���̕����̐؂���ʒu��Ԃ��Ă����B
//���؂���ʒu���󂯎��z��������ŗp�ӂ��Ă��炤�B
//int�����ꂽ�ꍇ�Aswscanf_s(%s)�ŕ��������āA���̌㔼�p���S�p���Ă���
//�ʏ폈���ɓ����悤�ɁB
//int SetFont(wchar_t *str)
//{
//	int font_clip[2][FONT_MAX] = {};
//	int length = 0;
//	int font_count = 0;
//
//	//�t�H���g�f�[�^���
//	//���z��ʒu�����̂܂ܐ؂���ʒu�ƂȂ�ׁA�t�H���g�摜�̔z�u�Ɠ����悤�ɕ����o�^����悤�ɁB
//	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
//	{
//		{ L'��',L'��',L'��',L'��',L'��',L'�A',L'�C',L'�E',L'�G',L'�I' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�J',L'�L',L'�N',L'�P',L'�R',L'��',L'��',L'��',L'��',L'��',L'�K',L'�M',L'�O',L'�Q',L'�S' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�T',L'�V',L'�X',L'�Z',L'�\',L'��',L'��',L'��',L'��',L'��',L'�U',L'�W',L'�Y',L'�[',L'�]' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�^',L'�`',L'�c',L'�e',L'�g',L'��',L'��',L'��',L'��',L'��',L'�_',L'�a',L'�d',L'�f',L'�h' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�i',L'�j',L'�k',L'�l',L'�m' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�n',L'�q',L'�t',L'�w',L'�z',L'��',L'��',L'��',L'��',L'��',L'�o',L'�r',L'�u',L'�x',L'�{' },
//		{ L'��',L'��',L'��',L'��',L'��',L'�}',L'�~',L'��',L'��',L'��' },
//		{ L'��',L'��',L'��',L'��',L'��',L'��' },
//		{ L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
//		{ L'��',L'��',L'��',L'��',L'��',L'��' },
//		{ L'�~',L'��',L'�F',L'�{',L'�|',L'�c',L'�B',L'�I',L'�H',L'�A',L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X',L'��',L'��',L'�O',L'�l',L'��',L'�Z',L'��',L'��',L'��',L'��' },
//		{ L'��',L'��',L'�l',L'��',L'��',L'��',L'�R',L'�c',L'��',L'�G',L'�f',L'��',L'��',L'��',L'�s',L'��',L'��',L'��',L'�O',L'�s' },
//		{ L'��',L'��',L'��',L'�v',L'��',L'��',L'�z',L'��',L'��',L'��',L'�U',L'��',L'�X',L'��',L'��',L'��',L'�K',L'�E',L'�Z',L'��',L'��',L'�H',L'�D' },
//		{ L'��',L'��',L'��',L'��',L'�C',L'�d',L'��',L'��',L'�o',L'��',L'��',L'��',L'�Z',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
//		{ L'�L',L'��',L'�s',L'��',L'��',L'��',L'��',L'�D',L'�F',L'��',L'��',L'�@',L'��',L'�P',L'��',L'�p',L'��',L'��',L'��',L'�^',L'��',L'��' },
//		{ L'�z',L'��',L'�t',L'��',L'��',L'��',L'�m',L'��',L'��',L'��',L'��',L'��',L'��',L'�F',L'��',L'��',L'��',L'�o',L'�K',L'��',L'�l' },
//		{ L'�f',L'��',L'��',L'��',L'�z',L'�u',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
//		{ L'��',L'�l',L'��',L'�W',L'��',L'�D',L'��',L'��',L'��',L'�e',L'��',L'��',L'�~',L'�c',L'��',L'�c',L'��',L'��',L'��',L'�f',L'�D' },
//		{ L'��',L'�@',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�p',L'��',L'�v',L'��',L'��',L'��',L'�U',L'��',L'�Y',L'��',L'��',L'��' },
//		{ L'��',L'��',L'��',L'��',L'�x',L'��',L'��',L'�\',L'��',L'��',L'�x',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�I',L'��' },
//		{ L'�Q',L'��',L'��',L'�U',L'��',L'��',L'�F',L'�o',L'��',L'�v',L'��',L'��',L'��',L'��',L'�q',L'��',L'��',L'��',L'��',L'�U',L'��' },
//		{ L'��',L'�W',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�N',L'��',L'��',L'��',L'�S',L'�x',L'�V',L'��' },
//	};
//
//	//�����݃��b�Z�[�W�̕�����̒������擾
//	for (int i = 0; str[i] != L'�G'; i++)
//	{
//		length = i;
//	}
//
//	while (font_count <= length)
//	{
//		//�t�H���g�f�[�^�ǂݍ��ݏ���
//		for (int i = 0; i < FONT_DATA_Y; i++)
//		{
//			for (int j = 0; j < FONT_DATA_X; j++)
//			{
//				//�t�H���g�f�[�^�̒[���ɓ��B����ƁA���̍s�Ɉڂ鏈��
//				if (font_data[i][j] == NULL)
//				{
//					break;
//				}
//				//����HIT������A���̐؂���ʒu��������
//				else if (str[font_count] == font_data[i][j])
//				{
//					font_clip[0][font_count] = j + 1;
//					font_clip[1][font_count] = i + 1;
//
//					break;
//				}
//			}
//
//			//�����I�����Ă���΁A�t�H���g�f�[�^�ǂݍ��ݏ������甲����
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
////�t�H���g�\���֐�
////���؂���f�[�^�z��2����ꂽ��A���̕�����\�����Ă����B
////Font::StrDraw�Ǝ���������x,y,x_size,y_size,color������悤��
//void DrawFont()
//{
//
//}

