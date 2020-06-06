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

    btn_close=new QPushButton(this) ;
    btn_screen1=new QPushButton(this) ;
    btn_screen2=new QPushButton(this) ;
    btn_screen3=new QPushButton(this) ;
    btn_screen4=new QPushButton(this) ;
    btn_screen5=new QPushButton(this) ;
    btn_screen6=new QPushButton(this) ;
    btn_screen7=new QPushButton(this) ;

    btn_ok=new QPushButton(this) ;

    connect(btn_screen1,SIGNAL(clicked()),this,SLOT(onScreen1ButtonClicked()));
    connect(btn_screen2,SIGNAL(clicked()),this,SLOT(onScreen2ButtonClicked()));
    connect(btn_screen3,SIGNAL(clicked()),this,SLOT(onScreen3ButtonClicked()));
    connect(btn_screen4,SIGNAL(clicked()),this,SLOT(onScreen4ButtonClicked()));
    connect(btn_screen5,SIGNAL(clicked()),this,SLOT(onScreen5ButtonClicked()));
    connect(btn_screen6,SIGNAL(clicked()),this,SLOT(onScreen6ButtonClicked()));
    connect(btn_screen7,SIGNAL(clicked()),this,SLOT(onScreen7ButtonClicked()));
    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClose()));
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

}
void ScreeningDialog::onScreen2ButtonClicked()
{}
void ScreeningDialog::onScreen3ButtonClicked()
{}
void ScreeningDialog::onScreen4ButtonClicked()
{}
void ScreeningDialog::onScreen5ButtonClicked()
{}
void ScreeningDialog::onScreen6ButtonClicked()
{}
void ScreeningDialog::onScreen7ButtonClicked()
{}

void ScreeningDialog::onClose()
{}
void ScreeningDialog::onOK()
{}
