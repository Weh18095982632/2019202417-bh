#ifndef FEARFULENEMY_H
#define FEARFULENEMY_H
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QTimer>

class WayPoint;
class QPainter;
class MyWidget;
class Tower;

class FearfulEnemy
{
public:
    FearfulEnemy(WayPoint *startWayPoint, MyWidget *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));

public slots:
    void doActivate();

public:
    void move();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MyWidget *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;



};

#endif // FEARFULENEMY_H
