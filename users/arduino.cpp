#include "arduino.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino(const QString& com_port_name)
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.portName() == com_port_name) {
            if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
                if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id) {

                    arduino_is_available = true;
                    arduino_port_name = serial_port_info.portName();
                }
            }
        }
    }

    qDebug() << "Arduino port name is:" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Arduino connected successfully";
            return 0;
        } else {
            qDebug() << "Failed to open Arduino port:" << serial->errorString();
            return 1;
        }
    }

    qDebug() << "Arduino not available";
    return -1;
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


QByteArray Arduino::read_from_arduino()
{

    if(serial->isReadable()){
         data = serial->readAll(); // Retrieve the received data
    }

    return data;  // Always return a QByteArray
}


int Arduino::write_to_arduino(const QStringList& dataList)
{
    if (serial->isWritable()) {
        QByteArray dataToSend = dataList.join(",").toUtf8(); // Join data with comma delimiter
        serial->write(dataToSend); // Send data to Arduino
        return 0; // Success
    } else {
        qDebug() << "Couldn't write to serial!";
        return -1; // Failure
    }
}

int Arduino::write_to_arduino_old(QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}

bool Arduino::check(QString data, QString *nom, QString *prenom)
{
    QSqlQuery query;

    QString check = "SELECT last_name, first_name FROM users WHERE empreint = :data";
    query.prepare(check);
    query.bindValue(":data", data);

    if (query.exec()) {
        if (query.next()) {
            *nom = query.value(0).toString();
            *prenom = query.value(1).toString();
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void Arduino::inserer( QString empreint , int idu){
    QSqlQuery query;

        // Construct the SQL UPDATE query with placeholders for user ID and empreinte data
        QString queryString = "UPDATE users SET empreint = :empreint "
                              "WHERE idu = :idu";
        query.prepare(queryString);

        // Bind the user ID and empreinte data to the query placeholders
        query.bindValue(":idu", idu);
        query.bindValue(":empreint", empreint);

        // Execute the query
        if (query.exec()) {
            qDebug() << "Empreinte updated successfully for user ID:" << idu;
        } else {
            qDebug() << "Error updating empreinte for user ID:" << idu;
            qDebug() << "Error details:" << query.lastError().text();
        }
}
void Arduino::update(QString currpos)
{
    QSqlQuery query;
    // Construct the SQL UPDATE query with placeholders for user ID and empreinte data
    QString queryString = "UPDATE sportifs SET curr_pos = :curr_pos "
                          "WHERE idu = 1";
    query.prepare(queryString);
    // Bind the user ID and empreinte data to the query placeholders
    query.bindValue(":idu", 1);
    query.bindValue(":curr_pos", currpos);
}
