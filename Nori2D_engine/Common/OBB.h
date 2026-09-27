

namespace col2d_obb {

    #define DEG_TO_RAD(x) ((x) * 0.0174532925f)

    inline
    float absDot(const XFloat2& a, const XFloat2& b)
    {
      return abs(a.x * b.x + a.y * b.y);
    }

    inline
    XFloat2 getDistanceV(const col2d::OBBox& a, const col2d::OBBox& b)
    {
      return XFloat2(
                (a.left + (a.width/ 2.f)) - (b.left + (b.width/ 2.f)) ,
                (a.top +  (a.height/ 2.f)) - (b.top + (b.height/ 2.f)) 
            );
    }

    inline
    XFloat2 getHeightV(const col2d::OBBox& a)
    {
      return XFloat2(
            a.height * cos( DEG_TO_RAD(a.rot - 90.f) ) / 2.f ,
            a.height * sin( DEG_TO_RAD(a.rot - 90.f) ) / 2.f 
            );
    }

    inline
    XFloat2 getWidthV(const col2d::OBBox& a)
    {
      return XFloat2(
                a.width * cosf( DEG_TO_RAD(a.rot) ) / 2.f ,
                a.width * sinf( DEG_TO_RAD(a.rot) ) / 2.f
             );
    }


    bool isCollision(const col2d::OBBox& a, const col2d::OBBox& b)
    { //final check
      XFloat2 dist = getDistanceV(a, b);
      XFloat2 vec[4] = {getHeightV(a), getHeightV(b), getWidthV(a), getWidthV(b)};

      for(int i=0; i<4; i++){
          float sum = 0;
          XFloat2 unit = vec[i].getNormalized();
          for(int j=0; j<4; j++){
              sum += absDot(vec[j], unit);
          }
          if(absDot(dist, unit) > sum){
              return false;
          }
      }
      return true;
    }

} // namespace obb_col




