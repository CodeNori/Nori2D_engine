#pragma once

#define USHORT unsigned short
#define BYTE unsigned char
#define CHAR char

#define PngImageID USHORT


class PngImage
{
public:

	USHORT idx;
public:
	struct Frame {
		USHORT x,y;
		USHORT size_x, size_y;	
	};
	struct FrameUV {
		float x1,x2,y1,y2;
	};
	PngImage() :idx(0xFFFF) {}
	PngImage(USHORT i) {idx = i;}
	bool operator <(const PngImage& rhs) const { return idx < rhs.idx; }
	bool operator==(const PngImage& rhs) const { return idx == rhs.idx; }
	bool operator!=(const PngImage& rhs) const { return idx != rhs.idx; }
	bool isNull() const { return idx == 0; }

	const CHAR* GetFileName() const;
	void GetWidthHeight(int& width, int& height) const;
	void GetWidthHeight(float& width, float& height) const;

	void* GetUserData() const;
	void SetUserData(void* ud);

	ID3D11ShaderResourceView* getDxRes();

	//~~ Frame ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void GetFrame(Frame& frame, int no) const;
	void GetFrameUV(FrameUV& frame, int no) const;
	void SetFrame(Frame* frame);

	//~~ Manager (static ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	static PngImage Get(const CHAR* fileName);
};


struct FrameAnimationInfo
{
	float    time;      //  한장 한장 넘어갈때 시간...Frame간의 간격 시간
    USHORT   start;      // Frame array 의 어디부터 시작하는가?  일반적으로  0
    BYTE     count;      // Frame 의 갯수
    BYTE     frame_no;    // 현재 출력되고 있는 Frame번호

    USHORT   anchor_x,anchor_y;   // Anchor 

};

struct PngFrame
{
	PngImage	png;
	XFloat2    leftTop;
	XFloat2    size;
	XFloat2    uv0;
	XFloat2    uv1;
};

