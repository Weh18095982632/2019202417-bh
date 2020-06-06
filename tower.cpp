#include "tower.h"
//#include "enemy.h"
//#include "bullet.h"
#include "MyWidget.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(42, 42);

Tower::Tower(QPoint pos, MyWidget *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
	: m_attacking(false)
    , m_attackRange(140)
	, m_damage(10)
	, m_fireRate(1000)
	, m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
	, m_game(game)
	, m_pos(pos)
	, m_sprite(sprite)
{
	m_fireRateTimer = new QTimer(this);
	connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
	delete m_fireRateTimer;
	m_fireRateTimer = NULL;
}

//void Tower::checkEnemyInRange()


void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

//void Tower::attackEnemy()


//void Tower::chooseEnemyForAttack(Enemy *enemy)


//void Tower::shootWeapon()

//void Tower::targetKilled()

