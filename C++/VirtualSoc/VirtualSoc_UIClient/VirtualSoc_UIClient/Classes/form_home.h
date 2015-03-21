#ifndef FORM_HOME_H
#define FORM_HOME_H

#include <QWidget>
#include "form_register.h"
#include "ChildWidgetListener.h"
#include "ApiComunicator.h"
#include "userdefaults.h"

namespace Ui {
class Form_Home;
}

class Form_Home : public QWidget, public ApiComunicatorListener
{
    Q_OBJECT
    
public:
    explicit Form_Home(QWidget *parent = 0);
    void setListener(ChildWidgetListener *listener);
    void didReceiveJSONFromComunicator(string &message);
    ~Form_Home();
    
private slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();


    void on_pushButton_clicked();

private:
    Ui::Form_Home *ui;

    ChildWidgetListener *_listener;
};

#endif // FORM_HOME_H
