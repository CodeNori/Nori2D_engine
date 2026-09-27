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
    void Draw(class D2Renderer* mRenderer);

};


