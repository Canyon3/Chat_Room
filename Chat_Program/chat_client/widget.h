#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "chatlist.h"
#include <QDialog>

namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void connect_success();
    void server_reply();

    void on_registerButton_clicked();

    void on_loginButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void client_register_handler(QString);
    void client_login_handler(QString, QString, QString);

    Ui::Widget *ui;
    QTcpSocket *socket;
    QString userName;
    QString IP;

    QPoint p;
};

#endif // WIDGET_H
