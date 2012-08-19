/*
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

#include "CPmdRenderer.h"
#include "CPmd.h"
#include "CImageLoader.h"
#include "CMMPRenderer.h"

CPmdRenderer::CPmdRenderer(void)
{
    pmd = NULL;
    hPmdVertex = 0;
    hPmdIndex = NULL;
}

CPmdRenderer::~CPmdRenderer(void)
{
    if (pmd != NULL) {
        delete pmd;
        pmd = NULL;
    }
    if (hPmdIndex != NULL) {
        delete [] hPmdIndex;
        hPmdIndex = NULL;
    }
}

void CPmdRenderer::load(string pmdPath)
{
    // pmdファイルのロード
    const char *path = pmdPath.c_str();
    pmd = new CPmd();
    pmd->load(const_cast<char *>(path));
    unsigned short *lpwFaceIndex = pmd->mlpwFaceIndex;
    hPmdIndex = new GLuint[pmd->mdwMaterialCount];
    glGenBuffers(1, &hPmdVertex);
    glBindBuffer(GL_ARRAY_BUFFER, hPmdVertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PMDVERTEX) * pmd->mdwVertexCount, pmd->mlpVertex[0].fPosition, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(pmd->mdwMaterialCount, hPmdIndex);
    for (unsigned long i = 0; i < pmd->mdwMaterialCount; i++) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hPmdIndex[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * pmd->mlpMaterial[i].dwFaceNumber, lpwFaceIndex, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        lpwFaceIndex += pmd->mlpMaterial[i].dwFaceNumber;
    }
    loadTexture();
}

void CPmdRenderer::render(GLuint *uniforms)
{
    // pmdの描画
    glBindBuffer(GL_ARRAY_BUFFER, hPmdVertex);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_UV);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(PMDVERTEX), BUFFER_OFFSET(0));
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(PMDVERTEX), BUFFER_OFFSET(sizeof(float) * 6));

    for (unsigned int i = 0; i < pmd->mdwMaterialCount; i++) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hPmdIndex[i]);

        if (pmd->mlpMaterial[i].byEdgeFlag != 1) {
            static const float fLightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
            static const float fLightAmb[] = {0.5f, 0.5f, 0.5f, 1.0f};
            float color[4];
            color[0] = pmd->mlpMaterial[i].fMirrorColor[0] + fLightAmb[0];
            color[1] = pmd->mlpMaterial[i].fMirrorColor[1] + fLightAmb[1];
            color[2] = pmd->mlpMaterial[i].fMirrorColor[2] + fLightAmb[2];
            color[3] = pmd->mlpMaterial[i].fAlpha + fLightAmb[3];
            color[0] = (color[0] > 1.0f) ? 1.0f : color[0];
            color[1] = (color[1] > 1.0f) ? 1.0f : color[1];
            color[2] = (color[2] > 1.0f) ? 1.0f : color[2];
            color[3] = (color[3] > 1.0f) ? 1.0f : color[3];
            color[0] *= pmd->mlpMaterial[i].fDiffuseColor[0] * fLightDif[0];
            color[1] *= pmd->mlpMaterial[i].fDiffuseColor[1] * fLightDif[1];
            color[2] *= pmd->mlpMaterial[i].fDiffuseColor[2] * fLightDif[2];
            color[3] *= pmd->mlpMaterial[i].fAlpha * fLightDif[3];
            glUniform4fv(uniforms[UNIFORM_COLOR], 1, color);
        } else {
            float color[] = {0.0f, 0.0f, 0.0f, 0.0f};
            glUniform4fv(uniforms[UNIFORM_COLOR], 1, color);
        }

        if (pmd->mlpMaterial[i].fAlpha > 0.99f) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }

        GLuint uiTexId = pmd->mlpMaterial[i].uiTexId;
        if (uiTexId != 0xFFFFFFFF) {
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, uiTexId);
            glUniform1i(uniforms[UNIFORM_TEXTURE], 0);
        } else {
            glDisable(GL_TEXTURE_2D);
        }
        glDrawElements(GL_TRIANGLES, pmd->mlpMaterial[i].dwFaceNumber, GL_UNSIGNED_SHORT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CPmdRenderer::loadTexture(void)
{
    // テクスチャの読み込み
    string parentDir = pmd->mszDirPath + string("/");
    string textureFileList[100];
    GLuint textureNoList[100];
    int nTexPos = 0;
    for (unsigned int i = 0; i < pmd->mdwMaterialCount; i++) {
        string textureFile = parentDir + pmd->mlpMaterial[i].szTextureFileName1;
        if (pmd->mlpMaterial[i].szTextureFileName1 != string("")) {
            int j;
            for (j = 0; j < nTexPos; j++) {
                if (textureFile == textureFileList[j]) {
                    pmd->mlpMaterial[i].uiTexId = textureNoList[j];
                    break;
                }
            }
            if (j == nTexPos) {
                CImageLoader *imageLoader = new CImageLoader();
                imageLoader->setImage(textureFile);
                int loadResult = imageLoader->loadImage();
                if (loadResult < 0) {
                    continue;
                }

                textureFileList[nTexPos] = textureFile;

                glGenTextures(1, &pmd->mlpMaterial[i].uiTexId);
                textureNoList[nTexPos] = pmd->mlpMaterial[i].uiTexId;

                glBindTexture(GL_TEXTURE_2D, textureNoList[nTexPos]);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                if (imageLoader->getDepth() == 24) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageLoader->getWidth(), imageLoader->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imageLoader->getImageData());
                } else {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageLoader->getWidth(), imageLoader->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageLoader->getImageData());
                }
                delete imageLoader;
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glBindTexture(GL_TEXTURE_2D, 0);

                nTexPos++;
            }
        }
    }
}
