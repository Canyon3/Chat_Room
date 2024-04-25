#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDialog>

namespace Ui {
class Addfriend;
}

class Addfriend : public QDialog
{
    Q_OBJECT

public:
    explicit Addfriend(QTcpSocket *s, QString u, QWidget *parent = 0);
    ~Addfriend();

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::Addfriend *ui;
    QTcpSocket *socket;
    QString userName;
};

#endif // ADDFRIEND_H
