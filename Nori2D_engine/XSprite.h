#pragma once
#include "PngImage.h"

#define D2_INDEX  USHORT

struct D2_VERTEX
{
    XFloat3  pos;
    XFloat2  uv;
    unsigned int   col;
};


struct XSprite
{
    XFloat2 pos;
    float   z;
    XFloat2 size;
    float   rotation;

    PngImage png;
    FrameAnimationInfo anim;
    float current_time;
	unsigned char  is_Alive = TRUE;

    XSprite();
    XSprite(PngImage png_);
    
    void SetImage(PngImage png_, PngImage::Frame* frame_, FrameAnimationInfo anim_) {
        png = png_;
        png.SetFrame(frame_);
        anim = anim_;
    }
    void SetPosition(XFloat2 pos_) { pos = pos_; }
    void SetSize(XFloat2 size_) { size = size_; }

    void ToVertex(D2_VERTEX* vt, D2_INDEX*  idx, int& vt_start, int& idx_start, unsigned int color ) const;
    void UpdateAnimation(float delta);
    bool TestEndOfAnim(float delta);

};

