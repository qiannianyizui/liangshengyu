#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSplitter>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QTimer>
#include <QDebug>
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
    m_cComComboBox          = new QComboBox;
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
    m_cIOEdit               = new QTextEdit;
    m_cPortScanTimer        = new QTimer;

    QStringList list;
    list.clear();
    list << tr("1200") << tr("2400") << tr("4800") << tr("9600")
         << tr("19200") << tr("57600") << tr("115200");
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

    layout->addWidget(m_cSplitter);
    m_cSplitter->addWidget(m_cIOEdit);
    m_cSplitter->addWidget(m_cComConfigureWidget);

    m_cPortScanTimer->setInterval(1000);
    connect(m_cPortScanTimer, SIGNAL(timeout()), this, SLOT(ScanPort()));
    m_cPortScanTimer->start();
}

void uComTool::ControlTimer(bool checked)
{
    if(true == checked)
    {
        m_cPortScanTimer->stop();
    }
    else
    {
        m_cPortScanTimer->start();
    }
}

void uComTool::ScanPort()
{
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        qDebug() << info.portName();
        m_cComComboBox->addItem(info.portName());
    }
}

void uComTool::ChgCtrChecked(bool checked)
{
    if(true == checked)
    {
        m_cComControlButton->setText(tr("关闭"));
    }
    else
    {
        m_cComControlButton->setText(tr("打开"));
    }
}
