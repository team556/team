#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�Q�[���I�[�o�[���
class CObjFightOver :public CObj
{
public:
	CObjFightOver() {};
	~CObjFightOver() {};
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

	float m_a;		//�����x
	float m_a_vec;	//�����x�x�N�g��
	bool  m_a_f;	//�����x�t���O
	float m_black_out_a;	//��ʈÓ]���ߓx
	float m_gameover_a;	//�Q�[���I�[�o�[�t�H���g�p���ߓx(�A���t�@�l)

	//int m_cnt;		//�J�E���g
};