#include "pch.h"

#define SPEED_Spaba twp->scl.x // This #define is to simply use a custom name over the twp->scl.x calls for better code readability.

//  Models, Animations and Collisions:

ModelInfo* MDL_Spaba = nullptr;
AnimationFile* ANIM_Spaba = nullptr;

CCL_INFO COLLI_Spaba = { 0, CollisionShape_Sphere, 0x77, 0, 0, { 0.0f, 0.0f, 0.0f }, 7.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };

//  Spaba - Main:

void DISPLAY_Spaba(task* tp)
{
    if (MissedFrames)
        return;

    auto twp = tp->twp;
    
    NJS_POINT3 SCALE_Spaba = { 0.02f, 0.02f, 0.02f }; // Since we are gonna scale down the model, we can write down the values we will use on a NJS_POINT3 and call it on njScale. That will scale our object.
    NJS_ACTION ACTION_Spaba = { MDL_Spaba->getmodel(), ANIM_Spaba->getmotion() }; // This NJS_ACTION will get our model and motion, we need to call it on njCnkAction in the display so it draws the model and animation. NOTE: This needs to be written inside the display, else the .dll will cause issues.

    njSetTexture(&TEXLIST_GCSpaba);
    njPushMatrix(0);
    njTranslateV(0, &twp->pos);
    njRotateXYZ(0, twp->ang.x, twp->ang.y, twp->ang.z);
    njScaleV(0, &SCALE_Spaba);
    
    SetupChunkModelRender();
    njCnkAction(&ACTION_Spaba, SPEED_Spaba); // We call our NJS_ACTION in this function, and since we need to tweak the animation speed we use twp->scl.x (any scl. is fine as long as it's available, in this case all 3 types are since the scaling was done with njScale) - Thanks to the #define we did above, we can write our custom name instead.
    ResetChunkModelRender();
    
    njPopMatrix(1u);
}

void EXEC_Spaba(task* tp)
{
    if (CheckRangeOut(tp))
        return;
    
    auto twp = tp->twp;

    switch (twp->mode)
    {
        case 0:

            tp->disp = DISPLAY_Spaba;
            CCL_Init(tp, &COLLI_Spaba, 1, 4u);

            twp->mode++;

            break;

        case 1:

            //  Since it's not recommended to tie the animation to the game framerate, we do the frame maths in our EXEC using a float value in twp like this: twp->scale.x += 0.5f

            SPEED_Spaba += 0.3f; // We can adjust the animation speed with this float - (It's twp->scale.x += 0.5f but with our custom name from the #define above)

            break;
    }

    EntryColliList(twp);

    tp->disp(tp);
}


//  Spaba - Load Assets:

void LOAD_Spaba()
{
    MDL_Spaba = LoadChunkModel("SpabaLEDGE");
    ANIM_Spaba = LoadObjectAnim("SpabaLEDGE");
}