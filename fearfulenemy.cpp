#include "fearfulenemy.h"
#include "waypoint.h"


FearfulEnemy::FearfulEnemy(WayPoint *startWayPoint, MyWidget *game, const QPixmap &sprite)
{
//    m_active=false;
//    m_maxHp=40;
//    m_currentHp=40;
//    m_walkingSpeed=1.0;
//    m_rotationSprite=0.0;
//    m_pos=startWayPoint->pos();
//    m_destinationWayPoint=startWayPoint->nextWayPoint();
//    m_game=game;
//    m_sprite=sprite;
}

void FearfulEnemy::doActivate()
{
    m_active = true;
}

void FearfulEnemy::move()
{
//    if (!m_active)
//        return;

//    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
//    {
//        // ���˵ִ���һ������
//        if (m_destinationWayPoint->nextWayPoint())
//        {
//            // ������һ������
//            m_pos = m_destinationWayPoint->pos();
//            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
//        }
//        else
//        {
//            // ��ʾ�������
//            m_game->getHpDamage();
//            m_game->removedEnemy(this);
//            return;
//        }
//    }

//    // ����ǰ�������·��
//    // Ŀ�꺽�������
//    QPoint targetPoint = m_destinationWayPoint->pos();
//    // δ���޸������������ƶ�״̬,�ӿ�,����,m_walkingSpeed�ǻ�׼ֵ

//    // ������׼��
//    qreal movementSpeed = m_walkingSpeed;
//    QVector2D normalized(targetPoint - m_pos);
//    normalized.normalize();
//    m_pos = m_pos + normalized.toPoint() * movementSpeed;

//    // ȷ������ѡ����
//    // Ĭ��ͼƬ����,��Ҫ����180��ת��
//    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}
