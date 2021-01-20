#ifndef WX_H
#define WX_H

#include <QWidget>
#include<QPushButton>
#include<QPixmap>
#include<QMouseEvent>
#include<QDebug>
#include<QKeyEvent>
#include<QMessageBox>
#include<QWheelEvent>
#include<QMainWindow>
#include<math.h>
#include<QSlider>
#include<QSpinBox>
#include<QFocusEvent>
class wx : public QPushButton
{
    Q_OBJECT
public:
    /*static int choose_id;
    int mouse_press_count;
    bool line_move;*/
        wx(QString pic);
        double add_length;
        double angle;
        bool m_move;
        QPoint m_start;
        QPoint m_btn;
        QPoint p_reflect;
        bool reflect_id;
        bool create_wx;
        bool get_id;
        void mousePressEvent(QMouseEvent *e);
            void mouseMoveEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
         void keyPressEvent(QKeyEvent *event);
        void get_angel(QPushButton *get);
         void wheelEvent(QWheelEvent *event);
        void leaveEvent(QEvent *e);
        void enterEvent(QEvent *e);
         wx *wx_r;
         wx *disturb_building;
         QSlider *pslider;
         QSpinBox *pspinbox;
         bool r_move;
         QPoint r_start;

signals:
         void delete_wx();
        void move_update();


public slots:
};


#endif // WX_H
