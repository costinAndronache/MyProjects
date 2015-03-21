#include "form_register.h"
#include "ui_form_register.h"

#include "ApiComunicator.h"
#include "CommonConstants.h"
#include <json/json.h>
#include <string>

Form_Register::Form_Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Register)
{
    ui->setupUi(this);

    std::string method = kRequestRegisterKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    _listener = NULL;
}

Form_Register::~Form_Register()
{
    delete ui;
}

void Form_Register::on_registerBtn_clicked()
{
    std::string username, password, firstName, lastName, someInfo;
    QString    qsAdminCode;

    username = ui->usernameTF->text().toStdString();
    password = ui->passwordTF->text().toStdString();
    firstName = ui->firstNameTF->text().toStdString();
    lastName = ui->lastNameTF->text().toStdString();
    someInfo = ui->someInfoTF->text().toStdString();
    qsAdminCode = ui->adminCodeTF->text();

    if(username.length() == 0 || password.length() == 0 || firstName.length() == 0
            || lastName.length() == 0 || someInfo.length() == 0)
    {
        ui->resultLabel->setText(QString("Please complete all the required fields."));
        return;
    }
    int adminCode = qsAdminCode.toInt();

    ApiComunicator::sharedInstance() -> requestRegister(username, password, firstName, lastName, someInfo, adminCode);
}

void Form_Register::didReceiveJSONFromComunicator(std::string &message)
{
    Json::Value root;
    Json::Reader reader;
    Json::Value result;

    reader.parse(message, root, false);
    result = root[kResultOfRequestKey];
    int succes = result[kSuccessKey].asInt();

    if( succes == 1)
    {
        ui->resultLabel->setText("Registered successfully!");
    }
    else
    {
        string errorDetails = result[kErrorDetailsKey].asString();

        QString qs = QString::fromUtf8(errorDetails.c_str(), errorDetails.length());
        ui->resultLabel->setText(qs);
    }
}

void Form_Register::on_loginBtn_clicked()
{
    std::string method = kRequestRegisterKey;

    if(this->_listener != NULL)
    {
        this->_listener->childWidgetWishesToClose(this);
    }
}

void Form_Register::setListener(ChildWidgetListener *listener)
{
    this->_listener = listener;
}
