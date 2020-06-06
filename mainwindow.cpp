#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1024,720);

    //����ͼ��
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //���ñ���
    this->setWindowTitle("Tower Defense");

    this->setContentsMargins(0,0,0,0);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout->setMargin(0);

    QHBoxLayout *hl=new QHBoxLayout(this);
    hl->addWidget(&mywidget);
    ui->mainwidget->setLayout(hl);

}

MainWindow::~MainWindow()
{
    delete ui;
}
