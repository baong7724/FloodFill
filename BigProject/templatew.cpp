#include "templatew.h"
#include "ui_templatew.h"

TemplateW::TemplateW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateW)
{
    ui->setupUi(this);
}

TemplateW::~TemplateW()
{
    delete ui;
}
