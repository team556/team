#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define DETAIL_MES_MAX_FONT_LINE (4) //�ڍא����̍ő�t�H���g�s��

//�I�u�W�F�N�g�F�퓬�������
class CObjPreparation :public CObj
{
public:
	CObjPreparation() {};
	~CObjPreparation() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	void Enemy_message(int enemy_id);		//�G�f���ڍא����\���֐�
	void Special_message(int special_id);	//�X�y�V�����Z�ڍא����\���֐�
private:
	float m_mou_x;	//�}�E�X�̈ʒuX
	float m_mou_y;	//�}�E�X�̈ʒuY
	bool  m_mou_r;	//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;	//�}�E�X�v�b�V���m�F(���N���b�N)

	bool  m_key_lf;	//���N���b�N�p�L�[�t���O
	bool  m_key_rf;	//�E�N���b�N�p�L�[�t���O

	float m_Pvx;	//�v���C���[�f���̈ړ��p�x�N�g��X
	float m_Pvy;	//�v���C���[�f���̈ړ��p�x�N�g��Y
	float m_Pr;		//�T�C���J�[�u�p�̊p�x(�v���C���[�f��y�ړ��Ɏg�p)
	float m_Psize;	//�v���C���[�f���̃T�C�Y

	float m_Svy;	//�X�y�V�����Z�E�C���h�E�A�A�C�R���̈ړ��p�x�N�g��Y

	float m_Bvx;	//�߂�{�^���̈ړ��p�x�N�g��X
	float m_Bvy;	//�߂�{�^���̈ړ��p�x�N�g��Y

	float m_Evx;	//�G�f��4�̈ړ��p�x�N�g��X

	float m_warning_message_x[2];	//�{�X�o���x�����b�Z�[�W�ړ��p�x�N�g��X
	float m_warning_message_y[2];	//�{�X�o���x�����b�Z�[�W�ړ��p�x�N�g��Y
	float m_warning_message_size;	//�{�X�o���x�����b�Z�[�W�T�C�Y
	float m_warning_message_alpha;	//�{�X�o���x�����b�Z�[�W���ߓx(�A���t�@�l)

	float m_Boss_vx[3];		//�{�X�f��(���o�p���܂�)�̈ړ��p�x�N�g��X
	float m_Boss_vy[3];		//�{�X�f��(���o�p���܂�)�̈ړ��p�x�N�g��Y
	float m_Boss_clip_pos;	//�{�X�f���`�挳�؂���ʒu�ύX�p

	float m_speed;		//�e���o�ňړ�����e�I�u�W�F�N�g(�v���C���[�f���A�e�G�f���A�{�X�f����)�̈ړ����x
	float m_save_speed;	//�ړ����x�ۑ��p�ϐ�

	float m_black_star_effect_size;	//�퓬��ʈڍs���o(����)�̃T�C�Y
	int	  m_staging_time;			//���o���ԊǗ��ϐ�
	bool  m_is_operatable;			//����\���m�F�t���O(true:����\�@false;����s��)

	float m_Back_Button_color;		//�߂�{�^���J���[���x
	float m_Special_icon_color[5];	//�X�y�V�����Z�A�C�R���J���[���x
	float m_Yes_Button_color;		//�ŏI�m�F[�͂�]�{�^���J���[(Red)���ߗp
	float m_No_Button_color;		//�ŏI�m�F[������]�{�^���J���[(Blue)���ߗp

	bool  m_Back_flag;				//�u�퓬������ʁ��z�[����ʁv�ڍs�J�n�t���O
	bool  m_Go_flag;				//�u�퓬������ʁ��퓬��ʁv�ڍs�J�n�t���O
	bool  m_boss_emerge_staging_f;	//�{�X�f���o�����o�J�n�t���O
	bool  m_finalcheck_f;			//�ŏI�m�F�E�C���h�E�\���Ǘ��t���O(true:�\�� / false:��\��)

	wchar_t m_detail_message[DETAIL_MES_MAX_FONT_LINE][13];	//�ڍא���(�G�f���A�X�y�V�����Z)�̃t�H���g�p
	wchar_t m_Enemy_detail_message[3][5][DETAIL_MES_MAX_FONT_LINE][13];//�e�G�f���̏ڍא������Ǘ��p([�X�e�[�W��][�G�f���i���o�[][�ő�t�H���g�s��][�����f�[�^�i�[�\��])
	float	m_detail_message_window_top;	//�ڍא���(�G�f���A�X�y�V�����Z)�E�C���h�E�̕`���\���ʒu(top)
	float	m_detail_message_window_left;	//�ڍא���(�G�f���A�X�y�V�����Z)�E�C���h�E�̕`���\���ʒu(left)
	float	m_detail_message_window_right;	//�ڍא���(�G�f���A�X�y�V�����Z)�E�C���h�E�̕`���\���ʒu(right)
	float	m_detail_message_window_bottom;	//�ڍא���(�G�f���A�X�y�V�����Z)�E�C���h�E�̕`���\���ʒu(bottom)
	float	m_detail_message_font_x;		//�ڍא���(�G�f���A�X�y�V�����Z)�t�H���g�ʒuX
	float	m_detail_message_font_y;		//�ڍא���(�G�f���A�X�y�V�����Z)�t�H���g�ʒuY
	float	m_detail_message_alpha;			//�ڍא���(�G�f���A�X�y�V�����Z)�̓��ߓx(�A���t�@�l)

	//int	  m_destroy_count;			//���݃X�e�[�W�ł̓G�f�����j��
	//static bool destroy_progress[4];//���݃X�e�[�W�ł̓G�f�����j�i�s�x(true:���j�@false:�����j)
};