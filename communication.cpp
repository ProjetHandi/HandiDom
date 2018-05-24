#include <QSerialPort>
#include <QSerialPortInfo>
#include "communication.h"
#include <QDebug>
#include <QByteArray>

QSerialPort serial;

COM::COM() {

}

void COM::setUpPIN() {
    serial.setPortName("/dev/ttyS0");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud115200);
    QByteArray output, input, input2;

    if (serial.isOpen() && serial.isWritable()) {
        output = "AT+CPIN=8822;\r\n";
        serial.write(output);
        serial.flush();

        serial.waitForReadyRead(2000);
        input = serial.readAll();
        serial.waitForReadyRead(2000);
        input2 = serial.readAll();
        qDebug() << input << " - " << input2;

        serial.close();
    }
    else {
        qDebug() << serial.errorString();
    }
}

void COM::call(QString number) {
    serial.setPortName("/dev/ttyS0");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud115200);
    QByteArray output, input, input2;

    if (serial.isOpen() && serial.isWritable()) {
        output = "ATD" + number.toLocal8Bit() + ";\r\n";
        serial.write(output);
        serial.flush();
        serial.close();
    }
    else {
        qDebug() << serial.errorString();
    }
}

void COM::hangup() {
    serial.setPortName("/dev/ttyS0");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud115200);
    QByteArray output, input, input2;

    if (serial.isOpen() && serial.isWritable()) {
        output = "ATH;\r\n";
        serial.write(output);
        serial.flush();
        serial.close();
    }
    else {
        qDebug() << serial.errorString();
    }
}
