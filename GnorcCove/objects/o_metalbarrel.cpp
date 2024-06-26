#include "pch.h"

//  Models and Collisions:

ModelInfo* MDL_MetalBarrel = nullptr;

CCL_INFO COL_MetalBarrel = { 0, CollisionShape_Cylinder, 0x77, 0, 0, { 0.0f, 9.0f, 0.0f }, 7.65f, 8.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Metal Barrel - Main:

void DISPLAY_MetalBarrel(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    njSetTexture(&TEXLIST_GnorcCove_Objects);
    
    njPushMatrix(0);
    
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    
    dsDrawObject(MDL_MetalBarrel->getmodel());
    
    njPopMatrix(1u);
}

void EXEC_MetalBarrel(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    if (!twp->mode)
    {
        tp->disp = DISPLAY_MetalBarrel;
        CCL_Init(tp, &COL_MetalBarrel, 1, 4u);

        twp->mode++;
    }

    EntryColliList(twp);

    tp->disp(tp);
}


//  Metal Barrel - Load Assets:

void LOAD_MetalBarrel()
{
    MDL_MetalBarrel = LoadBasicModel("GnorcCove_MetalBarrel");
}