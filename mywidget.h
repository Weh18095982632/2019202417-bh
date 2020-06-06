#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QTimer>


#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "fearfulenemy.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    
signals:


public slots:
    void updateMap();

public:
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *>  m_towersList; // 用来管理攻击塔的信息
    QList<WayPoint *> m_wayPointsList;	// 在paintEvent中需要进行绘制，那个类似的foreach(xxx) xxx.draw(xxx)
    QList<FearfulEnemy *> m_enemyList;
    int m_waves;
    bool m_gameWin;

public:
    void loadTowerPositions();
    bool canBuyTower()  const;
    void addWayPoints();
    void removedEnemy(FearfulEnemy *enemy);
    bool loadWave();


};

#endif // MYWIDGET_H
