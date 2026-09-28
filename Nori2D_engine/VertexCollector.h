#pragma once
#include "PngImage.h"
#include "XSprite.h"




struct VertexCollector
{
    struct VERT_t {
        D2_VERTEX vt[4];
        D2_INDEX  idx[6];
    };

    struct INDX_t {
        float x,z;
        PngImage png;
        USHORT no;
    };

    std::deque< VERT_t > items;
    std::deque< INDX_t > sprites;

    static VertexCollector* g;

    VertexCollector();
    
    void Add(XSprite& sp);
    void AddTile(D2_VERTEX* vt, D2_INDEX* idx, PngImage png, XFloat2 pos);
    int GetPrimitiveCount();

    void Sort();
    void Draw();

};


struct LineCollector
{
    D2_VERTEX vt0[1000];
    D2_INDEX  idx0[2000];
    USHORT vtCount = 0;
    USHORT primCount = 0;

    LineCollector();
    void Add(XFloat2* pt, int count, unsigned int color);
    void Add(XFloat2* pt, int vt_count, USHORT* idx, int idx_count, unsigned int color);
    void Draw();

};