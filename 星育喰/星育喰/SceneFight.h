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
	int m_time;		//�V�[���̃^�C��(�N���b�N����ɃV�[���ȍ~)

};