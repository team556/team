#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjBuild :public CObj
{
	public:
		CObjBuild() {};
		~CObjBuild() {};
		void Init();     //�C�j�V�����C�Y
		void Action();   //�A�N�V����
		void Draw();     //�h���[
	private:

};