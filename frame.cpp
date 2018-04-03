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

int n_contact = 1;
QMap<int, Contact> contacts;
QPushButton *t_contact[6];

Frame::Frame() : QWidget()
{
    QPushButton *precedent, *suivant, *telephoner;

    this->resize(602, 330);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(400, 300));

    QIcon fleche1, fleche2, tel;
    fleche1.addFile(QStringLiteral("img/ihm/f.png"), QSize(), QIcon::Normal, QIcon::Off);
    fleche2.addFile(QStringLiteral("img/ihm/f2.png"), QSize(), QIcon::Normal, QIcon::Off);
    tel.addFile(QStringLiteral("img/ihm/phone.png"), QSize(), QIcon::Normal, QIcon::Off);
    precedent = new QPushButton(this);
    suivant = new QPushButton(this);
    telephoner = new QPushButton(this);
    precedent->setIcon(fleche1);
    precedent->setIconSize(QSize(64, 64));
    precedent->setFlat(true);
    precedent->setGeometry(QRect(10, 100, 61, 81));
    suivant->setIcon(fleche2);
    suivant->setIconSize(QSize(64, 64));
    suivant->setFlat(true);
    suivant->setGeometry(QRect(530, 100, 61, 81));
    telephoner->setIcon(tel);
    telephoner->setIconSize(QSize(32, 32));
    telephoner->setFlat(true);
    telephoner->setGeometry(QRect(240, 270, 121, 51));
    sizePolicy.setHeightForWidth(telephoner->sizePolicy().hasHeightForWidth());
    telephoner->setSizePolicy(sizePolicy);
    telephoner->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(suivant, SIGNAL(clicked()), this, SLOT(getContacts()));

    query("SELECT * FROM contacts WHERE id <= 6");
    QMapIterator<int, Contact> i(contacts);
    int _n = 0;

    while (i.hasNext()) {
        _n++;
        i.next();
        qDebug() << i.value().getId_contact() << "|" << i.value().getNom().c_str() << "|" << i.value().getPrenom().c_str() << "|"
                 << i.value().getPhoto().c_str() << "|" << i.value().getTelephone().c_str()
                 << "|" << i.value().getFrequence().c_str();
    }

    int n = 0;
    QMapIterator<int, Contact> i2(contacts);

    while (i2.hasNext() && n != 6) {
        n++;
        i2.next();
        QIcon icon;
        t_contact[n] = new QPushButton(this);
        t_contact[n]->setFlat(true);
        icon.addFile(i2.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
        t_contact[n]->setIcon(icon);
        t_contact[n]->setIconSize(QSize(64,  64));
        t_contact[n]->setGeometry(QRect(100 + n * 50, 100, 121, 51));
    }

}

void Frame::makeCall(QString number) {
    QString programme("sudo python py/call.py " + number);
    QProcess process;
    process.startDetached(programme);
}

Frame::~Frame()
{

}

QString Frame::queryOne(QString command) {
    QString programme("python py/main.py " + command);
    QProcess process;
    QByteArray out;
    process.start(programme);
    process.waitForFinished(-1);
    out = process.readAllStandardOutput();
    out.toStdString();
    out.remove(out.length() - 1, 1);
    return out;
}

void Frame::getContacts() {
    query("SELECT * FROM contacts WHERE id > " + QString::number(contacts.last().getId_contact()));

    int n = 0;
    QMapIterator<int, Contact> i2(contacts);

    while (i2.hasNext() && n != 6) {
        n++;
        i2.next();
        QIcon icon;
        t_contact[n] = new QPushButton(this);
        t_contact[n]->setFlat(true);
        icon.addFile(i2.value().getPhoto().c_str(), QSize(), QIcon::Normal, QIcon::Off);
        t_contact[n]->setIcon(icon);
        t_contact[n]->setIconSize(QSize(64,  64));
        t_contact[n]->setGeometry(QRect(100 + n * 50, 100, 121, 51));
    }
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
        contacts.insert(res->getInt("id"), Contact(res->getInt("id"), res->getString("nom").asStdString(),
                                                                                  res->getString("prenom").asStdString(),
                                                                                  res->getString("photo").asStdString(),
                                                                                  res->getString("telephone").asStdString(),
                                                                                  res->getString("frequence").asStdString()));
        n_contact++;
    }

    delete stmt;
    delete con;
    delete res;
}
