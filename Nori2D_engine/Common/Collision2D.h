#pragma once

namespace col2d {

    // Axis-Aligned Bounding Box
    struct AABBox
    {
        float left, top,
              right, bottom;
    };

    // Oriented Bounding Box
    struct OBBox
    {
        float left, top, 
              width, height;
        float rot;
    };

    struct Convex
    {
         int   size;
         XFloat2  vt[];
    };


    struct RotConvex
    {
        float rot;
        XFloat2  center;

        Convex shape;
    };

    struct Convex_4
    {
        int   size = 4;
        XFloat2  vt[4];
    };

}

namespace col2d_obb {
    bool isCollision(const col2d::OBBox& a, const col2d::OBBox& b);
}
namespace col2d_convex {
    bool SAT_intersect(  const XFloat2* bounds_a, int A_size,
                            const XFloat2* bounds_b, int B_size);
    bool SAT_intersect_withPoint( const XFloat2* bounds_a, int A_size, 
                                 const XFloat2 pt );
}

#define NewConvexStack(cnt) (col2d::Convex*)_alloca( (cnt*sizeof(XFloat2)) + sizeof(col2d::Convex))

inline
col2d::Convex* NewConvex(int cnt)
{
    size_t sizeRC = sizeof(col2d::Convex);
    size_t sizeVt = sizeof(XFloat2)*cnt;

    col2d::Convex* cv = (col2d::Convex*)malloc(sizeRC + sizeVt);
    cv->size = cnt;

    return cv;
}

inline
void DeleteConvex(col2d::Convex* &cv)
{
    free((void*)cv);
    cv = nullptr;
}


inline
col2d::RotConvex* NewRotConvex(int cnt)
{
    size_t sizeRC = sizeof(col2d::RotConvex);
    size_t sizeVt = sizeof(XFloat2)*cnt;

    col2d::RotConvex* rc = (col2d::RotConvex*)malloc(sizeRC + sizeVt);
    rc->shape.size = cnt;

    return rc;
}

inline
void DeleteRotConvex(col2d::RotConvex* &rc)
{
    free((void*)rc);
    rc = nullptr;
}



inline 
int ConvertToConvex(const col2d::OBBox& box, col2d::Convex& b )
{
    XFloat2* convex = b.vt;
    convex[0] = { box.left, box.top};
    convex[1] = { box.left + box.width, box.top};
    convex[2] = { box.left + box.width, box.top - box.height};
    convex[3] = { box.left, box.top - box.height};
    XFloat2 center = { box.left + (box.width/2.f), 
                    box.top - (box.height/2.f) };
    convex[0] = convex[0].rotateByAngle(center, MATH_DEG_TO_RAD(box.rot));
    convex[1] = convex[1].rotateByAngle(center, MATH_DEG_TO_RAD(box.rot));
    convex[2] = convex[2].rotateByAngle(center, MATH_DEG_TO_RAD(box.rot));
    convex[3] = convex[3].rotateByAngle(center, MATH_DEG_TO_RAD(box.rot));

    b.size = 4;
    return 4;
}

inline
int ConvertToConvex(const col2d::RotConvex& a, col2d::Convex& ac)
{
    ac.size = a.shape.size;

    for(int i=0; i<ac.size; ++i )
        ac.vt[i] = a.center + a.shape.vt[i].rotateByAngle(XFloat2::ZERO, MATH_DEG_TO_RAD(a.rot));

    return ac.size;
}

inline 
void StarToConvex(const XFloat2& center, float range, col2d::Convex& b )
{
    XFloat2* convex = b.vt;
    convex[0] = { center.x-range, center.y};
    convex[1] = { center.x, center.y+range};
    convex[2] = { center.x+range, center.y};
    convex[3] = { center.x+(range/2.f), center.y-range};
    convex[4] = { center.x-(range/2.f), center.y-range};

    b.size = 5;
}

inline 
void StarToRotConvex(const XFloat2& center, float range, col2d::RotConvex& b )
{
    b.center = center;
    b.rot = 0.f;

    XFloat2* convex = b.shape.vt;
    convex[0] = { -range, 0.f};
    convex[1] = { 0.f, range};
    convex[2] = { range, 0.f};
    convex[3] = { (range/2.f), -range};
    convex[4] = { -(range/2.f), -range};

    b.shape.size = 5;
}


inline
bool isOverlapped(const col2d::AABBox& a, const col2d::AABBox& b) 
{
    return ((a.right > b.left) &&
            (b.right > a.left) &&
            (a.top > b.bottom) &&
            (b.top > a.bottom));
}

inline
bool isOverlapped(const col2d::OBBox& a, const col2d::OBBox& b)
{
    return col2d_obb::isCollision(a,b);
}

inline
bool isOverlapped(const col2d::Convex& a, const col2d::Convex& b)
{
    return col2d_convex::SAT_intersect(a.vt, a.size, b.vt, b.size);
}

inline
bool isOverlapped(const col2d::Convex_4& a, const col2d::Convex_4& b)
{
    return col2d_convex::SAT_intersect(a.vt, a.size, b.vt, b.size);
}


inline
bool isOverlapped(const col2d::RotConvex& a, const col2d::RotConvex& b)
{
    int cnt = a.shape.size;
    col2d::Convex* ac = NewConvexStack(cnt);
    ac->size = cnt;

    cnt = b.shape.size;
    col2d::Convex* ab = NewConvexStack(cnt);
    ab->size = cnt;


    for(int i=0; i<ac->size; ++i )
        ac->vt[i] = a.center + a.shape.vt[i].rotateByAngle(XFloat2::ZERO, MATH_DEG_TO_RAD(a.rot));

    for(int i=0; i<ab->size; ++i )
        ab->vt[i] = b.center + b.shape.vt[i].rotateByAngle(XFloat2::ZERO, MATH_DEG_TO_RAD(b.rot));

    bool r = isOverlapped(*ac, *ab);

    return r;
}


