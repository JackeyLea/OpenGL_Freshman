#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>

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

  mainloop(xdisplay, display, surface);

  destroyEGL(&display, &context, &surface);
  XDestroyWindow(xdisplay, xwindow);
  XCloseDisplay(xdisplay);

  return EXIT_SUCCESS;
}
