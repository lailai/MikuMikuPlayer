/*
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#ifndef _CPMDRENDERER_H_
#define _CPMDRENDERER_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>

#include "CPmd.h"

using namespace std;

class CPmdRenderer
{
public:
    CPmdRenderer(void);
    ~CPmdRenderer(void);
    void load(string pmdPath);
    void render(GLuint *uniforms);
private:
    CPmd *pmd;
    GLuint hPmdVertex;
    GLuint *hPmdIndex;
    void loadTexture(void);
};

#endif
