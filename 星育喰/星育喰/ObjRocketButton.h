#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�~�T�C��&�|�b�h�{�^��
class CObjRocketButton :public CObjFight //CObjFight���p������
{
public:
	CObjRocketButton(float x, float y, float h, float w, int n);
	~CObjRocketButton() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	void SetRecastBuff(float buff) { m_player_recast_buff = buff; }//�o�t�{���ݒ�p[�X�y�V�����Z:���~�b�g�u���C�N�p]
private:
	float m_x;		//���WX
	float m_y;		//���WY
	float m_h;		//height��
	float m_w;		//width��
	float m_a;		//alpha
	float m_a2;		//�l���s���A�C�R���A���L���X�g�Q�[�W�̓��ߓx(alpha)
	
	float m_button_color;//�|�b�h�~�T�C���{�^���̃J���[���x

	int m_get_line; //�擾�������C��(0�`2)
	int m_cnt;		//�J�E���g

	int Button_num; //�p���[�Ȃǂ̃{�^���ԍ�

	float m_player_recast_buff;	//�v���C���[�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{��[�X�y�V�����Z:���~�b�g�u���C�N�p]
	bool m_is_empty;	//���j�b�g������(0�ȉ�)���m�F�t���O(true:��(0�ȉ�)�@false:��(0����))
	
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool m_mou_f;		//�}�E�X�t���O

	float m_px;			//�f����X���W����p
	float m_py;			//�f����Y���W����p
	float m_size;		//�f����Size����p

	bool m_pow_f;		//pow�{�^���̃t���O
	bool m_def_f;		//def�{�^���̃t���O
	bool m_spe_f;		//spe�{�^���̃t���O
	bool m_bal_f;		//bal�{�^���̃t���O
	bool m_mis_f;		//mis�{�^���̃t���O

	int m_key_push;		//�����ꂽ�{�^���̃i���o�[�Ǝ�����Button_num��r�p�ϐ�
	bool m_key_push_f;	//1�`5�̂ǂꂩ�̃{�^���������Ă��邩�ǂ����̃t���O
};