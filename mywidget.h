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
    QList<Tower *>  m_towersList; // ����������������Ϣ
    QList<WayPoint *> m_wayPointsList;	// ��paintEvent����Ҫ���л��ƣ��Ǹ����Ƶ�foreach(xxx) xxx.draw(xxx)
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
