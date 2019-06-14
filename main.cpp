#include "yasav.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QTranslator translator;

    translator.load(QLocale::system(), ":/YASAV", "_");

    QApplication a(argc, argv);
    a.installTranslator(&translator);

    yasav w;
    w.show();

    return a.exec();
}
