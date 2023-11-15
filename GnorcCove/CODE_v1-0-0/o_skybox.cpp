#include "pch.h"

//  Load Skybox Model:

ModelInfo* MDL_GCSkybox = nullptr;

void LOAD_GCSkybox()
{
    MDL_GCSkybox = LoadBasicModel("GnorcCove_Skybox");
}


//  FuncHook for the skybox display function:

void SKYBOX_GnorcCove(task* obj);
FunctionHook <void, task*> TP_SkyboxDisplay_t(0x61D1F0, SKYBOX_GnorcCove);

void SKYBOX_GnorcCove(task* obj)
{
    auto data = obj->twp;

    if (Camera_Data1 && (data->mode == 1 || data->mode == 4))
    {
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

    else
    {
        return TP_SkyboxDisplay_t.Original(obj);
    }
}