#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�퓬�O���o
class CObjBefore_Fight_Effect :public CObj
{
public:
	CObjBefore_Fight_Effect() {};
	~CObjBefore_Fight_Effect() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_black_star_effect_size;	//�퓬�O���o(����)�̃T�C�Y
};