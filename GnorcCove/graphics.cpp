#include "pch.h"

//  Stage Names:

void STAGENAMES_GnorcCove()
{
    if (HD_GUI)
    {
        ReplaceTEX("AVA_STNAM", "TX_ST08", "StageNames", "HD_StageName_GnorcCove-JP", 365038, 256, 16);
        ReplaceTEX("AVA_STNAM_E", "TX_ST08_e", "StageNames", "HD_StageName_GnorcCove-EN", 10000416, 256, 16);
    }
    
    else
    {
        ReplaceTEX("AVA_STNAM", "TX_ST08", "StageNames", "SD_StageName_GnorcCove-JP", 365038, 256, 16);
        ReplaceTEX("AVA_STNAM_E", "TX_ST08_e", "StageNames", "SD_StageName_GnorcCove-EN", 10000416, 256, 16);
    }
}


//  TitleCards:

void TITLECARDS_GnorcCove()
{
    std::string index = ModPath;

    if (HD_GUI)
    {
        index += "\\textures\\TitleCards_HD\\index.txt";
        const char* HD_Index = index.c_str();

        ReplacePVR("S_STAGE05", HD_Index);
        ReplacePVR("A_STAGE01", HD_Index);
        ReplacePVR("B_STAGE01", HD_Index);
        
        ReplacePVR("S_STAGE05_E", HD_Index);        
        ReplacePVR("A_STAGE01_E", HD_Index);       
        ReplacePVR("B_STAGE01_E", HD_Index);
    }

    else
    {
        index += "\\textures\\TitleCards_SD\\index.txt";
        const char* SD_Index = index.c_str();

        ReplacePVR("S_STAGE05", SD_Index);
        ReplacePVR("A_STAGE01", SD_Index);
        ReplacePVR("B_STAGE01", SD_Index);

        ReplacePVR("S_STAGE05_E", SD_Index);        
        ReplacePVR("A_STAGE01_E", SD_Index);       
        ReplacePVR("B_STAGE01_E", SD_Index);

        ReplacePVR("S_STAGE05_DC", SD_Index);
        ReplacePVR("A_STAGE01_DC", SD_Index);
        ReplacePVR("B_STAGE01_DC", SD_Index);
        
        ReplacePVR("S_STAGE05_E_DC", SD_Index);        
        ReplacePVR("A_STAGE01_E_DC", SD_Index);        
        ReplacePVR("B_STAGE01_E_DC", SD_Index);
    }
}


//  Multiplayer Thumbnails:

void MULTITHUMBNAILS_GnorcCove()
{
	ReplaceTEX("AVA_MULTI", "multistg0300", "MultiThumbnails", "Multi_GnorcCove-S", 54926004, 128, 72);
	ReplaceTEX("AVA_MULTI", "multistg0301", "MultiThumbnails", "Multi_GnorcCove-B", 71757016, 192, 108);
    ReplaceTEX("AVA_MULTI", "multistg0302A", "MultiThumbnails", "Multi_GnorcCove-A", 71757026, 192, 108);
}


//  Stage Credits:

void STAGECREDITS_GnorcCove()
{
    if (HD_GUI)
    {
        ReplaceTEX("ENDBG_SONIC_1", "s_ev017", "StageCredits", "HD_StageCredits_GnorcCove-S00", 366016, 256, 256);
        ReplaceTEX("ENDBG_AMY_0", "a_ev008", "StageCredits", "HD_StageCredits_GnorcCove-A00", 366034, 256, 256);
        ReplaceTEX("ENDBG_AMY_0", "a_ev009", "StageCredits", "HD_StageCredits_GnorcCove-A01", 366035, 256, 256);
        ReplaceTEX("ENDBG_AMY_1", "a_ev010", "StageCredits", "HD_StageCredits_GnorcCove-A02", 366036, 256, 256);
        ReplaceTEX("ENDBG_BIG_0", "b_ev006", "StageCredits", "HD_StageCredits_GnorcCove-B00", 366082, 256, 256);
        ReplaceTEX("ENDBG_BIG_0", "b_ev007", "StageCredits", "HD_StageCredits_GnorcCove-B01", 366083, 256, 256);
    }

    else if (DC_Conversion)
    {
        ReplaceTEX("ENDBG_SONIC_1", "s_ev017", "StageCredits", "DC_StageCredits_GnorcCove-S00", 366016, 256, 256);
        ReplaceTEX("ENDBG_AMY_0", "a_ev008", "StageCredits", "DC_StageCredits_GnorcCove-A00", 366034, 256, 256);
        ReplaceTEX("ENDBG_AMY_0", "a_ev009", "StageCredits", "DC_StageCredits_GnorcCove-A01", 366035, 256, 256);
        ReplaceTEX("ENDBG_AMY_1", "a_ev010", "StageCredits", "DC_StageCredits_GnorcCove-A02", 366036, 256, 256);
        ReplaceTEX("ENDBG_BIG_0", "b_ev006", "StageCredits", "DC_StageCredits_GnorcCove-B00", 366082, 256, 256);
        ReplaceTEX("ENDBG_BIG_0", "b_ev007", "StageCredits", "DC_StageCredits_GnorcCove-B01", 366083, 256, 256);
    }

    else
    {
        ReplaceTEX("ENDBG_SONIC_1", "sonic_17", "StageCredits", "DX_StageCredits_GnorcCove-S00", 366016, 512, 512);
        ReplaceTEX("ENDBG_AMY_0", "amy_04", "StageCredits", "DX_StageCredits_GnorcCove-A00", 366030, 512, 512);
        ReplaceTEX("ENDBG_AMY_0", "amy_05", "StageCredits", "DX_StageCredits_GnorcCove-A01", 366031, 512, 512);
        ReplaceTEX("ENDBG_AMY_0", "amy_06", "StageCredits", "DX_StageCredits_GnorcCove-A02", 366032, 512, 512);
        ReplaceTEX("ENDBG_AMY_0", "amy_07", "StageCredits", "DX_StageCredits_GnorcCove-A03", 366033, 512, 512);
        ReplaceTEX("ENDBG_BIG_0", "big_04", "StageCredits", "DX_StageCredits_GnorcCove-B00", 366080, 512, 512);
        ReplaceTEX("ENDBG_BIG_0", "big_05", "StageCredits", "DX_StageCredits_GnorcCove-B01", 366081, 512, 512);
    }
}


//	Sound Test Entries:

SoundTestEntry SoundTestEntry_GnorcCove = { "Gnorc Cove:  Spyro the Dragon", 104 };


//  Init Graphics:

void INIT_Graphics()
{
    STAGENAMES_GnorcCove();
    TITLECARDS_GnorcCove();
    MULTITHUMBNAILS_GnorcCove();
    STAGECREDITS_GnorcCove();

    Soundtest_ActionStage[23] = SoundTestEntry_GnorcCove;
}