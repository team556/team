#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define WARE_MES_MAX_FONT_LINE (3) //�q�Ɏ��ށA�Z���A�Z�����A�������ő�t�H���g����

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

		wchar_t m_Ware_message[WARE_MES_MAX_FONT_LINE][100];	//����|�b�h�K�v�f��&�l�����b�Z�[�W�̃t�H���g�p

		float m_Ware_color;			//�q�ɃJ���[���x
		float m_Back_Button_color;	//�߂�{�^���J���[���x
		float m_object_ma;			//���ރ{�^���J���[���x
		float m_object_re;			//�Z���{�^���J���[���x
		float m_object_sp;			//�X�y�V�����Z�{�^���J���[���x
		float m_object_eq;			//�����{�^���J���[���x

		int k;	//���ނ̏������Ă��鐔

		//�Z��
		int p;	//�Z���p���[�̒l
		int s;	//�Z���X�s�[�h�̒l
		int d;	//�Z���f�B�t�F���X�̒l
		int b;	//�Z���o�����X�̒l
		int r;	//�������̒l

		//�Z���␳�l
		int crvp;//�␳�l�p���[
		int crp;

		int crvs;//�␳�l�X�s�[�h
		int crs;

		int crvd;//�␳�l�f�B�t�F���X
		int crd;

		int crvbh;//�␳�l�o�����X	�̗�
		int crbh;

		int crvbp;//�␳�l�o�����X	�p���[
		int crbp;

		int crvbs;//�␳�l�o�����X	�X�s�[�h
		int crbs;

		int crvr;//�␳�l������
		int crr;

		//����
		int eqpp;	//�����␳�l�p���[�v���X
		int epp;
		int eqpm;	//�����␳�l�p���[�}�C�i�X
		int epm;

		int eqsp;	//�����␳�l�X�s�[�h�v���X
		int esp;
		int eqsm;	//�����␳�l�X�s�[�h�}�C�i�X
		int esm;

		int eqdp;	//�����␳�l�f�B�t�F���X�v���X
		int edp;
		int eqdm;	//�����␳�l�f�B�t�F���X�}�C�i�X
		int edm;

		int eqbp;	//�����␳�l�o�����X�v���X
		int ebp;

		int epdp;	//�����␳�l�|�b�h�v���X
		int edpp;
		int m_time;
};