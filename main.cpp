#include "start.h"
#include "build.h"
#include "character.h"

#include <QApplication>

Character *character;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start start;
    start.show();
    return a.exec();
}
