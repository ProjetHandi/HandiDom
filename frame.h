#ifndef FRAME_H
#define FRAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMapIterator>
#include <contact.h>


class Frame : public QWidget
{
   Q_OBJECT

public:
    Frame(int user);
    void query(QString query);
    void updateContactsSuivant(int last);
    void getAllContacts();
    void updateContactsPrecedent();
private slots:
    void suivant();
    void precedent();
    void telephoner();
    void menu();
private:
    int userid;
    QGridLayout *layout = new QGridLayout;
};

#endif // FRAME_H
