#include "userinfowidget.h"
#include "ui_userinfowidget.h"

UserInfoWidget::UserInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoWidget)
{
    ui->setupUi(this);
}

UserInfoWidget::~UserInfoWidget()
{
    delete ui;
}

void UserInfoWidget::setupWithUserInfo(User u)
{
    QString firstname = QString::fromUtf8(u.firstName.c_str(), u.firstName.length());
    QString lastName = QString::fromUtf8(u.lastName.c_str(), u.lastName.length());
    QString someInfo = QString::fromLatin1(u.someInfo.c_str(), u.someInfo.length());

    ui->firstNameLabel->setText(firstname);
    ui->lastNameLabel->setText(lastName);
    ui->infoLabel->setText(someInfo);
}

void UserInfoWidget::populateWithInfoAboutUserID(int userID)
{
    string method = kRequestUserInfo;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestUserInfo(userID);
}

void UserInfoWidget::didReceiveJSONFromComunicator(string &message)
{
    Json::Reader reader;
    Json::Value root;
    Json::Value result;

    reader.parse(message, root, false);


    result = root[kResultOfRequestKey];
    int succes = result[kSuccessKey].asInt();
    if(succes == 1)
    {
        User u = User::friendFromJsonValue(result);
        this->setupWithUserInfo(u);
    }
    else
    {
        ui->infoLabel->setText("Error");
    }

    string method = kRequestUserInfo;
    ApiComunicator::sharedInstance()->removeListenerForMethod(this, method);
}
