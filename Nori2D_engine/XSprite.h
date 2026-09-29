#pragma once
#include "PngImage.h"


struct XSprite
{
    XFloat2 pos;
    float   z;
    XFloat2 size;
    float   rotation;
    unsigned int color;

    PngImage png;
    FrameAnimationInfo anim;
    float current_time;
	unsigned char  is_Alive = TRUE;

    col2d::AABBox  collisionBox;

    XSprite();
    XSprite(PngImage png_);
    
    void SetImage(PngImage png_, PngImage::Frame* frame_, FrameAnimationInfo anim_) {
        png = png_;
        png.SetFrame(frame_);
        anim = anim_;
    }
    void SetPosition(XFloat2 pos_) { pos = pos_; }
    void SetSize(XFloat2 size_) { size = size_; }
    col2d::AABBox getCollisionBox()
        { return {pos.x+ collisionBox.left,pos.y+ collisionBox.top, pos.x+ collisionBox.right, pos.y+ collisionBox.bottom }; }

    void ToVertex(struct D2_VERTEX* vt, D2_INDEX*  idx, int& vt_start, int& idx_start, unsigned int color ) const;
    void UpdateAnimation(float delta);
    bool TestEndOfAnim(float delta);

};

