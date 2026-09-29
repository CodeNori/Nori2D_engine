#include "pch.h"
#include "DemoGame.h"
#include "VertexCollector.h"
#include "DxVars.h"
#include "DxImGui.h"
#include "GameData.h"

#define RGB1(r,g,b)   (0xFF000000 | RGB(r,g,b))


DWORD  colorArray[] =
{
    RGB1(255, 0, 0),
    RGB1(200, 0, 0),
    RGB1(150, 0, 0),
    RGB1(100, 0, 0),
    RGB1(50, 0, 0),

    RGB1(0, 50,  0),
    RGB1(0, 100,  0),
    RGB1(0, 150,  0),
    RGB1(0, 200,  0),
    RGB1(0, 255,  0),

    RGB1(0,0, 255),
    RGB1(0,0, 200),
    RGB1(0,0, 150),
    RGB1(0,0, 100),
    RGB1(0,0, 50),

    RGB1(255, 255, 255),
    RGB1(255, 255, 255),
    RGB1(255, 255, 255)
};

DemoGame::DemoGame()
{
    sp_tree.SetImage(PngImage::Get(tree_FILE_NAME),  g_tree_frames, tree_animInfo3);
    sp_tree.SetPosition( XFloat2(500.f, 400.f) );
    sp_tree.SetSize({ (float)g_tree_frames[tree_animInfo3.start].size_x, 
                       (float)g_tree_frames[tree_animInfo3.start].size_y   });
    sp_tree.collisionBox = { -20, -60, -20+30, -60+60 };



    sp_char.SetImage(PngImage::Get(farmer_FILE_NAME),
                            g_char_frames_front,
                            char_animInfo);
    sp_char.SetPosition( XFloat2(300.f, 200.f) );
    sp_char.SetSize( {64.f, 64.f} );
    sp_char.collisionBox = { -12, -34, -12+24, -34+32 };
    sp_char.color = RGB1(255, 0, 0);


    sp_explosion.SetImage(PngImage::Get(explosion_FILE_NAME),
                            g_explosion_frames,
                            explosion_animInfo);
    sp_explosion.SetPosition(XFloat2(600.f, 300.f));
    sp_explosion.SetSize({ 64.f, 64.f });
    sp_explosion.collisionBox = { -12, -12, -12 + 32, -12 + 32 };

}

void DemoGame::Update(float delta)
{
    rot += delta;
    if (rot > MATH_PIX2) rot -= MATH_PIX2;
    sp_tree.rotation = rot;

    one_second += delta;
    if (one_second >= 1.f) {
        one_second = 0.f;
        sp_char.color = colorArray[char_color++];
        if (char_color >= 18) char_color = 0;
    }
}

void DemoGame::Draw(float delta)
{
    {
        VertexCollector vc;

        sp_char.UpdateAnimation(delta);
        sp_explosion.UpdateAnimation(delta);

        vc.Add(sp_tree);
        vc.Add(sp_char);
        vc.Add(sp_explosion);
        vc.Draw();
    }
     
    {
        LineCollector lvc;

        XFloat2 line[2];
        line[0] = { 500.f, 10.f };
        line[1] = { 500.f, 200.f };

        lvc.Add(line, 2, RGB1(0, 255, 0) );

        XFloat2 box[4];
        box[0] = { 300.f, 200.f };
        box[1] = { 500.f, 200.f };
        box[2] = { 500.f, 400.f };
        box[3] = { 300.f, 400.f };

        USHORT boxIdx[8];
        boxIdx[0] = 0;
        boxIdx[1] = 1;
        boxIdx[2] = 1;
        boxIdx[3] = 2;
        boxIdx[4] = 2;
        boxIdx[5] = 3;
        boxIdx[6] = 3;
        boxIdx[7] = 0;

        lvc.Add(box, 4, boxIdx, 8, RGB1(255, 0, 0));

        lvc.AddBox(sp_tree.getCollisionBox(), RGB1(255, 0, 0));
        lvc.AddBox(sp_char.getCollisionBox(), RGB1(255, 0, 0));
        lvc.AddBox(sp_explosion.getCollisionBox(), RGB1(255, 0, 0));
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


