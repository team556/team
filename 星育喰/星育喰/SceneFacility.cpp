//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL_ (0)
#define _HAS_ITERATOR_DEBUGGINGb (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneFacility.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneFacility::CSceneFacility()
{

}
//�f�X�g���N�^
CSceneFacility::~CSceneFacility()
{

}
//���������\�b�h
void CSceneFacility::InitScene()
{
	//test�p�O���O���t�B�b�N�ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�w�i.png", 0, TEX_SIZE_512);

}
//���s�����\�b�h
void CSceneFacility::Scene()
{
	//�`��J���[��� R=RED G=Green B=Blue A=alpha(���ߏ��) 
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�؂���
	RECT_F dst;	//�`��
	

	//�؂���
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�\��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

}