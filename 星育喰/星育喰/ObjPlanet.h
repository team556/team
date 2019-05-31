#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�f��(�v���C���[ & �G)
class CObjPlanet :public CObjFight //CObjFight���p������
{
public:
	CObjPlanet(float x, float y, float size, int type = g_Challenge_enemy);//���W+�T�C�Y(HP)+�G�i���o�[
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	//float GetHp() { return m_hp; }	
	float GetSiz() { return m_size; }		//���݃T�C�Y(HP)�擾�֐�
	float GetMaxSiz() { return m_siz_max; }	//�ő�T�C�Y(HP)�擾�֐�
	float GetScale_down_move() { return m_scale_down_move; }//�T�C�Y�k������X���W�ړ��ʂ�Ԃ�
	int  GetType() { return m_type; }
	int  GetLine() { return m_get_line; }
	bool GetInvincible() { return m_invincible_f; }//���G�ł��邩�ǂ����Ԃ�
	void SetVX(float vector) { m_px += vector; }//X�ړ��p
	void SetDamage() { m_size -= m_siz_max * 0.04; }//�Ăяo���ƃ_���[�W�������s��[�X�y�V�����Z:Explosion�p]
	void SetScale_down_move(int Planet_id) //�Ăяo���ƃT�C�Y�k�����AX���W�̈ړ����s��(Planet_id:�v���C���[ or �G�l�~�[���ʗp)[�X�y�V�����Z:Explosion�p]
	{
		Planet_id = Planet_id == 0 ? -1 : 1;//Planet_id��0�Ȃ�-1���A����ȊO�Ȃ�1��Planet_id�ɑ������
		m_scale_down_move = ((1 - (m_size / m_siz_max)) * 60) * Planet_id; 
	}
	void SetInvincible(bool is_Invincible) { m_invincible_f = is_Invincible; }//���G�t���O�ݒ�p[�X�y�V�����Z:Immortality�p]
	void SetRecastBuff(float buff) { m_enemy_recast_buff = buff; }//�o�t�{���ݒ�p[�X�y�V�����Z:���~�b�g�u���C�N�p]
	void SetEeatF() { m_eat_f = true; }//�Z�b�g�򂤃t���O

	void SetDelF() { m_del_f = true; }//�Z�b�g�����t���O
private:

	float m_px;			//�����WX
	float m_py;			//�����WY
	float m_size;		//���T�C�Y(����HP)
	float m_siz_max;	//�T�C�Y�}�b�N�X(�ő�HP)
	float m_siz_change_range;	//���T�C�Y�̕ύX��(�ŏ��T�C�Y�{���̕ϐ��̒l���ő�T�C�Y�ƂȂ�)[��:�ŏ��T�C�Y:60,���̕ϐ�:60 �� 60�`120�̃T�C�Y�ŕϓ�����f���ƂȂ�]
	//float m_siz_vec;	//�T�C�Y�ύX�x�N�g��
	//float m_siz_spd;	//�T�C�Y�ύX�X�s�[�h
	float m_get_siz;	//�Q�b�g���݃T�C�Y(HP)[�G�̌���HP�擾�p]
	float m_get_max_siz;//�Q�b�g�ő�T�C�Y(HP)[�G�̍ő�HP�擾�p]
	float m_mov_spd;	//�f���ړ��X�s�[�h
	float m_scale_down_move;	//�T�C�Y�k�����AX���W�ړ��p(�v���C���[�Ȃ獶�ɁA�G�l�~�[�Ȃ�E�Ɉړ�)

	//float m_hp;			//�q�b�g�|�C���g(m_size��HP���Ǘ����鎖�ɕύX�Bsize = hp)
	//float m_get_hp;		//�Q�b�gHP
	int m_cnt;			//�J�E���g
	int m_type;		//�f���^�C�v(��l�� == 0 != �G)
	int m_img_nam;	//�摜(image)�i���o�[

	bool m_invincible_f;	//���G�t���O(true:���G�@false:���G�ł͂Ȃ�)[�X�y�V�����Z:Immortality�p]
	float m_enemy_recast_buff;//�G�l�~�[�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{��[�X�y�V�����Z:���~�b�g�u���C�N�p]	


	int m_time;
	int m_attackf;		//�G�̍U���^�C�v

	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//�򂤃t���O(true = ��)
	float m_eat_spd;
	bool m_del_f;		//�����t���O(true = ����)

	bool m_win;			//�G�f���ɏ����������ɗ���鉹�y�̃t���O	
	bool m_failed;		//�G�f���ɔs�k�������ɗ���鉹�y�̃t���O

	int m_cntf;			//fight��m_cnt�ϐ��̒l���i�[����p
	int m_mov_stop;		//

	int Enemy_Attack_pattern_x;  //�G�U���p�^�[���̉����ǂݍ��ޗp
	int Enemy_Attack_pattern_y;  //�G�U���p�^�[���̏c���ǂݍ��ޗp

	int Enemy_Line_pattern_x;	////�G�U���p�^�[���̉����ǂݍ��ޗp
	int Enemy_Line_pattern_y;	////�G�U���p�^�[���̏c���ǂݍ��ޗp

	int m_get_line;				//�擾�������C���i���o�[
};