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
	int	m_speed;		//�G�f��(�w�i)3�̈ړ����x�ύX�p(�f�o�b�O�p �� �B���v�f)

	float m_Yes_Button_color;	//�ŏI�m�F[�͂�]�{�^���J���[(Red)���ߗp
	float m_No_Button_color;	//�ŏI�m�F[������]�{�^���J���[(Blue)���ߗp
	float m_del_color;	//�f�[�^�����{�^���J���[���x
	float m_del_alpha;	//�f�[�^���������ʒm�摜�̓��ߓx
	bool  m_del_f;		//�f�[�^�����ŏI�m�F�E�C���h�E�\���Ǘ��t���O(true:�\�����@false:��\��)

	bool  m_flag;		//true=�N���b�N�����@false=�N���b�N���ĂȂ�
	bool  m_key_f;		//�L�[�t���O
	float m_alpha;		//���ߓx(�A���t�@�l)
	float m_malpha;		//���ߓx0.0�`1.0�ɕς���
	float m_black_out_a;//��ʈÓ]���ߓx
	float m_des_y;		//���E�ϐ����摜�̈ʒuY
	float m_des_vec;	//���E�ϐ����摜�̃x�N�g��
	float m_des_a;		//���E�ϐ����摜�̓��ߓx

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	static bool after_once;	//�^�C�g����ʁ��z�[����ʈڍs����true(���ڈȍ~�K�ꂽ���̉��o�p�Ɏg�p)
};