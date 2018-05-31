#include "userframe.h"
#include <QApplication>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>
#include <QProcess>
#include <user.h>
#include <string>
#include <QMap>
#include <QMapIterator>
#include <QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <frame.h>
#include <QLabel>
#include <QtSql>
#include <QtSql/QSqlQuery>

QMap<int, User> user;
unsigned last_user = 0, n_user = 0, page_u = 0, nbPage_u;
QPushButton *t_user[6];
QLabel *l_user[6];
QPushButton *precedent_btn_u, *suivant_btn_u;

UserFrame::UserFrame() : QWidget()
{
    this->resize(800, 500);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    // this->setCursor(Qt::BlankCursor);
    this->setMinimumSize(QSize(400, 300));
    this->setWindowTitle("HandiDom");

    QIcon fleche1, fleche2;
    fleche1.addFile(QStringLiteral("img/ihm/f.png"), QSize(), QIcon::Normal, QIcon::Off);
    fleche2.addFile(QStringLiteral("img/ihm/f2.png"), QSize(), QIcon::Normal, QIcon::Off);
    precedent_btn_u = new QPushButton(this);
    layout->addWidget(precedent_btn_u, 4, 0);
    precedent_btn_u->setEnabled(false);
    suivant_btn_u = new QPushButton(this);
    layout->addWidget(suivant_btn_u, 4, 2);
    precedent_btn_u->setIcon(fleche1);
    precedent_btn_u->setIconSize(QSize(64, 64));
    precedent_btn_u->setFlat(true);
    precedent_btn_u->setGeometry(QRect(10, 100, 61, 81));
    suivant_btn_u->setIcon(fleche2);
    suivant_btn_u->setIconSize(QSize(64, 64));
    suivant_btn_u->setFlat(true);
    suivant_btn_u->setGeometry(QRect(530, 100, 61, 81));

    QObject::connect(suivant_btn_u, SIGNAL(clicked()), this, SLOT(suivant()));
    QObject::connect(precedent_btn_u, SIGNAL(clicked()), this, SLOT(precedent()));

    query("SELECT * FROM user");
    getAllUser();

    QMapIterator<int, User> map_i(user);
    int n = 0;
    while (map_i.hasNext() && n != 6) {
        map_i.next();
        QIcon icon;
        QString prenom = map_i.value().getPrenom();
        QString nom = map_i.value().getNom();
        l_user[n] = new QLabel;
        l_user[n]->setText(prenom + "\n" + nom);
        t_user[n] = new QPushButton;
        t_user[n]->setObjectName(QString::number(map_i.value().getId()));
        QObject::connect(t_user[n], SIGNAL(clicked()), this, SLOT(open_contacts()));
        t_user[n]->setFlat(true);
        icon.addFile(map_i.value().getPhoto(), QSize(), QIcon::Normal, QIcon::Off);
        t_user[n]->setIcon(icon);
        t_user[n]->setIconSize(QSize(140,  140));
        if (n <= 2) {
            layout->addWidget(t_user[n], 0, n, Qt::AlignCenter);
            layout->addWidget(l_user[n], 1, n, Qt::AlignCenter);
        }
        else {
            layout->addWidget(t_user[n], 2, n - 3, Qt::AlignCenter);
            layout->addWidget(l_user[n], 3, n - 3, Qt::AlignCenter);
        }
        n++;
    }

    if (!map_i.hasNext()) {
        suivant_btn_u->setEnabled(true);
    }
    page_u++;
    this->setLayout(layout);
    last_user = n;
    this->setFocus();
}

void UserFrame::open_contacts() {
    QObject* b = QObject::sender();
    int user = b->objectName().toInt();
    this->hide();
    Frame* fenetre = new Frame(user);
    fenetre->show();
    fenetre->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    fenetre->size(),
                    qApp->desktop()->availableGeometry()
                    )
                );
}

void UserFrame::updateUserSuivant(int last) {
    page_u++;
    QMapIterator<int, User> map_i(user);

    int n = 0;
    int n2 = 0;

    while (n2 != (sizeof(t_user) / sizeof(t_user[0]))) {
        l_user[n2]->hide();
        t_user[n2]->hide();
        n2++;
    }

    while (map_i.hasNext() && n < 6) {
        map_i.next();
        if (map_i.value().getId() > last) {
            QIcon icon;
            QString prenom = map_i.value().getPrenom();
            QString nom = map_i.value().getNom();
            l_user[n] = new QLabel;
            l_user[n]->setText(prenom + "\n" + nom);
            t_user[n] = new QPushButton;
            t_user[n]->setObjectName(QString::number(map_i.value().getId()));
            QObject::connect(t_user[n], SIGNAL(clicked()), this, SLOT(open_contacts()));
            t_user[n]->setFlat(true);
            icon.addFile(map_i.value().getPhoto(), QSize(), QIcon::Normal, QIcon::Off);
            t_user[n]->setIcon(icon);
            t_user[n]->setIconSize(QSize(140,  140));
            if (n <= 2) {
                layout->addWidget(t_user[n], 0, n, Qt::AlignCenter);
                layout->addWidget(l_user[n], 1, n, Qt::AlignCenter);
            }
            else {
                layout->addWidget(t_user[n], 2, n - 3, Qt::AlignCenter);
                layout->addWidget(l_user[n], 3, n - 3, Qt::AlignCenter);
            }
            t_user[n]->show();
            l_user[n]->show();
            n++;
        }

    }

    this->setLayout(layout);
    n_user = n;
    last_user += n;

    if (!map_i.hasNext()) {
        suivant_btn_u->setEnabled(false);
        this->setFocus();
    }
    precedent_btn_u->setEnabled(true);
}

void UserFrame::updateUserPrecedent() {
    QMapIterator<int, User> map_i(user);
    int n2 = 0;

    while (n2 != (sizeof(t_user) / sizeof(t_user[0]))) {
        l_user[n2]->hide();
        t_user[n2]->hide();
        n2++;
    }

    int n = 0;
    map_i.toBack();
    int last_element = user.last().getId();

    if (page_u - 1 == 1) {
        map_i.toFront();
    } else if (page_u < nbPage_u) {
        int offset = (last_element - n_user) % 6;
        if (offset != 0) {
            for(unsigned int i = 0; i <= last_element - n_user - (offset / n_user) - 1; i++) {
                map_i.previous();
            }
        }
        else {
            map_i.toFront();
            for(unsigned int i = 0; i <= 5; i++) {
                map_i.next();
            }
        }
    } else if (page_u == nbPage_u) {
        map_i.toFront();
        for(unsigned int i = 0; i <= last_element - n_user - 7 ; i++) {
            map_i.next();
        }
    }

    page_u--;

    while (map_i.hasNext() && n != 6) {
        map_i.next();
        QIcon icon;
        QString prenom = map_i.value().getPrenom();
        QString nom = map_i.value().getNom();
        l_user[n] = new QLabel;
        l_user[n]->setText(prenom + "\n" + nom);
        t_user[n] = new QPushButton;
        t_user[n]->setObjectName(QString::number(map_i.value().getId()));
        QObject::connect(t_user[n], SIGNAL(clicked()), this, SLOT(open_contacts()));
        t_user[n]->setFlat(true);
        icon.addFile(map_i.value().getPhoto(), QSize(), QIcon::Normal, QIcon::Off);
        t_user[n]->setIcon(icon);
        t_user[n]->setIconSize(QSize(140,  140));
        if (n <= 2) {
            layout->addWidget(t_user[n], 0, n, Qt::AlignCenter);
            layout->addWidget(l_user[n], 1, n, Qt::AlignCenter);
        }
        else {
            layout->addWidget(t_user[n], 2, n - 3, Qt::AlignCenter);
            layout->addWidget(l_user[n], 3, n - 3, Qt::AlignCenter);
        }
        t_user[n]->show();
        l_user[n]->show();
        n++;
    }

    if ((last_user - n) % 6 != 0) {
        last_user -= n_user;
    }
    else {
        last_user -= n;
    }

    if (page_u == 1) {
        precedent_btn_u->setEnabled(false);
        this->setFocus();
    }

    this->setLayout(layout);
    suivant_btn_u->setEnabled(true);
}

void UserFrame::suivant() {
    updateUserSuivant(last_user);
}

void UserFrame::precedent() {
    updateUserPrecedent();
}

void UserFrame::query(QString query) {
    {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("btsir123");
    db.setDatabaseName("HandiDom");
    bool ok = db.open();
    QSqlQuery q;
    q.exec(query);

    if(ok)
    while(q.next()) {
        user.insert(q.value("id").toInt(), User(q.value("id").toInt(),
                                                   q.value("prenom").toString(),
                                                   q.value("nom").toString(),
                                                   q.value("photo").toString()));
    }
    else
        qDebug() << "Erreur de connexion";
    db.close();
    }
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

void UserFrame::getAllUser() {
    QMapIterator<int, User> i(user);
    while (i.hasNext()) {
        i.next();
        nbPage_u++;
    }
    nbPage_u /= 6;
    nbPage_u++;
}
