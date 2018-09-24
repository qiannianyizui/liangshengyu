#include <QKeyEvent>
#include <QDebug>
#include "IOEdit.h"

IOEdit::IOEdit(QWidget *parent) : QLineEdit(parent)
{

}

void IOEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Tab:
        emit inputControlChar(Qt::Key_Tab);
        break;
    case Qt::Key_Return:
        emit inputControlChar(Qt::Key_Return);
        break;
    default:
        break;
    }
    QLineEdit::keyPressEvent(event);
}
