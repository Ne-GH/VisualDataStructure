/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/08/18 23:15
*******************************************************************************/


#ifndef VISUALDATASTRUCTURE_ABOUTDIALOG_H
#define VISUALDATASTRUCTURE_ABOUTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AboutDialog; }
QT_END_NAMESPACE

class AboutDialog : public QDialog {
Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);

    ~AboutDialog() override;

private:
    Ui::AboutDialog *ui;
};


#endif //VISUALDATASTRUCTURE_ABOUTDIALOG_H
