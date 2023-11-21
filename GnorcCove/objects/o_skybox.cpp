#include "pch.h"

//  Model:

ModelInfo* MDL_GnorcCove_Skybox = nullptr;


//  Skybox - Main:

void DISPLAY_GnorcCove_Skybox(task* tp)
{
    auto twp = tp->twp;

    njSetTexture(&TEXLIST_GnorcCove_Objects);

    Direct3D_SetNearFarPlanes(SkyboxDrawDistance.Minimum, SkyboxDrawDistance.Maximum);

    DisableFog();
    njPushMatrix(0);

    njTranslate(0, 0.0f, 0.0f, 0.0f);
    njScale(0, 20.0f, 20.0f, 20.0f);

    DrawModel(MDL_GnorcCove_Skybox->getmodel()->basicdxmodel);

    njPopMatrix(1u);
    ToggleStageFog();

    Direct3D_SetNearFarPlanes(LevelDrawDistance.Minimum, LevelDrawDistance.Maximum);
}

void EXEC_GnorcCove_Skybox(task* tp)
{
    auto twp = tp->twp;

    if (!twp->mode)
    {  
        SetGlobalPoint2Col_Colors(0x49008E, 0x49008E, 0x49008E);
        
        twp->mode++;
    }

    tp->disp(tp);
}

void BG_GnorcCove(task* tp)
{
    tp->exec = EXEC_GnorcCove_Skybox;
    tp->disp = DISPLAY_GnorcCove_Skybox;
}


//  Skybox - Load Assets:

void LOAD_GnorcCove_Skybox()
{
    MDL_GnorcCove_Skybox = LoadBasicModel("GnorcCove_Skybox");
}