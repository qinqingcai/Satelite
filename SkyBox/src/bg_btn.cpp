#include "bg_btn.h"

bg_btn::bg_btn(int * time_count)
{
    this->time_count=time_count;
    this->is_lagre=false;
    this->once_pain=false;
this->start=-100;

}
void bg_btn::mousePressEvent(QMouseEvent *e)
{
    this->is_lagre=false;
    this->once_pain=true;
    this->m_start=e->globalPos();
    /*QPainter painter(this->parentWidget());
     QPen pen(Qt::red,2);
     painter.setPen(pen);
     int i=0;
     while(i<=100)
     {i++;

     painter.drawEllipse(e->x(),e->y(),10,10);}*/
    this->c_x=e->x();
    this->c_y=e->y();
    //qDebug()<<"--"<<this->c_x<<"  "<<this->c_y;
    emit this->pain_cic();
     QLabel::mousePressEvent(e);

}
void bg_btn::mouseReleaseEvent(QMouseEvent *e)
{
    this->is_lagre=true;
    this->once_pain=true;
this->start=(*time_count)+15;
    QLabel::mouseReleaseEvent(e);
}
void bg_btn::mouseMoveEvent(QMouseEvent *e)
{
    this->s_x=e->x();
    this->s_y=e->y();
   QPoint relativepos=e->globalPos()-this->m_start;
    this->length_rate=sqrt(1.0*(pow(relativepos.x(),2)+pow(relativepos.y(),2))/(pow(this->width(),2)+pow(this->height(),2)));


}
void bg_btn::paintEvent(QPaintEvent *e)
{
     //QLabel::paintEvent(e);
    QPainter painter(this);
         QPen pen(Qt::red,0.5);
         painter.setPen(pen);

         QLinearGradient linearGradient(QPointF(40, 190),QPointF(70, 190));
             //插入颜色
             linearGradient.setColorAt(0, Qt::yellow);
             linearGradient.setColorAt(0.25, Qt::red);
             linearGradient.setColorAt(1, Qt::red);
             painter.setBrush(linearGradient);
             painter.drawRect(this->geometry());


if(!this->is_lagre)
{
   painter.drawEllipse(c_x-10,c_y-10,10,10);
}
else {
    if(this->start>=*time_count)
{

        QRadialGradient radialGradient(QPointF(c_x, c_y),100,QPointF(s_x,s_y));
        if(length_rate<0.1)
            length_rate=0.1;
        radialGradient.setColorAt(0, QColor(225, 150*(1-this->length_rate), 150*(1-this->length_rate), 150));
        radialGradient.setColorAt(1, QColor(250, 200, 200, 80));
        painter.setBrush(radialGradient);
        painter.drawEllipse(QPointF(c_x, c_y), 1500,1500);

}





}


this->setWindowOpacity(0.1);



}
void bg_btn::sleep(unsigned int msec)
{
    QTime reach=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reach);
}
