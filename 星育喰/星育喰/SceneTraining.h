#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�琬���
class CSceneTraining :public CScene
{
public:
	CSceneTraining();
	~CSceneTraining();
	void InitScene();  //�Q�[���^�C�g���̏��������\�b�h
	void Scene();      //�Q�[���^�C�g���̎��s�����\�b�h
private:
	//���z���[3]�͌�ɏZ�������Ǘ�����O���[�o���ϐ�����Ɍ��߂�ׁA
	//�z�u���鎖�̏o����ő�Z�����̒l�ɕς���悤�ɁB
	float m_ini_hx[3];			//Human�̏���X���W
	float m_ini_hy[3];			//Human�̏���Y���W
};