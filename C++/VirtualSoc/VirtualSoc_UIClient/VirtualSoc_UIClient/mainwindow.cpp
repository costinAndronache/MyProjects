#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form_home.h"
#include "hometabwidget.h"
#include "groupsandpostswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginForm = new Form_Home(this);
    registerForm = new Form_Register(this);
    mainWidget = new GroupsAndPostsWidget(this);

    loginForm->setListener(this);
    registerForm->setListener(this);
    mainWidget->setListener(this);

    registerForm->hide();
    mainWidget->hide();
    this->setCentralWidget(loginForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::childWidgetWishesToClose(QWidget *theChild)
{
    qDebug()<<"in child wishes to close";
    if(theChild == loginForm)
    {
        qDebug()<<"the child is the login form";
        loginForm->hide();
        registerForm->show();
        //this->setCentralWidget(registerForm);
    }
    else
        if(theChild == registerForm)
        {
            qDebug()<<"the child is the register form";
            registerForm->hide();
            loginForm->show();

           }
     else
        {
            mainWidget->hide();
            loginForm->show();
        }

}

void  MainWindow::loginWidgetFinishedLoggingIn(QWidget *theChild)
{
    loginForm->hide();
    mainWidget->show();
}
