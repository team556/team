#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�~�T�C���{�^��
class CObjPushMissile :public CObj
{
public:
	CObjPushMissile(float x, float y, float h, float w);
	~CObjPushMissile() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;		//���WX
	float m_y;		//���WY
	float m_h;		//height��
	float m_w;		//width��
	float m_a;		//alpha

	int m_get_line; //�擾�������C��(0�`2)
	int m_cnt;		//�J�E���g

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool m_mou_f;		//�}�E�X�t���O
};
