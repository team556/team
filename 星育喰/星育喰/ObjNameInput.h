
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjNameInput :public CObj
{
public:
	CObjNameInput() {};
	~CObjNameInput() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	int word_x[100];
	int word_y[100];
	int word[100][100];
	int word_w[50];
	int click_cut;
	float click_win[5];
	int m_tex_discri[5];
	bool m_tex_clar;
	bool m_f;
	int m_cut;
	bool m_finalcheck_f;
	int m_Yes_Button_color;
	int m_No_Button_color;
	bool m_key_f;

	char *c[5];
};
