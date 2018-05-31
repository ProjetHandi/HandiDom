#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "frame.h"
#include "userframe.h"
#include "communication.h"
#include <QDebug>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // COM communication;
    // communication.setUpPIN();

    UserFrame fenetre;
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
