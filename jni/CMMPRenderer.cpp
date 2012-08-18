/*
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <iostream>
#include <math.h>

#include "CMMPRenderer.h"
#include "bitmap24.h"
#include "glu.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    ATTRIB_UV
};

using namespace std;

/**
 * コンストラクタ
 */
CMMPRenderer::CMMPRenderer(void)
{
    vertexShader = "\
            attribute vec2 a_TextureCoord;\
            attribute highp vec4 a_Position;\
            attribute vec4 a_Color;\
            uniform mediump mat4 u_ProjectionMatrix;\
            uniform mediump mat4 u_ViewMatrix;\
            uniform mediump mat4 u_PerspectiveMatrix;\
            varying vec2 v_TextureCoord;\
            varying vec4 v_Color;\
            void main(void)\
            {\
                gl_Position = u_PerspectiveMatrix * u_ViewMatrix * u_ProjectionMatrix * a_Position;\
                v_TextureCoord = a_TextureCoord;\
                v_Color = a_Color;\
            }\
            ";

    fragmentShader = "\
            precision mediump float;\
            uniform sampler2D u_Texture;\
            varying vec2 v_TextureCoord;\
            varying vec4 v_Color;\
            void main(void)\
            {\
                gl_FragColor = texture2D(u_Texture, v_TextureCoord);\
            }\
            ";

    hProgram = 0;
    hVbo = 0;
    hIbo = 0;
}

/**
 * デストラクタ
 */
CMMPRenderer::~CMMPRenderer(void)
{
}

/**
 * 初期化処理メソッド
 */
void CMMPRenderer::init(void)
{
    GLuint hVertexShader = loadShader(vertexShader, GL_VERTEX_SHADER);
    GLuint hFragmentShader = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
    hProgram = loadProgram(hVertexShader, hFragmentShader);
    uniforms[UNIFORM_PROJ_MAT] = glGetUniformLocation(hProgram, "u_ProjectionMatrix");
    uniforms[UNIFORM_VIEW_MAT] = glGetUniformLocation(hProgram, "u_ViewMatrix");
    uniforms[UNIFORM_PERSPECTIVE_MAT] = glGetUniformLocation(hProgram, "u_PerspectiveMatrix");
    uniforms[UNIFORM_TEXTURE] = glGetUniformLocation(hProgram, "u_Texture");

    GLfloat  pfVertices[] = {
            -10.0f, 20.0f, -10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            10.0f, 20.0f, -10.0f, 1.0f, 1.0f, .0f, 1.0f, 1.0f, 0.0f};
    GLushort pIndices[] = {0, 1, 2, 0, 2, 3};
    glGenBuffers(1, &hVbo);
    glBindBuffer(GL_ARRAY_BUFFER, hVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 36, pfVertices, GL_STATIC_DRAW);
    glGenBuffers(1, &hIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6, pIndices, GL_STATIC_DRAW);

    // テクスチャの準備
    glGenTextures(1, &hTexture);
    glBindTexture(GL_TEXTURE_2D, hTexture);
    CBitmap24 *bmp = new CBitmap24();
    bmp->Load(string("/sdcard/MMD/creeper_512x512.bmp"));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->GetWidth(), bmp->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bmp->GetPixelAddress(0, 0));
    bmp->Delete();
    delete bmp;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * サーフェス変更時の処理
 */
void CMMPRenderer::changed(int width, int height)
{
    // 視界の設定(透視投影を使用)
    float fAspect = static_cast<float>(width) / static_cast<float>(height);
    gluPerspective(27, fAspect, 1.0, 3000.0, perspectiveMatrix);
    glUniformMatrix4fv(uniforms[UNIFORM_PERSPECTIVE_MAT], 1, GL_FALSE, perspectiveMatrix);
}

/**
 * メイン描画メソッド
 */
void CMMPRenderer::render(void)
{
    glClearColor(1.0f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat pfIdentity[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, hVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hIbo);
    glBindTexture(GL_TEXTURE_2D, hTexture);

    // 頂点座標属性の有効化
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    glEnableVertexAttribArray(ATTRIB_UV);

    // 頂点座標属性のポインタの設定
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(0));
    glVertexAttribPointer(ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(sizeof(GLfloat) * 3));
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(sizeof(GLfloat) * 7));

    // 視点の設定
    static float g_fRad = 0.0f;
    g_fRad += 0.01f;
    if (g_fRad > 2 * 3.14159265f) {
        g_fRad -= 2 * 3.14159265f;
    } else if (g_fRad < 0) {
        g_fRad += 2 * 3.14159265f;
    }
    gluLookAt(50.0f * sin(g_fRad), 20.0f, -50.0f * cos(g_fRad), 0.0f, 12.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);

    // 変数の設定
    glUniformMatrix4fv(uniforms[UNIFORM_PROJ_MAT], 1, GL_FALSE, pfIdentity);
    glUniformMatrix4fv(uniforms[UNIFORM_VIEW_MAT], 1, GL_FALSE, viewMatrix);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(uniforms[UNIFORM_TEXTURE], 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
    glDisable(GL_TEXTURE_2D);
}

/**
 * シェーダをロードします。
 */
GLuint CMMPRenderer::loadShader(string shaderCode, GLuint shaderType)
{
    GLuint hShader;
    hShader = glCreateShader(shaderType);
    const char *shadar = shaderCode.c_str();
    glShaderSource(hShader, 1, &shadar, NULL);
    glCompileShader(hShader);
    GLint bShaderCompiled;
    glGetShaderiv(hShader, GL_COMPILE_STATUS, &bShaderCompiled);
    if(!bShaderCompiled)
    {
        // コンパイルエラー
        // エラーログのメッセージ長を取得
        int  nLogLength, nCharsWritten;
        glGetShaderiv(hShader, GL_INFO_LOG_LENGTH, &nLogLength);

        // エラーログを取得
        char* pInfoLog = new char[nLogLength];
        glGetShaderInfoLog(hShader, nLogLength, &nCharsWritten, pInfoLog);

        // エラーログ出力
        __android_log_print(ANDROID_LOG_ERROR, "MMP", "Shader Compile [%s]", pInfoLog);

        delete [] pInfoLog;
    }
    return hShader;
}

/**
 * シェーダをリンクします。
 */
GLuint CMMPRenderer::loadProgram(GLuint hVertexShader, GLuint hFragmentShader)
{
    GLuint hProg;
    hProg = glCreateProgram();
    glAttachShader(hProg, hVertexShader);
    glAttachShader(hProg, hFragmentShader);
    glBindAttribLocation(hProg, ATTRIB_VERTEX, "a_Position");
    glBindAttribLocation(hProg, ATTRIB_COLOR, "a_Color");
    glBindAttribLocation(hProg, ATTRIB_UV, "a_TextureCoord");
    glLinkProgram(hProg);
    GLint bLinked;
    glGetProgramiv(hProg, GL_LINK_STATUS, &bLinked);
    if(!bLinked)
    {
        // コンパイルエラー
        // エラーログのメッセージ長を取得
        int  nLogLength, nCharsWritten;
        glGetShaderiv(hProg, GL_INFO_LOG_LENGTH, &nLogLength);

        // エラーログを取得
        char* pInfoLog = new char[nLogLength];
        glGetShaderInfoLog(hProg, nLogLength, &nCharsWritten, pInfoLog);

        // エラーログ出力
        __android_log_print(ANDROID_LOG_ERROR, "MMP", "Shader Link [%s]", pInfoLog);

        delete [] pInfoLog;
    }
    glUseProgram(hProg);
    return hProg;
}
