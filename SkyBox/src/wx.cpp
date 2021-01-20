#include "wx.h"
 //int wx::choose_id=0;

wx::wx(QString pic)
{
this->reflect_id=false;
    QPixmap pix;
     pix.load(pic);
     this->setFixedSize(pix.width()/3,pix.height()/3);
     this->setStyleSheet("QPushButton{border:0px;}"
                         "QPushButton:hover{border: 2px dotted green;}");

     this->setIcon(pix);
     this->setIconSize(QSize(pix.width()/3,pix.height()/3));
     this->add_length=0;
     this->create_wx=true;
     this->wx_r=NULL;
     this->disturb_building=NULL;
    // this->mouse_press_count=0;
     this->setWindowOpacity(0.5);
     this->pslider=NULL;
     this->pspinbox=NULL;
     this->get_id=true;

}
void wx::mousePressEvent(QMouseEvent *e)
{
if(e->button()==Qt::LeftButton)
{ this->m_move=true;
    this->m_start=e->globalPos();
    this->m_btn=this->frameGeometry().topLeft();
}
if(e->button()==Qt::RightButton&&this->create_wx)
{
    if(this->get_id)
        return;

    this->wx_r=new wx(":/assets/wx_g1.png");
    this->wx_r->setGeometry(this->geometry());
    this->wx_r->setParent(this->parentWidget());
    this->wx_r->show();
    this->create_wx=false;
    connect(this->wx_r,&wx::delete_wx,[=]()
    {
        this->wx_r->close();
        delete this->wx_r;
        this->wx_r=NULL;
        this->create_wx=true;

    });
}

    /*this->mouse_press_count++;
    if(this->mouse_press_count%2==1)
    {
        line_move=true;
        wx::choose_id=1;

    }
    else {
        this->line_move=false;
        wx::choose_id=0;
    }*/

        QPushButton::mousePressEvent(e);

}

void wx::mouseMoveEvent(QMouseEvent *e)
{

        QPoint relativepos=e->globalPos()-this->m_start;
        this->move(this->m_btn+relativepos);


    QPushButton::mouseMoveEvent(e);
}
void wx::mouseReleaseEvent(QMouseEvent *e)
{

    this->m_move=false;
    this->add_length=0;
    QPushButton::mouseReleaseEvent(e);
    /*qDebug()<<this->x()<<"  "<<this->y();
    qDebug()<<this->geometry().width()<<"  "<<this->height();
    qDebug()<<this->geometry().center().rx()<<"  "<<this->geometry().center().ry();
    qDebug()<<this->geometry().topLeft().rx()<<"  "<<this->geometry().topLeft().ry();
    qDebug()<<this->geometry().topRight().rx()<<"  "<<this->geometry().topRight().ry();
    qDebug()<<this->geometry().topRight().x()<<"  "<<this->geometry().topRight().y();
    qDebug()<<this->geometry().bottomLeft().x()<<"  "<<this->geometry().bottomLeft().y();*/
    emit this->move_update();

}
void wx::keyPressEvent(QKeyEvent *event)
{

    if(this->m_move==true)
    {
        if(event->key()==Qt::Key_Delete)
        {
            emit this->delete_wx();
        }
        else {
            QMessageBox::information(this,"Title","if you want to delete,press key of delete");

        }
    }


    QPushButton::keyPressEvent(event);
}
void wx::wheelEvent(QWheelEvent *event)
{
    if(this->get_id)
        return;
    /*if(this->line_move)
    {
        qDebug()<<event->delta();
    }*/
    this->add_length+=event->delta()/120.0;
    if(this->add_length!=0)
    {
       /* QFont font;
        font.setFamily("华文新魏");
         font.setPointSize(15);
        this->setFont(font);*/

        this->setToolTip(QString::fromLocal8Bit("伪距增加了%1米").arg(this->add_length));
    }
    //显示长度增加提示
    if(this->pslider==NULL)
    {
        int nMin=-150;
        int nMax=150;
        int nsinglestep=1;
        pspinbox=new QSpinBox(this->parentWidget());
        pspinbox->setMinimum(nMin);
        pspinbox->setMaximum(nMax);
        pspinbox->setSingleStep(nsinglestep);
        pspinbox->move(this->width()-20,this->height());

        this->pslider=new QSlider(this->parentWidget());
        this->pslider->setOrientation(Qt::Horizontal);
        this->pslider->setMinimum(nMin);
       this->pslider->setMaximum(nMax);
        this->pslider->setSingleStep(nsinglestep);
        this->pslider->setGeometry(QRect(this->width()-2,this->height()-20,5,100));

        connect(pspinbox,SIGNAL(valueChanged(int)),this->pslider,SLOT(setValue(int)));
        connect(this->pslider,SIGNAL(valueChanged(int)),pspinbox,SLOT(setValue(int)));
        this->pslider->setValue(0);
    }
    this->pslider->setValue(this->add_length);
    this->pslider->setGeometry(QRect(this->geometry().x(),this->geometry().bottomLeft().y(),100,20));
    pspinbox->move(this->geometry().x()+20,this->geometry().bottomLeft().y()+20);
    this->pslider->setStyleSheet("QSlider::groove:horizontal {height: 6px;background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71)); } QSlider::handle:horizontal { width: 1px;background: rgb(0, 160, 230);margin: -6px 0px -6px 0px; border-radius: 9px;}");
    this->pslider->show();
    this->pspinbox->show();



   // qDebug()<<this->add_length;
    QPushButton::wheelEvent(event);

}
void wx::get_angel(QPushButton *get)
{

    this->angle=atan2(get->geometry().center().y()-this->geometry().center().y(),get->geometry().center().x()-this->geometry().center().x());
    //qDebug()<<this->angle;
    //emit this->move_update();
}

void wx::leaveEvent(QEvent *e)
{
    if(this->pslider!=NULL)
    {
        this->pslider->hide();
        this->pspinbox->hide();
    }
    QPushButton::leaveEvent(e);

}
void wx::enterEvent(QEvent *e)
{
    if(this->pslider!=NULL)
    {
        this->pslider->show();
        this->pspinbox->show();
    }
    QPushButton::enterEvent(e);
}
