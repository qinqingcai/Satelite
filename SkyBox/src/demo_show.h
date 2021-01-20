#ifndef DEMO_SHOW_H
#define DEMO_SHOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QPushButton>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QBoxLayout>
#include<QGridLayout>
#include<QMouseEvent>
#include<QButtonGroup>
#include<QHBoxLayout>
#include<QDebug>
class demo_show : public QMainWindow
{
    Q_OBJECT
public:
    explicit demo_show(QWidget *parent = nullptr);
    QList<QString> mv_path;
    QList<QString> mv_name;
    QWidget *main_widget;
    QGridLayout *main_layout;
    QWidget *left_widget;
    QGridLayout *left_layout;
    QWidget *right_widget;
    QGridLayout *right_layout;
    QPushButton *left_close;
    QPushButton *left_visit;
     QPushButton *left_mini;

      QPushButton *btn_next;
      QPushButton *demo_next;

    void left();
    void right();
    void beauty();

    //播放器
    QWidget *mwidget;
   QMediaPlayer *player;
   QVideoWidget *videoWidget;
   QMediaPlaylist *Playlist;
   QString m_fileName;
   QMediaPlayer::State  m_playerState;
    QWidget *b_widget;
   QPushButton *stopBtn;
   QPushButton *fullScrBtn;
   QMediaPlayer *mVideoPlayer ,*mSurfacePlayer;
   QVideoWidget * mVideoWidget;
    void on_btn_select_video_clicked();

    QPushButton *btn;
    QPoint m_start;
    bool m_move;
     QPoint m_btn;
     void mousePressEvent(QMouseEvent *e);
         void mouseMoveEvent(QMouseEvent *e);
     void mouseReleaseEvent(QMouseEvent *e);

   void stopVideo();
   void fullScr();
   void setupUI();
   QButtonGroup *buttonGroup;
   void add_mv();
     QString fileName;
private slots:
   void on_changeButtonGroup(int);

signals:
   void close_signal();

public slots:
};

#endif // DEMO_SHOW_H
