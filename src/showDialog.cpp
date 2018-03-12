#include "showDialog.h"
#include "ui_showDialog.h"

ShowDialog::ShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDialog)
{
    ui->setupUi(this);
}

ShowDialog::~ShowDialog()
{
    delete ui;
}
