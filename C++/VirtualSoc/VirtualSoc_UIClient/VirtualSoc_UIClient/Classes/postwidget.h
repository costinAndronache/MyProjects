#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include "userdefaults.h"

namespace Ui {
class PostWidget;
}

class PostWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PostWidget(QWidget *parent = 0);
    void setupWithPost(Post p);

    ~PostWidget();
    
private:
    Ui::PostWidget *ui;
};

#endif // POSTWIDGET_H
