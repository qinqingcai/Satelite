#ifndef START_WIDGET_H
#define START_WIDGET_H

#include <QMainWindow>
#include<QGridLayout>
#include<QWidget>
#include<QPushButton>
#include"TWindow.h"
#include"mainwindow.h"
#include"demo_show.h"
#include<QMouseEvent>

class start_widget : public QMainWindow
{
    Q_OBJECT
public:
    QList<QString> mv_path;
    QList<QString> mv_name;

    explicit start_widget(QWidget *parent = nullptr);
    QWidget *main_widget;
    QGridLayout *main_layout;
    QWidget *left_widget;
    QGridLayout *left_layout;
    QWidget *right_widget;
    QGridLayout *right_layout;
    QPushButton *left_close;
    QPushButton *left_visit;
     QPushButton *left_mini;
     TWindow *mv_widget;
      QPushButton *btn_next;
      QPushButton *demo_next;
      MainWindow *app_widget;
      demo_show *demo_w;
      QPoint m_start;
      bool m_move;
       QPoint m_btn;
    void left();
    void right();
    void beauty();
    void mousePressEvent(QMouseEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void add_mv();

public slots:
};

#endif // START_WIDGET_H
