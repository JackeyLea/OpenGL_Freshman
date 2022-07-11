///
/// \note 加载字体并显示文字
///

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <unistd.h>//延时
#include <cmath>
#include <iostream>
#include <string>
#include <cstring>

#define ESCAPE 27//esc键ASCII码值

int window; //glut窗口标识号

GLuint base;//字体集的基本显示列表
GLfloat cnt1;//用于移动文字和颜色的计数器
GLfloat cnt2;//同上

void buildFont(){
    Display *dpy;
    XFontStruct *fontInfo;//存储字体

    base = glGenLists(96);//存储96个字符

    /*
    加载字体。
    你拥有什么字体由操作系统决定，
    我的系统中字体位于/usr/X11R6/lib/X11/fonts/*，
    同时包含fonts.alias和fonts.dir文件来说明.pcf.gz文件中是什么字体。
    在任何情况下，你的系统应该至少包含一种字体，否则你将看不见任何文字

    获取当前显示。
    这将根据环境变量打开与显示服务的第二个连接，并且至少持续到加载完字体为止。
    */
    dpy = XOpenDisplay(NULL);//默认为环境变量值

    fontInfo = XLoadQueryFont(dpy,"-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1");
    if(fontInfo==NULL){
        fontInfo = XLoadQueryFont(dpy,"fixed");
        if(fontInfo==NULL){
            std::cout<<"No X font found.\n"<<std::endl;
        }
    }

    /*
    加载字体信息之后，可以处理（旋转、缩放等）字体
    */

    /*
    从32（空格）开始，获取96个字符（z之后的一些字符），将其存储在base中
    */
    glXUseXFont(fontInfo->fid,32,96,base);

    //获取完显示列表后缩放内存
    XFreeFont(dpy,fontInfo);

    //关闭与显示服务器的连接
    XCloseDisplay(dpy);
}

void killFont(){
    glDeleteLists(base,96);//删除全部96个字符
}

//自定义显示方法
void glPrint(char *text){
    if(text==NULL){//没有东西显示就退出
        return ;
    }

    glPushAttrib(GL_LIST_BIT);//我们将通过glListBase偏移显示列表
    glListBase(base-32);//设置基准字符为32

    glCallLists(strlen(text),GL_UNSIGNED_BYTE,text);//绘制显示文本
    glPopAttrib();//取消glPushAtrrib的功能
}

//初始化函数，设置所有初始化值
void initGL(int width, int height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //将界面背景清空为红绿蓝alpha值对应的颜色
    glClearDepth(1.0);//设置清空深度缓冲区（depth buffer）
    glDepthFunc(GL_LESS);//设置深度测试的类型
    glEnable(GL_DEPTH_TEST);//设置进行深度测试（depth test）
    glShadeModel(GL_SMOOTH);//栅格化模式为平滑，只有平滑和两种模式

    glMatrixMode(GL_PROJECTION);//矩阵模式为投影模式
    glLoadIdentity();//重置投影矩阵

    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);//计算窗口的显示比例

    glMatrixMode(GL_MODELVIEW);//

    buildFont();
}

//OpenGL的主要绘图函数，绘制什么显示什么。
void displayGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空界面和depth缓冲区
    glLoadIdentity();//调整视场
    glTranslatef(0.0f,0.0f,-1.0f);//平移


    //基于文本位置的颜色
    glColor3f(1.0f*((float)(cos(cnt1))),1.0f*((float)(sin(cnt2))),1.0f-0.5f*((float)(cos(cnt1+cnt2))));

    //文本在屏幕的位置
    glRasterPos2f(-0.2f+0.35f*((float)(cos(cnt1))),0.35f*((float)(sin(cnt2))));

    glPrint("My name is JackeyLea");//显示文本

    cnt1+=0.001f;
    cnt2+=0.0081f;
    //双缓冲技术，交换缓冲区以显示刚刚绘制的图像
    glutSwapBuffers();
}

// 窗口大小变化回调函数
void reshapeGL(int w, int h)
{
    if(h==0){//防止出现长度为0的情况，尤其是下面还将h用作除数
        h=1;
    }
    glViewport(0, 0, w, h);//重置当前窗口的视场和角度
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<GLfloat>(w/h),0.1f,100.0f); //设置长宽视景
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//如果有按键按下调用此函数
void keyboard(unsigned char key, int x, int y)
{
    usleep(100);//稍微延时以免干扰

    if (key == ESCAPE)//如果是escape键
    {
        glutDestroyWindow(window); //销毁窗口
        exit(0);//正常退出程序
    }
}

int main(int argc,char **argv)
{
    //初始化glut状态，并且接管所有传给程序的参数
    glutInit(&argc, argv);
    //设置显示模式：双缓冲、RGBA颜色、alpha支持、depth缓冲支持
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    // 初始化窗口
    glutInitWindowSize(640, 480);       //初始界面大小
    glutInitWindowPosition(100, 100);   //界面初始位置，相对于屏幕左上角的像素值
    //创建界面，界面标题为argv[0]，即程序名称，也可以以字符串进行指定
    //同时获取创建的窗口ID号，销毁时使用
    window = glutCreateWindow(argv[0]); 

    glutIdleFunc(&displayGL);//即使没有任何事件，也重绘场景
    glutReshapeFunc(&reshapeGL);//注册调整窗口大小回调函数
    glutDisplayFunc(&displayGL);//注册主要绘图回调函数
    glutKeyboardFunc(&keyboard);//注册键盘回调函数

    initGL(640,480);//初始化窗口

    glutMainLoop();//开始事件处理引擎

    return 0;
}
