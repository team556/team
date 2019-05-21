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
	CObjRocket(float x, float y,bool type,int n);
	~CObjRocket() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;		//�~�T�C���̍��WX
	float m_y;		//�~�T�C���̍��WY
	float m_vx;		//�x�N�g��X
	float m_vy;		//�x�N�g��Y
	float m_size;	//�~�T�C���̃T�C�Y
	bool  m_mou_f;	//�}�E�X�t���b�O

	float m_r;		//�~�T�C���p�x
	float m_mov;	//
	float m_mov_spd;//��������

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	int m_get_line;		//�擾�������C���i���o�[
	int m_get_cnt;		//�擾�����J�E���g

	int ButtonU;		//�v���C���[���������|�b�h�̎��

	int m_time;
	int Enemypod;

	int m_Enemy_Pod_Level;	//�G�̃|�b�h���x�����(���x���ɍ��킹���|�b�g�`����s��)(1:���x��1�@2:���x��2�@3:���x��3)

	bool m_type;		//�������̃^�C�v(true��l��)
	int m_podhp;
	int m_hp_cnt;		//���G�^�C��
	bool m_hp_f;		//���G�t���O

	int m_Player_damage;//�v���C���[���󂯂�_���[�W��(�G�l�~�[�̍U����)
	int m_Enemy_damage; //�G�l�~�[���󂯂�_���[�W��(�v���C���[�̍U����)

	int  m_ani;			//���e�A�j���[�V����
	int m_ani_max;
	int  m_ani_time;	//���e�A�j���[�V�����Ԋu�^�C��
	bool m_del;			//�폜�`�F�b�N
	RECT_F m_eff;	   //���e�G�t�F�N�g�`��p

	float m_a;			//alpha(�����x)
	bool m_fight;		//�|�b�h���m�̏Փˎ��̃G�t�F�N�g�Ǘ�
	int m_bom;			//�����G�t�F�N�g�̃����_��(0�`3)

	int Enemy_Line_pattern_x;	////�G�U���p�^�[���̉����ǂݍ��ޗp
	int Enemy_Line_pattern_y;	////�G�U���p�^�[���̏c���ǂݍ��ޗp
};