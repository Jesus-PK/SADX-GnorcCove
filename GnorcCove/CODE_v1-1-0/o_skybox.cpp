#include "pch.h"

//  Load Skybox Model:

ModelInfo* MDL_GCSkybox = nullptr;

void LOAD_GCSkybox()
{
    MDL_GCSkybox = LoadBasicModel("GnorcCove_Skybox");
}


//  Replacement code for Twinkle Park skybox display function (0x61D1F0)
//  Since I'm fully replacing the original function and not letting the original code run, I do a WriteJump instead of FuncHook, you do either one or the other, not both:

void SKYBOX_GnorcCove(task* obj)
{
    auto data = obj->twp;

    Direct3D_SetNearFarPlanes(SkyboxDrawDistance.Minimum, SkyboxDrawDistance.Maximum);

    DisableFog();
    njPushMatrix(0);

    NJS_VECTOR skyboxPos = { 0,0,0 };
    njTranslateV(0, &skyboxPos);
    njScale(0, 20.0f, 20.0f, 20.0f);

    DrawModel(MDL_GCSkybox->getmodel()->basicdxmodel);

    njPopMatrix(1u);
    ToggleStageFog();

    SetGlobalPoint2Col_Colors(0x49008e, 0x49008e, 0x49008e);

    Direct3D_SetNearFarPlanes(LevelDrawDistance.Minimum, LevelDrawDistance.Maximum);
}