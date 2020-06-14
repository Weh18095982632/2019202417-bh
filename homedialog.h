#ifndef HOMEDIALOG_H
#define HOMEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QSoundEffect>
#include "mywidget.h"
#include "mainwindow.h"
#include "screeningdialog.h"

namespace Ui {
class HomeDialog;
}

class HomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HomeDialog(QWidget *parent = nullptr);
    ~HomeDialog();

private:
    Ui::HomeDialog *ui;

public slots:
    void onOpenMusic();
    void onOK();
    void onClose();
    void onMin();
    void onMenu();

    void oncurrentTower1();
    void oncurrentTower2();
    void oncurrentTower3();
    void oncurrentTower4();
    void oncurrentTower5();
    void oncurrentTower6();
    void oncurrentTower7();
    void oncurrentTower8();
    void oncurrentTower9();

public:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public:
    bool mIsPress;
    QPoint StartPos;
public:
    QPushButton *btn_music;
    QPushButton *btn_menu;
    QPushButton *btn_min;
    QPushButton *btn_close;

public:
    MyWidget mywidget;
    ScreeningDialog *dlg;

public:
    bool m_openmusic;
    int m_currentScreen;
};

#endif // HOMEDIALOG_H
