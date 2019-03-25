#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjInstitute :public CObj
{
	public:
		CObjInstitute() {};
		~CObjInstitute() {};
		void Init();     //�C�j�V�����C�Y
		void Action();   //�A�N�V����
		void Draw();     //�h���[

		float m_mou_x;
		float m_mou_y;

		bool m_mou_r;
		bool m_mou_l;

	private:
		void InitScene();	//
		void Scene();		//
		int m_x;
		int m_y;

		int m_time;

		bool m_turn;
		bool m_turn0;
		bool m_key_f;

};