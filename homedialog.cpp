#include "homedialog.h"
#include "ui_homedialog.h"


HomeDialog::HomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeDialog)
{
    ui->setupUi(this);
    m_openmusic=true;

    this->setFixedSize(1335,814);

    //设置图标
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //设置标题
    this->setWindowTitle("Tower Defense");

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(1);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    this->setObjectName("home_dialog");
    this->setStyleSheet("#home_dialog{color: rgb(255,255,255);}");
    //border-image:url(:/image/bg2.jpg);

    this->setContentsMargins(0,0,0,0);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout->setMargin(0);

    QHBoxLayout *hl=new QHBoxLayout(this);
    hl->addWidget(&mywidget);
    ui->mainwidget->setLayout(hl);

    btn_music=new QPushButton(this) ;
    btn_music->setObjectName("btn_music");
    btn_music->setStyleSheet("#btn_music{border-image:url(:/image/music_h.png);}");
    btn_music->setFixedSize(32,32);
    btn_music->setToolTip(QString::fromLocal8Bit("音效"));

    btn_min=new QPushButton(this) ;
    btn_min->setObjectName("btn_min");
    btn_min->setStyleSheet("#btn_min{border-image:url(:/image/min_n.png);}#btn_min:hover{border-image:url(:/image/min_h.png);}");
    btn_min->setFixedSize(40,40);
    btn_min->setToolTip(QString::fromLocal8Bit("最小化"));

    btn_close=new QPushButton(this) ;
    btn_close->setObjectName("btn_close");
    btn_close->setStyleSheet("#btn_close{border-image:url(:/image/close_n.png);}#btn_close:hover{border-image:url(:/image/close_h.png);}");
    btn_close->setFixedSize(40,40);
    btn_close->setToolTip(QString::fromLocal8Bit("关闭"));

    QHBoxLayout *hb=new QHBoxLayout(this);
    hb->addWidget(btn_music,0,Qt::AlignHCenter|Qt::AlignVCenter);
    hb->addWidget(btn_min,0,Qt::AlignHCenter|Qt::AlignVCenter);
    hb->addWidget(btn_close,0,Qt::AlignHCenter|Qt::AlignVCenter);
    QWidget *floatWidget=new QWidget(this);
    floatWidget->setLayout(hb);
    //floatRight->setGeometry(width()-530,60,530,height()-110);
    floatWidget->setGeometry(width()-150,0,140,40);


    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClose()));
    connect(btn_min,SIGNAL(clicked()),this,SLOT(onMin()));
    connect(btn_music,SIGNAL(clicked()),this,SLOT(onOpenMusic()));

}

HomeDialog::~HomeDialog()
{
    delete ui;
}
void HomeDialog::mouseMoveEvent(QMouseEvent *e)
{
    QPoint EndPos;
    if(e->buttons()==Qt::LeftButton&&mIsPress)
    {
        EndPos = e->globalPos()- StartPos;
        this->move(EndPos);
    }
}

void HomeDialog::mousePressEvent(QMouseEvent *e)
{
    mIsPress=true;
    if(e->buttons() == Qt::LeftButton)
    {
        //记录窗口此时的坐标
        StartPos = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void HomeDialog::mouseReleaseEvent(QMouseEvent *e)
{
    mIsPress=false;
}

void HomeDialog::onOpenMusic()
{

}
void HomeDialog::onOK()
{
    //w.show();
}
void HomeDialog::onClose()
{
    this->close();
}
void HomeDialog::onMin()
{
    this->setWindowState(Qt::WindowState::WindowMinimized);
}
