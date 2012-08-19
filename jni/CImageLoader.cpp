/*
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#include <android/log.h>
#include <iostream>

#include "CImageLoader.h"
#include "bitmap24.h"

using namespace std;

/**
 * コンストラクタ<br />
 * 空のインスタンスを生成します。
 */
CImageLoader::CImageLoader(void)
{
    imageData = NULL;
    imageWidth = 0;
    imageHeight = 0;
    imageDepth = 0;
    string filePath("");
    setImage(filePath);
}

/**
 * コンストラクタ<br />
 * 画像ファイルパスを持ったインスタンスを生成します。
 */
CImageLoader::CImageLoader(string filePath)
{
    imageData = NULL;
    imageWidth = 0;
    imageHeight = 0;
    imageDepth = 0;
    setImage(filePath);
}

/**
 * デストラクタ<br />
 */
CImageLoader::~CImageLoader(void)
{
    if (imageData != NULL) {
        delete [] imageData;
        imageData = NULL;
    }
}

/**
 * 画像ファイルパスを設定します。
 * @param filePath 画像ファイルパス
 */
void CImageLoader::setImage(string filePath)
{
    imageFilePath = filePath;
}

/**
 * 画像ファイルを読み込みます。
 */
int CImageLoader::loadImage(void)
{
    string::size_type offset = imageFilePath.rfind(".bmp");
    if (offset == string::npos) {
        offset = imageFilePath.rfind(".BMP");
    }
    if (offset == string::npos) {
        return -1;
    }
    if (imageFilePath.substr(offset) == string(".bmp") || imageFilePath.substr(offset) == string(".BMP")) {
__android_log_print(ANDROID_LOG_INFO, "MMP", "imageFilePath = %s", imageFilePath.c_str());
        CBitmap24 *bitmap = new CBitmap24();
        bitmap->Load(imageFilePath);
        imageWidth = bitmap->GetWidth();
        imageHeight = bitmap->GetHeight();
        imageDepth = 24;
        unsigned char *tmp = reinterpret_cast<unsigned char *>(bitmap->GetPixelAddress(0, 0));
        imageData = new unsigned char[imageWidth * imageHeight * (imageDepth / 8)];
        for (int i = 0; i < imageWidth * imageHeight * (imageDepth / 8); i++) {
            imageData[i] = tmp[i];
        }
        delete bitmap;
    }
    return 0;
}

/**
 * 画像データを取得します。
 * @param imageDataBuffer 予めメモリを確保したバッファ
 */
//void CImageLoader::getImageData(unsigned char *imageDataBuffer)
unsigned char *CImageLoader::getImageData(void)
{
//    for (int i = 0; i < imageWidth * imageHeight * (imageDepth / 8); i++) {
//        imageDataBuffer[i] = imageData[i];
//    }
	return imageData;
}

/**
 * 画像の横幅を取得します。
 * @return 画像の横幅
 */
int CImageLoader::getWidth(void)
{
    return imageWidth;
}

/**
 * 画像の高さを取得します。
 * @return 画像の高さ
 */
int CImageLoader::getHeight(void)
{
    return imageHeight;
}

/**
 * 画像の深さを取得します。
 * @return 画像の深さ
 */
int CImageLoader::getDepth(void)
{
    return imageDepth;
}
