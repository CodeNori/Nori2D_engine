#pragma once
#include <malloc.h>

namespace col2d_convex {


inline
XFloat2 calculate_normalised_projection_axis(
    const XFloat2 &current_point, 
    const XFloat2 &next_point) 
{
    XFloat2 axis(
        -(next_point.y - current_point.y),
         (next_point.x - current_point.x) );
    return axis.getNormalized();
}


void compute_projections(
    const std::vector<XFloat2> &bounds_a,
    const std::vector<XFloat2> &bounds_b,
    const XFloat2 &axis_normalised,
    std::vector<float> &projections_a,
    std::vector<float> &projections_b)
{
    projections_a.clear();
    projections_b.clear();

    for (size_t i = 0; i < bounds_a.size(); i++) {
        const float projection_a = axis_normalised.dot(bounds_a[i]);
        const float projection_b = axis_normalised.dot(bounds_b[i]);
        projections_a.push_back(projection_a);
        projections_b.push_back(projection_b);
    }
}

bool is_overlapping(
    const std::vector<float> &projections_a,
    const std::vector<float> &projections_b) 
{
    const float max_projection_a = *std::max_element(projections_a.begin(), projections_a.end());
    const float min_projection_a = *std::min_element(projections_a.begin(), projections_a.end());
    const float max_projection_b = *std::max_element(projections_b.begin(), projections_b.end());
    const float min_projection_b = *std::min_element(projections_b.begin(), projections_b.end());

    // True if projection overlaps but does not necessarily mean the polygons are intersecting yet
    return !(max_projection_a < min_projection_b or 
             max_projection_b < min_projection_a);
}




bool separating_axis_intersect(
    const std::vector<XFloat2> &bounds_a, 
    const std::vector<XFloat2> &bounds_b)
{
    std::vector<float> projections_a;
    std::vector<float> projections_b;
    projections_a.reserve(bounds_a.size());
    projections_b.reserve(bounds_b.size());

    for (size_t i = 0; i < bounds_a.size(); i++) {
        const XFloat2 current_point = bounds_a[i];
        const XFloat2 next_point = bounds_a[(i + 1) % bounds_a.size()];
        const XFloat2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections(bounds_a, bounds_b, axis_normalised, projections_a, projections_b);
        
        if (!is_overlapping(projections_a, projections_b)) return false;
    }

    for (size_t i = 0; i < bounds_b.size(); i++) {
        const XFloat2 current_point = bounds_b[i];
        const XFloat2 next_point = bounds_b[(i + 1) % bounds_b.size()];
        const XFloat2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections(bounds_a, bounds_b, axis_normalised, projections_a, projections_b);

        if (!is_overlapping(projections_a, projections_b)) return false;
    }

    return true;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline
void compute_projections_0(
    const XFloat2* bounds_a, size_t bounds_a_size,
    const XFloat2 &axis_normalised,
    float* projections_a )
{
    for (size_t i = 0; i < bounds_a_size; i++) {
        projections_a[i] = axis_normalised.dot(bounds_a[i]);
    }
}


inline
bool is_overlapping_0(
    const float* projections_a, int projections_a_size,
    const float* projections_b, int projections_b_size) 
{
    float max_projection_a = projections_a[0];
    float min_projection_a = projections_a[0];
    for(int i=0; i<projections_a_size; ++i) {
        max_projection_a = max(max_projection_a, projections_a[i]);
        min_projection_a = min(min_projection_a, projections_a[i]);
    }

    float max_projection_b = projections_b[0];
    float min_projection_b = projections_b[0];
    for(int i=0; i<projections_b_size; ++i) {
        max_projection_b = max(max_projection_b, projections_b[i]);
        min_projection_b = min(min_projection_b, projections_b[i]);
    }

    return !(max_projection_a < min_projection_b or 
             max_projection_b < min_projection_a);
}


bool SAT_intersect(
    const XFloat2* bounds_a, int A_size,
    const XFloat2* bounds_b, int B_size)
{
    float* projections_a = (float*)_alloca(A_size*sizeof(float) );
    float* projections_b = (float*)_alloca(B_size*sizeof(float) );

    for (size_t i = 0; i < A_size; i++) {
        const XFloat2 current_point = bounds_a[i];
        const XFloat2 next_point = bounds_a[(i + 1) % A_size];
        const XFloat2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections_0(bounds_a, A_size, axis_normalised, projections_a);    
        compute_projections_0(bounds_b, B_size, axis_normalised, projections_b);    
        
        if (!is_overlapping_0(projections_a, A_size, 
                              projections_b, B_size)) return false;
    }

    for (size_t i = 0; i < B_size; i++) {
        const XFloat2 current_point = bounds_b[i];
        const XFloat2 next_point = bounds_b[(i + 1) % B_size];
        const XFloat2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections_0(bounds_a, A_size, axis_normalised, projections_a);    
        compute_projections_0(bounds_b, B_size, axis_normalised, projections_b);    

        if (!is_overlapping_0(projections_a, A_size, 
                              projections_b, B_size)) return false;
    }


    return true;
}


bool SAT_intersect_withPoint(
    const XFloat2* bounds_a, int A_size, const XFloat2 pt
    )
{
    float projections_b;
    float* projections_a = (float*)_alloca(A_size*sizeof(float) );

    for (size_t i = 0; i < A_size; i++) {
        const XFloat2 current_point = bounds_a[i];
        const XFloat2 next_point = bounds_a[(i + 1) % A_size];
        const XFloat2 axis_normalised = calculate_normalised_projection_axis(current_point, next_point);
        compute_projections_0(bounds_a, A_size, axis_normalised, projections_a);    
        projections_b = axis_normalised.dot(pt);
        
        if (!is_overlapping_0(projections_a, A_size, 
                              &projections_b, 1)) return false;
    }

    return true;
}



}



