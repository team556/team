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
	float m_Ey[3];		//�G�f��(�w�i)3��Y���W���Ǘ�
	int m_time[3];		//�G�f��(�w�i)3�̎��Ԍo�߂��Ǘ�
	int m_Enemy_id;		//�e�G�f���̎��ʗp�ϐ�
	int m_Planet_id;	//�f���f�[�^�ǎ�p�ϐ�

	//bool  m_flag;		//true=�N���b�N�����@false=�N���b�N���ĂȂ�
	float m_alpha;		//���ߓx(�A���t�@�l)
	float m_Tra_color;	//��A�C�R���J���[���x
	float m_Eat_color;	//��A�C�R���J���[���x

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
};