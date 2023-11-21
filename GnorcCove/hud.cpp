#include "pch.h"

//  HD GUI check for sprites:

int ArrayID;
float SpriteHeight_Icon;

void SetSpriteSettings()
{ 
    //  Set Array ID:
    
    HD_GUI ? ArrayID = 1 : ArrayID = 0;


    //  Set sprite Height values:
    
    if (HUD_Plus)
        SpriteHeight_Icon = 416.0f;

    else if (DC_Conversion)
        SpriteHeight_Icon = (DC_HudTweaks) ? 400.0f : 416.0f;

    else
        SpriteHeight_Icon = 416.0f;
}


//  Key HUD:

static NJS_TEXANIM TEXANIM_ChestKey[] = {
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 26, 0x20 }, // ID 0 - TexID 26
    { 0x20, 0x20, 0, 0, 0, 0, 0x100, 0x100, 27, 0x20 }, // ID 1 - TexID 27
};

static NJS_SPRITE SPRITE_ChestKey = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &TEXLIST_GnorcCove_Objects, TEXANIM_ChestKey };

void DrawKeyCountHUD()
{
    SetSpriteSettings();
    
    SPRITE_ChestKey.p.x = 592.0f;
    SPRITE_ChestKey.p.y = SpriteHeight_Icon;
    
    if (HasKey == 0)
        return;
    
    else
        late_DrawSprite2D(&SPRITE_ChestKey, ArrayID, 22046.496f, NJD_SPRITE_ALPHA, LATE_LIG);
}

void DrawKeyHUD()
{
    ScaleUI(uiscale::Align_Automatic);
    SetSpriteParam();

    DrawKeyCountHUD();

    ResetSpriteParam();
    ResetScaleUI();
}