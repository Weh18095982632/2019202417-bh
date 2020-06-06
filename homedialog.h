#ifndef HOMEDIALOG_H
#define HOMEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMouseEvent>
#include "mywidget.h"
#include "mainwindow.h"

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

public:
    MyWidget mywidget;

public:
    bool m_openmusic;

};

#endif // HOMEDIALOG_H
