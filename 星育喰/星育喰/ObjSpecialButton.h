#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�y�V�����Z�{�^��
class CObjSpecialButton :public CObjFight //CObjFight���p������
{
public:
	CObjSpecialButton(float x, float y, float h, float w);
	~CObjSpecialButton() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;		//�X�y�V�����Z�{�^���̍��WX
	float m_y;		//�X�y�V�����Z�{�^���̍��WY
	float m_h;		//�X�y�V�����Z�{�^����height(����)
	float m_w;		//�X�y�V�����Z�{�^����width(��)
	float m_a;		//�X�y�V�����Z�{�^����alpha(���ߓx)

	//���z�񐔎��̈Ӗ��͈ȉ��̒ʂ�
	//0:�v���C���[�f���@1:�G�f��

	float m_hp[2];	//�f����HP[�G�ɑ�_���[�W�p]
	float m_size[2];//�f���̃T�C�Y[�G�ɑ�_���[�W�p]

	int m_line;		//�I�𒆂̃��C��(�ォ��0,1,2)[���E���p]

	bool m_invincible[2];	//���G�t���O[��莞�Ԗ��G�p]

	int  m_recast_time[2];		//�~�T�C���|�b�h�̃��L���X�g�^�C��[���Y�������A�b�v]



	int m_time[2];	//�X�y�V�����Z���ʎ��ԊǗ��p

	bool m_is_used_special[2];	//�X�y�V�����Z���g�p���ꂽ��(true:�g�p�ρ@false:���g�p)

	int  m_enemy_special_equipment;//�G�������̃X�y�V�����Z(0:�������@1:�G�ɑ�_���[�W�@2:���E���@3:��莞�Ԗ��G�@4:���Y�������A�b�v�@5:�Z���̎m�C���A�b�v)
	bool m_enemy_special_button;//�G�p�X�y�V�����Z�����{�^��(true:�����@false:�������ĂȂ�)





	int m_Planet_id; //�Gor�v���C���[���ʗp

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
};