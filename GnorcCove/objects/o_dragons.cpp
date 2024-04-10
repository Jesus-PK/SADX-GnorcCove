#include "pch.h"

//  Models, Animations and Collisions:

ModelInfo* MDL_Spyro = nullptr;
ModelInfo* MDL_Lateef = nullptr;
ModelInfo* MDL_Tomas = nullptr;

AnimationFile* ANIM_Spyro = nullptr;
AnimationFile* ANIM_Lateef = nullptr;
AnimationFile* ANIM_Tomas = nullptr;

CCL_INFO COL_Spyro = { 0, CollisionShape_Capsule, 0x77, 0, 0, { 0.0f, 6.0f, 0.0f }, 6.0f, 3.0f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COL_Lateef = { 0, CollisionShape_Capsule, 0x77, 0, 0, { 0.0f, 15.0f, 0.0f }, 7.5f, 12.5f, 0.0f, 0.0f, 0, 0, 0 };
CCL_INFO COL_Tomas = { 0, CollisionShape_Capsule, 0x77, 0, 0, { 0.0f, 17.5f, 0.0f }, 7.5f, 15.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Values:

#define SPEED_Dragon twp->scl.x

NJS_POINT3 SCALE_Dragon = { -0.04f, 0.04f, 0.04f };

NJS_POINT3 POS_LateefSmoke = { 0, 0, 0 };
NJS_POINT3 POS_TomasSmoke = { 0, 0, 0 };

NJS_POINT3 VELO_DragonSmoke = { 0, 0, 0 };


//  Spyro - Main:

void DISPLAY_Spyro(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_ACTION ACTION_Spyro = { MDL_Spyro->getmodel(), ANIM_Spyro->getmotion() };

    njSetTexture(&TEXLIST_GnorcCove_Dragons);
    
    njPushMatrix(0);
    
    njTranslate(0, twp->pos.x, twp->pos.y + 7.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScale(0, -0.02f, 0.02f, 0.02f);
    
    SetupChunkModelRender();
    njCnkAction(&ACTION_Spyro, SPEED_Dragon);
    ResetChunkModelRender();
    
    njPopMatrix(1u);
}

void EXEC_Spyro(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            tp->disp = DISPLAY_Spyro;
            CCL_Init(tp, &COL_Spyro, 1, 4u);

            twp->mode++;

            break;

        case 1:

            SPEED_Dragon += 0.33f;

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}


//  Dragons - Display Functions:

void DISPLAY_Lateef(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Lateef = { MDL_Lateef->getmodel(), ANIM_Lateef->getmotion() };

    njSetTexture(&TEXLIST_GnorcCove_Dragons);
    
    njPushMatrix(0);
    
    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Lateef, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}

void DISPLAY_Tomas(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;

    NJS_ACTION ACTION_Tomas = { MDL_Tomas->getmodel(), ANIM_Tomas->getmotion() };

    njSetTexture(&TEXLIST_GnorcCove_Dragons);
    
    njPushMatrix(0);
    
    njTranslate(0, twp->pos.x, twp->pos.y + 2.0f, twp->pos.z);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Dragon);

    SetupChunkModelRender();
    njCnkAction(&ACTION_Tomas, SPEED_Dragon);
    ResetChunkModelRender();

    njPopMatrix(1u);
}


//  Dragons - Exec Functions:

void EXEC_Lateef(task* tp)
{
    if (!CheckRangeOutWithR(tp, 250000.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Lateef;
                CCL_Init(tp, &COL_Lateef, 1, 4u);

                POS_LateefSmoke.x = twp->pos.x;
                POS_LateefSmoke.y = twp->pos.y + 15.0f;
                POS_LateefSmoke.z = twp->pos.z;

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.35f;

                if (++twp->wtimer > 410)
                {
                    CreateSmoke(&POS_LateefSmoke, &VELO_DragonSmoke, 5.0f);
                    FreeTask(tp);
                }

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}

void EXEC_Tomas(task* tp)
{
    if (!CheckRangeOutWithR(tp, 250000.0f))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:

                tp->disp = DISPLAY_Tomas;
                CCL_Init(tp, &COL_Tomas, 1, 4u);

                POS_TomasSmoke.x = twp->pos.x;
                POS_TomasSmoke.y = twp->pos.y + 20.0f;
                POS_TomasSmoke.z = twp->pos.z;

                twp->mode++;

                break;

            case 1:

                SPEED_Dragon += 0.35f;

                if (++twp->wtimer > 700)
                {
                    CreateSmoke(&POS_TomasSmoke, &VELO_DragonSmoke, 5.0f);
                    FreeTask(tp);
                }

                break;
        }

        EntryColliList(twp);

        tp->disp(tp);
    }
}


//  Dragons - ChildTaskSet:

childtaskset CTS_Lateef[] = {
    { EXEC_Lateef, 2, 0, {0}, {0}, 0 },
    { 0 }
};

childtaskset CTS_Tomas[] = {
    { EXEC_Tomas, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Dragons - Load Assets:

void LOAD_Dragons()
{
    MDL_Spyro = LoadChunkModel("GnorcCove_SpyroLEDGE");
    MDL_Lateef = LoadChunkModel("GnorcCove_Lateef");
    MDL_Tomas = LoadChunkModel("GnorcCove_Tomas");

    ANIM_Spyro = LoadObjectAnim("GnorcCove_SpyroLEDGE");
    ANIM_Lateef = LoadObjectAnim("GnorcCove_Lateef");
    ANIM_Tomas = LoadObjectAnim("GnorcCove_Tomas");
}