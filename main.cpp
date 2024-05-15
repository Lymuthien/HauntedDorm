#include "haunteddormgame.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    HauntedDormGame* app = new HauntedDormGame();
    app->Start();
    return a.exec();
}
