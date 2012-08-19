/**
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#ifndef _CPMD_H_
#define _CPMD_H_

/**
 * ヘッダ情報構造体
 */
typedef struct tagPmdHeader {
    char szMagic[4];	// PMD情報としてはサイズ3だが、終端記号がないのでサイズ4とする
    float fVersion;
    char szModelName[20];
    char szComment[256];
} PMDHEADER;

/**
 * 頂点情報構造体
 */
typedef struct tagPmdVertex {
    float fPosition[3];
    float fNormalVector[3];
    float fUv[2];
    unsigned short wBoneNumber[2];
    unsigned char byBoneWeight;
    unsigned char byEdgeFlag;
} PMDVERTEX;

/**
 * 材質情報構造体
 */
typedef struct tagPmdMaterial {
    float fDiffuseColor[3];
    float fAlpha;
    float fSpecularity;
    float fSpecularColor[3];
    float fMirrorColor[3];
    unsigned char byToonIndex;
    unsigned char byEdgeFlag;
    unsigned long dwFaceNumber;
    char szTextureFileName[21];	// PMD情報としてはサイズ20だが、終端記号がない場合もあるのでサイズ21とする
    char szTextureFileName1[21];	// テクスチャファイルとスフィアファイルに分けるためのバッファ
    char szTextureFileName2[21];
    unsigned int uiTexId;
} PMDMATERIAL;

/**
 * ボーン情報構造体
 */
typedef struct tagPmdBone {
    char szBoneName[20];
    unsigned short wParentBoneIndex;
    unsigned short wTailBoneIndex;
    unsigned char byBoneType;
    unsigned short wIKBoneIndex;
    float fBoneHeadPos[3];
    float fQuaternion[4];
} PMDBONE;

/**
 * PMD情報をまとめたクラス
 */
class CPmd
{
public:
    char *mszFilePath;
    char *mszDirPath;
    PMDHEADER mHeader;
    unsigned long mdwVertexCount;
    PMDVERTEX *mlpVertex;
    unsigned long mdwFaceCount;
    unsigned short *mlpwFaceIndex;
    unsigned long mdwMaterialCount;
    PMDMATERIAL *mlpMaterial;
    unsigned short mwBoneCount;
    PMDBONE *mlpBone;

    CPmd(void);
    virtual ~CPmd(void);
    int load(char *szFileName);
    void free(void);
};

#endif
