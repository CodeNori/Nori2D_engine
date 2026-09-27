#pragma once


/*
	Keyboard, Mouse 입력을 받아 Game Command로 변환해서 전달한다.

*/

class IInputManager
{

public:

	// Mouse 이벤트 처리..
	virtual void onLMouseDown(WPARAM button, int x, int y) {};
	virtual void onLMouseUp(WPARAM button, int x, int y) {};
	virtual void onMMouseDown(WPARAM button, int x, int y) {};
	virtual void onMMouseUp(WPARAM button, int x, int y) {};
	virtual void onRMouseDown(WPARAM button, int x, int y) {};
	virtual void onRMouseUp(WPARAM button, int x, int y) {};

	virtual void onMouseMove(WPARAM button, int x, int y) {};
	virtual void onKeyDown(WPARAM wParam, LPARAM lParam) {};
	virtual void onKeyUp(WPARAM wParam, LPARAM lParam) {};
	virtual void OnMouseWheel(float wheelDelta, int x, int y) {};

};

