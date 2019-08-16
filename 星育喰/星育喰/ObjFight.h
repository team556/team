#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�퓬���
class CObjFight :public CObj
{
public:
	CObjFight(int c = 0);	//c = cnt(�퓬����),e_n = m_ene_nam(�G�i���o�[)
	~CObjFight() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	int GetLine() { return m_line_nam; }//�I�����C����Ԃ�
	int GetCount() { return m_cnt; }	//�J�E���g����Ԃ�
	void SetEndCount() { m_cnt = 60; }	//�퓬�I���J�E���g���ɐݒ肷��
	void SetStart_Count() { m_start_count_f = true; }//�퓬�J�n�J�E���g�𓮍삳����
	void SetEnd() { m_end_f = true; }	//�N���A��ʍ쐬
	void SetBattle_start(bool start) { battle_start = start; }
	void SetExplosion_f(int id) { m_Explosion_f[id] = true; }
	void SetPrey_f(bool flag) { m_prey_f = flag; }
private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	
	float m_a;			//alpha(�����x)

	int m_line;			//�I��O
	int m_line_nam;		//�I�𒆃��C���i���o�[(�ォ��0,1,2)

	int m_cnt;			//�J�E���g�p

	float m_ex;
	float m_ey;

	float m_scale_down_cnt;		//�k����J�E���g(�w�i)
	float m_scale_down_speed;	//�k���X�s�[�h(�w�i)

	float m_font_a;				//�����x(�퓬�J�n���\�������"�X�^�[�g"�̕����p)

	int	  m_start_count;		//�퓬�J�n�J�E���g�p
	bool  m_start_count_f;		//�u�퓬�J�n�J�E���g�v�J�n�t���O(true�̎��A������J�n����)

	bool m_line_dis;	//�������C���I��\���p

	bool m_end_f;		//�N���A��ʍ쐬�p
	bool m_key_U_f;		//UP�p�L�[�t���O
	bool m_key_D_f;		//DOWN�p�L�[�t���O
	bool m_special_f;   //�X�y�V�����Z��ł������̃t���O

	int m_line_choice;	//���C���I��p

	int m_cuta;


	//���w�ʕ\�������������o�ɂĎg�p����ϐ���
	bool  m_Explosion_f[2];		//[�X�y�V�����Z:Explosion]�����Ǘ��t���O(true:�������@false:������)
	float m_Explosion_size[2];	//[�X�y�V�����Z:Explosion]�G�t�F�N�g�摜�T�C�Y�ύX�p
	float m_Explosion_width[2];	//[�X�y�V�����Z:Explosion]�G�t�F�N�g�摜�̕��ύX�p

	bool  m_prey_f;				//�ߐH�������������łȂ����m�F�p�t���O(true:�ߐH�������@false:�����łȂ�)
	int	  m_ani[4];				//���̃A�j���[�V�����p
protected:
	static bool battle_start;	//�퓬�J�n�t���O(true:�퓬�J�n�@false:�퓬�O or �ꎞ��~��)
	static bool battle_end;		//�퓬�I���t���O(true:�퓬�I���@false:�퓬��)

	static float Pla_One_pat_dem[3];	//�v���C���[�̃����p�^�[���f�����b�g�l�Ǘ��z��[0:�ヌ�[���@1:�����[���@2:�����[��][�ϓ��l��1.0�`1.5��6�i�K�B���[���Ō��x��0.1�������B���̃��[�������x��0.1�������B][���̒l���U���͂Ə�Z����A�ŏI�I�Ȏ󂯂�_���[�W�ƂȂ�]
	static float Ene_One_pat_dem[3];	//�G�l�~�|�̃����p�^�[���f�����b�g�l�Ǘ��z��[0:�ヌ�[���@1:�����[���@2:�����[��][�ϓ��l��1.0�`1.5��6�i�K�B���[���Ō��x��0.1�������B���̃��[�������x��0.1�������B][���̒l���U���͂Ə�Z����A�ŏI�I�Ȏ󂯂�_���[�W�ƂȂ�]

	static int p_pnam;		//�v���C���[�̔r�o�����|�b�h��
	static int e_pnam;		//�G�l�~�[�̔r�o�����|�b�h��

	static float damage_buff[2];//�_���[�W�̃o�t�{��[�X�y�V�����Z:���~�b�g�u���C�N�p]
};