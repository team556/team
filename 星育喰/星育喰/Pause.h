#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;


extern int Pause;

class CObjPause :public CObj
{
	public:
		CObjPause(float x, float y);
		~CObjPause() {};
		void Init();
		void Action();
		void Draw();
	private:
		float m_x;
		float m_y;
		int Pause;
};