#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H
#include "userdefaults.h"
#include "ApiComunicator.h"
#include <QWidget>

namespace Ui {
class UserInfoWidget;
}

class UserInfoWidget : public QWidget, ApiComunicatorListener
{
    Q_OBJECT
    
public:
    explicit UserInfoWidget(QWidget *parent = 0);
    ~UserInfoWidget();
    void setupWithUserInfo(User u);
    void populateWithInfoAboutUserID(int userID);
    void didReceiveJSONFromComunicator(string &message);

private:
    Ui::UserInfoWidget *ui;
};

#endif // USERINFOWIDGET_H
