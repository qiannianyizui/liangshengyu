#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class comboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit comboBox(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

public slots:
};

#endif // COMBOBOX_H
