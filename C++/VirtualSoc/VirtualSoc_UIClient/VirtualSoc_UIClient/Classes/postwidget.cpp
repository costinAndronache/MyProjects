#include "postwidget.h"
#include "ui_postwidget.h"

PostWidget::PostWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostWidget)
{
    ui->setupUi(this);
}

PostWidget::~PostWidget()
{
    delete ui;
}

void PostWidget::setupWithPost(Post p)
{
    QString contents = QString::fromUtf8(p.contents.c_str(), p.contents.length());
    ui->contentsLabel->setText(contents);
}
