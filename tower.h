#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QTimer>

#include "bullet.h"
#include "fearfulenemy.h"

class QPainter;
class MyWidget;
class QTimer;


class Tower : QObject
{
	Q_OBJECT
public:
    Tower(QPoint pos, MyWidget *game, const QPixmap &sprite = QPixmap(":/image/12lower.png"));
	~Tower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(FearfulEnemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();

private slots:
    void shootWeapon();

public:
	bool			m_attacking;
	int				m_attackRange;	// 代表塔可以攻击到敌人的距离
	int				m_damage;		// 代表攻击敌人时造成的伤害
	int				m_fireRate;		// 代表再次攻击敌人的时间间隔
	qreal			m_rotationSprite;
    int m_type;

    MyWidget *	m_game;
	QTimer *		m_fireRateTimer;

	const QPoint	m_pos;
	const QPixmap	m_sprite;

    FearfulEnemy *m_chooseEnemy;
	static const QSize ms_fixedSize;
};

#endif // TOWER_H
