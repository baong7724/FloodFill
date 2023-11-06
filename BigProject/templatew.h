#ifndef TEMPLATEW_H
#define TEMPLATEW_H

#include <QWidget>

namespace Ui {
class TemplateW;
}

class TemplateW : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateW(QWidget *parent = nullptr);
    ~TemplateW();

private:
    Ui::TemplateW *ui;
};

#endif // TEMPLATEW_H
