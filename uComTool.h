#ifndef UCOMTOOL_H
#define UCOMTOOL_H

#include <QMainWindow>

class QSerialPort;
class QSplitter;
class QPushButton;
class QComboBox;
class QLabel;
class QTextEdit;
class QGridLayout;
class QTimer;
class uComTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit uComTool(QWidget *parent = 0);
    ~uComTool();

protected:
    void Initialize(QGridLayout *layout);
    void ControlTimer(bool checked);

protected slots:
    void ScanPort();
    void ChgCtrChecked(bool checked);

private:
    QSerialPort    *m_cSerialPort;
    QSplitter      *m_cSplitter;
    QComboBox      *m_cComComboBox;
    QComboBox      *m_cBaudrateComboBox;
    QComboBox      *m_cDataBitsComboBox;
    QComboBox      *m_cStopBitsComboBox;
    QComboBox      *m_cParityComboBox;
    QComboBox      *m_cFlowControlComboBox;
    QLabel         *m_cComLabel;
    QLabel         *m_cBaudrateLabel;
    QLabel         *m_cDataBitsLabel;
    QLabel         *m_cStopBitsLabel;
    QLabel         *m_cParityLabel;
    QLabel         *m_cFlowControlLabel;
    QPushButton    *m_cComControlButton;
    QWidget        *m_cComConfigureWidget;
    QTextEdit      *m_cIOEdit;
    QWidget        *m_cMainWidget;
    QTimer         *m_cPortScanTimer;
};

#endif // UCOMTOOL_H
