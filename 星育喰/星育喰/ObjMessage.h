#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define MES_MAX (10)			//���b�Z�[�W�ő�i�[��
#define FONT_MAX (100)			//�t�H���g�i�[�ő吔
#define FONT_DATA_X (33)		//�t�H���g�f�[�^X
#define FONT_DATA_Y (22)		//�t�H���g�f�[�^Y
#define FONT_CLIP_SIZE (125.0f)	//�t�H���g�؂���T�C�Y
#define FONT_DRAW_SIZE (36.0f)	//�t�H���g�`��T�C�Y

//�I�u�W�F�N�g�F���b�Z�[�W
class CObjMessage :public CObj
{
public:
	CObjMessage(int id) { m_Scene_id = id; }
	~CObjMessage() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	wchar_t m_font_data[FONT_DATA_Y][FONT_DATA_X];	//�t�H���g�f�[�^(�摜�̂ǂ̈ʒu�ɂǂ̕���������̂��Ǘ����Ă���)
	wchar_t m_font[MES_MAX][FONT_MAX];	//�t�H���g���Ǘ��z��[���b�Z�[�W�i�[��][�t�H���g�f�[�^�i�[��]
	int m_font_column[FONT_MAX];		//�t�H���g�؂���ʒu(��)
	int m_font_line[FONT_MAX];			//�t�H���g�؂���ʒu(�s)
	int m_font_draw_x[FONT_MAX];		//�t�H���g�`��ʒuX
	int m_font_draw_y[FONT_MAX];		//�t�H���g�`��ʒuY
	float m_font_color[FONT_MAX][4];	//�t�H���g�J���[

	int m_time;			//���̃t�H���g�`��܂ł̎��ԊǗ�
	int m_font_count;	//���݉������ڂ�`�撆�ł��邩�Ǘ�
	int m_progress;		//���b�Z�[�W�i�s�x�̊Ǘ�
	int m_length;		//������̒������Ǘ�
	bool m_fast_f;		//���b�Z�[�W�`�摬�x�������t���O[true:�`�摬�x�������@false:�`�摬�x�ʏ�]
	bool m_skip_f;		//���b�Z�[�W�X�L�b�v�t���O[true:�X�L�b�v�������s�@false:�����s���]
	
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_key_f;		//�L�[�t���O

	int	  m_arrow_display_f;//���\���t���O(0:��\���@1:�\��)
	int	  m_arrow_angle_f;	//���p�x�t���O(0:������@1:�������@2:�������@3:�E����)
	float m_arrow_x;		//���X�ʒu
	float m_arrow_y;		//���Y�ʒu

	float m_swing_vec;		//�����A�j���[�V�����p(���摜�A�N���b�N�Ñ��摜�Ɏg�p)
	float m_swing_r;		//�����A�j���[�V����������̂ɕK�v�Ȋp�x�̒l�ۊǗp

	bool  m_black_out_f;		//��ʑS�̂��Ó]�t���O(true:�Ó]�@false:���])
	bool  m_reminder_f;			//�N���b�N�Ñ��摜�\���t���O(true:�\���@false:��\��)
	int   m_is_top_or_bottom;	//���b�Z�[�W�E�C���h�E�ʒu�ύX�p(0:���ɕ\���@1:��ɕ\��)

	int   m_message_window_num;	//���b�Z�[�W�E�C���h�E�o�^�ԍ��i�[�p
	

	//����{�I�ɂ�true�B���b�Z�[�W�I�� or ���b�Z�[�W�r���Ƀv���C���[�ɉ������삳����������false�ɂ���B
	bool m_run_switch;	//���b�Z�[�W�\���@�\ON/OFF�Ǘ��t���O[true:���삳����@false:��~������]
	
	//���V�[��ID�Ǘ��p
	int	m_Scene_id;//����e�X�g�Ŋ���U���Ă�����̂������A��������U���Ă��Ȃ��B


	//������
	//�V�[���ɂ���Ă͏���ɖK�ꂽ�������łȂ��A�Q�x�ڂɖK�ꂽ���ɔ�������`���[�g���A��������̂ŁA
	//����Ɋւ��ẮAstatic�ŖK�ꂽ���L�������Ă����A����Ŕ��f������ׂ��I
};