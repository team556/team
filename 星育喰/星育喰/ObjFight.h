#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define MIN_SIZE (30.0f) //�e�f���̍ŏ��T�C�Y(����ȏ�͏������Ȃ�Ȃ�)

//�I�u�W�F�N�g�F�퓬���
class CObjFight :public CObj
{
public:
	CObjFight(int c = 0, int e_n = 0);	//c = cnt(�퓬����),e_n = m_ene_nam(�G�i���o�[)
	~CObjFight() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	int GetLine() { return m_line_nam; }//�I�����C����Ԃ�
	int GetCount() { return m_cnt; }	//�J�E���g����Ԃ�
	void SetStart_Count() { m_start_count_f = true; }//�퓬�J�n�J�E���g�𓮍삳����
	void SetEnd() { m_end_f = true; }	//�N���A��ʍ쐬
private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	
	float m_a;			//alpha(�����x)

	int m_line;			//�I��O
	int m_line_nam;		//�I�𒆃��C���i���o�[(�ォ��0,1,2)

	int m_cnt;			//�J�E���g�p
	int m_ene_nam;		//�G�i���o�[

	float m_ex;
	float m_ey;

	float m_scale_down_cnt;		//�k����J�E���g(�w�i)
	float m_scale_down_speed;	//�k���X�s�[�h(�w�i)

	float m_font_a;				//�����x(�퓬�J�n���\�������"�X�^�[�g"�̕����p)

	int	  m_start_count;		//�퓬�J�n�J�E���g�p
	bool  m_start_count_f;		//�u�퓬�J�n�J�E���g�v�J�n�t���O(true�̎��A������J�n����)

	bool m_end_f;		//�N���A��ʍ쐬�p
protected:
	static bool battle_start;	//�퓬�J�n�t���O(true:�퓬�J�n�@false:�퓬�O or �ꎞ��~��)
	static bool battle_end;		//�퓬�I���t���O(true:�퓬�I���@false:�퓬��)

	static float damage_buff[2];//�_���[�W�̃o�t�{��[�X�y�V�����Z:�X�e���C�h���^�p]
};