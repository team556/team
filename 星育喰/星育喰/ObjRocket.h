#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�~�T�C��
class CObjRocket :public CObjFight //CObjFight���p������
{
public:
	CObjRocket(float x, float y,int type,int n);
	~CObjRocket() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
	float GetX() { return m_vx; }
	float GetY() { return m_vy; }
private:
	float m_x;		//�~�T�C���̍��WX
	float m_y;		//�~�T�C���̍��WY
	float m_vx;		//�x�N�g��X
	float m_vy;		//�x�N�g��Y
	float m_size;	//�~�T�C���̃T�C�Y

	float m_r;		//�p�x�ύX�p(+�ō���])
	float m_mov;	//
	float m_mov_spd;//��������

	int m_get_line;		//�擾�������C���i���o�[
	int m_get_cnt;		//�擾�����J�E���g

	int ButtonU;		//�|�b�h�̎��

	int ButtonUE;		//�G�l�~�[���������|�b�h�̎��
	int ButtonUP;		//�v���C���[���������|�b�h�̎��

	int m_atk_cnt;		//�_���[�W���[�g�̃J�E���g�p
	int m_atk_cnt_max;	//�_���[�W���[�g�̃J�E���g�ő�l(1/3�b)

	int m_Enemy_Pod_Level;	//�G�̃|�b�h���x�����(���x���ɍ��킹���|�b�g�`����s��)(1:���x��1�@2:���x��2�@3:���x��3)

	int m_type;		//�������̃^�C�v(0��l��)
	int m_podhp;		//�|�b�h����HP
	int m_pod_max_hp;	//�|�b�h�ő�HP
	int m_hp_cnt;		//���G�^�C��
	bool m_hp_f;		//���G�t���O

	int m_Player_damage;//�v���C���[���󂯂�_���[�W��(�G�l�~�[�̍U����)
	int m_Enemy_damage; //�G�l�~�[���󂯂�_���[�W��(�v���C���[�̍U����)

	int m_ani;			//���e�A�j���[�V����
	int m_ani_max;
	int m_ani_time;		//���e�A�j���[�V�����Ԋu�^�C��
	bool m_del;			//�폜�`�F�b�N
	RECT_F m_eff;		//���e�G�t�F�N�g�`��p

	float m_a;			//alpha(�����x)
	int m_bom;			//�����G�t�F�N�g�̃����_��(0�`3)
	bool m_fight;		//�|�b�h���m�̏Փ˒��t���O(��펞)
	int m_stop_cnt;		//�~�߂�܂ł̃J�E���g�p
	bool m_stop_f;		//���W�X�V���~�߂�t���O

	int Enemy_Line_pattern_x;	////�G�U���p�^�[���̉����ǂݍ��ޗp
	int Enemy_Line_pattern_y;	////�G�U���p�^�[���̏c���ǂݍ��ޗp

	int m_bomcount;		//�����̉񐔃J�E���g

	int m_level_comp[4];	//�������탌�x���̔�r�p
};