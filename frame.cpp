#include <QApplication>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>
#include <QProcess>
#include <contact.h>
#include <string>
#include <frame.h>
#include <QMap>
#include <QMapIterator>
#include <QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QtSql>
#include <QtSql/QSqlQuery>
#include "communication.h"

QMap<int, Contact> contacts;
unsigned last_contact = 0, n_contact = 0, page = 0, nbPage;
QPushButton *t_contact[6];
QLabel *l_contact[6];
QPushButton *precedent_btn, *suivant_btn, *telephoner_btn;
QLabel *page_lbl;
QString numTel[6];

Frame::Frame() : QWidget()
{
    this->resize(800, 500);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setCursor(Qt::BlankCursor);
    this->setMinimumSize(QSize(400, 300));
    this->setWindowTitle("HandiDom");
    QIcon icon;
    //icon.addFile(QStringLiteral(":/img/ihm/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);

    QIcon fleche1, fleche2, tel;
    fleche1.addFile(QStringLiteral("img/ihm/f.png"), QSize(), QIcon::Normal, QIcon::Off);
    fleche2.addFile(QStringLiteral("img/ihm/f2.png"), QSize(), QIcon::Normal, QIcon::Off);
    tel.addFile(QStringLiteral("img/ihm/phone.png"), QSize(), QIcon::Normal, QIcon::Off);
    precedent_btn = new QPushButton(this);
    layout->addWidget(precedent_btn, 4, 0);
    precedent_btn->setEnabled(false);
    telephoner_btn = new QPushButton(this);
    layout->addWidget(telephoner_btn, 4, 1);
    suivant_btn = new QPushButton(this);
    layout->addWidget(suivant_btn, 4, 2);
    precedent_btn->setIcon(fleche1);
    precedent_btn->setIconSize(QSize(64, 64));
    precedent_btn->setFlat(true);
    precedent_btn->setGeometry(QRect(10, 100, 61, 81));
    suivant_btn->setIcon(fleche2);
    suivant_btn->setIconSize(QSize(64, 64));
    suivant_btn->setFlat(true);
    suivant_btn->setGeometry(QRect(530, 100, 61, 81));
    telephoner_btn->setIcon(tel);
    telephoner_btn->setIconSize(QSize(75, 75));
    telephoner_btn->setFlat(true);
    telephoner_btn->setCursor(QCursor(Qt::PointingHandCursor));
    telephoner_btn->setEnabled(true);
    //page_lbl = new QLabel(this);
    //page_lbl->setText("Page 1");
    //layout->addWidget(page_lbl, 3, 1);

    QObject::connect(suivant_btn, SIGNAL(clicked()), this, SLOT(suivant()));
    QObject::connect(precedent_btn, SIGNAL(clicked()), this, SLOT(precedent()));

    query("SELECT * FROM contacts");
    getAllContacts();

    QMapIterator<int, Contact> map_i(contacts);
    int n = 0;
    while (map_i.hasNext() && n != 6) {
        map_i.next();
        QIcon icon;
        QString prenom = map_i.value().getPrenom().c_str();
        QString nom = map_i.value().getNom().c_str();
        l_contact[n] = new QLabel;
        numTel[n] = map_i.value().getTelephone().c_str();
        l_contact[n]->setText(prenom + "\n" + nom);
        t_contact[n] = new QPushButton;
        t_contact[n]->setObjectName(QString::number(map_i.value().getId_contact()));
        QObject::connect(t_contact[n], SIGNAL(clicked()), this, SLOT(telephoner()));
        t_contact[n]->setFlat(true);
        icon.addFile(map_i.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
        t_contact[n]->setIcon(icon);
        t_contact[n]->setIconSize(QSize(140,  140));
        if (n <= 2) {
            layout->addWidget(t_contact[n], 0, n, Qt::AlignCenter);
            layout->addWidget(l_contact[n], 1, n, Qt::AlignCenter);
        }
        else {
            layout->addWidget(t_contact[n], 2, n - 3, Qt::AlignCenter);
            layout->addWidget(l_contact[n], 3, n - 3, Qt::AlignCenter);
        }
        n++;
    }

    if (!map_i.hasNext()) {
        suivant_btn->setEnabled(false);
    }
    page++;
    this->setLayout(layout);
    last_contact = n;
    this->setFocus();
}

void Frame::updateContactsSuivant(int last) {
    page++;
    QMapIterator<int, Contact> map_i(contacts);

    int n = 0;
    int n2 = 0;

    while (n2 != (sizeof(t_contact) / sizeof(t_contact[0]))) {
        l_contact[n2]->hide();
        t_contact[n2]->hide();
        n2++;
    }

    while (map_i.hasNext() && n < 6) {
        map_i.next();
        if (map_i.value().getId_contact() > last) {
            QIcon icon;
            QString prenom = map_i.value().getPrenom().c_str();
            QString nom = map_i.value().getNom().c_str();
            l_contact[n] = new QLabel;
            numTel[n] = map_i.value().getTelephone().c_str();
            l_contact[n]->setText(prenom + "\n" + nom);
            t_contact[n] = new QPushButton;
            t_contact[n]->setObjectName(QString::number(map_i.value().getId_contact()));
            QObject::connect(t_contact[n], SIGNAL(clicked()), this, SLOT(telephoner()));
            t_contact[n]->setFlat(true);
            icon.addFile(map_i.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
            t_contact[n]->setIcon(icon);
            t_contact[n]->setIconSize(QSize(140,  140));
            if (n <= 2) {
                layout->addWidget(t_contact[n], 0, n, Qt::AlignCenter);
                layout->addWidget(l_contact[n], 1, n, Qt::AlignCenter);
            }
            else {
                layout->addWidget(t_contact[n], 2, n - 3, Qt::AlignCenter);
                layout->addWidget(l_contact[n], 3, n - 3, Qt::AlignCenter);
            }
            t_contact[n]->show();
            l_contact[n]->show();
            n++;
        }

    }

    this->setLayout(layout);
    n_contact = n;
    last_contact += n;

    // page_lbl->setText("Page " + QString::number(page));

    if (!map_i.hasNext()) {
        suivant_btn->setEnabled(false);
        this->setFocus();
    }
    precedent_btn->setEnabled(true);
}

void Frame::updateContactsPrecedent() {
    QMapIterator<int, Contact> map_i(contacts);
    int n2 = 0;

    while (n2 != (sizeof(t_contact) / sizeof(t_contact[0]))) {
        l_contact[n2]->hide();
        t_contact[n2]->hide();
        n2++;
    }

    int n = 0;
    map_i.toBack();
    int last_element = contacts.last().getId_contact();

    if (page - 1 == 1) {
        map_i.toFront();
    } else if (page < nbPage) {
        int offset = (last_element - n_contact) % 6;
        if (offset != 0) {
            for(unsigned int i = 0; i <= last_element - n_contact - (offset / n_contact) - 1; i++) {
                map_i.previous();
            }
        }
        else {
            map_i.toFront();
            for(unsigned int i = 0; i <= 5; i++) {
                map_i.next();
            }
        }
    } else if (page == nbPage) {
        map_i.toFront();
        for(unsigned int i = 0; i <= last_element - n_contact - 7 ; i++) {
            map_i.next();
        }
    }

    page--;

    while (map_i.hasNext() && n != 6) {
        map_i.next();
        QIcon icon;
        QString prenom = map_i.value().getPrenom().c_str();
        QString nom = map_i.value().getNom().c_str();
        l_contact[n] = new QLabel;
        numTel[n] = map_i.value().getTelephone().c_str();
        l_contact[n]->setText(prenom + "\n" + nom);
        t_contact[n] = new QPushButton;
        t_contact[n]->setObjectName(QString::number(map_i.value().getId_contact()));
        QObject::connect(t_contact[n], SIGNAL(clicked()), this, SLOT(telephoner()));
        t_contact[n]->setFlat(true);
        icon.addFile(map_i.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
        t_contact[n]->setIcon(icon);
        t_contact[n]->setIconSize(QSize(140,  140));
        if (n <= 2) {
            layout->addWidget(t_contact[n], 0, n, Qt::AlignCenter);
            layout->addWidget(l_contact[n], 1, n, Qt::AlignCenter);
        }
        else {
            layout->addWidget(t_contact[n], 2, n - 3, Qt::AlignCenter);
            layout->addWidget(l_contact[n], 3, n - 3, Qt::AlignCenter);
        }
        t_contact[n]->show();
        l_contact[n]->show();
        n++;
    }

    if ((last_contact - n) % 6 != 0) {
        last_contact -= n_contact;
    }
    else {
        last_contact -= n;
    }


    // page_lbl->setText("Page " + QString::number(page));
    if (page == 1) {
        precedent_btn->setEnabled(false);
        this->setFocus();
    }

    this->setLayout(layout);
    suivant_btn->setEnabled(true);
}

void Frame::suivant() {
    updateContactsSuivant(last_contact);
}

void Frame::precedent() {
    updateContactsPrecedent();
}

void Frame::telephoner() {
    COM c;
    QObject* b = QObject::sender();
    int index = b->objectName().toInt();
    if (index > 6)
        index -= (page - 1) * 6;
    qDebug() << numTel[index - 1];
    c.call(numTel[index]);
}

void Frame::query(QString query) {
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
        contacts.insert(q.value("id").toInt(), Contact(q.value("id").toInt(),
                                                   q.value("nom").toString().toStdString(),
                                                   q.value("prenom").toString().toStdString(),
                                                   q.value("photo").toString().toStdString(),
                                                   q.value("telephone").toString().toStdString(),
                                                   q.value("frequence").toInt()));
    }
    else
        qDebug() << "lol";
}

void Frame::getAllContacts() {
    QMapIterator<int, Contact> i(contacts);
    while (i.hasNext()) {
        i.next();
        nbPage++;
        /* qDebug() << i.value().getId_contact() << "|" << i.value().getNom().c_str() << "|" << i.value().getPrenom().c_str() << "|"
                 << i.value().getPhoto().c_str() << "|" << i.value().getTelephone().c_str()
                 << "|" << i.value().getFrequence();*/
    }
    nbPage /= 6;
    nbPage++;
    // qDebug() << nbPage;
}
