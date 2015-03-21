#include "form_home.h"
#include "ui_form_home.h"

#include <QMainWindow>
#include <string>
#include "CommonConstants.h"
using namespace std;

Form_Home::Form_Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Home)
{
    ui->setupUi(this);
    _listener = NULL;
}

Form_Home::~Form_Home()
{
    delete ui;
}

void Form_Home::setListener(ChildWidgetListener *listener)
{
    this->_listener = listener;
}

void Form_Home::on_loginBtn_clicked()
{
    string username, password;
    username = ui->usernameTextField->text().toStdString();
    password = ui->passwordTextField->text().toStdString();

    string method = kRequestLoginKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestLogin(username, password);
}

void Form_Home::on_registerBtn_clicked()
{
    if(this->_listener != NULL)
    {
      this->_listener->childWidgetWishesToClose(this);
    }

    string method = kRequestLoginKey;
    ApiComunicator::sharedInstance()->removeListenerForMethod(this, method);

    if (_listener != NULL)
    {
        _listener->childWidgetWishesToClose(this);
    }
}

void Form_Home::didReceiveJSONFromComunicator(string &message)
{
    Json::Value root;
    Json::Value result;
    Json::Reader reader;

    reader.parse(message, root, false);
    result = root[kResultOfRequestKey];
    int succes = result[kSuccessKey].asInt();

    if(succes == 1)
    {
        UserDefaults *defaults = UserDefaults::sharedInstance();
        defaults->isLoggedIn = true;
        defaults->firstName = result[kFirstNameKey].asString();
        defaults->lastName = result[kLastNameKey].asString();
        defaults->userID = result[kUserIDKey].asInt();
        defaults->username = result[kUsernameKey].asString();

        ui->titleLabel->setText("Login succesful.");

        _listener->loginWidgetFinishedLoggingIn(this);
    }
    else
    {
        ui->titleLabel->setText("Login failed.");
    }
}

void Form_Home::on_pushButton_clicked()
{
    UserDefaults::sharedInstance()->isLoggedIn = false;
    ui->titleLabel->setText("VirtualSoc Login");

}
