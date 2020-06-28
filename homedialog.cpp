#include "homedialog.h"
#include "ui_homedialog.h"


HomeDialog::HomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeDialog)
{
    ui->setupUi(this);
    m_openmusic=true;
    mywidget.m_currentTower=1;

    this->setFixedSize(896,550);

    //设置图标
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //设置标题
    this->setWindowTitle("Tower Defense");

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(1);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    this->setObjectName("home_dialog");
    this->setStyleSheet("#home_dialog{background-color: rgb(104, 104, 104);}");
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

    btn_menu=new QPushButton(this) ;
    btn_menu->setObjectName("btn_menu");
    btn_menu->setStyleSheet("#btn_menu{border-image:url(:/image/menu_n.png);}#btn_menu:hover{border-image:url(:/image/menu_h.png);}");
    btn_menu->setFixedSize(32,32);
    btn_menu->setToolTip(QString::fromLocal8Bit("关卡"));

    btn_min=new QPushButton(this) ;
    btn_min->setObjectName("btn_min");
    btn_min->setStyleSheet("#btn_min{border-image:url(:/image/min_n.png);}#btn_min:hover{border-image:url(:/image/min_h.png);}");
    btn_min->setFixedSize(32,32);
    btn_min->setToolTip(QString::fromLocal8Bit("最小化"));

    btn_close=new QPushButton(this) ;
    btn_close->setObjectName("btn_close");
    btn_close->setStyleSheet("#btn_close{border-image:url(:/image/close_n.png);}#btn_close:hover{border-image:url(:/image/close_h.png);}");
    btn_close->setFixedSize(32,32);
    btn_close->setToolTip(QString::fromLocal8Bit("关闭"));

    QHBoxLayout *hb=new QHBoxLayout(this);
    hb->addWidget(btn_music,0,Qt::AlignHCenter|Qt::AlignVCenter);
    hb->addWidget(btn_menu,0,Qt::AlignHCenter|Qt::AlignVCenter);
    hb->addWidget(btn_min,0,Qt::AlignHCenter|Qt::AlignVCenter);
    hb->addWidget(btn_close,0,Qt::AlignHCenter|Qt::AlignVCenter);
    QWidget *floatWidget=new QWidget(this);
    floatWidget->setLayout(hb);
    //floatRight->setGeometry(width()-530,60,530,height()-110);
    floatWidget->setGeometry(width()-200,0,190,40);


    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClose()));
    connect(btn_menu,SIGNAL(clicked()),this,SLOT(onMenu()));
    connect(btn_min,SIGNAL(clicked()),this,SLOT(onMin()));
    connect(btn_music,SIGNAL(clicked()),this,SLOT(onOpenMusic()));

    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(oncurrentTower1()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(oncurrentTower2()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(oncurrentTower3()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(oncurrentTower4()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(oncurrentTower5()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(oncurrentTower6()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(oncurrentTower7()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(oncurrentTower8()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(oncurrentTower9()));

    dlg=new ScreeningDialog(this);
    dlg->hide();

    connect(&mywidget,SIGNAL(updateGoldTomain(int)),this,SLOT(updategold(int)));
}

HomeDialog::~HomeDialog()
{
    delete ui;
    delete dlg;
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
    if(mywidget.audioPlayer()->openmusic)
    {
        mywidget.audioPlayer()->m_backgroundMusic->stop();
        btn_music->setStyleSheet("#btn_music{border-image:url(:/image/music_n.png);}");
    }
    else
    {
        mywidget.audioPlayer()->m_backgroundMusic->play();
        btn_music->setStyleSheet("#btn_music{border-image:url(:/image/music_h.png);}");
    }
    mywidget.audioPlayer()->openmusic=!mywidget.audioPlayer()->openmusic;
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
void HomeDialog::onMenu()
{
    dlg->m_nowScreen=mywidget.m_currentScreen;
    dlg->updateScreen();
    dlg->show();

    connect(dlg,SIGNAL(updateScreen()),this,SLOT(updateScreenToMyWidget()));

}

void HomeDialog::updateScreenToMyWidget()
{
    m_currentScreen=dlg->m_nowScreen;
    mywidget.m_currentScreen=m_currentScreen;

    if(m_currentScreen==1)
    {
        mywidget.m_enemyList.clear();
        mywidget.m_wayPointsList.clear();
        mywidget.m_towerPositionsList.clear();
        mywidget.m_towersList.clear();
        mywidget.loadTowerPositions();
        mywidget.addWayPoints();
        mywidget.loadWave();
    }
    else if(m_currentScreen==2)
    {
        mywidget.m_enemyList.clear();
        mywidget.m_wayPointsList.clear();
        mywidget.m_towerPositionsList.clear();
        mywidget.m_towersList.clear();
        mywidget.loadTowerPositions2();
        mywidget.addWayPoints2();
        mywidget.loadWave();
    }

    mywidget.repaint();
}

void HomeDialog::updategold(int gold)
{
    ui->label_resource->setText(QString::number(gold));
}

void HomeDialog::updategoldText(QString text)
{
    QMessageBox::warning(this,QString::fromLocal8Bit("警告"),text);
}
void HomeDialog::oncurrentTower1()
{
    mywidget.m_currentTower=1;
    ui->label_introduce->setText(QString::fromLocal8Bit("一级单体攻击防御塔\n攻击力：15\n射  程：200"));
}
void HomeDialog::oncurrentTower2()
{
    mywidget.m_currentTower=2;
    ui->label_introduce->setText(QString::fromLocal8Bit("二级单体攻击防御塔\n攻击力：20\n射  程：200"));
}
void HomeDialog::oncurrentTower3()
{
    mywidget.m_currentTower=3;
    ui->label_introduce->setText(QString::fromLocal8Bit("三级单体攻击防御塔\n攻击力：30\n射  程：200"));
}
void HomeDialog::oncurrentTower4()
{
    mywidget.m_currentTower=4;
    ui->label_introduce->setText(QString::fromLocal8Bit("一级冰霜防御塔\n攻击力：10\n射  程：200"));
}
void HomeDialog::oncurrentTower5()
{
    mywidget.m_currentTower=5;
    ui->label_introduce->setText(QString::fromLocal8Bit("二级冰霜防御塔\n攻击力：15\n射  程：200"));
}
void HomeDialog::oncurrentTower6()
{
    mywidget.m_currentTower=6;
    ui->label_introduce->setText(QString::fromLocal8Bit("三级冰霜防御塔\n攻击力：25\n射  程：200"));
}
void HomeDialog::oncurrentTower7()
{
    mywidget.m_currentTower=7;
    ui->label_introduce->setText(QString::fromLocal8Bit("一级群体攻击防御塔\n攻击力：10\n射  程：200"));
}
void HomeDialog::oncurrentTower8()
{
    mywidget.m_currentTower=8;
    ui->label_introduce->setText(QString::fromLocal8Bit("二级群体攻击防御塔\n攻击力：15\n射  程：200"));
}
void HomeDialog::oncurrentTower9()
{
    mywidget.m_currentTower=9;
    ui->label_introduce->setText(QString::fromLocal8Bit("三级群体攻击防御塔\n攻击力：25\n射  程：200"));
}
