#include "pch.h"

//	Custom levelOBJ - FuncHook to the original levelOBJ but I don't let the original code run at any point, so I'm replacing it completely with my custom code.
//	It will need a "WriteJump((void*)0x61D150, OBJ_GnorcCove);" in the Init so the game jumps to my function when it reaches the original one (Obj_TwinklePark) - Bring "void OBJ_GnorcCove(task* obj);" to the header:

void OBJ_GnorcCove(task* obj);
FunctionHook <void, task*> Obj_TwinklePark_t(0x61D150, OBJ_GnorcCove);

void OBJ_GnorcCove(task* obj)
{
	auto data = obj->twp;

	switch (data->mode)
	{
		case 0:

			ADXTaskInit();
			PlayMusic(MusicIDs_twnklpk1);

			data->mode++;

			break;


		case 1:

			SETVIEWDATA_GnorcCove();

			break;
	}
}


//	Animated Water Textures (TextID swap every frame):

void ANIMATEDWATER_GnorcCove()
{
	if (CurrentLevel != LevelIDs_TwinklePark || GameState != 4 && GameState != 15) // If the current level isn't Twinkle Park, don't do anything. If it isn't but the game isn't on GameState 4 or 15, don't do anything.
		return;

	TWINKLE02_TEXLIST.textures[10].texaddr = TEXLIST_GCWater.textures[(FrameCounter / 2) % (LengthOfArray(TEX_GCWater))].texaddr;
}


//	FuncHook to ADC_SetDrumCan - This function spawns those hardcoded drums where Amy can hide in her levels. If Amy and Twinkle Park are detected, the function will return nothing (removing the barrel spawns) and if not, the original code will run normally.
//	Extra NOTE: On IDA this function doesn't have any arguments, so it doesn't have any task related to it. It's simply a "void" unlike in OBJ_GnorcCove where I needed to put the arguments "(task* obj)":

void DeleteDrums_TwinklePark();
FunctionHook <void> ADC_SetDrumCan_t(0x4C5610, DeleteDrums_TwinklePark);

void DeleteDrums_TwinklePark()
{
	if (CurrentLevel == LevelIDs_TwinklePark)
	{
		return;
	}

	else
	{
		return ADC_SetDrumCan_t.Original();
	}
}


//	Delete ZERO - This function is loaded on Amy_Main, doesn't have any tasks related so it's a simple void function (seems to only delete his normal spawns and not the "special" ones):

void DeleteZERO_TwinklePark();
FunctionHook <void> AmyMain_LoadZERO_t(0x486A40, DeleteZERO_TwinklePark);

void DeleteZERO_TwinklePark()
{
	if (CurrentLevel == LevelIDs_TwinklePark)
	{
		return;
	}

	else
	{
		return AmyMain_LoadZERO_t.Original();
	}
}