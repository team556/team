//g—p‚·‚éƒwƒbƒ_[
#include "GameL\DrawTexture.h"

//g—p‚·‚éƒl[ƒ€ƒXƒy[ƒX
using namespace GameL;

//---Call_PlanetŠÖ”
//ˆø”1@int group	:ƒOƒ‹[ƒvŒˆ’è
//ˆø”2@int select	:˜f¯‘I‘ğ
//¥“à—e
//ƒ^ƒCƒgƒ‹‰æ–ÊAƒz[ƒ€‰æ–Ê‚Ì“G˜f¯(”wŒi)‚ğŒÄ‚Ño‚·ŠÖ”B
//“G˜f¯(”wŒi)‚Í3‚Â‘¶İ‚·‚é‚½‚ßA
//‘S‚Ä‚Ì“G˜f¯‚Ì‰æ‘œ‚ğ3ƒOƒ‹[ƒv‚É•ª‚¯A
//‚»‚±‚©‚çA‚»‚ê‚¼‚êw’è‚³‚ê‚½(ƒ‰ƒ“ƒ_ƒ€‚È)“G˜f¯ƒf[ƒ^‚ğ•Ô‚·B
void Call_Planet(int group, int select)
{
	if (group == 0)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"…˜f¯.png", 20, TEX_SIZE_512);	
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"…˜f¯.png", 20, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"…˜f¯.png", 20, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"ˆ«™.png", 20, TEX_SIZE_512);
		}
	}

	else if (group == 1)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"ƒŒƒCƒh1 128x.png", 22, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"ƒŒƒCƒh1 128x.png", 22, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"ƒŒƒCƒh1 128x.png", 22, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"ˆ«™.png", 22, TEX_SIZE_512);
		}
	}

	else  //(group == 2)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"‚Ú‚â‚¯‚½¯.png", 24, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"‚Ú‚â‚¯‚½¯.png", 24, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"‚Ú‚â‚¯‚½¯.png", 24, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"ˆ«™.png", 24, TEX_SIZE_512);
		}
	}

}