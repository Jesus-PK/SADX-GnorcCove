#include "pch.h"

//  Models and Collisions:

ModelInfo* MDL_BasicChest = nullptr;
ModelInfo* MDL_BCDebris01 = nullptr;
ModelInfo* MDL_BCDebris02 = nullptr;
ModelInfo* MDL_BCDebris03 = nullptr;
ModelInfo* MDL_Number5 = nullptr;

CCL_INFO COLLI_BasicChest = { 0, CollisionShape_Sphere, 0x77, 0x20, 0x400, { 0.0f, 5.25f, 0.0f }, 8.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };


//  Basic Chest - Debris Pieces:

void DISPLAY_BCDebris(task* tp)
{
    taskwk* twp = tp->twp;

    njSetTexture(&TEXLIST_GCObjects);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);

    if (twp->ang.x)
        njRotateX(0, twp->ang.x);

    if (twp->ang.y)
        njRotateY(0, twp->ang.y);

    ds_DrawObjectClip((NJS_OBJECT*)twp->counter.ptr, 1.0f); // The CTS system puts the model in twp->counter.
    njPopMatrix(1);
}

void EXEC_BCDebris(task* tp)
{
    if (!CheckRangeOutWithR(tp, 96100.0))
    {
        auto twp = tp->twp;

        switch (twp->mode)
        {
            case 0:
                
                tp->disp = DISPLAY_BCDebris;
                
                twp->mode = 1;

                // The debris movement is put in twp->scl
                // We calculate it randomly, njRandom returns a number between 0.0f and 1.0f
                twp->scl.x = njRandom() - 0.5f;
                twp->scl.y = njRandom() + 0.5f;
                twp->scl.z = njRandom() - 0.5f;
                
                break;
           
            case 1:
                
                // Apply movement to position every frame.
                twp->pos.x += twp->scl.x;
                twp->pos.y += twp->scl.y;
                twp->pos.z += twp->scl.z;

                // Rotate the debris around.
                twp->ang.x += 0x80;
                twp->ang.y += 0x100;

                // Let's fake gravity by reducing Y.
                twp->scl.y -= 0.05f;
                
                break;
        }

        DISPLAY_BCDebris(tp);
    }
}

childtaskset CTS_BCDebris[] = {
    { EXEC_BCDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_BCDebris, 2, 0, {0}, {0}, 0 },
    { EXEC_BCDebris, 2, 0, {0}, {0}, 0 },
    { 0 }
};


//  Basic chest - Value Number:

void DISPLAY_Number5(task* obj)
{
    if (MissedFrames)
        return;

    taskwk* twp = obj->twp;

    njSetTexture(&TEXLIST_GCObjects);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    dsDrawObject(MDL_Number5->getmodel());
    njPopMatrix(1u);
}


//  Basic Chest - Main:

void DISPLAY_BasicChest(task* obj)
{
    if (MissedFrames)
        return;
    
    taskwk* twp = obj->twp;

    if (twp->mode == 2) // This will stop displaying the object when it reaches mode 2 of it's EXEC function (aka, when the player breaks the object).
        return; // Must be placed below the taskwk* statement above to evade definition errors.

    njSetTexture(&TEXLIST_GCObjects);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    dsDrawObject(MDL_BasicChest->getmodel());
    njPopMatrix(1u);
}

void EXEC_BasicChest(task* tp)
{
    auto twp = tp->twp; // We get the taskwk part of our task (twp) - "Shortcut to twp".

    if (CheckRangeOut(tp)) // == True.
        return; // Object is out of range and will be deleted, no need to keep going.

    switch (twp->mode)
    {
        case 0:

            tp->disp = DISPLAY_BasicChest; // We tell the task that this is our display function.
            CCL_Init(tp, &COLLI_BasicChest, 1, 2u); // This inits the collision data we wrote above.

            twp->mode++; // This increments the variable mode, used to make a task progress. This means that the code above will run once. If it weren't present the code would run every frame.

            break;

        case 1:

            if (twp->flag & Status_Hurt && twp->cwp->hit_cwp) // Check if it touched a damage collision.
            {
                task* hit_tp = twp->cwp->hit_cwp->mytask;

                if (hit_tp && IsThisTaskPlayer(hit_tp) != -1) // Make sure it's a player who touched it.
                {
                    EnemyBounceAndRumble(hit_tp->twp->counter.b[0]); // EnemyBumpPlayer.
                    dsPlay_oneshot(SE_BOMB, 0, 0, 0);
                    Rings += 5; // Gives the player 5 rings when breaking the object.
                    Dead(tp); // This will delete the object but it won't delete it right away, can be tweak with a timer in the case below.
                    tp->disp = DISPLAY_Number5; // Calling an extra model here so it appears for a brief moment after destroying the object until the Dead(tp) timer deletes it.
                    CreateChildrenTask(CTS_BCDebris, tp); // Increment twp->mode when using this function.

                    twp->mode++;
                }
            }

            EntryColliList(twp); // We move the EntryColliList on the end of case 1 instead of outside the switch statement because we want the collision of our object to stop existing once we break the object.

            break;

        case 2:

            twp->ang.y += 750; // This will make the number spin.

            if (++twp->wtimer > 120) // This will destroy the object (needs "Dead(tp)" in the case above) after the specified time, so the object won't respawn if you leave it's render range and come back.
                FreeTask(tp);

            LoopTaskC(tp); // This is needed to run our childtasks (the debris pieces).

            break;
    }

    tp->disp(tp); // This call the display function of the task every frame.
}


//  Basic Chest - Load Assets:

void LOAD_BasicChest()
{
    MDL_BasicChest = LoadBasicModel("GnorcCove_BasicChest");
    MDL_BCDebris01 = LoadBasicModel("GnorcCove_BCDebris01");
    MDL_BCDebris02 = LoadBasicModel("GnorcCove_BCDebris02");
    MDL_BCDebris03 = LoadBasicModel("GnorcCove_BCDebris03");
    MDL_Number5 = LoadBasicModel("GnorcCove_Number5");

    CTS_BCDebris[0].ptr = MDL_BCDebris01->getmodel();
    CTS_BCDebris[1].ptr = MDL_BCDebris02->getmodel();
    CTS_BCDebris[2].ptr = MDL_BCDebris03->getmodel();
}