#pragma once

// Shorthand macros to simplify the TGLFunc<> declarations:
#define TGLFUNC_NAME(funcName) STRING_JOIN2(_real_, funcName)
#define TGLFUNC_DECL(funcName) TGLFUNC_NAME(funcName){ STRINGIZE(funcName) }
//#define TGLFUNC_CALL(funcName, ...) (TGLFUNC_NAME(funcName).callCount++, TGLFUNC_NAME(funcName).funcPtr(__VA_ARGS__))
#define TGLFUNC_CALL(funcName, ...) TGLFUNC_NAME(funcName).funcPtr(__VA_ARGS__)


// ================================================================================================
// These macros simplify defining our wrapper functions:
// ================================================================================================

//
// Functions with a return value:
//

#define GLFUNC_0_WRET(retType, funcName)                         \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(void)           \
    {                                                            \
        static GLProxy::TGLFunc<retType> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName);                           \
    }

#define GLFUNC_1_WRET(retType, funcName, t0, p0)                     \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0)              \
    {                                                                \
        static GLProxy::TGLFunc<retType, t0> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName, p0);                           \
    }

#define GLFUNC_2_WRET(retType, funcName, t0, p0, t1, p1)                 \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1)           \
    {                                                                    \
        static GLProxy::TGLFunc<retType, t0, t1> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName, p0, p1);                           \
    }

#define GLFUNC_3_WRET(retType, funcName, t0, p0, t1, p1, t2, p2)             \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2)        \
    {                                                                        \
        static GLProxy::TGLFunc<retType, t0, t1, t2> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName, p0, p1, p2);                           \
    }

#define GLFUNC_4_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3)         \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3)     \
    {                                                                            \
        static GLProxy::TGLFunc<retType, t0, t1, t2, t3> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName, p0, p1, p2, p3);                           \
    }

#define GLFUNC_5_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4)     \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4)  \
    {                                                                                \
        static GLProxy::TGLFunc<retType, t0, t1, t2, t3, t4> TGLFUNC_DECL(funcName); \
        return TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4);                           \
    }

#define GLFUNC_8_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7) \
    {                                                                                                    \
        static GLProxy::TGLFunc<retType, t0, t1, t2, t3, t4, t5, t6, t7> TGLFUNC_DECL(funcName);         \
        return TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5, p6, p7);                                   \
    }

//
// Functions returning void/nothing:
//

#define GLFUNC_0(funcName)                                    \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(void)           \
    {                                                         \
        static GLProxy::TGLFunc<void> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName);                               \
    }

#define GLFUNC_1(funcName, t0, p0)                                \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0)              \
    {                                                             \
        static GLProxy::TGLFunc<void, t0> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName, p0);                               \
    }

#define GLFUNC_2(funcName, t0, p0, t1, p1)                            \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1)           \
    {                                                                 \
        static GLProxy::TGLFunc<void, t0, t1> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName, p0, p1);                               \
    }

#define GLFUNC_3(funcName, t0, p0, t1, p1, t2, p2)                        \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2)        \
    {                                                                     \
        static GLProxy::TGLFunc<void, t0, t1, t2> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName, p0, p1, p2);                               \
    }

#define GLFUNC_4(funcName, t0, p0, t1, p1, t2, p2, t3, p3)                    \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3)     \
    {                                                                         \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3);                               \
    }

#define GLFUNC_5(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4)                \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4)  \
    {                                                                             \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4> TGLFUNC_DECL(funcName); \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4);                               \
    }

#define GLFUNC_6(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)              \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5) \
    {                                                                                   \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4, t5> TGLFUNC_DECL(funcName);   \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5);                                 \
    }

#define GLFUNC_7(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)             \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6) \
    {                                                                                          \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4, t5, t6> TGLFUNC_DECL(funcName);      \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5, p6);                                    \
    }

#define GLFUNC_8(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)            \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7) \
    {                                                                                                 \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4, t5, t6, t7> TGLFUNC_DECL(funcName);         \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5, p6, p7);                                       \
    }

#define GLFUNC_9(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)           \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8) \
    {                                                                                                        \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4, t5, t6, t7, t8> TGLFUNC_DECL(funcName);            \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5, p6, p7, p8);                                          \
    }

#define GLFUNC_10(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)         \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8, t9 p9) \
    {                                                                                                               \
        static GLProxy::TGLFunc<void, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9> TGLFUNC_DECL(funcName);               \
        TGLFUNC_CALL(funcName, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);                                             \
    }


// Macros for declaring functions in the header
//
// Functions with a return value:
//

#define GLFUNC_DECL_0_WRET(retType, funcName)                         \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(void);

#define GLFUNC_DECL_1_WRET(retType, funcName, t0, p0)                     \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0);

#define GLFUNC_DECL_2_WRET(retType, funcName, t0, p0, t1, p1)                 \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1);

#define GLFUNC_DECL_3_WRET(retType, funcName, t0, p0, t1, p1, t2, p2)             \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2);

#define GLFUNC_DECL_4_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3)         \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3);

#define GLFUNC_DECL_5_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4)     \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4);

#define GLFUNC_DECL_8_WRET(retType, funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) \
    GLPROXY_EXTERN retType GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7);

//
// Functions returning void/nothing:
//

#define GLFUNC_DECL_0(funcName)                                    \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(void);

#define GLFUNC_DECL_1(funcName, t0, p0)                                \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0);

#define GLFUNC_DECL_2(funcName, t0, p0, t1, p1)                            \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1);

#define GLFUNC_DECL_3(funcName, t0, p0, t1, p1, t2, p2)                        \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2);

#define GLFUNC_DECL_4(funcName, t0, p0, t1, p1, t2, p2, t3, p3)                    \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3);

#define GLFUNC_DECL_5(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4)                \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4);

#define GLFUNC_DECL_6(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)              \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5);

#define GLFUNC_DECL_7(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)             \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6);

#define GLFUNC_DECL_8(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)            \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7);

#define GLFUNC_DECL_9(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)           \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8);

#define GLFUNC_DECL_10(funcName, t0, p0, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)         \
    GLPROXY_EXTERN void GLPROXY_DECL funcName(t0 p0, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8, t9 p9);

//
// WGL functions:
//
GLFUNC_DECL_0_WRET(HDC, wglGetCurrentDC);
GLFUNC_DECL_0_WRET(HGLRC, wglGetCurrentContext);
GLFUNC_DECL_1_WRET(BOOL, wglDeleteContext, HGLRC, hglrc);
GLFUNC_DECL_1_WRET(BOOL, wglSwapBuffers, HDC, hdc);
GLFUNC_DECL_1_WRET(HGLRC, wglCreateContext, HDC, hdc);
GLFUNC_DECL_1_WRET(int, wglGetPixelFormat, HDC, hdc);
GLFUNC_DECL_2_WRET(BOOL, wglMakeCurrent, HDC, hdc, HGLRC, hglrc);
GLFUNC_DECL_2_WRET(BOOL, wglShareLists, HGLRC, hglrc1, HGLRC, hglrc2);
GLFUNC_DECL_2_WRET(BOOL, wglSwapLayerBuffers, HDC, hdc, UINT, flags);
GLFUNC_DECL_2_WRET(DWORD, wglSwapMultipleBuffers, UINT, n, const WGLSWAP*, sw);
GLFUNC_DECL_2_WRET(HGLRC, wglCreateLayerContext, HDC, hdc, int, b);
GLFUNC_DECL_2_WRET(int, wglChoosePixelFormat, HDC, hdc, const PIXELFORMATDESCRIPTOR*, pfd);
GLFUNC_DECL_3_WRET(BOOL, wglCopyContext, HGLRC, hglrc1, HGLRC, hglrc2, UINT, flags);
GLFUNC_DECL_3_WRET(BOOL, wglRealizeLayerPalette, HDC, hdc, int, b, BOOL, c);
GLFUNC_DECL_3_WRET(BOOL, wglSetPixelFormat, HDC, hdc, int, b, const PIXELFORMATDESCRIPTOR*, pfd);
GLFUNC_DECL_4_WRET(BOOL, wglUseFontBitmapsA, HDC, hdc, DWORD, b, DWORD, c, DWORD, d);
GLFUNC_DECL_4_WRET(BOOL, wglUseFontBitmapsW, HDC, hdc, DWORD, b, DWORD, c, DWORD, d);
GLFUNC_DECL_4_WRET(int, wglDescribePixelFormat, HDC, hdc, int, b, UINT, c, PIXELFORMATDESCRIPTOR*, pfd);
GLFUNC_DECL_5_WRET(BOOL, wglDescribeLayerPlane, HDC, hdc, int, b, int, c, UINT, d, LAYERPLANEDESCRIPTOR*, lpd);
GLFUNC_DECL_5_WRET(int, wglGetLayerPaletteEntries, HDC, hdc, int, b, int, c, int, d, COLORREF*, e);
GLFUNC_DECL_5_WRET(int, wglSetLayerPaletteEntries, HDC, hdc, int, b, int, c, int, d, const COLORREF*, e);
GLFUNC_DECL_8_WRET(BOOL, wglUseFontOutlinesA, HDC, hdc, DWORD, b, DWORD, c, DWORD, d, float, e, float, f, int, g, GLYPHMETRICSFLOAT*, gmf);
GLFUNC_DECL_8_WRET(BOOL, wglUseFontOutlinesW, HDC, hdc, DWORD, b, DWORD, c, DWORD, d, float, e, float, f, int, g, GLYPHMETRICSFLOAT*, gmf);

//
// wglGetProcAddress is a special case. We also want to log
// which extensions got dynamically loaded by the application.
//
GLPROXY_EXTERN PROC GLPROXY_DECL wglGetProcAddress(LPCSTR funcName);

// This is an undocummented function, it seems. So it is probably not called by most applications...
GLPROXY_EXTERN PROC GLPROXY_DECL wglGetDefaultProcAddress(LPCSTR funcName);

//
// GL Functions with a return value:
//
GLFUNC_DECL_0_WRET(GLenum, glGetError);
GLFUNC_DECL_1_WRET(GLboolean, glIsEnabled, GLenum, cap);
GLFUNC_DECL_1_WRET(GLboolean, glIsList, GLuint, list);
GLFUNC_DECL_1_WRET(GLboolean, glIsTexture, GLuint, texture);
GLFUNC_DECL_1_WRET(GLint, glRenderMode, GLenum, mode);
GLFUNC_DECL_1_WRET(GLuint, glGenLists, GLsizei, range);
GLFUNC_DECL_1_WRET(const GLubyte*, glGetString, GLenum, name);
GLFUNC_DECL_3_WRET(GLboolean, glAreTexturesResident, GLsizei, n, const GLuint*, textures, GLboolean*, residences);

//
// GL Functions returning void:
//
GLFUNC_DECL_0(glEnd);
GLFUNC_DECL_0(glEndList);
GLFUNC_DECL_0(glFinish);
GLFUNC_DECL_0(glFlush);
GLFUNC_DECL_0(glInitNames);
GLFUNC_DECL_0(glLoadIdentity);
GLFUNC_DECL_0(glPopAttrib);
GLFUNC_DECL_0(glPopClientAttrib);
GLFUNC_DECL_0(glPopMatrix);
GLFUNC_DECL_0(glPopName);
GLFUNC_DECL_0(glPushMatrix)
GLFUNC_DECL_1(glArrayElement, GLint, i);
GLFUNC_DECL_1(glBegin, GLenum, mode);
GLFUNC_DECL_1(glCallList, GLuint, list);
GLFUNC_DECL_1(glClear, GLbitfield, mask);
GLFUNC_DECL_1(glClearDepth, GLclampd, depth);
GLFUNC_DECL_1(glClearIndex, GLfloat, c);
GLFUNC_DECL_1(glClearStencil, GLint, s);
GLFUNC_DECL_1(glColor3bv, const GLbyte*, v);
GLFUNC_DECL_1(glColor3dv, const GLdouble*, v);
GLFUNC_DECL_1(glColor3fv, const GLfloat*, v);
GLFUNC_DECL_1(glColor3iv, const GLint*, v);
GLFUNC_DECL_1(glColor3sv, const GLshort*, v);
GLFUNC_DECL_1(glColor3ubv, const GLubyte*, v);
GLFUNC_DECL_1(glColor3uiv, const GLuint*, v);
GLFUNC_DECL_1(glColor3usv, const GLushort*, v);
GLFUNC_DECL_1(glColor4bv, const GLbyte*, v);
GLFUNC_DECL_1(glColor4dv, const GLdouble*, v);
GLFUNC_DECL_1(glColor4fv, const GLfloat*, v);
GLFUNC_DECL_1(glColor4iv, const GLint*, v);
GLFUNC_DECL_1(glColor4sv, const GLshort*, v);
GLFUNC_DECL_1(glColor4ubv, const GLubyte*, v);
GLFUNC_DECL_1(glColor4uiv, const GLuint*, v);
GLFUNC_DECL_1(glColor4usv, const GLushort*, v);
GLFUNC_DECL_1(glCullFace, GLenum, mode);
GLFUNC_DECL_1(glDepthFunc, GLenum, func);
GLFUNC_DECL_1(glDepthMask, GLboolean, flag);
GLFUNC_DECL_1(glDisable, GLenum, cap);
GLFUNC_DECL_1(glDisableClientState, GLenum, array);
GLFUNC_DECL_1(glDrawBuffer, GLenum, mode);
GLFUNC_DECL_1(glEdgeFlag, GLboolean, flag);
GLFUNC_DECL_1(glEdgeFlagv, const GLboolean*, flag);
GLFUNC_DECL_1(glEnable, GLenum, cap);
GLFUNC_DECL_1(glEnableClientState, GLenum, array);
GLFUNC_DECL_1(glEvalCoord1d, GLdouble, u);
GLFUNC_DECL_1(glEvalCoord1dv, const GLdouble*, u);
GLFUNC_DECL_1(glEvalCoord1f, GLfloat, u);
GLFUNC_DECL_1(glEvalCoord1fv, const GLfloat*, u);
GLFUNC_DECL_1(glEvalCoord2dv, const GLdouble*, u);
GLFUNC_DECL_1(glEvalCoord2fv, const GLfloat*, u);
GLFUNC_DECL_1(glEvalPoint1, GLint, i);
GLFUNC_DECL_1(glFrontFace, GLenum, mode);
GLFUNC_DECL_1(glGetPolygonStipple, GLubyte*, mask);
GLFUNC_DECL_1(glIndexMask, GLuint, mask);
GLFUNC_DECL_1(glIndexd, GLdouble, c);
GLFUNC_DECL_1(glIndexdv, const GLdouble*, c);
GLFUNC_DECL_1(glIndexf, GLfloat, c);
GLFUNC_DECL_1(glIndexfv, const GLfloat*, c);
GLFUNC_DECL_1(glIndexi, GLint, c);
GLFUNC_DECL_1(glIndexiv, const GLint*, c);
GLFUNC_DECL_1(glIndexs, GLshort, c);
GLFUNC_DECL_1(glIndexsv, const GLshort*, c);
GLFUNC_DECL_1(glIndexub, GLubyte, c);
GLFUNC_DECL_1(glIndexubv, const GLubyte*, c);
GLFUNC_DECL_1(glLineWidth, GLfloat, width);
GLFUNC_DECL_1(glListBase, GLuint, base);
GLFUNC_DECL_1(glLoadMatrixd, const GLdouble*, m);
GLFUNC_DECL_1(glLoadMatrixf, const GLfloat*, m);
GLFUNC_DECL_1(glLoadName, GLuint, name);
GLFUNC_DECL_1(glLogicOp, GLenum, opcode);
GLFUNC_DECL_1(glMatrixMode, GLenum, mode);
GLFUNC_DECL_1(glMultMatrixd, const GLdouble*, m);
GLFUNC_DECL_1(glMultMatrixf, const GLfloat*, m);
GLFUNC_DECL_1(glNormal3bv, const GLbyte*, v);
GLFUNC_DECL_1(glNormal3dv, const GLdouble*, v);
GLFUNC_DECL_1(glNormal3fv, const GLfloat*, v);
GLFUNC_DECL_1(glNormal3iv, const GLint*, v);
GLFUNC_DECL_1(glNormal3sv, const GLshort*, v);
GLFUNC_DECL_1(glPassThrough, GLfloat, token);
GLFUNC_DECL_1(glPointSize, GLfloat, size);
GLFUNC_DECL_1(glPolygonStipple, const GLubyte*, mask);
GLFUNC_DECL_1(glPushAttrib, GLbitfield, mask);
GLFUNC_DECL_1(glPushClientAttrib, GLbitfield, mask);
GLFUNC_DECL_1(glPushName, GLuint, name);
GLFUNC_DECL_1(glRasterPos2dv, const GLdouble*, v);
GLFUNC_DECL_1(glRasterPos2fv, const GLfloat*, v);
GLFUNC_DECL_1(glRasterPos2iv, const GLint*, v);
GLFUNC_DECL_1(glRasterPos2sv, const GLshort*, v);
GLFUNC_DECL_1(glRasterPos3dv, const GLdouble*, v);
GLFUNC_DECL_1(glRasterPos3fv, const GLfloat*, v);
GLFUNC_DECL_1(glRasterPos3iv, const GLint*, v);
GLFUNC_DECL_1(glRasterPos3sv, const GLshort*, v);
GLFUNC_DECL_1(glRasterPos4dv, const GLdouble*, v);
GLFUNC_DECL_1(glRasterPos4fv, const GLfloat*, v);
GLFUNC_DECL_1(glRasterPos4iv, const GLint*, v);
GLFUNC_DECL_1(glRasterPos4sv, const GLshort*, v);
GLFUNC_DECL_1(glReadBuffer, GLenum, mode);
GLFUNC_DECL_1(glShadeModel, GLenum, mode);
GLFUNC_DECL_1(glStencilMask, GLuint, mask);
GLFUNC_DECL_1(glTexCoord1d, GLdouble, s);
GLFUNC_DECL_1(glTexCoord1dv, const GLdouble*, v);
GLFUNC_DECL_1(glTexCoord1f, GLfloat, s);
GLFUNC_DECL_1(glTexCoord1fv, const GLfloat*, v);
GLFUNC_DECL_1(glTexCoord1i, GLint, s);
GLFUNC_DECL_1(glTexCoord1iv, const GLint*, v);
GLFUNC_DECL_1(glTexCoord1s, GLshort, s);
GLFUNC_DECL_1(glTexCoord1sv, const GLshort*, v);
GLFUNC_DECL_1(glTexCoord2dv, const GLdouble*, v);
GLFUNC_DECL_1(glTexCoord2fv, const GLfloat*, v);
GLFUNC_DECL_1(glTexCoord2iv, const GLint*, v);
GLFUNC_DECL_1(glTexCoord2sv, const GLshort*, v);
GLFUNC_DECL_1(glTexCoord3dv, const GLdouble*, v);
GLFUNC_DECL_1(glTexCoord3fv, const GLfloat*, v);
GLFUNC_DECL_1(glTexCoord3iv, const GLint*, v);
GLFUNC_DECL_1(glTexCoord3sv, const GLshort*, v);
GLFUNC_DECL_1(glTexCoord4dv, const GLdouble*, v);
GLFUNC_DECL_1(glTexCoord4fv, const GLfloat*, v);
GLFUNC_DECL_1(glTexCoord4iv, const GLint*, v);
GLFUNC_DECL_1(glTexCoord4sv, const GLshort*, v);
GLFUNC_DECL_1(glVertex2dv, const GLdouble*, v);
GLFUNC_DECL_1(glVertex2fv, const GLfloat*, v);
GLFUNC_DECL_1(glVertex2iv, const GLint*, v);
GLFUNC_DECL_1(glVertex2sv, const GLshort*, v);
GLFUNC_DECL_1(glVertex3dv, const GLdouble*, v);
GLFUNC_DECL_1(glVertex3fv, const GLfloat*, v);
GLFUNC_DECL_1(glVertex3iv, const GLint*, v);
GLFUNC_DECL_1(glVertex3sv, const GLshort*, v);
GLFUNC_DECL_1(glVertex4dv, const GLdouble*, v);
GLFUNC_DECL_1(glVertex4fv, const GLfloat*, v);
GLFUNC_DECL_1(glVertex4iv, const GLint*, v);
GLFUNC_DECL_1(glVertex4sv, const GLshort*, v);
GLFUNC_DECL_2(glAccum, GLenum, op, GLfloat, value);
GLFUNC_DECL_2(glAlphaFunc, GLenum, func, GLclampf, ref);
GLFUNC_DECL_2(glBindTexture, GLenum, target, GLuint, texture);
GLFUNC_DECL_2(glBlendFunc, GLenum, sfactor, GLenum, dfactor);
GLFUNC_DECL_2(glClipPlane, GLenum, plane, const GLdouble*, equation);
GLFUNC_DECL_3(glColor3b, GLbyte, red, GLbyte, green, GLbyte, blue);
GLFUNC_DECL_2(glColorMaterial, GLenum, face, GLenum, mode);
GLFUNC_DECL_2(glDeleteLists, GLuint, list, GLsizei, range);
GLFUNC_DECL_2(glDeleteTextures, GLsizei, n, const GLuint*, textures);
GLFUNC_DECL_2(glDepthRange, GLclampd, zNear, GLclampd, zFar);
GLFUNC_DECL_2(glEdgeFlagPointer, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_2(glEvalCoord2d, GLdouble, u, GLdouble, v);
GLFUNC_DECL_2(glEvalCoord2f, GLfloat, u, GLfloat, v);
GLFUNC_DECL_2(glEvalPoint2, GLint, i, GLint, j);
GLFUNC_DECL_2(glFogf, GLenum, pname, GLfloat, param);
GLFUNC_DECL_2(glFogfv, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_2(glFogi, GLenum, pname, GLint, param);
GLFUNC_DECL_2(glFogiv, GLenum, pname, const GLint*, params);
GLFUNC_DECL_2(glGenTextures, GLsizei, n, GLuint*, textures);
GLFUNC_DECL_2(glGetBooleanv, GLenum, pname, GLboolean*, params);
GLFUNC_DECL_2(glGetClipPlane, GLenum, plane, GLdouble*, equation);
GLFUNC_DECL_2(glGetDoublev, GLenum, pname, GLdouble*, params);
GLFUNC_DECL_2(glGetFloatv, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_2(glGetIntegerv, GLenum, pname, GLint*, params);
GLFUNC_DECL_2(glGetPixelMapfv, GLenum, map, GLfloat*, values);
GLFUNC_DECL_2(glGetPixelMapuiv, GLenum, map, GLuint*, values);
GLFUNC_DECL_2(glGetPixelMapusv, GLenum, map, GLushort*, values);
GLFUNC_DECL_2(glGetPointerv, GLenum, pname, void**, params);
GLFUNC_DECL_2(glHint, GLenum, target, GLenum, mode);
GLFUNC_DECL_2(glLightModelf, GLenum, pname, GLfloat, param);
GLFUNC_DECL_2(glLightModelfv, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_2(glLightModeli, GLenum, pname, GLint, param);
GLFUNC_DECL_2(glLightModeliv, GLenum, pname, const GLint*, params);
GLFUNC_DECL_2(glLineStipple, GLint, factor, GLushort, pattern);
GLFUNC_DECL_2(glNewList, GLuint, list, GLenum, mode);
GLFUNC_DECL_2(glPixelStoref, GLenum, pname, GLfloat, param);
GLFUNC_DECL_2(glPixelStorei, GLenum, pname, GLint, param);
GLFUNC_DECL_2(glPixelTransferf, GLenum, pname, GLfloat, param);
GLFUNC_DECL_2(glPixelTransferi, GLenum, pname, GLint, param);
GLFUNC_DECL_2(glPixelZoom, GLfloat, xfactor, GLfloat, yfactor);
GLFUNC_DECL_2(glPolygonMode, GLenum, face, GLenum, mode);
GLFUNC_DECL_2(glPolygonOffset, GLfloat, factor, GLfloat, units);
GLFUNC_DECL_2(glRasterPos2d, GLdouble, x, GLdouble, y);
GLFUNC_DECL_2(glRasterPos2f, GLfloat, x, GLfloat, y);
GLFUNC_DECL_2(glRasterPos2i, GLint, x, GLint, y);
GLFUNC_DECL_2(glRasterPos2s, GLshort, x, GLshort, y);
GLFUNC_DECL_3(glRasterPos3i, GLint, x, GLint, y, GLint, z);
GLFUNC_DECL_2(glRectdv, const GLdouble*, v1, const GLdouble*, v2);
GLFUNC_DECL_2(glRectfv, const GLfloat*, v1, const GLfloat*, v2);
GLFUNC_DECL_2(glRectiv, const GLint*, v1, const GLint*, v2);
GLFUNC_DECL_2(glRectsv, const GLshort*, v1, const GLshort*, v2);
GLFUNC_DECL_2(glSelectBuffer, GLsizei, size, GLuint*, buffer);
GLFUNC_DECL_2(glTexCoord2d, GLdouble, s, GLdouble, t);
GLFUNC_DECL_2(glTexCoord2f, GLfloat, s, GLfloat, t);
GLFUNC_DECL_2(glTexCoord2i, GLint, s, GLint, t);
GLFUNC_DECL_2(glTexCoord2s, GLshort, s, GLshort, t);
GLFUNC_DECL_2(glVertex2d, GLdouble, x, GLdouble, y);
GLFUNC_DECL_2(glVertex2f, GLfloat, x, GLfloat, y);
GLFUNC_DECL_2(glVertex2i, GLint, x, GLint, y);
GLFUNC_DECL_2(glVertex2s, GLshort, x, GLshort, y);
GLFUNC_DECL_3(glCallLists, GLsizei, n, GLenum, type, const void*, lists);
GLFUNC_DECL_3(glColor3d, GLdouble, red, GLdouble, green, GLdouble, blue);
GLFUNC_DECL_3(glColor3f, GLfloat, red, GLfloat, green, GLfloat, blue);
GLFUNC_DECL_3(glColor3i, GLint, red, GLint, green, GLint, blue);
GLFUNC_DECL_3(glColor3s, GLshort, red, GLshort, green, GLshort, blue);
GLFUNC_DECL_3(glColor3ub, GLubyte, red, GLubyte, green, GLubyte, blue);
GLFUNC_DECL_3(glColor3ui, GLuint, red, GLuint, green, GLuint, blue);
GLFUNC_DECL_3(glColor3us, GLushort, red, GLushort, green, GLushort, blue);
GLFUNC_DECL_3(glDrawArrays, GLenum, mode, GLint, first, GLsizei, count);
GLFUNC_DECL_3(glEvalMesh1, GLenum, mode, GLint, i1, GLint, i2);
GLFUNC_DECL_3(glFeedbackBuffer, GLsizei, size, GLenum, type, GLfloat*, buffer);
GLFUNC_DECL_3(glGetLightfv, GLenum, light, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_3(glGetLightiv, GLenum, light, GLenum, pname, GLint*, params);
GLFUNC_DECL_3(glGetMapdv, GLenum, target, GLenum, query, GLdouble*, v);
GLFUNC_DECL_3(glGetMapfv, GLenum, target, GLenum, query, GLfloat*, v);
GLFUNC_DECL_3(glGetMapiv, GLenum, target, GLenum, query, GLint*, v);
GLFUNC_DECL_3(glGetMaterialfv, GLenum, face, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_3(glGetMaterialiv, GLenum, face, GLenum, pname, GLint*, params);
GLFUNC_DECL_3(glGetTexEnvfv, GLenum, target, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_3(glGetTexEnviv, GLenum, target, GLenum, pname, GLint*, params);
GLFUNC_DECL_3(glGetTexGendv, GLenum, coord, GLenum, pname, GLdouble*, params);
GLFUNC_DECL_3(glGetTexGenfv, GLenum, coord, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_3(glGetTexGeniv, GLenum, coord, GLenum, pname, GLint*, params);
GLFUNC_DECL_3(glGetTexParameterfv, GLenum, target, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_3(glGetTexParameteriv, GLenum, target, GLenum, pname, GLint*, params);
GLFUNC_DECL_3(glIndexPointer, GLenum, type, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_3(glInterleavedArrays, GLenum, format, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_3(glLightf, GLenum, light, GLenum, pname, GLfloat, param);
GLFUNC_DECL_3(glLightfv, GLenum, light, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_3(glLighti, GLenum, light, GLenum, pname, GLint, param);
GLFUNC_DECL_3(glLightiv, GLenum, light, GLenum, pname, const GLint*, params);
GLFUNC_DECL_3(glMapGrid1d, GLint, un, GLdouble, u1, GLdouble, u2);
GLFUNC_DECL_3(glMapGrid1f, GLint, un, GLfloat, u1, GLfloat, u2);
GLFUNC_DECL_3(glMaterialf, GLenum, face, GLenum, pname, GLfloat, param);
GLFUNC_DECL_3(glMaterialfv, GLenum, face, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_3(glMateriali, GLenum, face, GLenum, pname, GLint, param);
GLFUNC_DECL_3(glMaterialiv, GLenum, face, GLenum, pname, const GLint*, params);
GLFUNC_DECL_3(glNormal3b, GLbyte, nx, GLbyte, ny, GLbyte, nz);
GLFUNC_DECL_3(glNormal3d, GLdouble, nx, GLdouble, ny, GLdouble, nz);
GLFUNC_DECL_3(glNormal3f, GLfloat, nx, GLfloat, ny, GLfloat, nz);
GLFUNC_DECL_3(glNormal3i, GLint, nx, GLint, ny, GLint, nz);
GLFUNC_DECL_3(glNormal3s, GLshort, nx, GLshort, ny, GLshort, nz);
GLFUNC_DECL_3(glNormalPointer, GLenum, type, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_3(glPixelMapfv, GLenum, map, GLsizei, mapsize, const GLfloat*, values);
GLFUNC_DECL_3(glPixelMapuiv, GLenum, map, GLsizei, mapsize, const GLuint*, values);
GLFUNC_DECL_3(glPixelMapusv, GLenum, map, GLsizei, mapsize, const GLushort*, values);
GLFUNC_DECL_3(glPrioritizeTextures, GLsizei, n, const GLuint*, textures, const GLclampf*, priorities);
GLFUNC_DECL_3(glRasterPos3d, GLdouble, x, GLdouble, y, GLdouble, z);
GLFUNC_DECL_3(glRasterPos3f, GLfloat, x, GLfloat, y, GLfloat, z);
GLFUNC_DECL_3(glRasterPos3s, GLshort, x, GLshort, y, GLshort, z);
GLFUNC_DECL_4(glRasterPos4d, GLdouble, x, GLdouble, y, GLdouble, z, GLdouble, w);
GLFUNC_DECL_3(glScaled, GLdouble, x, GLdouble, y, GLdouble, z);
GLFUNC_DECL_3(glScalef, GLfloat, x, GLfloat, y, GLfloat, z);
GLFUNC_DECL_3(glStencilFunc, GLenum, func, GLint, ref, GLuint, mask);
GLFUNC_DECL_3(glStencilOp, GLenum, fail, GLenum, zfail, GLenum, zpass);
GLFUNC_DECL_3(glTexCoord3d, GLdouble, s, GLdouble, t, GLdouble, r);
GLFUNC_DECL_3(glTexCoord3f, GLfloat, s, GLfloat, t, GLfloat, r);
GLFUNC_DECL_3(glTexCoord3i, GLint, s, GLint, t, GLint, r);
GLFUNC_DECL_3(glTexCoord3s, GLshort, s, GLshort, t, GLshort, r);
GLFUNC_DECL_3(glTexEnvf, GLenum, target, GLenum, pname, GLfloat, param);
GLFUNC_DECL_3(glTexEnvfv, GLenum, target, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_3(glTexEnvi, GLenum, target, GLenum, pname, GLint, param);
GLFUNC_DECL_3(glTexEnviv, GLenum, target, GLenum, pname, const GLint*, params);
GLFUNC_DECL_3(glTexGend, GLenum, coord, GLenum, pname, GLdouble, param);
GLFUNC_DECL_3(glTexGendv, GLenum, coord, GLenum, pname, const GLdouble*, params);
GLFUNC_DECL_3(glTexGenf, GLenum, coord, GLenum, pname, GLfloat, param);
GLFUNC_DECL_3(glTexGenfv, GLenum, coord, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_3(glTexGeni, GLenum, coord, GLenum, pname, GLint, param);
GLFUNC_DECL_3(glTexGeniv, GLenum, coord, GLenum, pname, const GLint*, params);
GLFUNC_DECL_3(glTexParameterf, GLenum, target, GLenum, pname, GLfloat, param);
GLFUNC_DECL_3(glTexParameterfv, GLenum, target, GLenum, pname, const GLfloat*, params);
GLFUNC_DECL_3(glTexParameteri, GLenum, target, GLenum, pname, GLint, param);
GLFUNC_DECL_3(glTexParameteriv, GLenum, target, GLenum, pname, const GLint*, params);
GLFUNC_DECL_3(glTranslated, GLdouble, x, GLdouble, y, GLdouble, z);
GLFUNC_DECL_3(glTranslatef, GLfloat, x, GLfloat, y, GLfloat, z);
GLFUNC_DECL_3(glVertex3d, GLdouble, x, GLdouble, y, GLdouble, z);
GLFUNC_DECL_3(glVertex3f, GLfloat, x, GLfloat, y, GLfloat, z);
GLFUNC_DECL_3(glVertex3i, GLint, x, GLint, y, GLint, z);
GLFUNC_DECL_3(glVertex3s, GLshort, x, GLshort, y, GLshort, z);
GLFUNC_DECL_4(glClearAccum, GLfloat, red, GLfloat, green, GLfloat, blue, GLfloat, alpha);
GLFUNC_DECL_4(glClearColor, GLclampf, red, GLclampf, green, GLclampf, blue, GLclampf, alpha);
GLFUNC_DECL_4(glColor4b, GLbyte, red, GLbyte, green, GLbyte, blue, GLbyte, alpha);
GLFUNC_DECL_4(glColor4d, GLdouble, red, GLdouble, green, GLdouble, blue, GLdouble, alpha);
GLFUNC_DECL_4(glColor4f, GLfloat, red, GLfloat, green, GLfloat, blue, GLfloat, alpha);
GLFUNC_DECL_4(glColor4i, GLint, red, GLint, green, GLint, blue, GLint, alpha);
GLFUNC_DECL_4(glColor4s, GLshort, red, GLshort, green, GLshort, blue, GLshort, alpha);
GLFUNC_DECL_4(glColor4ub, GLubyte, red, GLubyte, green, GLubyte, blue, GLubyte, alpha);
GLFUNC_DECL_4(glColor4ui, GLuint, red, GLuint, green, GLuint, blue, GLuint, alpha);
GLFUNC_DECL_4(glColor4us, GLushort, red, GLushort, green, GLushort, blue, GLushort, alpha);
GLFUNC_DECL_4(glColorMask, GLboolean, red, GLboolean, green, GLboolean, blue, GLboolean, alpha);
GLFUNC_DECL_4(glColorPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_4(glDrawElements, GLenum, mode, GLsizei, count, GLenum, type, const void*, indices);
GLFUNC_DECL_4(glGetTexLevelParameterfv, GLenum, target, GLint, level, GLenum, pname, GLfloat*, params);
GLFUNC_DECL_4(glGetTexLevelParameteriv, GLenum, target, GLint, level, GLenum, pname, GLint*, params);
GLFUNC_DECL_4(glRasterPos4f, GLfloat, x, GLfloat, y, GLfloat, z, GLfloat, w);
GLFUNC_DECL_4(glRasterPos4i, GLint, x, GLint, y, GLint, z, GLint, w);
GLFUNC_DECL_4(glRasterPos4s, GLshort, x, GLshort, y, GLshort, z, GLshort, w);
GLFUNC_DECL_4(glRectd, GLdouble, x1, GLdouble, y1, GLdouble, x2, GLdouble, y2);
GLFUNC_DECL_4(glRectf, GLfloat, x1, GLfloat, y1, GLfloat, x2, GLfloat, y2);
GLFUNC_DECL_4(glRecti, GLint, x1, GLint, y1, GLint, x2, GLint, y2);
GLFUNC_DECL_4(glRects, GLshort, x1, GLshort, y1, GLshort, x2, GLshort, y2);
GLFUNC_DECL_4(glRotated, GLdouble, angle, GLdouble, x, GLdouble, y, GLdouble, z);
GLFUNC_DECL_4(glRotatef, GLfloat, angle, GLfloat, x, GLfloat, y, GLfloat, z);
//GLFUNC_DECL_4(glScissor, GLint, x, GLint, y, GLsizei, width, GLsizei, height);
GLFUNC_DECL_4(glTexCoord4d, GLdouble, s, GLdouble, t, GLdouble, r, GLdouble, q);
GLFUNC_DECL_4(glTexCoord4f, GLfloat, s, GLfloat, t, GLfloat, r, GLfloat, q);
GLFUNC_DECL_4(glTexCoord4i, GLint, s, GLint, t, GLint, r, GLint, q);
GLFUNC_DECL_4(glTexCoord4s, GLshort, s, GLshort, t, GLshort, r, GLshort, q);
GLFUNC_DECL_4(glTexCoordPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer);
GLFUNC_DECL_4(glVertex4d, GLdouble, x, GLdouble, y, GLdouble, z, GLdouble, w);
GLFUNC_DECL_4(glVertex4f, GLfloat, x, GLfloat, y, GLfloat, z, GLfloat, w);
GLFUNC_DECL_4(glVertex4i, GLint, x, GLint, y, GLint, z, GLint, w);
GLFUNC_DECL_4(glVertex4s, GLshort, x, GLshort, y, GLshort, z, GLshort, w);
GLFUNC_DECL_4(glVertexPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer);
//GLFUNC_DECL_4(glViewport, GLint, x, GLint, y, GLsizei, width, GLsizei, height);
GLFUNC_DECL_5(glCopyPixels, GLint, x, GLint, y, GLsizei, width, GLsizei, height, GLenum, type);
GLFUNC_DECL_5(glDrawPixels, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const void*, pixels);
GLFUNC_DECL_5(glEvalMesh2, GLenum, mode, GLint, i1, GLint, i2, GLint, j1, GLint, j2);
GLFUNC_DECL_5(glGetTexImage, GLenum, target, GLint, level, GLenum, format, GLenum, type, void*, pixels);
GLFUNC_DECL_6(glCopyTexSubImage1D, GLenum, target, GLint, level, GLint, xoffset, GLint, x, GLint, y, GLsizei, width);
GLFUNC_DECL_6(glFrustum, GLdouble, left, GLdouble, right, GLdouble, bottom, GLdouble, top, GLdouble, zNear, GLdouble, zFar);
GLFUNC_DECL_6(glMap1d, GLenum, target, GLdouble, u1, GLdouble, u2, GLint, stride, GLint, order, const GLdouble*, points);
GLFUNC_DECL_6(glMap1f, GLenum, target, GLfloat, u1, GLfloat, u2, GLint, stride, GLint, order, const GLfloat*, points);
GLFUNC_DECL_6(glMapGrid2d, GLint, un, GLdouble, u1, GLdouble, u2, GLint, vn, GLdouble, v1, GLdouble, v2);
GLFUNC_DECL_6(glMapGrid2f, GLint, un, GLfloat, u1, GLfloat, u2, GLint, vn, GLfloat, v1, GLfloat, v2);
GLFUNC_DECL_6(glOrtho, GLdouble, left, GLdouble, right, GLdouble, bottom, GLdouble, top, GLdouble, zNear, GLdouble, zFar);
GLFUNC_DECL_7(glBitmap, GLsizei, width, GLsizei, height, GLfloat, xorig, GLfloat, yorig, GLfloat, xmove, GLfloat, ymove, const GLubyte*, bitmap);
GLFUNC_DECL_7(glCopyTexImage1D, GLenum, target, GLint, level, GLenum, internalFormat, GLint, x, GLint, y, GLsizei, width, GLint, border);
GLFUNC_DECL_7(glReadPixels, GLint, x, GLint, y, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, void*, pixels);
GLFUNC_DECL_7(glTexSubImage1D, GLenum, target, GLint, level, GLint, xoffset, GLsizei, width, GLenum, format, GLenum, type, const void*, pixels);
GLFUNC_DECL_8(glCopyTexImage2D, GLenum, target, GLint, level, GLenum, internalFormat, GLint, x, GLint, y, GLsizei, width, GLsizei, height, GLint, border);
GLFUNC_DECL_8(glCopyTexSubImage2D, GLenum, target, GLint, level, GLint, xoffset, GLint, yoffset, GLint, x, GLint, y, GLsizei, width, GLsizei, height);
GLFUNC_DECL_8(glTexImage1D, GLenum, target, GLint, level, GLint, internalformat, GLsizei, width, GLint, border, GLenum, format, GLenum, type, const void*, pixels);
//GLFUNC_DECL_9(glTexImage2D, GLenum, target, GLint, level, GLint, internalformat, GLsizei, width, GLsizei, height, GLint, border, GLenum, format, GLenum, type, const void *, pixels);
GLFUNC_DECL_9(glTexSubImage2D, GLenum, target, GLint, level, GLint, xoffset, GLint, yoffset, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const void*, pixels);
GLFUNC_DECL_10(glMap2d, GLenum, target, GLdouble, u1, GLdouble, u2, GLint, ustride, GLint, uorder, GLdouble, v1, GLdouble, v2, GLint, vstride, GLint, vorder, const GLdouble*, points);
GLFUNC_DECL_10(glMap2f, GLenum, target, GLfloat, u1, GLfloat, u2, GLint, ustride, GLint, uorder, GLfloat, v1, GLfloat, v2, GLint, vstride, GLint, vorder, const GLfloat*, points);