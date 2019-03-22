#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjWarehouse :public CObj
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
		int m_obx;//�琬��ʃI�u�W�F�N�gX��
		int m_oby;//�琬��ʃI�u�W�F�N�gY��

		int m_time;

		bool m_turn;
		bool m_turn0;
		bool m_key_f;

		bool m_obj;

};