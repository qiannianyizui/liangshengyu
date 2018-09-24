#include <QMouseEvent>
#include "comboBox.h"

comboBox::comboBox(QWidget *parent) : QComboBox(parent)
{

}

void comboBox::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->buttons())
    {
        emit clicked();
    }
}
