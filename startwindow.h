#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <homedialog.h>
#include <QMouseEvent>
#include <QMediaPlayer>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private:
    Ui::StartWindow *ui;

public slots:
    void onOpenMusic();
    void onOK();
    void onClose();
    void onMin();

public:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public:
    bool mIsPress;
    QPoint StartPos;

public:
    QPushButton *btn_music;
    QPushButton *btn_min;
    QPushButton *btn_close;
    QPushButton *btn_startGame;

public:
    bool m_openmusic;

public:
    HomeDialog homedlg;
};

#endif // STARTWINDOW_H
