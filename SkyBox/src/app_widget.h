#ifndef APP_WIDGET_H
#define APP_WIDGET_H

#include <QMainWindow>
#include<QPixmap>
#include<QPainter>
#include"wx.h"
#include<QDebug>
#include<QList>
#include<ctime>
#include<QMenuBar>
#include<QAction>
#include<QMenu>
#include<QPen>
#include"Matrix.h"
#include"math.h"
#include<QMessageBox>
#include<QLabel>
#include<QFont>
#include<QRadioButton>
#include<QButtonGroup>
#include<QMessageBox>
#include<QToolBar>
#include<QToolButton>
#include<QResizeEvent>
#include<QButtonGroup>
#include<QTimer>
#include<QSlider>
#include<QSpinBox>
#include<QTime>
#include"bg_btn.h"
class app_widget : public QMainWindow
{
    Q_OBJECT
public:
    explicit app_widget(QWidget *parent = nullptr);
    double const_error;
    QList<wx *> wx_list;
    QList<bool > wx_see_list;
    QList<wx *> building_list;
    wx *get;
    wx *get_r;
    int cir_x;
    int cir_y;
    bool ispain;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
    QLabel *label_see;
    QLabel *label_high;
    QLabel *label_low;
    QLabel *label_dqc;
    QLabel *label_dlc;
    QLabel *label_tk;
    bg_btn * ylabel;
    QSlider *pslider;
    QSpinBox *pspinbox;
    QRadioButton *choose_error;
    QRadioButton *choose_nothing;
    QToolBar *toolbar;
    QLabel *o_label;
    QLabel *x_label;
    QLabel *y_label;

    static int const REBOOT_CODE;
    int time_count;
    double pic_count;

    void paintEvent(QPaintEvent *e);
    void position_get();
    bool disturb(QPoint p1,QPoint p2,QPoint m,int length,int width);
    void enable_see_wx();
    bool get_reflect(wx *p1,QPoint p2,int &x,int &y);
    double get_dlc_rate();
        double get_random();
        /*Matrix get_line_deal(Matrix Z,Matrix X,double x0,double y0);
        double get_rms(Matrix v);*/

public slots:
    void timerUpDate();
    void reboot();
    void select_which();


public slots:
};

#endif // APP_WIDGET_H
