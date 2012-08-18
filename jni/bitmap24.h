#ifndef __BITMAP24_H__
#define __BITMPA24_H__

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef long  LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

#ifndef _WINDOWS_
/*BITMAPFILEHEADER*/
struct BITMAPFILEHEADER
{
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
};

/*BITMAPINFOHEADER*/
struct BITMAPINFOHEADER
{
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};
#endif
/* COLOR構造体 */
struct COLOR24
{
	BYTE r, g, b;
};

const COLOR24 COLOR24_BLACK = {0, 0, 0};
const COLOR24 COLOR24_WHITE = {255, 255, 255};
#ifndef _WINDOWS_
const long BI_RGB = 0L;
#endif

struct MY_BITMAP
{
	BITMAPFILEHEADER bmf;
	BITMAPINFOHEADER bmi;
};

/*
 * 24ビットBitmapクラス
 */
class CBitmap24
{
private:
	int m_Width;
	int m_Height;
	MY_BITMAP m_Header;
	void *m_Buffer;
	COLOR24 m_OutColor;

private:
public:
	CBitmap24(void);
	CBitmap24(int width, int height);
	virtual ~CBitmap24(void);

	void InitHeader();
	void Delete();
	void Resize(int width, int height);
	void Copy(CBitmap24 *obj);
	void Load(string filename);
	void Save(string filename);

	int GetWidth() {return m_Width;};
	int GetHeight() {return m_Height;};
	MY_BITMAP *GetHeader() {return &m_Header;};
	void SetHeader(MY_BITMAP *header) {m_Header = *header;};
	void *GetBuffer() {return m_Buffer;};
	void *GetPixelAddress(int x, int y);
	void *GetPixelAddressNC(int x, int y){return (BYTE *)m_Buffer + ((m_Width * y + x) * sizeof(COLOR24));};
	void SetPixel(int x, int y, COLOR24 *color);
	COLOR24 GetPixel(int x, int y);
	COLOR24 GetOutColor() {return m_OutColor;};
	void SetOutColor(COLOR24 color) {m_OutColor = color;};
};

#endif
