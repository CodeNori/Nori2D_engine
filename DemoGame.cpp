#include "pch.h"
#include "DemoGame.h"
#include "VertexCollector.h"
#include "DxVars.h"
#include "DxImGui.h"
#include "GameData.h"

#define RGB1(r,g,b)   (0xFF000000 | RGB(r,g,b))


DemoGame::DemoGame()
{
    sp.SetImage(PngImage::Get(tree_FILE_NAME),  g_tree_frames, tree_animInfo);
    sp.SetPosition( XFloat2(500.f, 400.f) );
    sp.SetSize( {180.f, 180.f} );



    sp_char.SetImage(PngImage::Get(farmer_FILE_NAME),
                            g_char_frames_right,
                            char_animInfo);
    sp_char.SetPosition( XFloat2(300.f, 300.f) );
    sp_char.SetSize( {64.f, 64.f} );


    sp_explosion.SetImage(PngImage::Get(explosion_FILE_NAME),
                            g_explosion_frames,
                            explosion_animInfo);
    sp_explosion.SetPosition(XFloat2(600.f, 300.f));
    sp_explosion.SetSize({ 64.f, 64.f });

}

void DemoGame::Update(float delta)
{

}

void DemoGame::Draw(float delta)
{
    {
        VertexCollector vc;

        sp_char.UpdateAnimation(delta);
        sp_explosion.UpdateAnimation(delta);

        vc.Add(sp);
        vc.Add(sp_char);
        vc.Add(sp_explosion);
        vc.Draw();
    }
     
    {
        LineVertexCollector lvc;

        XFloat2 line[2];
        line[0] = { 500.f, 10.f };
        line[1] = { 500.f, 200.f };

        lvc.Add(line, 2, RGB1(0, 255, 0) );

        XFloat2 box[4];
        box[0] = { 100.f, 20.f };
        box[1] = { 300.f, 20.f };
        box[2] = { 300.f, 100.f };
        box[3] = { 100.f, 100.f };

        USHORT boxIdx[8];
        boxIdx[0] = 0;
        boxIdx[1] = 1;
        boxIdx[2] = 1;
        boxIdx[3] = 2;
        boxIdx[4] = 2;
        boxIdx[5] = 3;
        boxIdx[6] = 3;
        boxIdx[7] = 0;

        lvc.Add(box, 4, boxIdx, 8, 0xFF0000FF);

        lvc.Draw();
    }

}

void DemoGame::DrawGUI(float delta)
{
    if ( ImGui::Begin(u8"호우시절") )
    {
        ImGui::BulletText(" %d ", mRenderedSpriteCount);

    }
    ImGui::End();
}


