#pragma once

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(_ptr) { if(_ptr){_ptr->Release();} _ptr = nullptr; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(_ptr) { if(_ptr){ delete (_ptr);} _ptr = nullptr; }
#endif

// new callbacks based on C++11
#define AX_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define AX_CALLBACK_1(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define AX_CALLBACK_2(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define AX_CALLBACK_3(__selector__, __target__, ...)                                                          \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
              ##__VA_ARGS__)

#ifndef D2_INDEX

#define D2_INDEX  USHORT

struct D2_VERTEX
{
	XFloat3  pos;
	XFloat2  uv;
	unsigned int   col;
};

#endif

struct Dx11Vars
{
	int width;
	int height;


	HINSTANCE	hInstance;	
	std::string titleBarText;
	bool		titleBarStats;
	HWND		hWnd;

	//D3D_FEATURE_LEVEL		dxFeatureLevel;
	IDXGISwapChain* swapChain = 0;
	ID3D11Device* device = 0;
	ID3D11DeviceContext* context = 0;

	ID3D11RenderTargetView* backBufferRTV = 0;
	ID3D11DepthStencilView* depthStencilView = 0;

	D3D_FEATURE_LEVEL		dxFeatureLevel;

	class D2Renderer* renderer;
	class DxWindow* window;
	class IGame* game;

	float getHalfWidth()  {return ((float)width)/2.f;}
	float getHalfHeight() {return ((float)height)/2.f;}

	bool OpenWindow2D();
	void CloseWindow2D();
	HRESULT Run();

};



extern Dx11Vars g_Dx11;





