#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, bool type);//���W+�^�C�v���󂯎��
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	float m_px;		//�����WX
	float m_py;		//�����WY
	float m_size;	//���T�C�Y
	float m_cnt;	//�k���p�J�E���g
	
	int m_pnam;		//�摜�i���o�[
};