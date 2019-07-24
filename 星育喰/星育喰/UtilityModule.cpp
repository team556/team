//�g�p����w�b�_�[
#include <math.h>   //���w�v�Z�w�b�_�[
#include <time.h>
#include "GameL\DrawTexture.h"
#include "UtilityModule.h"

#include "Gamehead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define FONT_LENGTH_MAX (256)	//�t�H���g�ɂĕ\���\�ȕ������E��(���̒l���z���镶�����͐���ɏ�������Ȃ�)
#define WIDTH_DATA_NUM (10)		//���p�S�p�f�[�^���̐�

//��FontDraw�ANumConversion�֐��Ŏg�p����ϐ�
wchar_t con_num[FONT_LENGTH_MAX] = {};	//int��wchar_t�ɕϊ��������Ǘ��z��
wchar_t font[FONT_LENGTH_MAX] = {};		//�t�H���g���Ǘ��z��
int font_column[FONT_LENGTH_MAX] = {};	//�t�H���g�؂���ʒu(��)
int font_line[FONT_LENGTH_MAX] = {};	//�t�H���g�؂���ʒu(�s)
int length = 0;							//������̒������Ǘ�


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
		RECT_F bullet = { 0.0f,0.0f,0.0f,0.0f };
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


//---FontDraw�֐�
//����1�@wchar_t *str	:�o�͂������������͏ꏊ
//����2�@float x		:�t�H���g�\���ʒuX
//����3  float y		:�t�H���g�\���ʒuY
//����4  float x_size	:�t�H���g�̃T�C�YX(����)
//����5  float y_size	:�t�H���g�̃T�C�YY(�c��)
//����6  float color[4]	:�t�H���g�J���[&���ߓx(RGBA)
//����7  bool  right_alignment :[true:�E�l�߁@false:���l��]
//�����e
//*str�ɓ��͂��ꂽ����(wchar_t)���t���[�t�H���g�摜�ƏƂ炵���킹�A�t���[�t�H���g�����A
//x,y,x_size,y_size,color[4]�̏��ɏ]���A�t���[�t�H���g�������������o�͂���֐��B
//�����͂��镶���͕K���S�p������p���鎖�B
//���p�����A�t�H���g�f�[�^�ɓo�^����ĂȂ��������͎g�p�s�Ȃ̂Œ��ӁB(���͂���Ƌ󔒈����ƂȂ�)
//�܂��A�ǂݍ��ݔԍ�121�Ԃɔ������W.png�̉摜��������ΐ���ɓ��삵�Ȃ��̂Œ��ӁB
void FontDraw(wchar_t *str, float x, float y, float x_size, float y_size, float color[4], bool right_alignment)
{
	//�t�H���g�f�[�^���
	//���z��ʒu�����̂܂ܐ؂���ʒu�ƂȂ�ׁA�t�H���g�摜�̔z�u�Ɠ����悤�ɕ����o�^����悤��
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'��',L'��',L'��',L'��',L'��',L'�A',L'�C',L'�E',L'�G',L'�I' },
		{ L'��',L'��',L'��',L'��',L'��',L'�J',L'�L',L'�N',L'�P',L'�R',L'��',L'��',L'��',L'��',L'��',L'�K',L'�M',L'�O',L'�Q',L'�S' },
		{ L'��',L'��',L'��',L'��',L'��',L'�T',L'�V',L'�X',L'�Z',L'�\',L'��',L'��',L'��',L'��',L'��',L'�U',L'�W',L'�Y',L'�[',L'�]' },
		{ L'��',L'��',L'��',L'��',L'��',L'�^',L'�`',L'�c',L'�e',L'�g',L'��',L'��',L'��',L'��',L'��',L'�_',L'�a',L'�d',L'�f',L'�h' },
		{ L'��',L'��',L'��',L'��',L'��',L'�i',L'�j',L'�k',L'�l',L'�m' },
		{ L'��',L'��',L'��',L'��',L'��',L'�n',L'�q',L'�t',L'�w',L'�z',L'��',L'��',L'��',L'��',L'��',L'�o',L'�r',L'�u',L'�x',L'�{' },
		{ L'��',L'��',L'��',L'��',L'��',L'�}',L'�~',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'�v',L'�b' },
		{ L'�~',L'��',L'�F',L'�{',L'�|',L'�c',L'�B',L'�I',L'�H',L'�A',L'��',L'�D',L'��',L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X',L'��',L'��',L'�O',L'�l',L'��',L'�Z',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'�l',L'��',L'��',L'��',L'�R',L'�c',L'��',L'�G',L'�f',L'��',L'��',L'��',L'�s',L'��',L'��',L'��',L'�O',L'�s',L'�S',L'��',L'�^' },
		{ L'��',L'��',L'��',L'�v',L'��',L'��',L'�z',L'��',L'��',L'��',L'�U',L'��',L'�X',L'��',L'��',L'��',L'�K',L'�E',L'�Z',L'��',L'��',L'�H',L'�D' },
		{ L'��',L'��',L'��',L'��',L'�C',L'�d',L'��',L'��',L'�o',L'��',L'��',L'��',L'�Z',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'�L',L'��',L'�s',L'��',L'��',L'��',L'��',L'�D',L'�F',L'��',L'��',L'�@',L'��',L'�P',L'��',L'�p',L'��',L'��',L'��',L'�^',L'��',L'��' },
		{ L'�z',L'��',L'�t',L'��',L'��',L'��',L'�m',L'��',L'��',L'��',L'��',L'��',L'��',L'�F',L'��',L'��',L'��',L'�o',L'�K',L'��',L'�l' },
		{ L'�f',L'��',L'��',L'��',L'�z',L'�u',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'�l',L'��',L'�W',L'��',L'�D',L'��',L'��',L'��',L'�e',L'��',L'��',L'�~',L'�c',L'��',L'�c',L'��',L'��',L'��',L'�f',L'�D' },
		{ L'��',L'�@',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�p',L'��',L'�v',L'��',L'��',L'��',L'�U',L'��',L'�Y',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'�x',L'��',L'��',L'�\',L'��',L'��',L'�x',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�I',L'��' },
		{ L'�Q',L'��',L'��',L'�U',L'��',L'��',L'�F',L'�o',L'��',L'�v',L'��',L'��',L'��',L'��',L'�q',L'��',L'��',L'��',L'��',L'�U',L'��' },
		{ L'��',L'�W',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�N',L'��',L'��',L'��',L'�S',L'�x',L'�V',L'��' },
	};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�������̏I��蕔���Ɉ�(�G)������
	swprintf_s(font, L"%s�G", str);

	//������������������̒������擾	
	for (int i = 0; font[i] != L'�G'; i++)
	{
		length = i + 1;
	}

	//���t�H���g�\������
	//������̒���(�����̐�)���A�t�H���g�\���������s��
	//���t�H���g�P�P��for���ŕ����̑������񂵂āA�\�����Ă���B
	for (int i = 0; i <= length; i++)
	{
		//���t�H���g�f�[�^�ǂݍ��ݏ���
		//���\���������������������W.png�̂ǂ��ɂ��邩����
		for (int j = 0; j < FONT_DATA_Y; j++)
		{
			for (int k = 0; k < FONT_DATA_X; k++)
			{
				//�t�H���g�f�[�^�̒[���ɓ��B����ƁA���̍s�Ɉڂ鏈��
				if (font_data[j][k] == NULL)
				{
					break;
				}
				//����HIT������A���̐؂���ʒu��������
				else if (font[i] == font_data[j][k])
				{
					font_column[i] = k + 1;
					font_line[i] = j + 1;

					break;//����HIT�����̂ŁA�t�H���g�f�[�^�ǂݍ��ݏ������甲����
				}
			}

			//�����I�����Ă���΁A�t�H���g�f�[�^�ǂݍ��ݏ������甲����
			if (font_column[i] != 0 || font_line[i] != 0)
			{
				break;
			}
		}

		//���t�H���g�\������
		src.m_top = FONT_CLIP_SIZE * (font_line[i] - 1);
		src.m_left = FONT_CLIP_SIZE * (font_column[i] - 1);
		src.m_right = FONT_CLIP_SIZE * font_column[i];
		src.m_bottom = FONT_CLIP_SIZE * font_line[i];

		dst.m_top = y;

		//�E�l�߂̏���
		if (right_alignment == true)
		{
			dst.m_left = x + (x_size * i) - (x_size * (length - 1));
			dst.m_right = x + (x_size * (i + 1)) - (x_size * (length - 1));
		}
		//���l�߂̏���
		else
		{
			dst.m_left = x + (x_size * i);
			dst.m_right = x + (x_size * (i + 1));
		}

		dst.m_bottom = y + (y_size);

		//�ȉ��̓t�H���g�؂���ʒu(��A�s)�̂ǂ��炩��0�����͂���Ă����ꍇ�A
		//���̃t�H���g��\�����Ȃ������B
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

		//�ǂݍ��ݔԍ�121�Ԃɔ������W.png�̉摜��������ΐ���ɓ��삵�Ȃ��̂Œ��ӁB
		Draw::Draw(121, &src, &dst, color, 0.0f);
	}

	//�t�H���g�؂���ʒu(��A�s)������������
	for (int i = 0; i <= length; i++)
	{
		font_column[i] = 0;
		font_line[i] = 0;
	}
}

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
//FontDraw(NumConversion(1234), 20, 50, 25, 50, d, false);
//
//���g�p�^�C�~���O��
//����|�b�h�E�C���h�E�̕K�v���ސ��A�e�{�݂̃��x���A�b�v�ɕK�v��HP���Ƃ������A
//���l���ϓ����镔���̃t���[�t�H���g�`��Ɏg�p���ׂ��B
//�������������̊֐��́A���̕����̃v���O�������y�ɂ���ׂɍ쐬�������̂ł���B
wchar_t* NumConversion(unsigned int conversion)
{
	//�����̔��p�S�p�f�[�^���
	//�����p���S�p�ɕϊ��̍ۂɎg�p�B
	wchar_t halfwidth_data[WIDTH_DATA_NUM] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };
	wchar_t fullwidth_data[WIDTH_DATA_NUM] = { L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X' };



	//������(unsigned int)������(wchar_t)������
	//�����łɕ����̏I��蕔���Ɉ�(�G)������
	swprintf_s(con_num, L"%u�G", conversion);

	//������������������̒������擾	
	for (int i = 0; con_num[i] != L'�G'; i++)
	{
		length = i + 1;
	}

	//�����p���S�p�ϊ�����
	for (int i = 0; i <= length; i++)
	{
		for (int j = 0; j <= WIDTH_DATA_NUM; j++)
		{
			//���������������ƈ�v���锼�p�f�[�^��T���A
			//�����������ƁA���̔z�񕔕��ɔ��p�ɑΉ�����S�p�f�[�^������B
			if (con_num[i] == halfwidth_data[j])
			{
				con_num[i] = fullwidth_data[j];

				break;//�S�p�f�[�^�������̂ŁA���p���S�p�ϊ��������甲����
			}
		}
	}

	return con_num;
}