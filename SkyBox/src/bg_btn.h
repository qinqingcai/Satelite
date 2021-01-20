#ifndef BG_BTN_H
#define BG_BTN_H

#include <QLabel>
#include<QMouseEvent>
#include<QPainter>
#include<QPen>
#include<QDebug>
#include<QPaintEvent>
#include<QTimer>
#include<QThread>
#include<QTime>
#include<QRadialGradient>
#include<QPointF>
#include<QPoint>
class bg_btn : public QLabel
{
    Q_OBJECT
public:
    bg_btn(int * time_count);
    int * time_count;
    int start;
    int c_x;
    int c_y;
    int s_x;
    int s_y;
    bool is_lagre;
    bool once_pain;
   QPoint  m_start;
   double length_rate;
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void sleep(unsigned int msec);
    void mouseMoveEvent(QMouseEvent *e);
signals:
    void pain_cic();
public slots:
};

#endif // BG_BTN_H
