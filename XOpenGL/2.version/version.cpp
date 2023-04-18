#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <EGL/egl.h>

bool initializeEGL(EGLNativeDisplayType nativedisplay, EGLNativeWindowType nativewindow, EGLDisplay *display, EGLContext *context, EGLSurface *surface)
{
  *display = eglGetDisplay(nativedisplay);
  if (*display == EGL_NO_DISPLAY) {
    fprintf(stderr, "eglGetDisplay failed: %d\n", eglGetError());
    return false;
  }

  if (!eglInitialize(*display, nullptr, nullptr)) {
    fprintf(stderr, "eglInitialize failed: %d\n", eglGetError());
    return false;
  }

  if(eglBindAPI(EGL_OPENGL_API)){
    fprintf(stderr,"eglBindAPI failed: %d\n",eglGetError());
  }

  EGLint attr[] = {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
    EGL_BUFFER_SIZE, 32,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_NONE};
  EGLConfig config = nullptr;
  EGLint numConfigs = 0;
  if (!eglChooseConfig(*display, attr, &config, 1, &numConfigs)) {
    fprintf(stderr, "eglChooseConfig failed: %d\n", eglGetError());
    return false;
  }
  if (numConfigs != 1) {
    fprintf(stderr, "eglChooseConfig failed (numConfigs must be 1 but %d): %d\n", numConfigs, eglGetError());
    return false;
  }

  *surface = eglCreateWindowSurface(*display, config, nativewindow, nullptr);
  if (*surface == EGL_NO_SURFACE) {
    fprintf(stderr, "eglCreateWindowSurface failed: %d\n", eglGetError());
    return false;
  }

  EGLint ctxattr[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE};
  *context = eglCreateContext(*display, config, EGL_NO_CONTEXT, ctxattr);
  if (*context == EGL_NO_CONTEXT) {
    fprintf(stderr, "eglCreateContext failed: %d\n", eglGetError());
    return false;
  }

  if (!eglMakeCurrent(*display, *surface, *surface, *context)) {
    fprintf(stderr, "eglMakeCurrent failed: %d\n", eglGetError());
    return false;
  }

  return true;
}

void destroyEGL(EGLDisplay *display, EGLContext *context, EGLSurface *surface)
{
  eglDestroyContext(display, context);
  eglDestroySurface(display, surface);
  eglTerminate(display);
}

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface)
{
  for (;;) {
    XPending(xdisplay);
    //glClearColor(0.25f, 0.25f, 0.5f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(display, surface);
    usleep(1000);
  }
}

int main(int argc, char *argv[])
{
  Display *xdisplay = XOpenDisplay(nullptr);
  if (xdisplay == nullptr) {
    fprintf(stderr, "XOpenDisplay failed\n");
    return EXIT_FAILURE;
  }

  Window xwindow = XCreateSimpleWindow(xdisplay, DefaultRootWindow(xdisplay), 100, 100, 640, 480,
                                       1, BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));
  XMapWindow(xdisplay, xwindow);

  EGLDisplay display = nullptr;
  EGLContext context = nullptr;
  EGLSurface surface = nullptr;
  if (!initializeEGL(xdisplay, xwindow, &display, &context, &surface)) {
    return EXIT_FAILURE;
  }

  const GLubyte *name = glGetString(GL_VENDOR);           //返回负责当前OpenGL实现厂商的名字
  const GLubyte *flag = glGetString(GL_RENDERER);         //返回一个渲染器标识符，通常是个硬件平台
  const GLubyte *OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
  const GLubyte *gluVersion = gluGetString(GLU_VERSION);  //返回当前GLU工具库版本
  const GLubyte *glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);

  printf("OpenGL实现厂商的名字：%s\n", name);
  printf("渲染器标识符：%s\n", flag);
  printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
  printf("OGLU工具库版本：%s\n", gluVersion);
  printf("GLSL版本：%s\n",glsl);

  mainloop(xdisplay, display, surface);

  destroyEGL(&display, &context, &surface);
  XDestroyWindow(xdisplay, xwindow);
  XCloseDisplay(xdisplay);

  return EXIT_SUCCESS;
}
