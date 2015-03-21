#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>
#include "userdefaults.h"

namespace Ui {
class GroupWidget;
}

class GroupWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GroupWidget(QWidget *parent = 0);
    void setUpWithGroup(Group g);
    ~GroupWidget();
    
private:
    Ui::GroupWidget *ui;

};

#endif // GROUPWIDGET_H
