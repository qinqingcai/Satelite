#include "start_widget.h"

start_widget::start_widget(QWidget *parent) : QMainWindow(parent)
{

    this->resize(1024,800);

     main_widget=new QWidget();
     main_layout=new QGridLayout();
     main_widget->setLayout(main_layout);

     left_widget=new QWidget();
     left_widget->setObjectName("left_widget");
     left_layout=new QGridLayout();
     left_widget->setLayout(left_layout);

     right_widget=new QWidget();
     right_widget->setObjectName("right_widget");
     right_layout=new QGridLayout();
     right_widget->setLayout(right_layout);

     this->main_layout->addWidget(this->left_widget,0,0,12,2);
     this->main_layout->addWidget(this->right_widget,0,2,12,10);
     app_widget=NULL;
     demo_w=NULL;
     this->setCentralWidget(this->main_widget);
     this->left();
     this->right();
     this->beauty();
}
void start_widget::left()
{
   left_close=new QPushButton();
    left_visit=new QPushButton();
    left_mini=new QPushButton();
    btn_next=new QPushButton();
    btn_next->setText(QString::fromLocal8Bit("进入操作界面"));
    btn_next->setObjectName("left_button");
    demo_next=new QPushButton();
    demo_next->setObjectName("left_button");
    demo_next->setText(QString::fromLocal8Bit("示例"));

    this->left_layout->addWidget(left_mini,0,0,1,1);
    this->left_layout->addWidget(left_visit,0,1,1,1);
    this->left_layout->addWidget(left_close,0,2,1,1);
    this->left_layout->addWidget(btn_next,1,0,3,3);
    this->left_layout->addWidget(demo_next,4,0,3,3);
     this->left_layout->addWidget(new QWidget,7,0,6,3);
    connect(left_close,&QPushButton::pressed,[=](){
        if(demo_w!=NULL)
        {
            demo_w->close();

            delete demo_w;
            demo_w=NULL;

        }

        if(app_widget!=NULL)
        {


            delete app_widget;
            app_widget=NULL;


        }

        this->close();

    });
    connect(left_mini,&QPushButton::pressed,[=](){
        this->setWindowState(Qt::WindowMinimized);
    });
    connect(left_visit,&QPushButton::pressed,[=](){
        this->setWindowState(Qt::WindowMaximized);
    });
    connect(btn_next,&QPushButton::pressed,[=](){

        if(app_widget!=NULL)
        {

            delete app_widget;
            app_widget=NULL;

        }
        app_widget=new MainWindow();

        app_widget->show();

       connect(app_widget,&MainWindow::close_signals,[=](){




                app_widget=NULL;




    });

        connect(app_widget,&MainWindow::rebooot_signals,[=](){
            if(app_widget!=NULL)
            {

                delete app_widget;
                app_widget=NULL;

            }
            btn_next->click();

    });
   });
    connect(demo_next,&QPushButton::pressed,[=](){
        //实例
        if(demo_w!=NULL)
        {

            delete demo_w;
            demo_w=NULL;

        }
      demo_w=new demo_show();

        demo_w->show();
        connect(demo_w,&demo_show::close_signal,[=]()
        {
            if(demo_w!=NULL)
            {


                delete demo_w;
                demo_w=NULL;

            }
        });
    });



}
void start_widget::right()
{
    mv_widget=new TWindow();
    this->right_layout->addWidget(mv_widget,0,0,12,10);

}
void start_widget::beauty()
{
    this->left_close->setFixedSize(15,15);
    left_close->setToolTip(QString::fromLocal8Bit("关闭"));
    this->left_mini->setFixedSize(15,15);
    this->left_mini->setToolTip(QString::fromLocal8Bit("最小化"));
     this->left_visit->setFixedSize(15,15);
    this->left_visit->setToolTip(QString::fromLocal8Bit("最大化"));
    left_close->setStyleSheet(
               "QPushButton{background:#F76677;border-radius:5px;}QPushButton:hover{background:red;}");
      left_visit->setStyleSheet(
               "QPushButton{background:#F7D674;border-radius:5px;}QPushButton:hover{background:yellow;}");
    left_mini->setStyleSheet(
               "QPushButton{background:#6DDF6D;border-radius:5px;}QPushButton:hover{background:green;}");
     left_widget->setStyleSheet(
               "QPushButton{border:none;color:white;}QPushButton#left_label{ border:none; border-bottom:1px solid white;font-size:50px; font-weight:1000;font-family: \"Helvetica Neue\", Helvetica, Arial, sans-serif;}QPushButton#left_button:hover{border-left:4px solid red;font-weight:1100;}");
       right_widget->setStyleSheet(
            "  QWidget#right_widget{color:#232C51;background:white; border-top:1px solid darkGray;border-bottom:1px solid darkGray;border-right:1px solid darkGray;border-top-right-radius:10px; border-bottom-right-radius:10px;}QLabel#right_lable{border:none;font-size:16px;font-weight:700;font-family:\"Helvetica Neue\", Helvetica, Arial, sans-serif;}"
           );
         this->setWindowOpacity(1.0) ;
           this->setAttribute(Qt::WA_TranslucentBackground) ;

           this->setWindowFlag(Qt::FramelessWindowHint);
           this->main_layout->setSpacing(0);


}
void start_widget::mousePressEvent(QMouseEvent *e)
{
if(e->button()==Qt::LeftButton)
{ this->m_move=true;
    this->m_start=e->globalPos();
    this->m_btn=this->frameGeometry().topLeft();
}
QMainWindow::mousePressEvent(e);
}
void start_widget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint relativepos=e->globalPos()-this->m_start;
    this->move(this->m_btn+relativepos);


QMainWindow::mouseMoveEvent(e);
}


void start_widget::mouseReleaseEvent(QMouseEvent *e)
{

    this->m_move=false;

    QMainWindow::mouseReleaseEvent(e);

}
void start_widget::add_mv()
{
    mv_path.append("Ionosphere.mp4");
    mv_name.append(QString::fromLocal8Bit("电离层"));
    mv_path.append("position.mp4");
    mv_name.append(QString::fromLocal8Bit("定位"));
    mv_path.append("disturb_b.mp4");
    mv_name.append(QString::fromLocal8Bit("建筑物遮挡"));
    mv_path.append("length_add.mp4");
    mv_name.append(QString::fromLocal8Bit("伪距增加"));
    mv_path.append("false_satelite.mp4");

    mv_name.append(QString::fromLocal8Bit("伪卫星"));
    mv_path.append("add_satelite.mp4");
    mv_name.append(QString::fromLocal8Bit("增加卫星"));
    mv_path.append("reboot.mp4");
    mv_name.append(QString::fromLocal8Bit("重置"));
    mv_path.append("mul_path.mp4");
    mv_name.append(QString::fromLocal8Bit("多路径效应"));







}
