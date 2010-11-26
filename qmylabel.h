#ifndef QMYLABEL_H
#define QMYLABEL_H

#include <QLabel>

typedef enum T_Type
{
    Nothing,
    Shark,
    Fish
} type;

class QMyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMyLabel(QWidget *parent = 0);

    void SetType(type p_type);
    type GetType();

signals:

public slots:

private:
    type m_type;

};

#endif // QMYLABEL_H
