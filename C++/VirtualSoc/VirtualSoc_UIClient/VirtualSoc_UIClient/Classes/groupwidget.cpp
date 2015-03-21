#include "groupwidget.h"
#include "ui_groupwidget.h"

GroupWidget::GroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWidget)
{
    ui->setupUi(this);
}

GroupWidget::~GroupWidget()
{
    delete ui;
}

void GroupWidget::setUpWithGroup(Group g)
{
    QString name = QString::fromUtf8(g.groupName.c_str(), g.groupName.length());
    QString desc = QString::fromUtf8(g.groupDescription.c_str(), g.groupDescription.length());

    ui->groupNameLabel->setText(name);
    ui->groupDescLabel->setText(desc);
}
