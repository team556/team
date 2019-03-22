#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjWarehouse :public CObjTraining//CObjTraining���p������
{
	public:
		CObjWarehouse() {};
		~CObjWarehouse() {};
		void Init();     //�C�j�V�����C�Y
		void Action();   //�A�N�V����
		void Draw();     //�h���[

		float m_mou_x;
		float m_mou_y;

		bool m_mou_r;
		bool m_mou_l;

	private:
		int m_x;
		int m_y;
		//int m_obx;//�琬��ʃI�u�W�F�N�gX��
		//int m_oby;//�琬��ʃI�u�W�F�N�gY��

		int m_time;

		bool m_key_f;

		bool m_key_ma;	//���ރ{�^���t���O
		bool m_key_re;	//�Z���{�^���t���O
		bool m_key_sp;	//�X�y�V�����Z�{�^���t���O
		bool m_key_eq;	//�����{�^���t���O
		bool m_key_md;	//�߂�{�^���t���O

		float m_Ware_color;	//�q�ɃJ���[���x
		bool m_f;

};