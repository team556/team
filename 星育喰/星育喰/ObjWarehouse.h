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

		float m_mou_x;		//�}�E�Xx���W
		float m_mou_y;		//�}�E�Xy���W

		bool m_mou_r;		//�E�N���b�N�t���O
		bool m_mou_l;		//���N���b�N�t���O

	private:
		int m_x;
		int m_y;

		bool m_key_lf;  //���N���b�N�p�L�[�t���O

		float m_Ware_color;			//�q�ɃJ���[���x
		float m_Back_Button_color;	//�߂�{�^���J���[���x
		float m_object_ma;			//���ރ{�^���J���[���x
		float m_object_re;			//�Z���{�^���J���[���x
		float m_object_sp;			//�X�y�V�����Z�{�^���J���[���x
		float m_object_eq;			//�����{�^���J���[���x
		float m_Ware_botton_color[10];	//�q�Ƀ{�^���摜�W�J���[���x

};