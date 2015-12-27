#include "myglwidget.h"
#include <QKeyEvent>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    translate = -6.0;
    xRot = yRot = zRot = 0.0;

    // �ر��Զ���䱳��
    setAutoFillBackground(false);
}

// ��ʼ������
void MyGLWidget::initializeGL()
{
}

// �����ӿڴ�С
void MyGLWidget::resizeGL(int w, int h)
{
    setupViewport(w, h);
}

// ��Ⱦ����
void MyGLWidget::paintGL()
{
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        translate -= 1;
        if (translate <= -20)
            translate = -1;
        break;
    }
    //updateGL();
    update();
    QGLWidget::keyPressEvent(event);
}

void MyGLWidget::paintEvent(QPaintEvent *)
{
    // �ڵ�ǰ�����н���OpenGL�Ļ���
    makeCurrent();
    // ��ģ����ͼ����ѹ���ջ
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // ��������ǰinitializeGL()�����е�ȫ������
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    textures[0] = bindTexture(QPixmap("../myOpenGL/side1.png"));
    textures[1] = bindTexture(QPixmap("../myOpenGL/side2.png"));
    textures[2] = bindTexture(QPixmap("../myOpenGL/side3.png"));
    glEnable(GL_TEXTURE_2D);

    // �ú���������ǰresizeGL()�����е�ȫ������
    setupViewport(width(), height());

    // ��������ǰpaintGL()�����е�ȫ������
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, translate);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();

    // �ر����õĹ��ܲ�����ģ����ͼ����
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // ������2D��ͼ������
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, 100, 100);
    painter.end();
}

void MyGLWidget::setupViewport(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
