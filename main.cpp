#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    if (!QGLFormat::hasOpenGL()) {
        QMessageBox::information(0, application.applicationName(), "This system does not support OpenGL.");
        return -1;
    }

    if (QGLFormat::openGLVersionFlags() < QGLFormat::OpenGL_Version_3_0) {
        QMessageBox::information(0, application.applicationName(), "This system does not support OpenGL 3.0 Contexts");
        return -2;
    }

    MainWindow w;
    w.setApplication(&application);
    w.show();

    return application.exec();
}
