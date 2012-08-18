#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#ifndef _GLU_H_
#define _GLU_H_

void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
			   GLfloat centerx, GLfloat centery, GLfloat centerz,
			   GLfloat upx, GLfloat upy, GLfloat upz,
			   GLfloat *m);

void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *m);

#endif
