#include "mywidget.h"
#include "waypoint.h"
#include "fearfulenemy.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QDir>

#include "plistreader.h"

static const int TowerCost = 50;
MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    m_waves = 0;
    m_gameWin=false;
    m_currentScreen=1;
    m_gameEnded=false;
    m_playrGold=1000;
    m_playerHp=5;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    m_audioPlayer = new AudioPlayer(this);
    m_audioPlayer->startBGM();

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}
void MyWidget::gameStart()
{
    loadWave();
}
AudioPlayer *MyWidget::audioPlayer() const
{
    return m_audioPlayer;
}
void MyWidget::awardGold(int gold)
{
    m_playrGold += gold;
    //update();
    emit updateGoldTomain(m_playrGold);
}

void MyWidget::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
//      QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
//		QPainter painter(this);
//		painter.setPen(QPen(Qt::red));
//		painter.drawText(rect(), Qt::AlignCenter, text);
        if(m_gameEnded)
            QMessageBox::information(this,QString::fromLocal8Bit("信息"),QString::fromLocal8Bit("You Lost !"));
        if(m_gameWin)
            QMessageBox::information(this,QString::fromLocal8Bit("信息"),QString::fromLocal8Bit("You Lost !"));
        m_gameEnded=false;
        m_gameWin=false;
        return;
    }
    QPainter cachePainter(this);
    if(m_currentScreen==1)
    {
        QImage img=QImage(":/image/map_31.png");
        //QPainter cachePainter(&cachePix);
        cachePainter.drawImage(QRect(0,0,640,480),img);
    }
    else if(m_currentScreen==2)
    {
        QImage img=QImage(":/image/map_32.png");
        //QPainter cachePainter(&cachePix);
        cachePainter.drawImage(QRect(0,0,640,480),img);
    }

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

    foreach (const FearfulEnemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
//	drawPlayerGold(&cachePainter);

    //QPainter painter(this);
    //painter.drawPixmap(0, 0, cachePix);
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            //m_audioPlayer->playSound(TowerPlaceSound);
            //m_playrGold -= TowerCost;
            it->setHasTower();

            QPixmap pixmap;
            if(m_currentTower==1)
                pixmap=QPixmap(":/image/11lower.png");
            else if(m_currentTower==2)
                pixmap=QPixmap(":/image/12lower.png");
            else if(m_currentTower==3)
                pixmap=QPixmap(":/image/13lower.png");
            else if(m_currentTower==4)
                pixmap=QPixmap(":/image/21lower.png");
            else if(m_currentTower==5)
                pixmap=QPixmap(":/image/22lower.png");
            else if(m_currentTower==6)
                pixmap=QPixmap(":/image/23lower.png");
            else if(m_currentTower==7)
                pixmap=QPixmap(":/image/31lower.png");
            else if(m_currentTower==8)
                pixmap=QPixmap(":/image/32lower.png");
            else if(m_currentTower==9)
                pixmap=QPixmap(":/image/33lower.png");
            Tower *tower = new Tower(it->centerPos(), this, pixmap);
            tower->m_type=m_currentTower;
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }

//    QPoint pressPos = event->pos();
//        auto it = m_towerPositionsList.begin();
//        while (it != m_towerPositionsList.end())
//        {
//            if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
//            {
//                it->setHasTower();
//                Tower *tower = new Tower(it->centerPos(), this);
//                m_towersList.push_back(tower);
//                update();
//                break;
//            }

//            ++it;
//        }
}

void MyWidget::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MyWidget::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

bool MyWidget::canBuyTower()
{

    if(m_playrGold >= TowerCost*(m_currentTower%10))
    {
        m_playrGold=m_playrGold-TowerCost*(m_currentTower%10);
        //emit updateGoldTomain(m_playrGold);
        return true;
    }
    else
    {
        //emit updateGoldTextTomain(QString::fromLocal8Bit("金币不足！"));
        return true;
    }
}

void MyWidget::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(40, 75),
        QPoint(75, 280),
        QPoint(115, 125),
        QPoint(200, 120),
        QPoint(200, 195),
        QPoint(200, 280),
        QPoint(240, 355),
        QPoint(320,120),
        QPoint(330, 195),
        QPoint(395, 105),
        QPoint(425, 280),
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void MyWidget::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(580, 450));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint11 = new WayPoint(QPoint(580, 340));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(55, 340));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint3 = new WayPoint(QPoint(55, 260));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(460, 260));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(460, 80));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(380, 80));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(380, 180));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(100, 180));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(100, 55));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(10, 55));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);
}

void MyWidget::loadTowerPositions2()
{
    QPoint pos[] =
    {
        QPoint(80, 320),
        QPoint(115, 225),
        QPoint(155, 75),
        QPoint(240, 120),
        QPoint(240, 195),
        QPoint(240, 280),
        QPoint(355,120),
        QPoint(355, 220),
        QPoint(400, 320),
        QPoint(440, 105),
        QPoint(520, 320),
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void MyWidget::addWayPoints2()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(580, 450));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint11 = new WayPoint(QPoint(580, 300));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(420, 300));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint3 = new WayPoint(QPoint(420, 100));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(220, 100));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(220, 300));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(60, 300));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(60, 460));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

}


void MyWidget::removedEnemy(FearfulEnemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if (m_enemyList.empty())
    {
        ++m_waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
void MyWidget::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}
void MyWidget::getHpDamage(int damage/* = 1*/)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}
void MyWidget::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}
bool MyWidget::loadWave()
{
//    if (m_waves >= 6)
//        return false;
//    WayPoint *startWayPoint = m_wayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
//    int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };
//    for (int i = 0; i < 6; ++i)
//    {
//        FearfulEnemy *enemy = new FearfulEnemy(startWayPoint, this);
//        m_enemyList.push_back(enemy);
//        QTimer::singleShot(100,enemy,SLOT(doActivate()));
//        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
//    }
//    return true;

//    if (m_waves >= m_wavesInfo.size())
//		return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();
        //spawnTime=500;
        FearfulEnemy *enemy;
        if(curWavesInfo.size()-i>1)
             enemy= new FearfulEnemy(startWayPoint, this);
        else
            enemy= new FearfulEnemy(startWayPoint, this,QPixmap(":/image/boss.png"));
        //FearfulEnemy *enemy = new FearfulEnemy(startWayPoint, this);
        m_enemyList.append(enemy);
//        QTimer timer;
//        timer.setSingleShot(true);
//        connect(&timer,SIGNAL(timeout()),enemy,SLOT(doActivate()));

        QTimer::singleShot(spawnTime, enemy,SLOT(doActivate()));
        //QTimer::singleShot(spawnTime,enemy,SLOT(doActivate()));
    }

    return true;
}
void MyWidget::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
void MyWidget::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}
QList<FearfulEnemy *> MyWidget::enemyList() const
{
    return m_enemyList;
}
void MyWidget::updateMap()
{
    foreach (FearfulEnemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();

    update();
}
