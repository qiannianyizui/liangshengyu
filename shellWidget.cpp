#include <QTextBlock>
#include <QDebug>
#include <QScrollBar>
#include <QMouseEvent>
#include <QKeyEvent>
#include "IOEdit.h"
#include "shellWidget.h"

shellWidget::shellWidget(QWidget *parent) :
    QPlainTextEdit(parent)
{
    this->setReadOnly(true);

    QFont font = this->font();
    font.setPointSize(font.pointSize()+2);
    this->setFont(font);
    this->appendPlainText("#");

    m_cInputEdit = new IOEdit(this->viewport());
   // m_cInputEdit->setStyleSheet("border-style:none; background-color:transparent;");
    connect(m_cInputEdit, SIGNAL(inputControlChar(enum Qt::Key)), this, SLOT(GetEditCmd(enum Qt::Key)));

    connect(m_cInputEdit,SIGNAL(textEdited(QString)), this, SLOT(GotoBottom()));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(GotoBottom()));

    m_bEchoFlag = false;
}

void shellWidget::resizeEvent(QResizeEvent *event)
{
    UpdateEditPosition();
    QPlainTextEdit::resizeEvent(event);
}

void shellWidget::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->buttons())
    {
        m_cInputEdit->setFocus();
    }
    QPlainTextEdit::mousePressEvent(event);
}

void shellWidget::GotoBottom()
{
    QScrollBar *scrollbar = this->verticalScrollBar();
    if (scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

void shellWidget::UpdateEditPosition()
{
    QRectF rect = this->blockBoundingGeometry(this->document()->lastBlock());
    qDebug() << rect;
    m_cInputEdit->move(rect.topRight().toPoint());
    m_cInputEdit->resize(this->viewport()->size().width(), rect.height());
    m_cInputEdit->setFocus();
}

void shellWidget::SwitchNewLine(QString data)
{
    if (m_bEchoFlag == false && data == m_cPrevCmd)
    {
        return;
    }
    int count = data.count("\n");

    for (int i = 0; i < count; i++)
    {
        QString lineText = data.section("\n", i, i);
        this->insertPlainText(lineText + "\n");
    }
    this->insertPlainText(data.section("\n", count, count));
    UpdateEditPosition();
}

void shellWidget::GetEditCmd(enum Qt::Key code)
{
    QString cmd = m_cInputEdit->text();
    m_cPrevCmd = cmd + "\r\n";
    switch (code)
    {
    case Qt::Key_Tab:
        cmd = cmd + "\t";
        break;
    case Qt::Key_Return:
        m_cInputEdit->clear();
        this->moveCursor(QTextCursor::End);
        this->insertPlainText(cmd);
        this->appendPlainText("#");
        UpdateEditPosition();
        cmd = cmd + "\n";
        break;
    default:
        break;
    }
    emit inputFinished(cmd);
}
