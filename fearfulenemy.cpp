#include "fearfulenemy.h"
#include "waypoint.h"
#include "utility.h"
#include "mywidget.h"

#include <QVector2D>

static const int Health_Bar_Width = 20;

const QSize FearfulEnemy::ms_fixedSize(52, 52);

FearfulEnemy::FearfulEnemy(WayPoint *startWayPoint, MyWidget *game, const QPixmap &sprite)
    : m_sprite(sprite)
{
    m_active=false;
    m_maxHp=40;
    m_currentHp=40;
    m_walkingSpeed=1.0;
    m_rotationSprite=0.0;
    m_pos=startWayPoint->pos();
    m_destinationWayPoint=startWayPoint->nextWayPoint();
    m_game=game;
    //m_sprite=sprite;
}
FearfulEnemy::~FearfulEnemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}
void FearfulEnemy::doActivate()
{
    m_active = true;
}

void FearfulEnemy::move()
{
    //if (!m_active)
    //   return;


    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // ���˵ִ���һ������
        if (m_destinationWayPoint->nextWayPoint())
        {
            // ������һ������
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // ��ʾ�������
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // ����ǰ�������·��
    // Ŀ�꺽�������
    QPoint targetPoint = m_destinationWayPoint->pos();
    // δ���޸������������ƶ�״̬,�ӿ�,����,m_walkingSpeed�ǻ�׼ֵ

    // ������׼��
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;

    // ȷ������ѡ����
    // Ĭ��ͼƬ����,��Ҫ����180��ת��
    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void FearfulEnemy::draw(QPainter *painter) const
{
    //if (!m_active)
    //    return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // ����Ѫ��
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // ����ƫת����,������+ƫ��=����
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // ���Ƶ���
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void FearfulEnemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // ֪ͨgame,�˵����Ѿ�����
    m_game->removedEnemy(this);
}

void FearfulEnemy::getDamage(int damage)
{
    m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;

    // ����,��Ҫ�Ƴ�
    if (m_currentHp <= 0)
    {
        m_game->audioPlayer()->playSound(EnemyDestorySound);
        m_game->awardGold(200);
        getRemoved();
    }
}

void FearfulEnemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// ���������Ѿ������˹�����Χ
void FearfulEnemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint FearfulEnemy::pos() const
{
    return m_pos;
}

