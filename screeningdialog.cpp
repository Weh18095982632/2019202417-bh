#include "screeningdialog.h"
#include "ui_screeningdialog.h"

ScreeningDialog::ScreeningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeningDialog)
{
    ui->setupUi(this);
    m_nowScreen=1;
    //设置图标
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //设置标题
    this->setWindowTitle("Tower Defense");
    this->setFixedSize(500,233);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(1);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setObjectName("screen_dialog");
    this->setStyleSheet("#screen_dialog{border-image:url(:/image/bg3.png);}");

    btn_close=new QPushButton(this) ;
    btn_close->setObjectName("btn_close");
    btn_close->setStyleSheet("#btn_close{border-image:url(:/image/no.png);}");
    btn_close->setFixedSize(100,40);
    btn_close->setToolTip(QString::fromLocal8Bit("关闭"));

    btn_close1=new QPushButton(this) ;
    btn_close1->setObjectName("btn_close1");
    btn_close1->setStyleSheet("#btn_close1{border-image:url(:/image/close_n.png);}#btn_close1:hover{border-image:url(:/image/close_h.png);}");
    btn_close1->setFixedSize(32,32);
    btn_close1->setToolTip(QString::fromLocal8Bit("关闭"));

    btn_ok=new QPushButton(this) ;
    btn_ok->setObjectName("btn_ok");
    btn_ok->setStyleSheet("#btn_ok{border-image:url(:/image/ok.png);}");
    btn_ok->setFixedSize(100,40);
    btn_ok->setToolTip(QString::fromLocal8Bit("确定"));

    btn_screen1=new QPushButton(this) ;
    btn_screen1->setObjectName("btn_screen1");
    btn_screen1->setStyleSheet("#btn_screen1{border-image:url(:/image/level1.png);}");
    btn_screen1->setFixedSize(32,32);
    btn_screen1->setToolTip(QString::fromLocal8Bit("关卡一"));

    btn_screen2=new QPushButton(this) ;
    btn_screen2->setObjectName("btn_screen2");
    btn_screen2->setStyleSheet("#btn_screen2{border-image:url(:/image/level2.png);}");
    btn_screen2->setFixedSize(32,32);
    btn_screen2->setToolTip(QString::fromLocal8Bit("关卡二"));

    btn_screen3=new QPushButton(this) ;
    btn_screen3->setObjectName("btn_screen3");
    btn_screen3->setStyleSheet("#btn_screen3{border-image:url(:/image/unknow.png);}");
    btn_screen3->setFixedSize(32,32);
    btn_screen3->setToolTip(QString::fromLocal8Bit("未知"));

    label1=new QLabel();
    label1->setFixedSize(32,32);
    label1->setObjectName("label1");
    label1->setStyleSheet("#label1{border-image:url(:/image/level.png);}");

    label2=new QLabel();
    label2->setFixedSize(32,32);
    label2->setObjectName("label2");
    label2->setStyleSheet("#label2{border-image:url(:/image/touming.png);}");
    //label2->hide();

    label3=new QLabel();
    label3->setFixedSize(32,32);
    label3->setObjectName("label3");
    label3->setStyleSheet("#label3{border-image:url(:/image/touming.png);}");
    //label3->setVisible(false);
//    btn_screen4=new QPushButton(this) ;
//    btn_screen5=new QPushButton(this) ;
//    btn_screen6=new QPushButton(this) ;
//    btn_screen7=new QPushButton(this) ;

    QVBoxLayout *vb=new QVBoxLayout();

    QHBoxLayout *hb1=new QHBoxLayout();
    QHBoxLayout *hb2=new QHBoxLayout();
    QHBoxLayout *hb3=new QHBoxLayout();
    QHBoxLayout *hb4=new QHBoxLayout();

    hb1->addWidget(btn_close1);
    hb1->setAlignment(Qt::AlignRight);

    hb2->addWidget(btn_screen1);
    hb2->addWidget(btn_screen2);
    hb2->addWidget(btn_screen3);

    hb3->addWidget(label1);
    hb3->addWidget(label2);
    hb3->addWidget(label3);

    hb4->addWidget(btn_ok);
    hb4->addWidget(btn_close);
    vb->addLayout(hb1);
    vb->addSpacerItem(new QSpacerItem(10,30,QSizePolicy::Fixed,QSizePolicy::Fixed));
    vb->addLayout(hb2);
    vb->addLayout(hb3);
    vb->addSpacerItem(new QSpacerItem(10,40,QSizePolicy::Fixed,QSizePolicy::Fixed));
    vb->addLayout(hb4);

    QWidget *wgt=new QWidget(this);
    wgt->setLayout(vb);
    wgt->setGeometry(50,0,400,200);

    connect(btn_screen1,SIGNAL(clicked()),this,SLOT(onScreen1ButtonClicked()));
    connect(btn_screen2,SIGNAL(clicked()),this,SLOT(onScreen2ButtonClicked()));
    connect(btn_screen3,SIGNAL(clicked()),this,SLOT(onScreen3ButtonClicked()));
//    connect(btn_screen4,SIGNAL(clicked()),this,SLOT(onScreen4ButtonClicked()));
//    connect(btn_screen5,SIGNAL(clicked()),this,SLOT(onScreen5ButtonClicked()));
//    connect(btn_screen6,SIGNAL(clicked()),this,SLOT(onScreen6ButtonClicked()));
//    connect(btn_screen7,SIGNAL(clicked()),this,SLOT(onScreen7ButtonClicked()));
    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClose()));
    connect(btn_close1,SIGNAL(clicked()),this,SLOT(onClose()));
    connect(btn_ok,SIGNAL(clicked()),this,SLOT(onOK()));
}

ScreeningDialog::~ScreeningDialog()
{
    delete ui;
}
void ScreeningDialog::mouseMoveEvent(QMouseEvent *e)
{
    QPoint EndPos;
    if(e->buttons()==Qt::LeftButton&&mIsPress)
    {
        EndPos = e->globalPos()- StartPos;
        this->move(EndPos);
    }
}

void ScreeningDialog::mousePressEvent(QMouseEvent *e)
{
    mIsPress=true;
    if(e->buttons() == Qt::LeftButton)
    {
        //记录窗口此时的坐标
        StartPos = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void ScreeningDialog::mouseReleaseEvent(QMouseEvent *e)
{
    mIsPress=false;
}
void ScreeningDialog::onScreen1ButtonClicked()
{
    m_nowScreen=1;
    label1->setStyleSheet("#label1{border-image:url(:/image/level.png);}");
    label2->setStyleSheet("#label2{border-image:url(:/image/touming.png);}");
}
void ScreeningDialog::onScreen2ButtonClicked()
{
    m_nowScreen=2;
    label1->setStyleSheet("#label1{border-image:url(:/image/touming.png);}");
    label2->setStyleSheet("#label2{border-image:url(:/image/level.png);}");
}
void ScreeningDialog::onScreen3ButtonClicked()
{
    QMessageBox::warning(this,QString::fromLocal8Bit( "提示"),QString::fromLocal8Bit("更多功能开发中，敬请期待！"));
}
void ScreeningDialog::onScreen4ButtonClicked()
{}
void ScreeningDialog::onScreen5ButtonClicked()
{}
void ScreeningDialog::onScreen6ButtonClicked()
{}
void ScreeningDialog::onScreen7ButtonClicked()
{}

void ScreeningDialog::onClose()
{
    this->hide();
}
void ScreeningDialog::onOK()
{
    this->hide();
}

void ScreeningDialog::updateScreen()
{
//    if(m_nowScreen==1)
//    {
//        label1->setStyleSheet("#label1{border-image:url(:/image/label1.png);}");
//        label2->setStyleSheet("#label2{border-image:url(:/image/touming.png);}");
//    }
//    else if(m_nowScreen==2)
//    {
//        label1->setStyleSheet("#label1{border-image:url(:/image/touming.png);}");
//        label2->setStyleSheet("#label2{border-image:url(:/image/label2.png);}");
//    }
}
