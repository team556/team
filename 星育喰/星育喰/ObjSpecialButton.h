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
	float m_x;		//�X�y�V�����Z�{�^���̈ʒuX
	float m_y;		//�X�y�V�����Z�{�^���̈ʒuY
	float m_h;		//�X�y�V�����Z�{�^����height(����)
	float m_w;		//�X�y�V�����Z�{�^����width(��)
	float m_a;		//�X�y�V�����Z�{�^����alpha(���ߓx)

	bool m_is_used_special;	//�X�y�V�����Z���g�p���ꂽ��(true:�g�p�ρ@false:���g�p)



	int m_get_line; //�擾�������C��(0�`2)
	int m_cnt;		//�J�E���g

	int Button_num; //�p���[�Ȃǂ̃{�^���ԍ�

	float m_create_x;	//�v���C���[�f���|�b�h�쐬X�ʒu�����p

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool m_mou_f;		//�}�E�X�t���O
};