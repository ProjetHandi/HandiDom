#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "frame.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Frame fenetre;
    fenetre.show();
    fenetre.setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    fenetre.size(),
                    qApp->desktop()->availableGeometry()
                    )
                );

    return app.exec();
}
