#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QMessageBox>
#include <QTimer>

#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "fearfulenemy.h"
#include "audioplayer.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    
signals:
    void updateGoldTomain(int gold);
    void updateGoldTextTomain(QString text);

public slots:
    void updateMap();
    void gameStart();

public:
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *>  m_towersList; // 用来管理攻击塔的信息
    QList<WayPoint *> m_wayPointsList;	// 在paintEvent中需要进行绘制，那个类似的foreach(xxx) xxx.draw(xxx)
    QList<FearfulEnemy *> m_enemyList;
    QList<QVariant>	m_wavesInfo;
    QList<Bullet *>			m_bulletList;
    int m_waves;
    bool m_gameWin;
    int m_currentTower;
    int m_currentScreen;

    int						m_playerHp;
    AudioPlayer *			m_audioPlayer;
    bool					m_gameEnded;
    int						m_playrGold;

public:
    AudioPlayer* audioPlayer() const;
    void awardGold(int gold);

    void loadTowerPositions2();
    void addWayPoints2();
    void loadTowerPositions();
    bool canBuyTower() ;
    void addWayPoints();
    void getHpDamage(int damage = 1);
    void removedEnemy(FearfulEnemy *enemy);
    void removedBullet(Bullet *bullet);
    bool loadWave();

    void doGameOver();
    void preLoadWavesInfo();

    void addBullet(Bullet *bullet);
    QList<FearfulEnemy *> enemyList() const;

    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
};

#endif // MYWIDGET_H
