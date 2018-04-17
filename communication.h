#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>

class COM
{
public:
    COM();
    void setUpPIN();
    void call(QString number);
};

#endif // COMMUNICATION_H
