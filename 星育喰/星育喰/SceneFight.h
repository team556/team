#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�퓬���
class CSceneFight :public CScene
{
public:
	CSceneFight();
	~CSceneFight();
	void InitScene();  //�Q�[���^�C�g���̏��������\�b�h
	void Scene();      //�Q�[���^�C�g���̎��s�����\�b�h
private:
	float m_cnt;		//�k����J�E���g
	float m_speed;		//�k���X�s�[�h

	float m_a;			//�����x
};