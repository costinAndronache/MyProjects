#ifndef FORM_REGISTER_H
#define FORM_REGISTER_H

#include <QWidget>
#include "ApiComunicator.h"
#include "ChildWidgetListener.h"

namespace Ui {
class Form_Register;
}

class Form_Register : public QWidget, public ApiComunicatorListener
{
    Q_OBJECT
    
public:
    explicit Form_Register(QWidget *parent = 0);
    void didReceiveJSONFromComunicator(std::string &message);
    void setListener(ChildWidgetListener *listener);
    ~Form_Register();
    
private slots:
    void on_registerBtn_clicked();
    void on_loginBtn_clicked();

private:
    Ui::Form_Register *ui;
    Form_Register *registerForm;
    ChildWidgetListener *_listener;
};

#endif // FORM_REGISTER_H
