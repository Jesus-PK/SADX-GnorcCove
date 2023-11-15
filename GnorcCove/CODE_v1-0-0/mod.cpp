#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//	HelperFunctions pointer for external use:

			HelperFunctionsGlobal = helperFunctions;


		//	Disable DC Conversion Twinkle Park:

			WriteData<5>((void*)0x422C3E, 0x90);


		//	"If you reach the function Obj_TwinklePark, jump to my function instead" - Sora_yx 2023 (This is the WriteJump for my custom LevelOBJ):

			WriteJump((void*)0x61D150, OBJ_GnorcCove);


		//	Remove number of "No-freecam" boxes in Twinkle Park Act 2:

			WriteData((int*)0x4349BF, 0);


		//	Load Level Stuff:

			LANDTABLE_GnorcCove();
			DEATHZONES_GnorcCove();
			STARTPOSITIONS_GnorcCove(helperFunctions);
			PATHS_GnorcCove(helperFunctions);
			FILES_GnorcCove(helperFunctions);


		//	Load Object Assets:

			LOADOBJECTS_GnorcCove();


		//	Load Object List and Texture List:

			INITOBJECTS_GnorcCove();


		//	Load TitleCards and Mission Cards:

			TITLECARDS_GnorcCove(path, helperFunctions);
			MISSIONCARDS_GnorcCove();
	}


	__declspec(dllexport) void __cdecl OnFrame()
	{
		//	Animated Textures Function:

			ANIMATEDWATER_GnorcCove();


		//	Lantern Engine .dll Check:

			CHECK_LanternEngine();
	}


	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}