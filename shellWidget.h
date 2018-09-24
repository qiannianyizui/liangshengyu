#ifndef SHELLWIDGET_H
#define SHELLWIDGET_H

#include <QPlainTextEdit>

class IOEdit;
class shellWidget:public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit shellWidget(QWidget *parent=0);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void inputFinished(QString);

private slots:
    void GotoBottom();
    void UpdateEditPosition();
    void SwitchNewLine(QString data);
    void GetEditCmd(Qt::Key code);

private:
    IOEdit * m_cInputEdit;
    bool m_bEchoFlag;
    QString m_cPrevCmd;
};

#endif // SHELLDEMO_H
