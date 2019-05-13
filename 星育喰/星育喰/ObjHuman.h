#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�Z��
class CObjHuman :public CObjTraining	//CObjTraining���p������
{
public:
	CObjHuman(float x, float y, int n);//�쐬���̍��W�p����
	~CObjHuman() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
	
	void Turn(int* pos);		//�������]
private:
	float m_hx;			//Human��X���W
	float m_hy;			//Human��Y���W
	float m_mov_spd;	//�����̑���
	float m_size;		//Human�̃T�C�Y

	int m_pos;			//Human�̌���(0�`3�Ŏl����)
	int m_ani_time;		//�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;	//�`��t���[��
	int m_nam;			//�Z���i���o�[
	int m_cnt;			//�J�E���g

	bool m_move;		//true�����Ă���,false�����ĂȂ�
	bool m_turn;		//�^�[���t���O,ture�̈�O
};