#ifndef UCOMTOOL_H
#define UCOMTOOL_H

#include <QMainWindow>

class QSerialPort;
class QSplitter;
class QPushButton;
class QComboBox;
class QLabel;
class QGridLayout;
class QTimer;
class comboBox;
class shellWidget;
class uComTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit uComTool(QWidget *parent = 0);
    ~uComTool();

signals:
    void ReadFinished(QString data);

protected:
    void Initialize(QGridLayout *layout);
    bool ControlPort(bool checked);
    void SetBaudRate();
    void SetDataBits();
    void SetStopBits();
    void SetParity();
    void SetFlowControl();

protected slots:
    void ScanPort();
    void ChgCtrChecked(bool checked);
    void ReadData();
    void WriteData(QString cmd);
    void GetCmd(QString cmd);

private:
    QSerialPort    *m_cSerialPort;
    QSplitter      *m_cSplitter;
    comboBox       *m_cComComboBox;
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
    shellWidget    *m_cIOWidget;
    QWidget        *m_cMainWidget;
};

#endif // UCOMTOOL_H
