#ifndef FRAME_H
#define FRAME_H

#include <QMainWindow>
#include <QPushButton>
#include <contact.h>


class Frame : public QWidget
{
   Q_OBJECT

public:
    Frame();
    QString queryOne(QString command);
    void makeCall(QString number);
    void query(QString query);
    ~Frame();
private slots:
     void getContacts();
private:

};

#endif // FRAME_H
