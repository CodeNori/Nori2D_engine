#pragma once



namespace iso_tile
{

    extern XFloat2 g_screen_offset;
    extern XFloat2 to_screen_coord(const XFloat2 tile);
    extern XFloat2 to_grid_coord(const XFloat2 screen);

    inline
    POINT to_grid_coord_i(const XFloat2 screen)
    {
        XFloat2 pos = to_grid_coord(screen);
        return { floorf(pos.x), floorf(pos.y) };
    }

}
