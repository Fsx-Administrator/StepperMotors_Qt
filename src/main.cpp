#include "debugwindow.h"
#include "mainwindow.h"
#include "shortcutmanager.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DebugWindow d(&w);
    ShortcutManager::registerShortcut(QKeyCombination(Qt::ControlModifier, Qt::Key_D), &w, [&d]() -> void {
        d.show();
    });

    return a.exec();
}
