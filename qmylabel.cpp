#include "qmylabel.h"

QMyLabel::QMyLabel(QWidget *parent) :
    QLabel(parent)
{
}


void QMyLabel::SetType(type p_type)
{
    m_type = p_type;
}

type QMyLabel::GetType()
{
    return m_type;
}
