#pragma once


inline
void DrawRotConvex(const col2d::RotConvex& a, const Float4& lineColor)
{
    int size = a.shape.size;
    VERTEX_LINE* vt = (VERTEX_LINE*)_alloca((size+1)* sizeof(VERTEX_LINE)  ); 
    
    for(int i=0; i<size; ++i ) {
        XFloat2 pos = a.center + a.shape.vt[i].rotateByAngle(XFloat2::ZERO, MATH_DEG_TO_RAD(a.rot));
        vt[i].x = pos.x / g_Dx11.half_width;
        vt[i].y = pos.y / g_Dx11.half_height;
        vt[i].z = 0.f;
        vt[i].color = lineColor;
    }
    vt[size] = vt[0];

    DxLineRenderer::get()->DrawPt(vt,size+1);
}

inline
void DrawConvex(const col2d::Convex& a, const Float4& lineColor)
{
    int size = a.size;
    VERTEX_LINE* vt = (VERTEX_LINE*)_alloca((size+1)* sizeof(VERTEX_LINE)  ); 

    for(int i=0; i<size;++i) {
        vt[i].x = a.vt[i].x / g_Dx11.half_width;
        vt[i].y = a.vt[i].y / g_Dx11.half_height;
        vt[i].z = 0.f;
        vt[i].color = lineColor;
    }
    vt[size] = vt[0];

    DxLineRenderer::get()->DrawPt(vt,size+1);
}

inline
void DrawOBBox(const col2d::OBBox& a, const Float4& lineColor)
{
    col2d::Convex* convex = NewConvexStack(4);
    ConvertToConvex(a,*convex);
    DrawConvex(*convex, lineColor);
}


