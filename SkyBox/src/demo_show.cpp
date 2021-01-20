#include "demo_show.h"

demo_show::demo_show(QWidget *parent) : QMainWindow(parent)
{
    this->setStyleSheet("QWidget#left_widget{background:gray;border-top:1px solid white;border-bottom:1px solid white; border-left:1px solid white;border-top-left-radius:10px;border-bottom-left-radius:10px;}");

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

     this->setCentralWidget(this->main_widget);
     this->left();
    this->right();
     this->beauty();
      setupUI();
      //初始化 默认选中
      buttonGroup->button(1)->click();
      btn->click();
}
void demo_show::left()
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
   // this->left_layout->addWidget(btn_next,1,0,2,3);
   // this->left_layout->addWidget(demo_next,3,0,2,3);

    connect(left_close,&QPushButton::pressed,[=](){


        this->close();
        emit close_signal();


    });
    connect(left_mini,&QPushButton::pressed,[=](){
        this->setWindowState(Qt::WindowMinimized);
    });
    connect(left_visit,&QPushButton::pressed,[=](){
        this->setWindowState(Qt::WindowMaximized);
    });
   fileName="";







}
void demo_show::right()
{
   /* QGridLayout *hg=new QGridLayout();
    b_widget->setLayout(hg);*/
    mwidget=new QWidget(this);

    mVideoPlayer = new QMediaPlayer(this);
    mSurfacePlayer = new QMediaPlayer(this);
    mVideoWidget  = new QVideoWidget(this);

    mVideoWidget->setStyleSheet("QVideoWidget{background:gray;}");
        mVideoPlayer->setVideoOutput(mVideoWidget);

        btn=new QPushButton(this);
        stopBtn=new QPushButton(this);
        fullScrBtn=new QPushButton(this);

        btn->setText(QString::fromLocal8Bit("播放"));
        stopBtn->setText(QString::fromLocal8Bit("暂停"));
        fullScrBtn->setText(QString::fromLocal8Bit("选择内容"));

        connect(btn,&QPushButton::pressed,[=](){
            this->on_btn_select_video_clicked();
        });
        connect(stopBtn,&QPushButton::pressed,[=](){
            this->stopVideo();
        });
        connect(fullScrBtn,&QPushButton::pressed,[=](){
            this->fullScr();
        });
        this->right_layout->addWidget(mVideoWidget,0,0,8,3);
        this->right_layout->addWidget(btn,8,0,1,1);
        this->right_layout->addWidget(stopBtn,8,1,1,1);
        this->right_layout->addWidget(fullScrBtn,8,2,1,1);


   // this->right_layout->addWidget(mVideoWidget,0,0,10,10);


}
void demo_show::beauty()
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
     left_widget->setStyleSheet( "QWidget#left_button:checked{border-left:4px solid yellow;font-weight:800;}"

                 "QPushButton{border:none;color:white;}QPushButton#left_label{ border:none; border-bottom:1px solid white;font-size:18px; font-weight:700;font-family: \"Helvetica Neue\", Helvetica, Arial, sans-serif;}QPushButton#left_button:hover{border-left:4px solid red;font-weight:700;}");
       right_widget->setStyleSheet(
            "  QWidget#right_widget{color:#232C51;background:white; border-top:1px solid darkGray;border-bottom:1px solid darkGray;border-right:1px solid darkGray;border-top-right-radius:10px; border-bottom-right-radius:10px;}QLabel#right_lable{border:none;font-size:16px;font-weight:700;font-family:\"Helvetica Neue\", Helvetica, Arial, sans-serif;}"

           );
       btn->setStyleSheet("QPushButton{background:gray;color:white;border-radius:2px;font-weight:700;}QPushButton:hover{border-left:4px solid red;font-weight:1000;}");
       stopBtn->setStyleSheet("QPushButton{background:gray;color:white;border-radius:2px;font-weight:700;}QPushButton:hover{border-left:4px solid red;font-weight:1000;}");
      fullScrBtn->setStyleSheet("QPushButton{background:gray;color:white;border-radius:2px;font-weight:700;}QPushButton:hover{border-left:4px solid red;font-weight:1000;}");
       this->setWindowOpacity(1.0) ;
           this->setAttribute(Qt::WA_TranslucentBackground) ;

           this->setWindowFlag(Qt::FramelessWindowHint);
           this->main_layout->setSpacing(0);


}
void demo_show::on_btn_select_video_clicked()

{

 //   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("video (*.mp4 *.wav *.avi *.*)"));

    if(fileName.isEmpty())

        return;
    qDebug()<<fileName;
    mVideoPlayer->setMedia(QUrl(fileName));


    mVideoPlayer->play();
    this->update();




}


void demo_show::stopVideo()
{
    m_playerState = QMediaPlayer::StoppedState;
    mVideoPlayer->stop();
}

void demo_show::fullScr()
{
    if(m_playerState == QMediaPlayer::PlayingState)
    {
         mVideoWidget->setFullScreen(true);
    }
    else
    {
         mVideoWidget->setFullScreen(false);
    }

}
void demo_show::mousePressEvent(QMouseEvent *e)
{
if(e->button()==Qt::LeftButton)
{ this->m_move=true;
    this->m_start=e->globalPos();
    this->m_btn=this->frameGeometry().topLeft();
}
QMainWindow::mousePressEvent(e);
}
void demo_show::mouseMoveEvent(QMouseEvent *e)
{
    QPoint relativepos=e->globalPos()-this->m_start;
    this->move(this->m_btn+relativepos);


QMainWindow::mouseMoveEvent(e);
}


void demo_show::mouseReleaseEvent(QMouseEvent *e)
{

    this->m_move=false;

    QMainWindow::mouseReleaseEvent(e);

}
void  demo_show::setupUI()

{

    /*QPushButton *button1 = new QPushButton("button1");

    button1->setObjectName("left_button");

    button1->setCheckable(true);

    QPushButton *button2 = new QPushButton("button2");

    button2->setObjectName("left_button");

    button2->setCheckable(true);

    QPushButton *button3 = new QPushButton("button3");

    button3->setObjectName("left_button");

    button3->setCheckable(true);*/
    add_mv();
    buttonGroup = new QButtonGroup;
    QPushButton *checked_button;

    for (int i = 0; i < mv_path.size(); ++i) {
        QPushButton *button = new QPushButton();
        button->setText(mv_name.at(i));
        buttonGroup->addButton(button,i);
        button->setObjectName("left_button");
        button->setCheckable(true);
         this->left_layout->addWidget(button,1+2*i,0,2,3);


    }


    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(on_changeButtonGroup(int)));
    buttonGroup->setExclusive(true);












}



void demo_show::on_changeButtonGroup(int id)

{

    QPushButton *checkedButton = qobject_cast<QPushButton*>(buttonGroup->checkedButton());

    QString checkedBtnObjectName = checkedButton->objectName();

    qDebug()<<tr("被选中按钮的objectName==%1").arg(mv_path.at(id));

    //"D:/as.mp4"
    fileName=QDir::currentPath()+"/mp4/"+mv_path.at(id);
    fullScrBtn->setText(mv_name.at(id));
    qDebug()<<QDir::currentPath();


}


void demo_show::add_mv()
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


