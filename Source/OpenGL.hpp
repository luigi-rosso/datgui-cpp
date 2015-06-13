#ifndef _SPLITCELL_DATGUI_OPENGL_HPP_
#define _SPLITCELL_DATGUI_OPENGL_HPP_

#ifdef LINUX
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE
// Cross Platform Compatability on iOS
#define GL_HALF_FLOAT			GL_HALF_FLOAT_OES
#define GL_DEPTH_COMPONENT24	GL_DEPTH_COMPONENT24_OES
#endif

#if TARGET_OS_IPHONE
// iOS
#define IS_GL_ES 1
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#elif TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define IS_GL_ES 1
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#elif TARGET_OS_MAC
// Other kinds of Mac OS

#ifndef __gl_h_
#include <OpenGL/gl.h>
#endif
#ifndef _OPENGL_H
#include <OpenGL/OpenGL.h>
#endif
#else
// Unknown mac platform

#endif
#endif

#endif