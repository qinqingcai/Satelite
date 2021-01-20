#include "mainwindow.h"
#include "ui_mainwindow.h"
int const MainWindow::REBOOT_CODE=-1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setStyleSheet("QWidget:hover{border: 2px dotted green;}");
    this->time_count=0;//设置时间起点
     label=new QLabel(this);
    qsrand(time(NULL));
    ui->setupUi(this);

    this->setWindowOpacity(1.0) ;
      this->setAttribute(Qt::WA_TranslucentBackground) ;

      this->setWindowFlag(Qt::FramelessWindowHint);

    this->setWindowTitle("navigation");
    this->setWindowIcon(QPixmap(":/assets/wx.png"));
    //设置初始界面
    this->setWindowState(Qt::WindowMaximized);
    wx *we=new wx(":/assets/wx_1.png");
    we->setParent(this);
    we->move(this->width()/6+10*(qrand() % 10),50);
    wx *we1=new wx(":/assets/wx_1.png");
    we1->setParent(this);
    we1->move(300+10*(qrand() % 10),50);
    wx *we2=new wx(":/assets/wx_1.png");
    we2->setParent(this);
    we2->move(600+10*(qrand() % 10),50);
    wx *we3=new wx(":/assets/wx_1.png");
    we3->setParent(this);
    we3->move(800,50);
    wx_list.append(we);
    wx_list.append(we2);
    wx_list.append(we1);
    wx_list.append(we3);


    this->get_r=new wx(":/assets/receiver.png");
     get_r->setParent(this);
     get_r->move(this->width()/2,700);
     this->get=new wx(":/assets/get1.png");
      get->setParent(this);
      get->move(this->width()/2,this->height()-100);
    //响应初始的卫星
    we->get_angel(this->get);
    we1->get_angel(this->get);
    we2->get_angel(this->get);
    we3->get_angel(this->get);
    //设置卫星标识
    we->get_id=false;
    we1->get_id=false;
    we2->get_id=false;
    we3->get_id=false;

    connect(we,&wx::delete_wx,[=]()
    {
        if(we->wx_r!=NULL)
        {

            we->wx_r->close();
            delete we->wx_r;
            we->wx_r=NULL;
        }
        we->close();
        this->wx_list.removeOne(we);
        delete we;
       qDebug()<<this->wx_list.count();
       this->update();
    });
    connect(we,&wx::move_update,[=]()
    {
         we->get_angel(this->get);
         if(we->geometry().bottomLeft().y()>ylabel->geometry().topLeft().y())
         {
             we->move(we->geometry().topLeft().x(),ylabel->geometry().topLeft().y()-we->height());
         }
       this->update();
    });

    connect(we1,&wx::delete_wx,[=]()
    {
        if(we1->wx_r!=NULL)
        {

            we1->wx_r->close();
            delete we1->wx_r;
            we1->wx_r=NULL;
        }
        we1->close();
        this->wx_list.removeOne(we1);
        delete we1;
       qDebug()<<this->wx_list.count();
       this->update();
    });
    connect(we1,&wx::move_update,[=]()
    {
        we1->get_angel(this->get);
        if(we1->geometry().bottomLeft().y()>ylabel->geometry().topLeft().y())
        {
            we1->move(we1->geometry().topLeft().x(),ylabel->geometry().topLeft().y()-we->height());
        }
       this->update();
    });
    connect(this->get,&wx::move_update,[=]()
    {
        this->position_get();
       this->update();
    });


    connect(we2,&wx::delete_wx,[=]()
    {
        if(we2->wx_r!=NULL)
        {

            we2->wx_r->close();
            delete we2->wx_r;
            we2->wx_r=NULL;
        }
        we2->close();
        this->wx_list.removeOne(we2);
        delete we2;
       qDebug()<<this->wx_list.count();
       this->update();
    });
    connect(we2,&wx::move_update,[=]()
    {
        we2->get_angel(this->get);
        if(we2->geometry().bottomLeft().y()>ylabel->geometry().topLeft().y())
        {
            we2->move(we2->geometry().topLeft().x(),ylabel->geometry().topLeft().y()-we2->height());
        }
       this->update();
    });
    connect(we3,&wx::delete_wx,[=]()
    {
        if(we3->wx_r!=NULL)
        {

            we3->wx_r->close();
            delete we3->wx_r;
            we3->wx_r=NULL;
        }
        we3->close();
        this->wx_list.removeOne(we3);
        delete we3;
       qDebug()<<this->wx_list.count();
       this->update();
    });
    connect(we3,&wx::move_update,[=]()
    {
        we3->get_angel(this->get);
        if(we3->geometry().bottomLeft().y()>ylabel->geometry().topLeft().y())
        {
            we3->move(we3->geometry().topLeft().x(),ylabel->geometry().topLeft().y()-we3->height());
        }
       this->update();
    });


    //增加退出按键
    QMenuBar * bar=menuBar();
    bar->setStyleSheet("QMenuBar{background:gray;}");
       this->setMenuBar(bar);
    bar->addMenu(QString::fromLocal8Bit("                         "));


      QMenu * startmenu=bar->addMenu(QString::fromLocal8Bit("设置"));
      startmenu->setIcon(QIcon(":/assets/set.png"));
      connect(startmenu,&QMenu::triggered,[=](){
          qDebug()<<"==========";
      });


      //增加卫星个数

      QAction * wxnew= startmenu->addAction(QString::fromLocal8Bit("增加卫星个数"));
      connect(wxnew,&QAction::triggered,[=]()
         {
             wx * add_wx=new wx(":/assets/wx_1.png");
             add_wx->setParent(this);
             add_wx->move(this->width()/4+50*(qrand() % 10),50);
             add_wx->show();
             add_wx->get_id=false;
             add_wx->get_angel(this->get);
             this->wx_list.append(add_wx);
             qDebug()<<this->wx_list.count();
             this->update();
             connect(add_wx,&wx::delete_wx,[=]()
             {
                 if(add_wx->wx_r!=NULL)
                 {

                     add_wx->wx_r->close();
                     delete add_wx->wx_r;
                     add_wx->wx_r=NULL;
                 }
                 add_wx->close();
                 this->wx_list.removeOne(add_wx);
                 delete add_wx;
                qDebug()<<this->wx_list.count();
                this->update();
             });

             connect(add_wx,&wx::move_update,[=]()
             {
                 add_wx->get_angel(this->get);
                 if( add_wx->geometry().bottomLeft().y()>ylabel->geometry().topLeft().y())
                 {
                      add_wx->move( add_wx->geometry().topLeft().x(),ylabel->geometry().topLeft().y()-we->height());
                 }
                this->update();
             });

         }

         );
      QMenu * menumin=bar->addMenu(QString::fromLocal8Bit(""));
      menumin->setStyleSheet("QMenu{background:#F76677;border-radius:5px;}QMenu:hover{background:red;}");
      menumin->setIcon(QIcon(QPixmap(":/assets/min.png").scaled(15,15)));
      QAction * minaction= menumin->addAction(QString::fromLocal8Bit("最小化"));
      connect(minaction,&QAction::triggered,[=]()
         {
             this->setWindowState(Qt::WindowMinimized);

         }
         );
      QMenu * menumax=bar->addMenu(QString::fromLocal8Bit(""));
      menumax->setStyleSheet("QMenu{background:#F76677;border-radius:5px;}QMenu:hover{background:red;}");
      menumax->setIcon(QIcon(QPixmap(":/assets/max.png").scaled(15,15)));
      QAction * maxaction= menumax->addAction(QString::fromLocal8Bit("最大化"));
      connect(maxaction,&QAction::triggered,[=]()
         {
             this->setWindowState(Qt::WindowMaximized);

         }
         );
      QMenu * startmenu1=bar->addMenu(QString::fromLocal8Bit("退出"));
      startmenu1->setStyleSheet("QMenu{background:#F76677;border-radius:5px;}QMenu:hover{background:red;}");
      startmenu1->setIcon(QIcon(QPixmap(":/assets/close.png").scaled(15,15)));
      QAction * quitaction= startmenu1->addAction(QString::fromLocal8Bit("退出"));
      connect(quitaction,&QAction::triggered,[=]()
         {
             this->close();
          emit close_signals();


         }
         );

      //计算坐标
      QAction * calculate_position= startmenu->addAction(QString::fromLocal8Bit("解算接收机坐标"));
      connect(calculate_position,&QAction::triggered,[=]()
      {
          this->position_get();
      });
      //增加电离层选项
      label1=new QLabel(this);
       QFont font;
      font.setFamily("华文新魏");
       font.setPointSize(12);
      label1->setFont(font);
      label1->setWordWrap(true);
      label1->setText(QString::fromLocal8Bit("是否补偿电离层误差"));
 this->const_error=0;

      QButtonGroup *groupButton=new QButtonGroup(this);
           pGreenSwitchControl = new SwitchControl(this);
     //       pGreenSwitchControl->setCheckedColor(QColor(0, 160, 230));
            connect(pGreenSwitchControl, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));
     /* choose_error=new QRadioButton(this);
      choose_error->setText("Yes");
      choose_nothing=new QRadioButton(this);
      choose_nothing->setText("NO");
      groupButton->addButton(choose_nothing,0);
      groupButton->addButton(choose_error,1);
      choose_nothing->setChecked(true);
      this->const_error=0;
        choose_error->move(this->width()-200,160);
        choose_nothing->move(this->width()-200,140);
      connect(choose_nothing,&QRadioButton::clicked,[=]()
      {
            this->const_error=0;

      });
      connect(choose_error,&QRadioButton::clicked,[=]()
      {
          int index=1+this->pslider->value()/10;


          double rate=index*0.08;
          this->const_error=rate;

      });*/

      //增加建筑物
      QAction * add_building=startmenu->addAction(QString::fromLocal8Bit("增加建筑物"));
      connect(add_building,&QAction::triggered,[=]()
      {
          wx * build=new wx(":/assets/building.png");
          build->setParent(this);
          build->move(800,200);
          build->show();
          this->building_list.append(build);
          connect(build,&wx::delete_wx,[=]()
          {
              build->close();
                this->building_list.removeOne(build);
              qDebug()<<this->building_list.count();
              delete build;


          });
          connect(build,&wx::move_update,[=]()
          {
             this->update();
          });
          qDebug()<<"buiolding";

      });

     QAction * number_wx=startmenu->addAction(QString::fromLocal8Bit("可见卫星个数"));
      connect(number_wx,&QAction::triggered,[=]()
      {
          this->enable_see_wx();
          QList<bool >::iterator tmp;
          int i=0;
          for(tmp=this->wx_see_list.begin();tmp!=this->wx_see_list.end();tmp++)
          {
              if(*tmp)
              {
                  qDebug()<<"can see";
                  i++;
              }
              else {
                  qDebug()<<"can't see";
              }

          }


      });
      //重置
      QAction * restart=startmenu->addAction(QString::fromLocal8Bit("重置"));
      connect(restart,&QAction::triggered,[=]()
      {
          this->reboot();
      });
      //增加工具栏

     toolbar=new QToolBar();
     toolbar->setGeometry(0,65,100,this->height());
      addToolBar(Qt::LeftToolBarArea,toolbar);

    toolbar->setWindowOpacity(0.5);
    toolbar->setIconSize(QSize(toolbar->width(),toolbar->height()/3));

     toolbar->setFloatable(false);

     QAction *tool_add_wx=new QAction();
     tool_add_wx->setToolTip(QString::fromLocal8Bit("增加卫星"));
     //QPixmap(":/wx.png").scaled(100,toolbar->height())
     tool_add_wx->setIcon(QIcon(":/assets/wx.png"));
     toolbar->addAction(tool_add_wx);

    connect(tool_add_wx,&QAction::triggered,
            [=]()
    {

        wxnew->trigger();
    });



    QAction *tool_add_building=new QAction();

    tool_add_building->setToolTip(QString::fromLocal8Bit("增加周围建筑物"));
    tool_add_building->setIcon(QIcon(":/assets/building.png"));
    toolbar->addAction(tool_add_building);

   connect(tool_add_building,&QAction::triggered,
           [=]()
   {

       add_building->trigger();
   });



  //增加重置快捷按钮
  QAction *tool_reboot=new QAction();
  tool_reboot->setToolTip(QString::fromLocal8Bit("一键重置"));
  tool_reboot->setIcon(QIcon(":/assets/reboot.png"));

  connect(tool_reboot,&QAction::triggered,
          [=]()
  {

      this->reboot();
  });

    QTimer *qtimer=new QTimer(this);
    connect(qtimer, SIGNAL(timeout()),this,SLOT(timerUpDate()));
    qtimer->start(500);



    //增加电离层
    int nMin=0;
    int nMax=150;
    int nsinglestep=1;
    pspinbox=new QSpinBox(this);
    pspinbox->setMinimum(nMin);
    pspinbox->setMaximum(nMax);
    pspinbox->setSingleStep(nsinglestep);
    //pspinbox->move(this->width()-100,this->height()/2);

    this->pslider=new QSlider(this);
    this->pslider->setOrientation(Qt::Vertical);
    this->pslider->setMinimum(nMin);
   this->pslider->setMaximum(nMax);
    this->pslider->setSingleStep(nsinglestep);


    connect(pspinbox,SIGNAL(valueChanged(int)),this->pslider,SLOT(setValue(int)));
    connect(pspinbox,SIGNAL(valueChanged(int)),this,SLOT(select_which()));
    connect(this->pslider,SIGNAL(valueChanged(int)),pspinbox,SLOT(setValue(int)));
    this->pslider->setValue(10);

    this->ispain=false;
    this->ylabel=new bg_btn(&(this->time_count));
    this->ylabel->setParent(this);
        this->ylabel->setGeometry(QRect(0,this->height()/3,this->width()-200,60));
        this->ylabel->setStyleSheet("QLabel{border:0px;}");

    toolbar->addWidget(this->pslider);
    this->toolbar->addWidget(this->pspinbox);



    this->statusBar()->addPermanentWidget(this->label);
    //增加滑动条文字提示
    this->label_low=new QLabel(this);
    this->label_high=new QLabel(this);
    this->label_low->setText(QString::fromLocal8Bit("弱"));
    this->label_high->setText(QString::fromLocal8Bit("强"));

    //坐标轴
    this->o_label=new QLabel(this);
    this->x_label=new QLabel(this);
    this->y_label=new QLabel(this);
    this->toolbar->addWidget(this->label1);

   //this->toolbar->addWidget(this->pGreenSwitchControl);

    //增加图层说明
    this->label_dlc=new QLabel(this);
    this->label_tk=new QLabel(this);
    this->label_dqc=new QLabel(this);
    this->label_tk->setText(QString::fromLocal8Bit("外太空"));
   // label_tk->setStyleSheet("QLabel{ font-size:20px; font-weight:1000;font-family: \"Helvetica Neue\", Helvetica, Arial, sans-serif;}");
    label_tk->setStyleSheet("QLabel{ font-size:20px; font-weight:1000;font-family: \"Microsoft YaHei\";}");
    this->label_dlc->setText(QString::fromLocal8Bit("电离层"));
    this->label_dqc->setText(QString::fromLocal8Bit("大气层"));
    label_dlc->setStyleSheet("QLabel{ font-size:20px; font-weight:1000;font-family: \"Microsoft YaHei\";}");
    label_dqc->setStyleSheet("QLabel{ font-size:20px; font-weight:1000;font-family: \"Microsoft YaHei\";}");
    toolbar->addAction(tool_reboot);





}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    toolbar->setGeometry(0,65,100,this->height()-100);
    toolbar->setIconSize(QSize(toolbar->width(),toolbar->height()/6));
    this->pslider->resize(30,this->toolbar->height()/6);
    this->label1->resize(this->toolbar->width(),100);
    this->pspinbox->move(0,this->toolbar->geometry().bottomLeft().y()/2+20);
    this->label1->move(0,this->toolbar->height()*2/3-30);


    this->pGreenSwitchControl->move(0,this->toolbar->height()*2/3+130);
    pGreenSwitchControl->raise();

   // this->choose_error->move(0,this->toolbar->height()*2/3+50);
   // this->choose_nothing->move(0,this->toolbar->height()*2/3+70);
    this->label_high->move(this->pslider->geometry().topRight().x(),this->pslider->geometry().topRight().y()+60);
    this->label_low->move(this->pslider->geometry().bottomRight().x(),this->pslider->geometry().bottomRight().y()+60);

this->ylabel->setGeometry(QRect(this->width()/18,this->height()/4.1,this->width(),120));
    QPainter painter(this);

     QPixmap pix;
      pix.load((":/assets/bg_new.png"));
     painter.drawPixmap(0,0,this->width(),this->height(),pix);
     QPen pen1(Qt::white,0.1);
   pen1.setStyle(Qt::DashLine);
     painter.setPen(pen1);
     QLinearGradient linearGradient(QPointF(this->ylabel->geometry().topLeft()),QPointF(this->ylabel->geometry().bottomLeft()));
         //插入颜色
         linearGradient.setColorAt(0, QColor(210, 200-this->pic_count*12, 200-this->pic_count*12));
         //linearGradient.setColorAt(0.5, Qt::red);
         linearGradient.setColorAt(0.5, QColor(210, 200-this->pic_count*8, 200-this->pic_count*8));
         linearGradient.setColorAt(1, QColor(210, 200-this->pic_count*4, 200-this->pic_count*4));
         painter.setBrush(linearGradient);
         painter.drawRect(this->ylabel->geometry());
     QPen pen(Qt::red,2);
   pen.setStyle(Qt::DashLine);
     painter.setPen(pen);
    /* if(this->ispain==true)
     {

         painter.drawEllipse(ylabel->geometry().left()+ylabel->c_x,ylabel->geometry().top()+ylabel->c_y,20,20);
     }*/

    QList<wx *>::iterator tmp;
    QList<bool >::iterator tmp_bool;
    this->enable_see_wx();
     for(tmp=this->wx_list.begin(),tmp_bool=this->wx_see_list.begin();tmp!=this->wx_list.end();tmp++,tmp_bool++)
     {

         /*painter.drawLine((this->get->geometry().topLeft()+this->get->geometry().topRight())/2,
                          ((*tmp)->geometry().bottomRight()+(*tmp)->geometry().bottomLeft())/2);*/
         if((*tmp_bool)==true)
         {
             if((*tmp)->wx_r!=NULL)
             {
                 painter.drawLine((*tmp)->wx_r->geometry().center(),this->get->geometry().center());
             }
             //painter.drawLine(this->get->geometry().center(),(*tmp)->geometry().center());
                painter.drawLine(this->get->geometry().center().x()+1.0*(*tmp)->add_length*cos((*tmp)->angle),
                                 this->get->geometry().center().y()+1.0*(*tmp)->add_length*sin((*tmp)->angle),
                                 (*tmp)->geometry().center().x(),(*tmp)->geometry().center().y()
                                 );
         }
         else
         {
             //初略计算，减少使用斜率计算交叉点
             (*tmp)->get_angel(this->get);
             double tmp_x=this->get->geometry().center().x()-(*tmp)->disturb_building->geometry().center().x();
             double tmp_y=this->get->geometry().center().y()-(*tmp)->disturb_building->geometry().center().y();
             double d_length=sqrt(tmp_x*tmp_x+tmp_y*tmp_y);
             painter.drawLine(this->get->geometry().center().x()-d_length*cos((*tmp)->angle),
                              this->get->geometry().center().y()-d_length*sin((*tmp)->angle),
                              (*tmp)->geometry().center().x(),(*tmp)->geometry().center().y()
                              );
             //painter.drawLine((*tmp)->geometry().center(),(*tmp)->disturb_building->geometry().center());
             if((*tmp)->reflect_id)
         {


                 painter.drawLine((*tmp)->geometry().center(),(*tmp)->p_reflect);
                 painter.drawLine(this->get->geometry().center(),(*tmp)->p_reflect);
                 qDebug()<<(*tmp)->p_reflect.x()<<" ---  "<<(*tmp)->p_reflect.y();

         }
         }



     }

     //画坐标轴
     QPen pen2(Qt::black,3);
     painter.setPen(pen2);
     painter.drawLine(this->centralWidget()->geometry().topLeft(),this->centralWidget()->geometry().bottomLeft());
     painter.drawLine(this->centralWidget()->geometry().bottomLeft(),this->centralWidget()->geometry().bottomRight());
     painter.drawLine(this->centralWidget()->geometry().bottomRight().x(),this->centralWidget()->geometry().bottomRight().y(),
                      this->centralWidget()->geometry().bottomRight().x()-5,this->centralWidget()->geometry().bottomRight().y()-5);
     painter.drawLine(this->centralWidget()->geometry().bottomRight().x(),this->centralWidget()->geometry().bottomRight().y(),
                      this->centralWidget()->geometry().bottomRight().x()-5,this->centralWidget()->geometry().bottomRight().y()+5);
     painter.drawLine(this->centralWidget()->geometry().topLeft().x(),this->centralWidget()->geometry().topLeft().y(),
                      this->centralWidget()->geometry().topLeft().x()-5,this->centralWidget()->geometry().topLeft().y()+5);
     painter.drawLine(this->centralWidget()->geometry().topLeft().x(),this->centralWidget()->geometry().topLeft().y(),
                      this->centralWidget()->geometry().topLeft().x()+5,this->centralWidget()->geometry().topLeft().y()+5);
     //显示文字

     QFont font;
    font.setFamily("微软雅黑");
     font.setPointSize(15);
     this->x_label->setFont(font);
     x_label->move(this->centralWidget()->geometry().bottomRight().x()/2,this->centralWidget()->geometry().bottomRight().y()-50);

     x_label->setText(QString::fromLocal8Bit("水平(m)"));
     this->y_label->setFont(font);
     y_label->move(this->centralWidget()->geometry().topLeft().x()+50,this->height()/2);

     y_label->setText(QString::fromLocal8Bit("高程(m)"));
     //设置图层标签位置
      font.setPointSize(25);
     this->label_tk->setFont(font);
     this->label_dlc->setFont(font);
     this->label_dqc->setFont(font);
     this->label_tk->move(this->centralWidget()->geometry().topLeft().x()-70,100);
     this->label_dlc->move(this->centralWidget()->geometry().topLeft().x()-70,300);
     this->label_dqc->move(this->centralWidget()->geometry().topLeft().x()-70,600);

     this->update();




}
bool MainWindow::disturb(QPoint p1,QPoint p2,QPoint m,int length,int width)
{
    double l_x;
    double r_x;
    double t_y;
    double b_y;
    if(p1.x()>p2.x())
    {
        l_x=p2.x();
        r_x=p1.x();
    }
    else {
        l_x=p1.x();
        r_x=p2.x();
    }
    if(p1.y()>p2.y())
    {
       t_y=p2.y();
       b_y=p1.y();
    }
    else {
        t_y=p1.y();
        b_y=p2.y();
    }
    if(m.x()>r_x||m.x()+length<=l_x)
    {
        return true;
    }
    if(m.y()<t_y||m.y()-width>=b_y)
    {
        return true;
    }


    //使用double来存储int防止溢出
    double a=((p2.x() - p1.x())*(m.y() - p1.y()) - (p2.y() - p1.y())*(m.x() - p1.x()));
    double b=((p2.x() - p1.x())*(m.y() - width - p1.y()) - (p2.y() - p1.y())*(m.x() + length - p1.x()));
    double c=((p2.x() - p1.x())*(m.y() - p1.y()) - (p2.y() - p1.y())*(m.x() + length- p1.x()));
    double d=((p2.x()- p1.x())*(m.y() - width - p1.y()) - (p2.y() - p1.y())*(m.x() - p1.x()));

   if(a*b<0||c*d<0)
       return false;
    else
        return true;
}


void MainWindow::enable_see_wx()
{
    this->wx_see_list.clear();
    QList<wx *>::iterator tmp_wx;
    QList<wx *>::iterator tmp_building;
   // qDebug()<<"------------";
    for(tmp_wx=this->wx_list.begin();tmp_wx!=this->wx_list.end();tmp_wx++)
    {

        for(tmp_building=this->building_list.begin();tmp_building!=this->building_list.end();tmp_building++)
        {
            if(!(MainWindow::disturb((*tmp_wx)->geometry().center(),this->get->geometry().center(),(*tmp_building)->geometry().bottomLeft(),(*tmp_building)->width(),(*tmp_building)->height())))
            {
                    this->wx_see_list.append(false);
                (*tmp_wx)->disturb_building=*tmp_building;

                    /*qDebug()<<"CAn't see"<<(*tmp_building)->width();
                    qDebug()<<(*tmp_building)->height();*/
                    break;
            }


        }
        if(tmp_building==building_list.end())
        {
            this->wx_see_list.append(true);
            //qDebug()<<"CAn see";
        }

    }
    //qDebug()<<"------------";
}

void MainWindow::position_get()
{
    this->enable_see_wx();
    QList<bool >::iterator tmp_see;
    QList<wx *>::iterator tmp_wx;
    int icount=0;
    for(tmp_see=this->wx_see_list.begin(),tmp_wx=this->wx_list.begin();tmp_see!=this->wx_see_list.end();tmp_see++,tmp_wx++)
    {
    if((*tmp_see)==true)
        icount++;
    else {
        int dx=100,dy=100;
        QList<wx *>::iterator tmp_building;
        (*tmp_wx)->reflect_id=false;
        for(tmp_building=this->building_list.begin();tmp_building!=this->building_list.end();tmp_building++)
        {
            if(this->get_reflect(*tmp_building,(*tmp_wx)->geometry().center(),dx,dy))
            {
                (*tmp_wx)->reflect_id=true;
                (*tmp_wx)->p_reflect.rx()=dx;

                (*tmp_wx)->p_reflect.ry()=dy;
                icount++;

                //qDebug()<<dx<<"=====    "<<dy;
                break;
            }
        }


    }
    }
    if(icount<4)
    {
            this->get_r->move(this->get_r->x()+pow(-1,int(qrand() % 2))*(qrand() % 5000)/100.0+30,this->get_r->y()+10+pow(-1,int(qrand() % 2))*(20+ (qrand() % 5000)/100.0));
        //QMessageBox::information(this,"Title",QString::fromLocal8Bit("可观测的卫星个数不能小于4"));
        label->setText(QString::fromLocal8Bit("可观测的卫星个数不能小于4颗      "));
        return ;
    }
    Matrix H(icount,3);
    Matrix Z0(icount,1);
    Matrix Z(icount,1);int i=0;
    Matrix tmp_Z(icount,1);
    Matrix result(3,1);
    Matrix Delt(3,3);
    Matrix delt(1,1);//单位中误差
    Matrix v(icount,1);
    Matrix tp(3,3);

   QFont font;
   font.setFamily("微软雅黑");
  font.setPointSize(15);
  label->setFont(font);
   QList<wx *>::iterator tmp;
     for(tmp=this->wx_list.begin(),tmp_see=this->wx_see_list.begin();tmp!=this->wx_list.end();tmp++,tmp_see++)
     {
         if((*tmp_see)==true)
         {

             Z(i,0)=sqrt(pow(this->get->geometry().center().x()-(*tmp)->geometry().center().x(),2)+pow(this->get->geometry().center().y()-(*tmp)->geometry().center().y(),2))+

          this->get_random()+(*tmp)->add_length+this->ylabel->height()/sin((*tmp)->angle)*(get_dlc_rate()-this->const_error);
             qDebug()<<"Get"<<get_dlc_rate()<<"   "<<this->const_error;

             if((*tmp)->wx_r==NULL)
             {
             Z0(i,0)=sqrt(pow(this->get->geometry().center().x()-(*tmp)->geometry().center().x(),2)+pow(this->get->geometry().center().y()-(*tmp)->geometry().center().y(),2));
             H(i,0)=(this->get->geometry().center().x()-(*tmp)->geometry().center().x())/Z0(i,0);
             H(i,1)=(this->get->geometry().center().y()-(*tmp)->geometry().center().y())/Z0(i,0);
             H(i,2)=1;
             }
             else {
                 Z0(i,0)=sqrt(pow(this->get->geometry().center().x()-(*tmp)->wx_r->geometry().center().x(),2)+pow(this->get->geometry().center().y()-(*tmp)->wx_r->geometry().center().y(),2));
                 H(i,0)=(this->get->geometry().center().x()-(*tmp)->wx_r->geometry().center().x())/Z0(i,0);
                 H(i,1)=(this->get->geometry().center().y()-(*tmp)->wx_r->geometry().center().y())/Z0(i,0);
                 H(i,2)=1;

             }

             i++;
         }
         else {
             int dx=100,dy=100;
             QList<wx *>::iterator tmp_building;
             (*tmp)->reflect_id=false;
             for(tmp_building=this->building_list.begin();tmp_building!=this->building_list.end();tmp_building++)
             {
                 if(this->get_reflect(*tmp_building,(*tmp)->geometry().center(),dx,dy))
                 {
                     (*tmp)->reflect_id=true;
                     (*tmp)->p_reflect.rx()=dx;

                     (*tmp)->p_reflect.ry()=dy;

                     //qDebug()<<dx<<"=====    "<<dy;
                     break;
                 }
             }
             if(tmp_building!=this->building_list.end())
             {

                 Z(i,0)=sqrt(pow(this->get->geometry().center().x()-(*tmp)->p_reflect.x(),2)+pow(this->get->geometry().center().y()-(*tmp)->p_reflect.y(),2))+
                           sqrt(pow((*tmp)->geometry().center().x()-(*tmp)->p_reflect.x(),2)+pow((*tmp)->geometry().center().y()-(*tmp)->p_reflect.y(),2)) ;
                              Z0(i,0)=sqrt(pow(this->get->geometry().center().x()-(*tmp)->geometry().center().x(),2)+pow(this->get->geometry().center().y()-(*tmp)->geometry().center().y(),2));
                              H(i,0)=(this->get->geometry().center().x()-(*tmp)->geometry().center().x())/Z0(i,0);
                              H(i,1)=(this->get->geometry().center().y()-(*tmp)->geometry().center().y())/Z0(i,0);
                              H(i,2)=1;
                              //qDebug()<< H(i,0)<<"  "<< H(i,1);
                              i++;

             }


         }


     }


     try {
         result=((H.getTranspose()*H).getInverse())*(H.getTranspose())*(Z-Z0);


           tmp_Z=Z0-Z;
           Matrix tmp_x=H*result;



        Matrix v=tmp_x+tmp_Z;
        qDebug()<<v(0,0)<<"==="<<v(1,0)<<"=="<<v(2,0);


         result(0,0)=result(0,0)+this->get->geometry().center().x();
         result(1,0)=result(1,0)+this->get->geometry().center().y();
         delt=(v.getTranspose()*v)/(1.0*this->wx_list.count()-3);

                tp=H.getTranspose()*H;
                 Delt=double(delt(0,0))*(tp.getInverse());




         label->clear();

         QString str;

         str=QString::fromLocal8Bit("解算坐标：水平:%1高程 :%2 实际坐标:水平 :%3高程 :%4 (m)").arg(result(0,0)-this->centralWidget()->geometry().bottomLeft().x(),6).arg(this->centralWidget()->height()-result(1,0),6).arg(-this->centralWidget()->geometry().bottomLeft().x()+this->get->geometry().center().x()).arg(this->centralWidget()->height()-this->get->geometry().center().y());
         if(icount>4)

           {
                    str+=QString::fromLocal8Bit("单位中误差：%3水平误差:%1高程误差:%1").arg(Delt(0,0)).arg(Delt(1,1));
           }


           label->setText(str);





     } catch (...) {
   qDebug()<<"error";
     }
     label->show();
     if(abs(result(0,0)-this->get->geometry().center().x())>=300)
      {
          result(0,0)=this->get->geometry().center().x()+200+(qrand() % 5000)/100.0;
      }
      if(abs(result(1,0)-this->get->geometry().center().y())>=300)
      {
          result(1,0)=this->get->geometry().center().y()+200+(qrand() % 5000)/100.0;
      }

    int move_x=result(0,0)-this->get->width()/2;
    int move_y=result(1,0)-this->get->height()/2;
    if(move_x>=this->width())
        move_x=this->width();
    else if (move_x<=this->get_r->width()/2) {
        move_x=this->get_r->width()/2;

    }
    if(move_y>=this->height())
        move_y=this->height();
    else if (move_y<=this->get_r->height()/2) {
        move_y=this->get_r->height()/2;

    }


this->get_r->move(move_x,move_y);




/*qDebug()<<"delt_x:"<<Delt(0,0)<<"  "<<Delt(0,1)<<"  "<<Delt(0,2);
qDebug()<<"delt_y:"<<Delt(1,0)<<"  "<<Delt(1,1)<<"  "<<Delt(1,2);
qDebug()<<"delt_y:"<<Delt(2,0)<<"  "<<Delt(2,1)<<"  "<<Delt(2,2);*/
}
void MainWindow::timerUpDate()
{
    this->position_get();
    this->time_count++;
    if(time_count>100000000)
    {
        this->time_count=0;
    }
    if(this->pslider->value()>0&&(this->time_count)%10==0)
    {

        this->pslider->setValue(this->pslider->value()-1);
    }
    this->pic_count=this->pslider->value()/10.0;
    /*int index=13-this->pslider->value()/10;
        QPixmap *pixmap = new QPixmap(QString(":/y%1.png").arg(index));
        pixmap->scaled(this->ylabel->size(), Qt::KeepAspectRatio);
        this->ylabel->setScaledContents(true);
        this->ylabel->setPixmap(*pixmap);*/
}

bool MainWindow::get_reflect(wx *p1,QPoint p2,int &x,int &y)
{
    double x1=p1->geometry().left()-this->get->geometry().center().x();
    double x2=p1->geometry().left()-p2.x();
    double x3=p1->geometry().right()-this->get->geometry().center().x();
    double x4=p1->geometry().right()-p2.x();
    qDebug()<<x1<<x2<<x3<<x4;
   if(x1*x2<0||x3*x4<0)
       return false;
   if(x2>0)
   {
       x=p1->geometry().left();
   }
   if(p2.x()>p1->geometry().right())
   {
       x=p1->geometry().right();
   }
    if(2*x-p2.x()<0||2*x-p2.x()>this->width())
        return false;

    try {
        double k=1.0*(this->get->geometry().center().y()-p2.y())/(this->get->geometry().center().x()-(2*x-p2.x()));
        qDebug()<<k;
        y=k*(x-this->get->geometry().center().x())+this->get->geometry().center().y();
        if(y>=p1->geometry().top()&&y<=p1->geometry().bottom())
        {
            return true;
        }
        else {
            return false;
        }

    } catch (...) {
       //qDebug()<<"error";
       return false;

    }

}
double MainWindow::get_random()
{
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    static double i=0;
    double q;
    if(this->time_count<=10)
    {
        q=(qrand()%600/10.0)*(pow(-1,qrand()%2));
        if(i==q)
        {
           q=(qrand()%600/10.0)*(pow(-1,qrand()%2));
        }

    }
    else if (this->time_count<=20) {
        q=(qrand()%200/10.0)*(pow(-1,qrand()%2));
        if(i==q)
        {
            q=(qrand()%200/10.0)*(pow(-1,qrand()%2));
        }

    }
    else if (this->time_count<=30) {
        q=(qrand()%80/10.0)*(pow(-1,qrand()%2));
        if(i==q)
        {
            q=(qrand()%80/10.0)*(pow(-1,qrand()%2));
        }

    }
    else {
         q=(qrand()%50/10.0)*(pow(-1,qrand()%2));

         if(i==q)
         {
             q=(qrand()%30/10.0)*(pow(-1,qrand()%2));
         }
    }
   i=q;
    q=q*(pow(-1,qrand()%2));
    //qDebug()<<q;
    return q;
}
double MainWindow::get_dlc_rate()
{
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    static double i=0;
    double q=0;
    int index=1+this->pslider->value()/10;


    double rate=index*0.08;
    if(this->ylabel->start>=*(this->ylabel->time_count))
    {
        q=qrand()%100/1000.0;
        while (i==q) {

            q=qrand()%100/10000.0;

        }
        i=q;
        rate+=this->ylabel->length_rate*q;
    }
    //qDebug()<<"the rate"<<rate;
    return rate;
}
void MainWindow::reboot()
{
   if(QMessageBox::Ok== QMessageBox::question(this,"Question",QString::fromLocal8Bit("是否重置"), QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {emit rebooot_signals();
  }
}

void MainWindow::select_which()
{
    if(this->pslider->value()%10==0)
    {this->pGreenSwitchControl->setToggle(false);
        this->const_error=0;
    }

}
void MainWindow::get_disturb_point(wx *p1,QPoint p2,int &x,int &y)
{

}
void MainWindow::onToggled(bool bChecked)
{
    qDebug() << "State : " << bChecked;
    if(bChecked)
    {
        int index=1+this->pslider->value()/10;


        double rate=index*0.08;
        this->const_error=rate;

    }
    else {
          this->const_error=0;

    }
}
