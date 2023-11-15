#include "pch.h"
#include "o_basicchest.h"
#include "o_door.h"
#include "o_exitportal.h"
#include "o_exittext.h"
#include "o_metalbarrel.h"
#include "o_metalchest.h"
#include "o_platform.h"
#include "o_skybox.h"
#include "o_spaba.h"
#include "o_tntbarrel.h"

//  Custom Textures:

NJS_TEXNAME TEX_GCWater[14] = { 0 };
NJS_TEXLIST TEXLIST_GCWater = { arrayptrandlength(TEX_GCWater) };

NJS_TEXNAME TEX_GCObjects[13] = { 0 };
NJS_TEXLIST TEXLIST_GCObjects = { arrayptrandlength(TEX_GCObjects) };

NJS_TEXNAME TEX_GCSpaba[17] = { 0 };
NJS_TEXLIST TEXLIST_GCSpaba = { arrayptrandlength(TEX_GCSpaba) };


//	Object List:

//	If the object functions is in SADXFunctionsNew.h, you can just put the name of the function.
//	If it is on SADXFunctions.h (be the name or address), you need to put (TaskFuncPtr) before the name/address. Like this "(TaskFuncPtr)Ring_Main" or "(TaskFuncPtr)0x450370"

//	If you don't use the enums for the first field (HillTop has them on sadx-utils.h), basically IM_MWK = 1, TWK = 2, FWK = 4, AWK = 8 - So for example 14 = IM_TWK | IM_FWK | IM_AWK, - 6 = IM_TWK | IM_FWK,
//	This is handy to translate the number values from SATools .cpp of the objectlist to enum values:

_OBJ_ITEMENTRY OBJECTLIST_GnorcCove_LIST[] = {
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x450370, "O RING" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x79B2F0, "O RING GROUP" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A4C30, "O SPRING GROUND" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A4E50, "O SPRING AIR" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x79F860, "O SPRING TRIPLE" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A4450, "O DASH PANEL" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D6F10, "O ITEMBOX" },
	{ 15, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x4C07D0, "O ITEMBOX AIR" },
	{ 15, 6, 1, 1000000.0f, 0, (TaskFuncPtr)0x44F540, "O CHECKPOINT" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x46B170, "O CAPSULE" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A21C0, "O BALLOON" },
	{ 3, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A7AD0, "S FROGGY" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A1AA0, "O TIKAL" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A30E0, "O SPIKES" },
	{ 6, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A4260, "O IRON BALL SWING" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x7A3E50, "O IRON BALL FALLING" },
	{ 6, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x4CBA80, "O SWITCH" },
	{ 14, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4CA530, "O ROCKET" },
	{ 14, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4CA660, "O ROCKET C" },
	{ 14, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4CA7D0, "O ROCKET V" },
	{ 14, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4CA900, "O ROCKET VC" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D4850, "C PUSHWALL" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D4700, "C SPHERE" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D4770, "C CYLINDER" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D47E0, "C CUBE" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D4B70, "C LEDGE" },
	{ 2, 0, 1, 1000000.0f, 0, (TaskFuncPtr)0x4D4E10, "C NOT UNDERWATER" },
	{ 2, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x4AD140, "E KIKI" },
	{ 3, 3, 1, 250000.0f, 0, (TaskFuncPtr)0x7B2E00, "E BUYON" },
	{ 2, 3, 1, 250000.0f, 0, (TaskFuncPtr)0x4A6700, "E EGGKEEPER" },
	{ 2, 2, 1, 1000000.0f, 0, (TaskFuncPtr)0x7B0A70, "E ZERO" },
	{ 2, 2, 1, 1000000.0f, 0, EXEC_BasicChest, "O BASIC CHEST"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_MetalChest, "O METAL CHEST"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_ExitPortal, "O EXIT PORTAL"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_ExitText, "O EXIT TEXT"},
	{ 3, 3, 1, 1000000.0f, 0, (TaskFuncPtr)0x624020, "O BARREL" },
	{ 2, 2, 1, 1000000.0f, 0, EXEC_MetalBarrel, "O METAL BARREL"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_GCPlatform, "O PLATFORM"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_GCDoor, "O DOOR"},
	{ 2, 2, 1, 1000000.0f, 0, EXEC_Spaba, "O SPABA"}
};

_OBJ_ITEMTABLE OBJECTLIST_GnorcCove = { LengthOfArray(OBJECTLIST_GnorcCove_LIST), 0, OBJECTLIST_GnorcCove_LIST };


//	Texture List:

TEX_PVMTABLE TEXTURELIST_GnorcCove[] = {
	{ "OBJ_TWINKLE", &OBJ_TWINKLE_TEXLIST },
	{ "E_BUYON", &E_BUYON_TEXLIST },
	{ "E_AMENBO", &E_AMENBO_TEXLIST },
	{ "BG_SHAREOBJ", &BG_SHAREOBJ_TEXLIST },
	{ "E_SARU", &E_SARU_TEXLIST },
	{ "KOAR", &KOAR_TEXLIST },
	{ "WARA", &WARA_TEXLIST },
	{ "USA", &USA_TEXLIST },
	{ "ZOU", &ZOU_TEXLIST },
	{ "BANB", &BANB_TEXLIST },
	{ "TOGEBALL_TOGEBALL", &TOGEBALL_TOGEBALL_TEXLIST },
	{ "E_BOMB", &E_BOMB_TEXLIST },

	{ "GnorcCove_Water", &TEXLIST_GCWater },
	{ "GnorcCove_Objects", &TEXLIST_GCObjects },
	{ "GnorcCove_Spaba", &TEXLIST_GCSpaba },
	{ "E_ROBO", &E_ROBO_TEXLIST },
	{ 0 }
};


//	Load Object Assets:

void LOADOBJECTS_GnorcCove()
{
	LOAD_BasicChest();
	LOAD_GCDoor();
	LOAD_ExitPortal();
	LOAD_ExitText();
	LOAD_MetalBarrel();
	LOAD_MetalChest();
	LOAD_GCPlatform();
	LOAD_GCSkybox();
	LOAD_Spaba();
	LOAD_TNTBarrel();
}


//	Load Object List and Texture List:

void INITOBJECTS_GnorcCove()
{
	ListofPvmList[LevelIDs_TwinklePark] = TEXTURELIST_GnorcCove;

	objItemTable[LevelIDs_TwinklePark * 8] = &OBJECTLIST_GnorcCove;
	objItemTable[LevelIDs_TwinklePark * 8 + 1] = &OBJECTLIST_GnorcCove;
}