#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_click_vy;	//"�N���b�N�ŃX�^�[�g"�̈ړ��p�x�N�g���x
	float m_r;			//�T�C���J�[�u�p�̊p�x("�N���b�N�ŃX�^�[�g"�㉺�ӂ�ӂ�Ɏg�p)
	
	float m_Ey[3];		//�G�f��(�w�i)3��Y���W���Ǘ�
	int m_time[3];		//�G�f��(�w�i)3�̎��Ԍo�߂��Ǘ�
	int m_Enemy_id;		//�e�G�f���̎��ʗp�ϐ�
	int m_Planet_id;	//�f���f�[�^�ǎ�p�ϐ�

	bool  m_flag;		//true=�N���b�N�����@false=�N���b�N���ĂȂ�
	float m_alpha;		//���ߓx(�A���t�@�l)

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
};