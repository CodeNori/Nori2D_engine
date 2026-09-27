#include "pch.h"
#include "DemoGame.h"
#include "VertexCollector.h"
#include "DxVars.h"
#include "DxImGui.h"
#include "GameData.h"



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
    VertexCollector vc;

    sp_char.UpdateAnimation(delta);
    sp_explosion.UpdateAnimation(delta);

    vc.Add(sp);
    vc.Add(sp_char);
    vc.Add(sp_explosion);
    vc.Draw(g_Dx11.renderer);
}

void DemoGame::DrawGUI(float delta)
{
    if ( ImGui::Begin(u8"호우시절") )
    {
        ImGui::BulletText(" %d ", mRenderedSpriteCount);

    }
    ImGui::End();
}


