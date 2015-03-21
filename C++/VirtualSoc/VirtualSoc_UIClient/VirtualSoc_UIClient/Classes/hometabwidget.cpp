#include "hometabwidget.h"
#include "ui_hometabwidget.h"

HomeTabWidget::HomeTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeTabWidget)
{
    ui->setupUi(this);
    loginForm = new Form_Home(this);
    registerForm = new Form_Register(this);
    mainWidget = new GroupsAndPostsWidget(this);

    loginForm->setListener(this);
    registerForm->setListener(this);
    mainWidget->setListener(this);

    mainWidget->hide();
    registerForm->hide();
}

HomeTabWidget::~HomeTabWidget()
{
    delete ui;
}

void HomeTabWidget::childWidgetWishesToClose(QWidget *theChild)
{
    if(theChild == loginForm)
    {
        loginForm->hide();
        registerForm->show();
    }
    else
        if(theChild == registerForm)
        {
            registerForm->hide();
            loginForm->show();
           }
     else
        {
            mainWidget->hide();
            loginForm->show();
        }

}

void HomeTabWidget::loginWidgetFinishedLoggingIn(QWidget *theChild)
{
    loginForm->hide();
    mainWidget->show();
}
