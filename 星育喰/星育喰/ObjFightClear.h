#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�N���A���
class CObjFightClear :public CObj
{
public:
	CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, int skill);
	CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, wchar_t Mat_nameB[20], int *Mat_typeB, int Mat_numB, int skill);
	~CObjFightClear() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	//float m_x;
	//float m_y;
	//bool  m_f;

	//float m_mou_x;		//�}�E�X�̈ʒuX
	//float m_mou_y;		//�}�E�X�̈ʒuY
	//bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_key_f;		//�L�[�t���O

	float m_click_a;		//alpha �����x(�N���b�N�Ñ��t�H���g�p)
	float m_click_a_vec;	//m_click_a�x�N�g��
	bool m_click_a_f;		//�s�������t���O
	float m_result_a;		//alpha(���ߓx)(�퓬���ʃt�H���g�p)
	float m_black_out_a;	//��ʈÓ]���ߓx
	float m_clear_a;		//alpha(���ߓx)(�N���A���b�Z�[�W�̃t�H���g�p)

	bool  m_scene_migration_f;//�V�[���ڍs���o�t���O(true = �z�[����ʂɂ��銴���ƂȂ�B�����ۂɂ͂��̎��_�ł͂܂��ڍs���Ă��Ȃ�)

	int		m_people;		//�l���Z����
	int		m_large;		//�l���T�C�Y(HP)��
	wchar_t m_mat_name[2][20];//�l�����ޖ�
	int		*m_mat_type[2];	//�l�����ގ�� & ���ݐ�
	int		m_mat_num[2];	//�l�����ސ�
	int		m_skill;		//�l���X�y�V�����Z

	//int m_cnt;		//�J�E���g
	//int m_cnt_max;	//�J�E���g�}�b�N�X

	//int m_page_nam;		//�y�[�W��

	bool m_Stage_Clear_f;	//�X�e�[�W�N���A�t���O
	bool m_Game_Clear_f;	//�Q�[���@�N���A�t���O
};