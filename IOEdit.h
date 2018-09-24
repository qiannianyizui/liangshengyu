#ifndef IOEDIT_H
#define IOEDIT_H

#include <QLineEdit>

class IOEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit IOEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void inputControlChar(enum Qt::Key code);

public slots:
};

#endif // IOEDIT_H
