#ifndef SHELLWIDGET_H
#define SHELLWIDGET_H

#include <QPlainTextEdit>

class shellWidget:public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit shellWidget(QWidget *parent=0);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void GoToBottom();

signals:
    void inputFinished(QString);

private slots:
    void SwitchNewLine(QString data);

private:
    int m_iCursorPosition;
    int m_bEchoFlag;
};

#endif // SHELLDEMO_H
