#include "widget.h"
#include "ui_widget.h"
#include <QSettings>

Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("CUIT CHAT");
    socket = new QTcpSocket;
    QSettings settingsread("config.ini",QSettings::IniFormat);
    QString ip = settingsread.value("DevOption/IP").toString();
    QString username = settingsread.value("DevOption/username").toString();
    qDebug()<<"username"<<username;
    if(!username.isEmpty())
    {
       ui->userLineEdit->setText(username);
       ui->checkBox->setChecked(true);
    }

    if(!ip.isEmpty())
    {
        IP=ip;
        socket->connectToHost(QHostAddress(IP), 8000);
    }

    connect(socket, &QTcpSocket::connected, this, &Widget::connect_success);
    connect(socket, &QTcpSocket::readyRead, this, &Widget::server_reply);

    ui->lineEdit->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton->setStyleSheet("border-image: url(:/btn_off.png);");

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

}

Widget::~Widget()
{
    delete ui;
}

void Widget::connect_success()
{
    QString det2 = "连接服务器成功";
    ui->pushButton->setStyleSheet("border-image: url(:/btn_on.png);");
    det2 = tr("<font size='10' color='black'>") + det2+tr("</font>");
    QMessageBox::warning(this, "提示", det2);
}

void Widget::on_registerButton_clicked()
{
    QString username = ui->userLineEdit->text();
    QString password = ui->passwdLineEdit->text();

    QJsonObject obj;
    obj.insert("cmd", "register");
    obj.insert("user", username);
    obj.insert("password", password);

    QByteArray ba = QJsonDocument(obj).toJson();
    socket->write(ba);
}

void Widget::server_reply()
{
    QByteArray ba = socket->readAll();
    QJsonObject obj = QJsonDocument::fromJson(ba).object();
    QString cmd = obj.value("cmd").toString();
    if (cmd == "register_reply")
    {
        client_register_handler(obj.value("result").toString());
    }
    else if (cmd == "login_reply")
    {
        client_login_handler(obj.value("result").toString(),
        obj.value("friend").toString(), obj.value("group").toString());
    }
}

void Widget::client_register_handler(QString res)
{
    if (res == "success")
    {
        QString det2 = "注册成功";
        det2 = tr("<font size='10' color='black'>") + det2+tr("</font>");
        QMessageBox::warning(this, "提示", det2);
    }
    else if (res == "failure")
    {
        QString det2 = "注册失败";
        det2 = tr("<font size='10' color='black'>") + det2+tr("</font>");
        QMessageBox::warning(this, "提示", det2);
    }
}

void Widget::on_loginButton_clicked()
{
    QString username = ui->userLineEdit->text();
    QString password = ui->passwdLineEdit->text();
    if(username.isEmpty())
    {
        QString det = "请输入用户名";
        det = tr("<font size='10' color='black'>") + det+tr("</font>");
        QMessageBox::warning(this, "提示", det);
        return;
    }

    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("DevOption"); //
    settings.setValue("username",username);
    settings.endGroup();

    QJsonObject obj;
    obj.insert("cmd", "login");
    obj.insert("user", username);
    obj.insert("password", password);




    userName = username;

    QByteArray ba = QJsonDocument(obj).toJson();
    socket->write(ba);
}

void Widget::client_login_handler(QString res, QString fri, QString group)
{
    if (res == "user_not_exist")
    {
        QString det2 = "用户不存在";
        det2 = tr("<font size='10' color='black'>") + det2+tr("</font>");
        QMessageBox::warning(this, "提示", det2);
    }
    else if (res == "password_error")
    {
        QString det2 = "密码错误";
        det2 = tr("<font size='10' color='black'>") + det2+tr("</font>");
        QMessageBox::warning(this, "提示", det2);
    }
    else if (res == "success")
    {
        this->hide();
        socket->disconnect(SIGNAL(readyRead()));
        Chatlist *c = new Chatlist(socket, fri, group, userName);
        c->chatlistIP = IP;
        c->setWindowTitle(userName);
        c->show();
    }
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}

void Widget::on_toolButton_2_clicked()   //最小化按钮
{
    showMinimized();
}


void Widget::on_toolButton_clicked()
{
    close();
}

void Widget::on_pushButton_2_clicked() //确定IP
{
    IP = ui->lineEdit->text();
    QSettings settings("config.ini",QSettings::IniFormat);
    settings.beginGroup("DevOption"); //
    settings.setValue("IP",IP);
    settings.endGroup();
    socket->connectToHost(QHostAddress(IP), 8000);
    ui->lineEdit->setVisible(false);
    ui->pushButton_2->setVisible(false);
}


void Widget::on_pushButton_clicked() //点击开启lineedit和确定按钮
{
    ui->lineEdit->setVisible(true);
    ui->pushButton_2->setVisible(true);
}



