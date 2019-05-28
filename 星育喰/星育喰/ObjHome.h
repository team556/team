#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�z�[��
class CObjHome :public CObj
{
public:
	CObjHome() {};
	~CObjHome() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_Pvx;		//�v���C���[�f���̈ړ��p�x�N�g��X
	float m_Pvy;		//�v���C���[�f���̈ړ��p�x�N�g��Y
	float m_boost;		//�v���C���[�f����X�ړ����x�㏸�p
	float m_rx;			//�T�C���J�[�u�p�̊p�x(�v���C���[�f��x�ړ��Ɏg�p)
	float m_ry;			//�T�C���J�[�u�p�̊p�x(�v���C���[�f��y�ړ��Ɏg�p)
	float m_size;		//�v���C���[�f���̃T�C�Y

	int m_Mig_time;		//�V�[���ڍs�܂ł̎��ԊǗ��ϐ�

	float m_Ey[3];		//�G�f��(�w�i)3��Y���W���Ǘ�
	int m_time[3];		//�G�f��(�w�i)3�̎��Ԍo�߂��Ǘ�
	int m_Enemy_id;		//�e�G�f���̎��ʗp�ϐ�
	int m_Planet_id;	//�f���f�[�^�ǎ�p�ϐ�
	int	m_speed;		//�G�f��(�w�i)3�̈ړ����x�ύX�p(�f�o�b�O�p �� �B���v�f)

	float m_Tra_move;	//��A�C�R���̈ړ��p�x�N�g��
	float m_Eat_move;	//��A�C�R���̈ړ��p�x�N�g��
	float m_Tra_color;	//��A�C�R���J���[���x
	float m_Eat_color;	//��A�C�R���J���[���x
	float m_alpha;		//���ߓx(�A���t�@�l)
	bool  m_Tra_flag;	//��A�C�R���N���b�N��true�t���O
	bool  m_Eat_flag;	//��A�C�R���N���b�N��true�t���O
	bool  m_status_flag;//�v���C���[�f���X�e�[�^�X�\���t���O(true:�\���@false:��\��)

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool  m_key_f;		//�L�[�t���O
};