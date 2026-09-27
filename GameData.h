#pragma once

static const char* tree_FILE_NAME = "Content\\tiles.png";
static const char* farmer_FILE_NAME = "Content\\farmer11.png";


static
PngImage::Frame g_tree_frames[] =
{
    // Tree0
    { 460, 844,   180,180 },  //0 

    // Tree1
    { 0, 870,   66,154 },  //1 

    // Tree2
    { 67, 870,   66,154 },  //2 

    // Tree3
    { 133, 785,   50,100 }  //6 

};

static
PngImage::Frame g_char_frames_back[] =
{
    {    0,0,   32,32 },
    { 1 * 32,0,   32,32 },
    { 2 * 32,0,   32,32 },
    { 3 * 32,0,   32,32 },
    { 4 * 32,0,   32,32 },
    { 5 * 32,0,   32,32 }
};

static
PngImage::Frame g_char_frames_front[] =
{
    { 6 * 32,0,   32,32 },
    { 7 * 32,0,   32,32 },
    {      0,32,   32,32 },
    { 1 * 32,32,   32,32 },
    { 2 * 32,32,   32,32 },
    { 3 * 32,32,   32,32 }
};

static
PngImage::Frame g_char_frames_left[] =
{
    { 4 * 32,32,   32,32 },
    { 5 * 32,32,   32,32 },
    { 6 * 32,32,   32,32 },
    { 7 * 32,32,   32,32 },
    {    0,64,  32,32 },
    { 1 * 32,64,  32,32 },
};

static
PngImage::Frame g_char_frames_right[] =
{
    { 2 * 32,64,  32,32 },
    { 3 * 32,64,  32,32 },
    { 4 * 32,64,  32,32 },
    { 5 * 32,64,  32,32 },
    { 6 * 32,64,  32,32 },
    { 7 * 32,64,  32,32 },
};

static
FrameAnimationInfo tree_animInfo = { 0.1f, 0, 0, 0, 80,166 };

static
FrameAnimationInfo char_animInfo = { 0.1f, 0, 6, 0, 24,34 };
