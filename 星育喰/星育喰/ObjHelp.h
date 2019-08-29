#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�w���v�{�^��
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_num = Scene_num; }//�쐬���ɓn���ꂽ�l���Am_Scene_num�ɑ��
	~CObjHelp() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	void SetMig_stageF() { m_mig_staging_f = true; }//�V�[���ڍs���o�t���OON�p
	void SetTra_EatF(bool staging) { m_Tra_Eat_f = staging; }//�琬or�퓬���f�t���O�ݒ�p
	void SetOperatable(bool operatable) { m_is_operatable = operatable; }//�w���v�{�^������ېݒ�p
	void SetAlpha(float alpha) { m_Help_Button_alpha = alpha; }//�w���v�{�^�����ߓx�ݒ�p
private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_key_f;		//�}�E�X�̘A�Ő���(�L�[�t���O)

	float m_px;			//�w���v�{�^���̍��WX
	float m_py;			//�w���v�{�^���̍��WY
	float m_vec;		//�w���v�{�^���̈ړ��x�N�g��

	float m_Help_Button_color;	//�w���v�{�^���̃J���[���x
	float m_Back_Button_color;	//�߂�{�^���̃J���[���x
	float m_Page_Back_Button_color;	//�y�[�W�߂��{�^���̃J���[���x
	float m_Page_Next_Button_color;	//�y�[�W�i�߂�{�^���̃J���[���x

	float m_Help_Button_alpha;	//�w���v�{�^���̓��ߓx

	bool  m_mig_staging_f;	//�V�[���ڍs���o�t���O(true:�ڍs���o���@false:�ڍs���o�O)
	bool  m_Tra_Eat_f;		//�琬or�퓬���f�t���O(true:�琬��ʈڍs�@false:�퓬������ʈڍs)[�z�[����ʃV�[���ڍs���o�ł̂ݎg�p]
	bool  m_is_operatable;	//�w���v�{�^������\���m�F�t���O(true:����\�@false;����s��)

	int m_page_num;		//���ݕ\�����̃w���v�摜�ԍ�(�y�[�W)
	int m_page_max;		//���݃V�[���ŕ\������w���v�摜(�y�[�W)�̍ő吔
	int m_help_reg_num;	//�w���v�{�^���A�w���v�摜�̓o�^�ԍ�[���̒l�ɂ̓w���v�{�^���̓o�^�ԍ��������A�w���v�摜�͖������w���v�{�^���̒l�̌�ɑ����悤�ɏ��Ԓʂ�ɓo�^����](�V�[�����Ƀw���v�摜�o�^�ԍ����Ⴄ����m_Scene_num���l�����Ēl������)
	int m_Back_reg_num;	//�߂�{�^���摜�̓o�^�ԍ�(�V�[�����ɖ߂�{�^���摜�o�^�ԍ����Ⴄ����m_Scene_num���l�����Ēl������)

	int m_Scene_num;	//���ݕ\�����̃V�[���ԍ�(1:�z�[�� ,2:�琬 ,3:����)
};