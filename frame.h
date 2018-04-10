#ifndef FRAME_H
#define FRAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <contact.h>


class Frame : public QWidget
{
   Q_OBJECT

public:
    Frame();
    void query(QString query);
    bool queryHasMore(int last);
    void updateContactsSuivant(int last);
    void closeEvent(QCloseEvent *event);
    void getAllContacts();
    void updateContactsPrecedent(int last);
    ~Frame();
private slots:
    void suivant();
    void precedent();
    void telephoner();
private:
    QGridLayout *layout = new QGridLayout;
};

#endif // FRAME_H
