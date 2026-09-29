#pragma once

#include "Common/entt.hpp"
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <string>
#include <map> 
#include <unordered_map>
#include <vector>
#include <deque>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <functional>

#include "Common/Common.h"

typedef DirectX::XMFLOAT4 XFloat4;
typedef DirectX::XMFLOAT3 XFloat3;
typedef entt::entity ActorID;

#include "DxVars.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "Lib/lua55.lib")



extern entt::registry ecs1;


