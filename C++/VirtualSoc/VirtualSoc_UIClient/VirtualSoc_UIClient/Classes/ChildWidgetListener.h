#ifndef CHILDWIDGETLISTENER_H
#define CHILDWIDGETLISTENER_H

#include <QtWidgets>
#include <iostream>

class ChildWidgetListener
{
public:
    virtual void childWidgetWishesToClose(QWidget *theChild)
    {
        std::cout<<"Empty child widget listener.";
    }

    virtual void loginWidgetFinishedLoggingIn(QWidget *theChild)
    {
        std::cout<<"yuhuu .. ";
    }
};

#endif // CHILDWIDGETLISTENER_H
