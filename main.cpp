#include "uComTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    uComTool w;
    w.show();

    return a.exec();
}
