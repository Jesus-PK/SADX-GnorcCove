#include "pch.h"

//  Models and Collisions:

ModelInfo* MDL_ExitPortal = nullptr;


//  Exit Portal - Main:

void DISPLAY_ExitPortal(task* obj)
{
    if (MissedFrames)
        return;
    
    taskwk* twp = obj->twp;

    njSetTexture(&TEXLIST_GCObjects);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    dsDrawObject(MDL_ExitPortal->getmodel());
    njPopMatrix(1u);
}

void EXEC_ExitPortal(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:
        {
            auto object = GetMobileLandObject();

            tp->disp = DISPLAY_ExitPortal;
            tp->dest = B_Destructor;

            object->pos[0] = twp->pos.x;
            object->pos[1] = twp->pos.y;
            object->pos[2] = twp->pos.z;

            object->ang[0] = twp->ang.x;
            object->ang[1] = twp->ang.y;
            object->ang[2] = twp->ang.z;

            object->scl[0] = 1.0f;
            object->scl[1] = 1.0f;
            object->scl[2] = 1.0f;

            object->basicdxmodel = MDL_ExitPortal->getmodel()->basicdxmodel;

            RegisterCollisionEntry(ColFlags_Solid, tp, object);

            twp->counter.ptr = object;

            twp->mode++;

            break;
        }
        
        case 1:
        {
            MirenObjCheckCollisionP(twp, 100.0f);

            if (CheckCollisionP(&twp->pos, 18.75f))
            {
                LoadLevelResults();

                twp->mode++;
            }

            break;
        }
    }

    tp->disp(tp);
}


//  Exit Portal - Load Assets:

void LOAD_ExitPortal()
{
    MDL_ExitPortal = LoadBasicModel("ExitPortal");
}