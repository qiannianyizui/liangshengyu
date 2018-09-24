#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSplitter>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QTextCodec>
#include <QDebug>
#include "comboBox.h"
#include "shellWidget.h"
#include "uComTool.h"

uComTool::uComTool(QWidget *parent) :
    QMainWindow(parent)
{
    QGridLayout *mainWidgetLayout = new QGridLayout;
    m_cMainWidget = new QWidget;
    m_cMainWidget->setLayout(mainWidgetLayout);
    this->setCentralWidget(m_cMainWidget);

    Initialize(mainWidgetLayout);
}

uComTool::~uComTool()
{

}

void uComTool::Initialize(QGridLayout *layout)
{
    m_cSerialPort           = new QSerialPort(this);
    m_cSplitter             = new QSplitter(Qt::Horizontal);
    m_cComComboBox          = new comboBox;
    m_cBaudrateComboBox     = new QComboBox;
    m_cDataBitsComboBox     = new QComboBox;
    m_cStopBitsComboBox     = new QComboBox;
    m_cParityComboBox       = new QComboBox;
    m_cFlowControlComboBox  = new QComboBox;
    m_cComLabel             = new QLabel(tr("串口"));
    m_cBaudrateLabel        = new QLabel(tr("波特率"));
    m_cDataBitsLabel        = new QLabel(tr("数据位"));
    m_cStopBitsLabel        = new QLabel(tr("停止位"));
    m_cParityLabel          = new QLabel(tr("校验位"));
    m_cFlowControlLabel     = new QLabel(tr("流控制"));
    m_cComControlButton     = new QPushButton("打开");
    m_cComConfigureWidget   = new QWidget;
    m_cIOWidget             = new shellWidget;

    connect(m_cSerialPort, SIGNAL(readyRead()), this, SLOT(ReadData()));

    connect(m_cComComboBox, SIGNAL(clicked()), this, SLOT(ScanPort()));

    QStringList list;
    list.clear();
    list << tr("1200") << tr("2400") << tr("4800") << tr("9600")
         << tr("19200") << tr("38400") << tr("57600") << tr("115200");
    m_cBaudrateComboBox->addItems(list);

    list.clear();
    list << tr("5") << tr("6") << tr("7") << tr("8");
    m_cDataBitsComboBox->addItems(list);

    list.clear();
    list << tr("1") << tr("1.5") << tr("2");
    m_cStopBitsComboBox->addItems(list);

    list.clear();
    list << tr("无校验") << tr("偶校验") << tr("奇校验") << tr("0校验") << tr("1校验");
    m_cParityComboBox->addItems(list);

    list.clear();
    list << tr("无") << tr("hardware") << tr("software");
    m_cFlowControlComboBox->addItems(list);

    m_cComControlButton->setCheckable(true);
    m_cComControlButton->setChecked(false);
    connect(m_cComControlButton, SIGNAL(clicked(bool)), this, SLOT(ChgCtrChecked(bool)));

    QGridLayout *configureWidgetLayout = new QGridLayout;
    m_cComConfigureWidget->setLayout(configureWidgetLayout);
    configureWidgetLayout->addWidget(m_cComLabel, 0, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cComComboBox, 0, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cBaudrateLabel, 1, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cBaudrateComboBox, 1, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cDataBitsLabel, 2, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cDataBitsComboBox, 2, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cStopBitsLabel, 3, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cStopBitsComboBox, 3, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cParityLabel, 4, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cParityComboBox, 4, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cFlowControlLabel, 5, 0, 1, 1);
    configureWidgetLayout->addWidget(m_cFlowControlComboBox, 5, 1, 1, 1);
    configureWidgetLayout->addWidget(m_cComControlButton, 6, 0, 1, 1);

    connect(m_cIOWidget, SIGNAL(inputFinished(QString)), this, SLOT(GetCmd(QString)));
    connect(this, SIGNAL(ReadFinished(QString)), m_cIOWidget, SLOT(SwitchNewLine(QString)));

    layout->addWidget(m_cSplitter);
    m_cSplitter->addWidget(m_cIOWidget);
    m_cSplitter->addWidget(m_cComConfigureWidget);
}

bool uComTool::ControlPort(bool checked)
{
    int ret = true;
    if (true == checked)
    {
        m_cSerialPort->setPortName(m_cComComboBox->currentText());
        SetBaudRate();
        SetDataBits();
        SetStopBits();
        SetParity();
        SetFlowControl();
        if (false == m_cSerialPort->open(QIODevice::ReadWrite))
        {
            ret = false;
        }
    }
    else
    {
        m_cSerialPort->clear();
        m_cSerialPort->close();
    }
    return ret;
}

void uComTool::SetBaudRate()
{
    switch (m_cBaudrateComboBox->currentIndex())
    {
    case 0:
        m_cSerialPort->setBaudRate(QSerialPort::Baud1200);
        break;
    case 1:
        m_cSerialPort->setBaudRate(QSerialPort::Baud2400);
        break;
    case 2:
        m_cSerialPort->setBaudRate(QSerialPort::Baud4800);
        break;
    case 3:
        m_cSerialPort->setBaudRate(QSerialPort::Baud9600);
        break;
    case 4:
        m_cSerialPort->setBaudRate(QSerialPort::Baud19200);
        break;
    case 5:
        m_cSerialPort->setBaudRate(QSerialPort::Baud38400);
        break;
    case 6:
        m_cSerialPort->setBaudRate(QSerialPort::Baud57600);
        break;
    case 7:
        m_cSerialPort->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        break;
    }
}

void uComTool::SetDataBits()
{
    switch (m_cDataBitsComboBox->currentIndex())
    {
    case 0:
        m_cSerialPort->setDataBits(QSerialPort::Data5);
        break;
    case 1:
        m_cSerialPort->setDataBits(QSerialPort::Data6);
        break;
    case 2:
        m_cSerialPort->setDataBits(QSerialPort::Data7);
        break;
    case 3:
        m_cSerialPort->setDataBits(QSerialPort::Data8);
        break;
    default:
        break;
    }

}
void uComTool::SetStopBits()
{
    switch (m_cStopBitsComboBox->currentIndex())
    {
    case 0:
        m_cSerialPort->setStopBits(QSerialPort::OneStop);//停止位设置为1
        break;
    case 1:
        m_cSerialPort->setStopBits(QSerialPort::OneAndHalfStop);
    case 2:
        m_cSerialPort->setStopBits(QSerialPort::TwoStop);
    default:
        break;
    }
}

void uComTool::SetParity()
{
    switch (m_cParityComboBox->currentIndex())
    {
    case 0:
        m_cSerialPort->setParity(QSerialPort::NoParity);
        break;
    case 1:
        m_cSerialPort->setParity(QSerialPort::EvenParity);
        break;
    case 2:
        m_cSerialPort->setParity(QSerialPort::OddParity);
        break;
    case 3:
        m_cSerialPort->setParity(QSerialPort::SpaceParity);
        break;
    case 4:
        m_cSerialPort->setParity(QSerialPort::MarkParity);
        break;
    default:
        break;
    }
}
void uComTool::SetFlowControl()
{
    switch (m_cFlowControlComboBox->currentIndex())
    {
    case 0:
        m_cSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        break;
    case 1:
        m_cSerialPort->setFlowControl(QSerialPort::HardwareControl);
        break;
    case 2:
        m_cSerialPort->setFlowControl(QSerialPort::SoftwareControl);
        break;
    default:
        break;
    }
}


void uComTool::ScanPort()
{
    m_cComComboBox->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_cComComboBox->addItem(info.portName());
    }
}

void uComTool::ChgCtrChecked(bool checked)
{
    if (true == checked)
    {
        m_cComControlButton->setText(tr("关闭"));
    }
    else
    {
        m_cComControlButton->setText(tr("打开"));
    }
    if (false == ControlPort(checked))
    {
        m_cComControlButton->setText(tr("打开"));
    }
}

void uComTool::ReadData()
{
    QString data = m_cSerialPort->readAll();

    emit ReadFinished(data);
}

void uComTool::WriteData(QString cmd)
{
    m_cSerialPort->write(cmd.toLatin1());
    m_cSerialPort->waitForBytesWritten(100);
}

void uComTool::GetCmd(QString cmd)
{
    WriteData(cmd);
}
