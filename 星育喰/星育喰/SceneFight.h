#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�퓬���
class CSceneFight :public CScene
{
public:
	CSceneFight(int e_n);
	~CSceneFight();
	void InitScene();  //�Q�[���^�C�g���̏��������\�b�h
	void Scene();      //�Q�[���^�C�g���̎��s�����\�b�h
private:
	int m_ene_nam;		//�G�̃i���o�[
};