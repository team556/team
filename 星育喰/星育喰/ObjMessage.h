#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define STR_MAX (50) //�����ő吔
#define STR_SIZE (64.0f)//�ꕶ���̑傫��

//�I�u�W�F�N�g�F���b�Z�[�W�\��
class CObjMessage :public CObj
{
public:
	CObjMessage() {};
	~CObjMessage() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	wchar_t str[10][STR_MAX]; //�����Ǘ��z��[���b�Z�[�W��][����]
	int str_column[STR_MAX];//�t�H���g�ǂݍ��݈ʒu(��)
	int str_line[STR_MAX];//�t�H���g�ǂݍ��݈ʒu(�s)
	int str_draw_x[STR_MAX];//�t�H���g�\���ʒuX
	int str_draw_y[STR_MAX];//�t�H���g�\���ʒuY
	int time;				//���ԊǗ�
	int text_count;			//���݉������ڂ��Ǘ�
	int page;				//�y�[�W���Ǘ�
	int now_max;//�����񒷂��Ǘ�


	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
};