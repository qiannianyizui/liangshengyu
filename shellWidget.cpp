#include <QTextBlock>
#include <QDebug>
#include <QScrollBar>
#include <QMouseEvent>
#include <QKeyEvent>
#include "shellWidget.h"

shellWidget::shellWidget(QWidget *parent)
: QPlainTextEdit(parent),
  m_iCursorPosition(0),
  m_bEchoFlag(false)
{

}

void shellWidget::resizeEvent(QResizeEvent *event)
{

}

void shellWidget::mousePressEvent(QMouseEvent *event)
{

}


void shellWidget::keyPressEvent(QKeyEvent *event)
{
    static QString cmd = tr("");
    if( (event->modifiers() == Qt::ControlModifier) && (event->key()) == Qt::Key_C )
    {
        this->insertPlainText("\n");
        inputFinished("\n");
        m_iCursorPosition = 0;
        m_bEchoFlag = true;
        cmd.clear();
        return;
    }

    switch(event->key())
    {
    case Qt::Key_Return:
        cmd = cmd + "\n";
        this->insertPlainText("\n");
        inputFinished(cmd);
        cmd.clear();
        m_iCursorPosition = 0;
        m_bEchoFlag = true;
        return;
        break;
    case Qt::Key_Left:
        if( m_iCursorPosition > 0 )
        {
            m_iCursorPosition = m_iCursorPosition - 1;
            this->moveCursor(QTextCursor::PreviousCharacter);
        }
        return;
        break;
    case Qt::Key_Right:
        if( m_iCursorPosition < cmd.length())
        {
            m_iCursorPosition = m_iCursorPosition + 1;
            this->moveCursor(QTextCursor::NextCharacter);
        }
        return;
        break;
    case Qt::Key_Up:
        //inputFinished());
        return;
        break;
    case Qt::Key_Down:
        return;
        break;
    case Qt::Key_Backspace:
        if( m_iCursorPosition <= 0 )
        {
            return;
        }
        cmd = cmd.remove(m_iCursorPosition - 1, 1);
        m_iCursorPosition = m_iCursorPosition - 1;
        break;
    case Qt::Key_Control:
        return;
        break;
    case Qt::Key_Tab:
        cmd = cmd + "\t";
        inputFinished(cmd);
        cmd.clear();
        m_iCursorPosition = 0;
        m_bEchoFlag = true;
        return;
        break;
    case Qt::Key_Space:
        cmd = cmd + " ";
        m_iCursorPosition = m_iCursorPosition + 1;
        break;
    default:
        cmd = cmd + event->text();
        m_iCursorPosition = m_iCursorPosition + 1;
        break;
    }
    QPlainTextEdit::keyPressEvent(event);
}

void shellWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void shellWidget::GoToBottom()
{
    QScrollBar *bar = this->verticalScrollBar();
    bar->setSliderPosition(bar->maximum());
}

void shellWidget::SwitchNewLine(QString data)
{
    if( true == m_bEchoFlag )
    {
        m_bEchoFlag = 0;
        return;
    }
    int count = data.count("\n");

    for (int i = 0; i < count; i++)
    {
        QString lineText = data.section("\n", i, i);
        this->insertPlainText(lineText + "\n");
    }
    this->insertPlainText(data.section("\n", count, count));
    GoToBottom();
}
