/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/19 00:24
*******************************************************************************/


#ifndef SETTING_H
#define SETTING_H


#include <QDialog>
#include <QColor>
namespace Ui{
    class Setting;
}
class Setting : public QDialog{
    Q_OBJECT
private:
    Ui::Setting *ui;
    QColor _item_color = DefaultColor;

protected:
public:
    inline static QColor DefaultColor = "#00aaff";


    explicit Setting(QWidget *parent = nullptr);
    ~Setting() override;
    void LoadSettingFile();




};


#endif
