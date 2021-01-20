#include "TWindow.h"
#include"start_widget.h"
#include <QApplication>
#include <QSurfaceFormat>
#include<QMainWindow>
#include<QHBoxLayout>
#include<QPushButton>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setVersion(3, 3);
    fmt.setDepthBufferSize(24);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
#ifdef _DEBUG
    fmt.setOption(QSurfaceFormat::DebugContext);
#endif
    QSurfaceFormat::setDefaultFormat(fmt);

    /*QMainWindow *mainw=new QMainWindow();
    TWindow *w=new TWindow();
    w->setParent(mainw);
    w->setGeometry(100,100,500,500);





    mainw->show();
    mainw->resize(800,600);*/
    start_widget w;
    w.show();
    app.setStyleSheet("QWidget#left_widget{background:gray;border-top:1px solid white;border-bottom:1px solid white; border-left:1px solid white;border-top-left-radius:10px;border-bottom-left-radius:10px;}");
    return app.exec();
}
