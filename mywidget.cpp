#include "mywidget.h"
#include "waypoint.h"
#include "fearfulenemy.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    loadTowerPositions();
    addWayPoints();

    m_waves = 0;
    m_gameWin=false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

}

void MyWidget::paintEvent(QPaintEvent *)
{
//	if (m_gameEnded || m_gameWin)
//	{
//		QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
//		QPainter painter(this);
//		painter.setPen(QPen(Qt::red));
//		painter.drawText(rect(), Qt::AlignCenter, text);
//		return;
//	}

    QPixmap cachePix(":/image/map_31.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

//    foreach (const Enemy *enemy, m_enemyList)
//        enemy->draw(&cachePainter);

//	foreach (const Bullet *bullet, m_bulletList)
//		bullet->draw(&cachePainter);

//	drawWave(&cachePainter);
//	drawHP(&cachePainter);
//	drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
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

            Tower *tower = new Tower(it->centerPos(), this);
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

bool MyWidget::canBuyTower() const
{
    return true;
}

void MyWidget::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(80, 120),
        QPoint(180, 200),
        QPoint(160, 460),
        QPoint(400, 220),
        QPoint(400, 460),
        QPoint(400, 590),
        QPoint(500, 220),
        QPoint(470, 460),
        QPoint(670, 460),
        QPoint(585, 325),
        QPoint(645,325),
        QPoint(830, 565),
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void MyWidget::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(930, 745));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint11 = new WayPoint(QPoint(930, 545));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(85, 545));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint3 = new WayPoint(QPoint(85, 420));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(750, 420));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(750, 80));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(590, 80));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(590, 280));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(170, 280));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(170, 100));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(10, 100));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);
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


bool MyWidget::loadWave()
{
    if (m_waves >= 6)
        return false;
    WayPoint *startWayPoint = m_wayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };
    for (int i = 0; i < 6; ++i)
    {
        FearfulEnemy *enemy = new FearfulEnemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        //QTimer::singleShot(100,enemy,SLOT(doActivate()));
        //QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}


void MyWidget::updateMap()
{
//    foreach (Enemy *enemy, m_enemyList)
//        enemy->move();
//    update();
}
