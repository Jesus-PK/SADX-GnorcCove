#include "pch.h"
#include "deathzones.h"
#include "paths.h"

//	FogData to call in my custom LevelOBJ. Since I don't let the original OBJ code run, that killed the fog (which I wanted) but introduces an issue where I don't call any FogData in my OBJ and my level takes the FogData of the previous level I played.
//	To evade this issue, I created this "fake" FogData by disabling the fog values on the last variable (the 0 in the end means disabled) and called this on my OBJ. So with this I'm calling actual FogData for my stage but since it's disabled, there won't be any fog in the level.

//	NOTE: Each line inside the FogData[] array means an act in consecutive order. For example, I only need this fog on the first two acts so writing these two lines is enough. If you don't have any FogData for a playable act, the level will be covered in fog everywhere (that's why I added FogData for TP2, just in case)
//	Arguments are Min / Max distance / Color / ON (1) or OFF (0):

___stcFog FOGDATA_GnorcCove[] = {
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 },
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 },
	{ 100.0f, 1000.0f, 0xFFFFFF, 0 }
};

//	DrawDistance values for my custom LevelOBJ - Each line represents a clip setting (High, Medium, Low) - Arguments are min / max draw distance:

___stcClip DRAWDISTANCE_GnorcCove[] = {
	{ -1.0f, -6000.0f },
	{ -1.0f, -6000.0f },
	{ -1.0f, -6000.0f }
};

___stcClip SKYBOXDRAWDISTANCE_GnorcCove[] = {
	{ -1.0f, -10000.0f },
	{ -1.0f, -10000.0f },
	{ -1.0f, -10000.0f }
};

//	Function with these values - It needs to be called inside "Case 1" in my custom LevelOBJ. The FogData works fine if called in Case 0 but the DrawDistance doesn't work in Case 0:

void SETVIEWDATA_GnorcCove()
{
	gFog = FOGDATA_GnorcCove[ssActNumber];
	gClipMap = DRAWDISTANCE_GnorcCove[ClipLevel];
	gClipSky = SKYBOXDRAWDISTANCE_GnorcCove[ClipLevel];
}


//	Load Landtable:

LandTableInfo* MDL_GCLandtable = nullptr;

void LANDTABLE_GnorcCove()
{
	LoadLandTable(&MDL_GCLandtable, "GnorcCove_Landtable", HelperFunctionsGlobal, nullptr);

	GeoLists[LevelIDs_TwinklePark * 8] = MDL_GCLandtable->getlandtable();
	GeoLists[LevelIDs_TwinklePark * 8 + 1] = MDL_GCLandtable->getlandtable();
}


//	Load Deathzones:

void DEATHZONES_GnorcCove()
{
	KillingCollisionModelsListList[LevelIDs_TwinklePark][0] = GCDeathzones;
	KillingCollisionModelsListList[LevelIDs_TwinklePark][1] = GCDeathzones;
}


//	Start Positions:

StartPosition GnorcCove00 = { LevelIDs_TwinklePark, 0, { -1010.9f, 25, 343.09f }, 0xC000 };
StartPosition GnorcCove01 = { LevelIDs_TwinklePark, 1, { -1010.9f, 25, 343.09f }, 0xC000 };

void STARTPOSITIONS_GnorcCove(const HelperFunctions& helperFunctions)
{
	for (unsigned char i = 0; i < Characters_MetalSonic; ++i)
	{
		helperFunctions.RegisterStartPosition(i, GnorcCove00);
		helperFunctions.RegisterStartPosition(i, GnorcCove01);
	}
}


//	Paths:

void PATHS_GnorcCove(const HelperFunctions& helperFunctions)
{
	helperFunctions.RegisterPathList(PATHDATA_GnorcCove00);
	helperFunctions.RegisterPathList(PATHDATA_GnorcCove01);
}


//	File Replacements:

#define ReplaceBIN(a, b) helperFunctions.ReplaceFile("system\\" a ".BIN", "system\\" b ".BIN");

void FILES_GnorcCove(const HelperFunctions& helperFunctions)
{
	// SET Replacement:

	ReplaceBIN("SET0300S", "SET_GnorcCoveS");
	ReplaceBIN("SET0301A", "SET_GnorcCoveA");
	ReplaceBIN("SET0301B", "SET_GnorcCoveB");


	// CAM Replacement:

	ReplaceBIN("CAM0300S", "CAM_GnorcCoveS");
	ReplaceBIN("CAM0301A", "CAM_GnorcCoveA");
	ReplaceBIN("CAM0301B", "CAM_GnorcCoveB");


	// PL Replacement:

	ReplaceBIN("PL_30B", "PL_GnorcCove");
	ReplaceBIN("PL_31B", "PL_GnorcCove");


	// OST Replacement:

	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\twnklpk1.wma", "system\\OST_GnorcCove.adx");
}