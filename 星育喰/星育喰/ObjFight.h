#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�퓬���
class CObjFight :public CObj
{
public:
	CObjFight() {};
	~CObjFight() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	int GetLine() { return m_line_nam; }//�I�����C����Ԃ�
	int GetCount() { return m_cnt; }	//�J�E���g����Ԃ�
	void SetEndF() { m_end_f = true; }	//�I���t���O�𗧂Ă�

private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	
	float m_a;			//alpha(�����x)

	int m_line;			//�I��O
	int m_line_nam;		//�I�𒆃��C���i���o�[(�ォ��0,1,2)

	int m_cnt;			//�J�E���g�p

	bool m_end_f;		//�I������t���O

	float m_hp;			//�G�f��HP
	float m_hp2;		//�v���C���[�f��HP
	float m_ex;
	float m_ey;

protected:
	static bool battle_start;	//�퓬�J�n�t���O(true:�퓬�J�n�@false:�퓬�O)
	static bool battle_end;		//�퓬�I���t���O(true:�퓬�I���@false:�퓬��)
};