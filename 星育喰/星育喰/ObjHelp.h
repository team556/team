#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjHelp :public CObj
{
public:
	CObjHelp() {};
	~CObjHelp() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;
	float m_y;
	bool  m_help_f;		//�w���v�\���t���O
	
	int m_page_nam;		//�y�[�W��

	int m_Scene_nam;	//���ݕ\�����̃V�[���ԍ�(1:�z�[�� ,2:�琬 ,3:���� ,4:�퓬)

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool m_key_f;		//�}�E�X�̘A�Ő���
};