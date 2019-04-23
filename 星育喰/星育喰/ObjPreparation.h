#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define ENEMY_PLANET_DETAIL_MES_MAX_FONT_LINE (3) //�G�f���ڍא������b�Z�[�W�̍ő�t�H���g�s��

//�I�u�W�F�N�g�F�퓬�������
class CObjPreparation :public CObj
{
public:
	CObjPreparation() {};
	~CObjPreparation() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool  m_key_lf;		//���N���b�N�p�L�[�t���O
	bool  m_key_rf;		//�E�N���b�N�p�L�[�t���O

	float m_Pvx;		//�v���C���[�f���̈ړ��p�x�N�g��X
	float m_Pvy;		//�v���C���[�f���̈ړ��p�x�N�g��Y
	//float m_boost;		//�v���C���[�f����X�ړ����x�㏸�p
	//float m_rx;			//�T�C���J�[�u�p�̊p�x(�v���C���[�f��x�ړ��Ɏg�p)
	//float m_ry;			//�T�C���J�[�u�p�̊p�x(�v���C���[�f��y�ړ��Ɏg�p)
	float m_Psize;		//�v���C���[�f���̃T�C�Y

	float m_Evx;		//�G�f��4�̈ړ��p�x�N�g��X
						//�{�X�f���̃��c�͌ʂŗp�ӗ\��
	float m_speed;		//�J�n���o�A�I�����o�ňړ�����I�u�W�F�N�g(�v���C���[�f���A�e�G�f����)�̈ړ����x

	int m_staging_time;		//���o���ԊǗ��ϐ�

	float m_Back_Button_color;	//�߂�{�^���J���[���x
	float m_Yes_Button_color;	//�ŏI�m�F[�͂�]�{�^���J���[(Red)���ߗp
	float m_No_Button_color;	//�ŏI�m�F[������]�{�^���J���[(Blue)���ߗp
	float m_alpha;				//���ߓx(�A���t�@�l)

	wchar_t m_Enemy_detail_message[ENEMY_PLANET_DETAIL_MES_MAX_FONT_LINE][22];	//�G�f���ڍא������b�Z�[�W�̃t�H���g�p
	float	m_Enemy_detail_message_window_x_size;	//�G�f���ڍא����E�C���h�E�̃T�C�YX
	float	m_Enemy_detail_message_window_y_size;	//�G�f���ڍא����E�C���h�E�̃T�C�YY

	static bool destroy_progress[4];//���݃X�e�[�W�ł̓G�f�����j�i�s�x
};