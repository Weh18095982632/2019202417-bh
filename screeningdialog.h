#ifndef SCREENINGDIALOG_H
#define SCREENINGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>

namespace Ui {
class ScreeningDialog;
}

class ScreeningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeningDialog(QWidget *parent = nullptr);
    ~ScreeningDialog();

private:
    Ui::ScreeningDialog *ui;

public slots:
    void onScreen1ButtonClicked();
    void onScreen2ButtonClicked();
    void onScreen3ButtonClicked();
    void onScreen4ButtonClicked();
    void onScreen5ButtonClicked();
    void onScreen6ButtonClicked();
    void onScreen7ButtonClicked();

    void onClose();
    void onOK();

public:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public:
    bool mIsPress;
    QPoint StartPos;
public:
    QPushButton *btn_close;
    QPushButton *btn_screen1;
    QPushButton *btn_screen2;
    QPushButton *btn_screen3;
    QPushButton *btn_screen4;
    QPushButton *btn_screen5;
    QPushButton *btn_screen6;
    QPushButton *btn_screen7;

    QPushButton *btn_ok;

public:
    bool m_nowScreen;
    QPixmap m_nowImg;

};

#endif // SCREENINGDIALOG_H
