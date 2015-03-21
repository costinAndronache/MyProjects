#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Queue.h"
#include "form_home.h"
#include "form_register.h"
#include "groupsandpostswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ChildWidgetListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void childWidgetWishesToClose(QWidget *theChild);
    void loginWidgetFinishedLoggingIn(QWidget *theChild);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Form_Home *loginForm;
    Form_Register *registerForm;
    GroupsAndPostsWidget *mainWidget;

};

#endif // MAINWINDOW_H
