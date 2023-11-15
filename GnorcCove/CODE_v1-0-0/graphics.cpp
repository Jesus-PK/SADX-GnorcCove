#include "pch.h"

//	TitleCards:

#define	ReplaceTitleCard(a) do { \
		_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\TitleCards\\index.txt", path); \
		helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

#define ReplaceTitleCard_Tikal(a) do { \
		_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\TitleCards_T\\index.txt", path); \
		helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)


void TITLECARDS_GnorcCove(const char* path, const HelperFunctions& helperFunctions)
{
	char pathbuf[MAX_PATH];

	HMODULE DLL_TikalOverAmy = GetModuleHandle(L"TOA");

	ReplaceTitleCard("S_STAGE05");
	ReplaceTitleCard("S_STAGE05_E");
	ReplaceTitleCard("B_STAGE01");
	ReplaceTitleCard("B_STAGE01_E");

	if (DLL_TikalOverAmy == nullptr)
	{
		ReplaceTitleCard("A_STAGE01");
		ReplaceTitleCard("A_STAGE01_E");
	}
	
	else
	{
		ReplaceTitleCard_Tikal("A_STAGE01");
		ReplaceTitleCard_Tikal("A_STAGE01_E");
	}
}


//	Mission Cards:

NJS_TEXNAME TEX_GCMission[4] = { 0 };

DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

FunctionHook<void> MissionCard_Result_t(0x457BB0);
FunctionHook<void> LoadMissionImage_t(0x457450);


//  A simple if and else if check to load the correct TexID depending on the character and language.
//  The operators "?" and ":" are basically another way of doing a condition.
//  Basically it can be translated as "if" and "else": "If current character isn't Amy -> Load TexID 0, else load TexID 1 - Very simple, MissionSpriteAnim.texid:

void MISSIONTYPE_Check()
{
    if (Language == ENGLISH)
    {
        MissionSpriteAnim.texid = CurrentCharacter != Characters_Amy ? 0 : 1;
    }

    else if (Language == JAPANESE)
    {
        MissionSpriteAnim.texid = CurrentCharacter != Characters_Amy ? 2 : 3;
    }
}

void MissionCard_Result_r()
{
    // We tell the game to load TexID 0 before calling the original function to fix a crash that happens if we try to load a vanilla card after we loaded one of our custom cards that used ID 1 or higher.
    // This happens because the game only uses TexID 0 for the mission cards and it doesn't change it, so we need to force that to fix this issue - Can be placed either inside the if condition or outside, needs to be present on both hooks:
    if (CurrentLevel != LevelIDs_TwinklePark)
    {
        MissionSpriteAnim.texid = 0;
        
        return MissionCard_Result_t.Original();
    }

    // Edit the texlist of the mission card to make it use our card instead:
    StageMissionTexlist.textures = TEX_GCMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("GnorcCove_MissionCards", &StageMissionTexlist); // It's very important to load the .PVMX here at this specific spot after "StageMissionTexlist.nbTexture = 1;" instead of loading it through my PVMTABLE.
    MISSIONTYPE_Check();

    // Load the task which will diplay the mission card:
    task* tp = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    tp->twp->mode = 0;
    tp->twp->counter.b[1] = GetPlayerNumber();
    tp->twp->wtimer = (MissedFrames_B * 72.0f);
    tp->twp->pos.x = 320.0f;
    tp->twp->pos.y = 240.0f;
    
    tp->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void LoadMissionImage_r()
{
    if (CurrentLevel != LevelIDs_TwinklePark)
    {
        MissionSpriteAnim.texid = 0;
        
        return LoadMissionImage_t.Original();
    }

    // Edit the texlist of the mission card to make it use our card instead:
    StageMissionTexlist.textures = TEX_GCMission;
    StageMissionTexlist.nbTexture = 1;
    
    LoadPVM("GnorcCove_MissionCards", &StageMissionTexlist);
    MISSIONTYPE_Check();

    // Load the task which will diplay the mission card:
    task* task = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
    
    task->twp->mode = 0;
    task->twp->counter.b[1] = GetPlayerNumber();
    task->twp->wtimer = 120;
    task->twp->pos.x = 320.0f;
    task->twp->pos.y = 360.0f;
    
    task->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void MISSIONCARDS_GnorcCove()
{
    MissionCard_Result_t.Hook(MissionCard_Result_r);
    LoadMissionImage_t.Hook(LoadMissionImage_r);
}


//  Lantern Engine error message:

static int LanternErrorMessageTimer = 300;

void CHECK_LanternEngine()
{
    HMODULE DLL_LanternEngine = GetModuleHandle(L"sadx-dc-lighting");

    if (CurrentLevel == LevelIDs_TwinklePark && DLL_LanternEngine == nullptr && LanternErrorMessageTimer)
    {
        SetDebugFontSize(Uint16(10.0f * (float)VerticalResolution / 480.0f));
        SetDebugFontColor(0xFFBFBFBF);
        
        DisplayDebugString(NJM_LOCATION(2, 1), "Failed to detect Lantern Engine mod.");
        DisplayDebugString(NJM_LOCATION(2, 2), "The objects in this level will have no lighting.");
        DisplayDebugString(NJM_LOCATION(2, 3), "Please install and enable Lantern Engine for correct visuals.");
        
        LanternErrorMessageTimer--;
    }
}