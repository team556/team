////�g�p����w�b�_�[�t�@�C��
//#include "GameL\DrawTexture.h"
//#include "GameHead.h"
//#include "GameL\HitBoxManager.h"
//#include "ObjHuman.h"
//#include "UtilityModule.h"
//
//
////�g�p����l�[���X�y�[�X
//using namespace GameL;
//
////�R���X�g���N�^
//CObjHuman::CObjHuman(float x, float y, int n)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_hx = x;
//	m_hy = y;
//	m_nam = n;
//}
//
////�C�j�V�����C�Y
//void CObjHuman::Init()
//{
//	m_size = 70.0f;
//	m_pos = 0;			//����( 0�� 1�� 2�� 3�� )
//	m_move = false;		//�����I�t
//	m_mov_spd = 4.0f;	//��������
//	m_cnt = 0;			//�J�E���g
//	m_turn = false;		//��ʊO����
//	m_turn_count = 60;	//�{��HIT���^�[���J�E���g(1�b)
//
//	//�����蔻��pHitBox���쐬
//	Hits::SetHitBox(this, m_hx, m_hy, m_size, m_size, ELEMENT_PLAYER, OBJ_HUMAN, 1);
//}
//
////�A�N�V����
//void CObjHuman::Action()
//{
//	m_cnt++;
//
//	if (m_cnt == 60 + (90 * m_nam)) {
//		m_pos = Rand(0, 3);	//�����������_���Ɍ��߂�
//		m_move = true;		//�������
//	}
//	else if (m_cnt == 120 + 70 * m_nam) {
//		m_cnt = 0;
//		m_move = false;		//�Î~���
//	}
//
//	bool check = CheckWindow(m_hx, m_hy, 0.0f, 0.0f, 1200.0f - m_size, 700.0f - m_size);
//	if (check == false)//��ʊO�̏ꍇ
//	{
//		if (m_turn == false) {
//			CObjHuman::Turn(&m_pos);//�������]�֐�
//			m_turn = true;
//		}
//	}
//	else {
//		m_turn = false;
//	}
//
//	if (m_move == true) {//�����Ă鎞
//		switch (m_pos) {
//		case 0:m_hx -= m_mov_spd; break;//��
//		case 1:m_hy -= m_mov_spd; break;//��
//		case 2:m_hx += m_mov_spd; break;//��
//		case 3:m_hy += m_mov_spd; break;//��
//		default:break;
//		}
//		m_ani_time += 1;//�A�j���[�V������i�߂�
//	}
//	else{
//		m_ani_frame = 0;	//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
//		m_ani_time = 0;		//�A�j���[�V�������~�߂�
//	}
//
//	
//
//	if (m_ani_time > 6) {	//�A�j���[�V��������Ԋu
//		m_ani_frame += 1;
//		m_ani_time = 0;
//	}
//
//	if (m_ani_frame == 4)	//�t���[��4��0�ɖ߂�
//		m_ani_frame = 0;	//0�`3�����[�v
//
//	CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾
//	hit->SetPos(m_hx, m_hy);				//�ʒu���X�V
//
//	//�^�[���J�E���g��0�ȏ�̎��A
//	//�^�[���J�E���g�����X��0�ɋ߂Â���B
//	if (m_turn_count >= 0)
//	{
//		m_turn_count--;
//	}
//
//	//�{�݂ɓ���������������]������
//	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
//	{
//		//�^�[���J�E���g��0�̎��̂ݔ��]������
//		if (m_turn_count <= 0) 
//		{
//			CObjHuman::Turn(&m_pos);//�������]�֐�
//			m_turn_count= 60;//�^�[���J�E���g��60�ɖ߂�(1�b)
//		}
//	}
//}
//
////�h���[
//void CObjHuman::Draw()
//{
//	//���V�[���؂�ւ����o��ɔ�\���ɂ��鏈��
//	if (scene_change_start == true)
//	{
//		return;
//	}
//
//	int AniData[4] = { 1,0,1,2, };
//	int PosData[4] = { 0,2,0,1, };
//
//	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
//	RECT_F src;//�؂���ʒu
//	RECT_F dst;//�\���ʒu
//	
//	src.m_top   =  0.0f + (PosData[m_pos] * 70.0f);
//	src.m_left  =  0.0f + (AniData[m_ani_frame] * 64.0f);
//	src.m_right = 64.0f + (AniData[m_ani_frame] * 64.0f);
//	src.m_bottom= 70.0f + (PosData[m_pos] * 70.0f);
//	
//	dst.m_top   = m_hy;
//	dst.m_left  = m_hx;
//	dst.m_right = m_hx + m_size;
//	dst.m_bottom= m_hy + m_size;
//
//	if (m_pos == 2){
//		dst.m_left  = m_hx + m_size;
//		dst.m_right = m_hx;
//	}
//
//	//10�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
//	Draw::Draw(10, &src, &dst, c, 0.0f);
//}
//
//void CObjHuman::Turn(int* pos)
//{//�����𔽓]������
//	if (*pos == 0 || *pos == 1) { *pos += 2; }
//	else{ *pos -= 2; }
//	switch (*pos) {//���]�����ɐi��
//	case 0:m_hx -= m_mov_spd; break;//��
//	case 1:m_hy -= m_mov_spd; break;//��
//	case 2:m_hx += m_mov_spd; break;//��
//	case 3:m_hy += m_mov_spd; break;//��
//	}
//}