#include <QApplication>
#include <QPushButton>
#include <mysql_driver.h>
#include <QStyle>
#include <QDesktopWidget>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
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
#include <QGridLayout>

QMap<int, Contact> contacts;
int last_contact = 0;
QPushButton *t_contact[6];
QPushButton *precedent_btn, *suivant_btn, *telephoner_btn;

Frame::Frame() : QWidget()
{
    this->resize(800, 500);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(400, 300));
    this->setWindowTitle("HandiDom");
    QIcon icon;
    icon.addFile(QStringLiteral(":/img/ihm/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);

    QIcon fleche1, fleche2, tel;
    fleche1.addFile(QStringLiteral("img/ihm/f.png"), QSize(), QIcon::Normal, QIcon::Off);
    fleche2.addFile(QStringLiteral("img/ihm/f2.png"), QSize(), QIcon::Normal, QIcon::Off);
    tel.addFile(QStringLiteral("img/ihm/phone.png"), QSize(), QIcon::Normal, QIcon::Off);
    precedent_btn = new QPushButton(this);
    layout->addWidget(precedent_btn, 2, 0);
    precedent_btn->setEnabled(false);
    telephoner_btn = new QPushButton(this);
    layout->addWidget(telephoner_btn, 2, 1);
    suivant_btn = new QPushButton(this);
    layout->addWidget(suivant_btn, 2, 2);
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

    QObject::connect(suivant_btn, SIGNAL(clicked()), this, SLOT(suivant()));
    QObject::connect(precedent_btn, SIGNAL(clicked()), this, SLOT(precedent()));
    QObject::connect(telephoner_btn, SIGNAL(clicked()), this, SLOT(telephoner()));

    query("SELECT * FROM contacts WHERE id <= 6");

    int n = 0;
    QMapIterator<int, Contact> i2(contacts);
    while (i2.hasNext() && n != 6) {
        i2.next();
        QIcon icon;
        t_contact[n] = new QPushButton(this);
        t_contact[n]->setAttribute(Qt::WA_DeleteOnClose);
        t_contact[n]->setFlat(true);
        icon.addFile(i2.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
        t_contact[n]->setIcon(icon);
        t_contact[n]->setIconSize(QSize(100,  100));
        if (n <= 2) {
            layout->addWidget(t_contact[n], 0, n);
        }
        else {
            layout->addWidget(t_contact[n], 1, n - 3);
        }
        n++;
    }


    this->setLayout(layout);
    last_contact = contacts.last().getId_contact();
    this->setFocus();
}

void Frame::closeEvent (QCloseEvent *event)
{
    //QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Fermeture de l'application",
                                                                    //tr("Voulez vous fermer l'application ?\n"),
                                                                    //QMessageBox::No | QMessageBox::Yes,
                                                                    //QMessageBox::Yes);
        //if (resBtn != QMessageBox::Yes) {
            //event->ignore();
        //} else {
            event->accept();
        //}
}

Frame::~Frame() {

}

void Frame::updateContactsSuivant(int last) {
    query("SELECT * FROM contacts WHERE id > " + QString::number(contacts.last().getId_contact()) + " LIMIT 6");

    int n = 0;
    int n2 = 0;
    QMapIterator<int, Contact> i2(contacts);

    while (n2 != (sizeof(t_contact) / sizeof(t_contact[0]))) {
        t_contact[n2]->hide();
        n2++;
    }

    while (i2.hasNext() && n != 6) {
        i2.next();
        if (i2.value().getId_contact() > last) {
            QIcon icon;
            t_contact[n] = new QPushButton(this);
            t_contact[n]->setAttribute(Qt::WA_DeleteOnClose);
            t_contact[n]->setFlat(true);
            icon.addFile(i2.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
            t_contact[n]->setIcon(icon);
            t_contact[n]->setIconSize(QSize(100,  100));
            if (n <= 2) {
                layout->addWidget(t_contact[n], 0, n);
            }
            else {
                layout->addWidget(t_contact[n], 1, n - 3);
            }
            t_contact[n]->show();
            n++;
        }
    }

    this->setLayout(layout);
    precedent_btn->setEnabled(true);

    last_contact = contacts.last().getId_contact();

    if (!queryHasMore(last_contact)) {
        suivant_btn->setEnabled(false);
        this->setFocus();
    }
}

void Frame::updateContactsPrecedent(int last) {
    int n2 = 0;
    while (n2 != (sizeof(t_contact) / sizeof(t_contact[0]))) {
        t_contact[n2]->hide();
        n2++;
    }

    QMapIterator<int, Contact> i(contacts);
//    i.toBack();

/*    int n = 0;
    while (i.hasPrevious() && n != 6) {
        i.previous();
        n++;
    } */

    int n3 = 0;
    i.toBack();
    while (i.hasPrevious() && n3 != 6) {
        i.previous();
        //if (i.value().getId_contact() < last) {
            QIcon icon;
            qDebug() << n3;
            t_contact[n3] = new QPushButton(this);
            t_contact[n3]->setAttribute(Qt::WA_DeleteOnClose);
            t_contact[n3]->setFlat(true);
            icon.addFile(i.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
            t_contact[n3]->setIcon(icon);
            t_contact[n3]->setIconSize(QSize(100,  100));
            if (n3 <= 2) {
                layout->addWidget(t_contact[n3], 0, n3);
            }
            else {
                layout->addWidget(t_contact[n3], 1, n3 - 3);
            }
            t_contact[n3]->show();
            n3++;
        //}
    }
    this->setLayout(layout);
    suivant_btn->setVisible(true);
}

void Frame::suivant() {
    updateContactsSuivant(last_contact);
}

void Frame::precedent() {
    updateContactsPrecedent(last_contact);
}

void Frame::telephoner() {
    getAllContacts();
}

void Frame::query(QString query) {
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    sql::Statement *stmt;

    driver = get_driver_instance();
    con = driver->connect("127.0.0.1", "root", "btsir123");
    stmt = con->createStatement();
    stmt->execute("USE HandiDom");

    prep_stmt = con->prepareStatement(query.toStdString());
    res = prep_stmt->executeQuery();

    while(res->next()) {
        contacts.insert(res->getInt("id"), Contact(res->getInt("id"),
                                                   res->getString("nom").asStdString(),
                                                   res->getString("prenom").asStdString(),
                                                   res->getString("photo").asStdString(),
                                                   res->getString("telephone").asStdString(),
                                                   res->getInt("frequence")));
    }

    delete stmt;
    delete con;
    delete res;
}

bool Frame::queryHasMore(int last) {
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    sql::Statement *stmt;

    driver = get_driver_instance();
    con = driver->connect("127.0.0.1", "root", "btsir123");
    stmt = con->createStatement();
    stmt->execute("USE HandiDom");

    prep_stmt = con->prepareStatement("SELECT * FROM contacts WHERE id > " + QString::number(last).toStdString() + " HAVING id IS NOT NULL");
    res = prep_stmt->executeQuery();

    if(!res->next()) {
        delete stmt;
        delete con;
        delete res;
        return false;
    }

    delete stmt;
    delete con;
    delete res;
    return true;
}

void Frame::getAllContacts() {
    QMapIterator<int, Contact> i(contacts);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.value().getId_contact() << "|" << i.value().getNom().c_str() << "|" << i.value().getPrenom().c_str() << "|"
                 << i.value().getPhoto().c_str() << "|" << i.value().getTelephone().c_str()
                 << "|" << i.value().getFrequence();
    }
}
