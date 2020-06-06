#include "startwindow.h"
#include "ui_startwindow.h"

#include <QWidget>
#include <QSound>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //设置标题
    this->setWindowTitle("Tower Defense");

    this->setFixedSize(570,755);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(1);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    this->setObjectName("start_dialog");
    this->setStyleSheet("#start_dialog{border-image:url(:/image/bg1.jpg);}");

    m_openmusic=true;

//    QMediaPlayer* player = new QMediaPlayer;
//    player->setMedia(QUrl("qrc:/config/launch_sound.wav"));//指定源为qrc文件
//    player->setVolume(100);
//    player->play();
    QSound *sound = new QSound("qrc:/config/launch_sound.wav");//获取资源文件中的声音文件
    sound->play();//播放
    sound->setLoops(9999);//设置循环次数

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
    floatWidget->setGeometry(width()-150,10,140,40);

    btn_startGame=new QPushButton(this) ;
    btn_startGame->setObjectName("btn_startGame");
    btn_startGame->setStyleSheet("#btn_startGame{border-image:url(:/image/startgame.png);}");
    btn_startGame->setFixedSize(220,76);
    btn_startGame->setToolTip(QString::fromLocal8Bit("开始游戏"));

    btn_startGame->setGeometry(175,500,220,76);

    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClose()));
    connect(btn_min,SIGNAL(clicked()),this,SLOT(onMin()));
    connect(btn_music,SIGNAL(clicked()),this,SLOT(onOpenMusic()));
    connect(btn_startGame,SIGNAL(clicked()),this,SLOT(onOK()));
}

StartWindow::~StartWindow()
{
    delete ui;
}
void StartWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint EndPos;
    if(e->buttons()==Qt::LeftButton&&mIsPress)
    {
        EndPos = e->globalPos()- StartPos;
        this->move(EndPos);
    }
}

void StartWindow::mousePressEvent(QMouseEvent *e)
{
    mIsPress=true;
    if(e->buttons() == Qt::LeftButton)
    {
        //记录窗口此时的坐标
        StartPos = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void StartWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mIsPress=false;
}
void StartWindow::onOpenMusic()
{

}

void StartWindow::onOK()
{
    homedlg.show();
}
void StartWindow::onClose()
{
    this->close();
}
void StartWindow::onMin()
{
    this->setWindowState(Qt::WindowState::WindowMinimized);
}
