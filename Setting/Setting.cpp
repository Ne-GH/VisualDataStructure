/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/19 00:28
*******************************************************************************/
#include "Setting.h"
#include "ui_Setting.h"

#include <QColorDialog>
#include <QPushButton>
#include <filesystem>



/*******************************************************************************
 * 参数：当前颜色
 * 返回值：选择的颜色，如果没有选择有效颜色，返回当前颜色
*******************************************************************************/
QColor GetColor(QColor cur_color,QWidget *parent) {
    QColor color = QColorDialog::getColor(Qt::red, parent, "选择颜色");
    if (color.isValid())
        return color;
    return cur_color;
}

Setting::Setting(QWidget *parent) : QDialog(parent) ,ui(new Ui::Setting) {
    ui->setupUi(this);




    // ui->splitter->setStretchFactor(0,1);
    // ui->splitter->setStretchFactor(1,9);
    //
    // QObject::connect(ui->listWidget,&QListWidget::itemSelectionChanged,[&]{
    //     switch (ui->listWidget->currentRow()) {
    //         case 0: {
    //
    //             QColorDialog colorDialog;
    //             QColor selected_color;
    //             if (colorDialog.exec() == QColorDialog::Accepted) {
    //                 // 用户选择了颜色
    //                 selected_color = colorDialog.currentColor();
    //             } else {
    //                 // 用户没有选择颜色
    //             }
    //
    //
    //             return ;
    //         }
    //
    //     }
    // });
    //
    //
    // QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok),&QPushButton::clicked,[=]{
    //
    //     qDebug() << "1";
    // });
    //
    // QObject::connect(ui->buttonBox->button(QDialogButtonBox::Cancel),&QPushButton::clicked,[=]{
    //
    //     qDebug() << "2";
    // });
}

Setting::~Setting() {

}

/*******************************************************************************
 * 使用JSON加载配置文件,第一个参数默认为"./config.json"
*******************************************************************************/
void Setting::LoadSettingFile(std::string file_path) {
    using namespace std::filesystem;

    if (!exists(file_path)) {
        qDebug() << "配置文件不存在";
        // TODO 创建默认JSON配置文件
        return;
    }

    // TODO 加载配置文件




}




