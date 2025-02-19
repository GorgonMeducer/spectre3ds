#ifndef GS_H
#define GS_H

#include <3ds.h>
#include "math3.h"

#define GS_MATRIXSTACK_SIZE (8)

typedef enum
{
	GS_PROJECTION = 0,
	GS_MODELVIEW = 1,
	GS_MATRIXTYPES
}GS_MATRIX;

typedef struct
{
	u8* data;
	u32 currentSize; // in bytes
	u32 maxSize; // in bytes
	u32 numVertices;
	u32* commands;
	u32 commandsSize;
}gsVbo_s;


void gsInit(shaderProgram_s* shader);
void gsExit(void);
void gsShaderSet(shaderProgram_s* shader);

void gsStartFrame(void);
void gsAdjustBufferMatrices(mtx44 transformation);

void* gsLinearAlloc(size_t size);
void gsLinearFree(void* mem);

float* gsGetMatrix(GS_MATRIX m);
int gsLoadMatrix(GS_MATRIX m, float* data);
int gsPushMatrix();
int gsPopMatrix();
int gsMatrixMode(GS_MATRIX m);

void gsLoadIdentity();
void gsFrustum(float left, float right, float bottom, float top, float near, float far);
void gsProjectionMatrix(float fovy, float aspect, float near, float far);
void gsOrthoMatrix(float width, float height, float near, float far);
void gsRotateX(float x);
void gsRotateY(float y);
void gsRotateZ(float z);
void gsScale(float x, float y, float z);
void gsTranslate(float x, float y, float z);
int gsMultMatrix(float* data);

int gsVboInit(gsVbo_s* vbo);
int gsVboCreate(gsVbo_s* vbo, u32 size);
int gsVboClear(gsVbo_s* vbo);
int gsVboFlushData(gsVbo_s* vbo);
int gsVboDestroy(gsVbo_s* vbo);
int gsVboDraw(gsVbo_s* vbo);
int gsVboDrawDirectly(gsVbo_s* vbo);
void* gsVboGetOffset(gsVbo_s* vbo);
int gsVboAddData(gsVbo_s* vbo, void* data, u32 size, u32 units);

#define GS_NO_NORMALS

typedef struct
{
	vect3Df_s position;
	float texcoord[2];
#ifndef GS_NO_NORMALS
	vect3Df_s normal;
#endif
}faceVertex_s;

typedef struct
{
	vect3Df_s position;
	float texcoord[2];
	float lightmap[2];
}bspVertex_t;

typedef struct
{
	unsigned char position[4];
	float texcoord[2];
}mdlVertex_s;

//GPU framebuffer address
extern u32* gsGpuOut;
//GPU depth buffer address
extern u32* gsGpuDOut;
//background color (blue)
extern u32 gsBackgroundColor;

#endif
