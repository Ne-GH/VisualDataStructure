/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/19 00:28
*******************************************************************************/
#include "Setting.h"
#include "ui_Setting.h"

#include <QColorDialog>
#include <QPushButton>
#include <filesystem>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>



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

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,9);

    QObject::connect(ui->listWidget,&QListWidget::itemSelectionChanged,[&]{
        switch (ui->listWidget->currentRow()) {
            case 0: {
                QJsonObject tmp_json    ;
                QColorDialog colorDialog;
                QColor selected_color;
                if (colorDialog.exec() == QColorDialog::Accepted) {
                    // 用户选择了颜色
                    selected_color = colorDialog.currentColor();
                    tmp_json["color"] = selected_color.name();
                } else {
                    // 用户没有选择颜色
                }

                for (auto obj : tmp_json) {
                    qDebug() << obj;
                }
                if (!tmp_json.empty()) {
                    qDebug() << "有配置信息未保存";

                }
                return ;
            }

        }
    });


    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok),&QPushButton::clicked,[=]{

        qDebug() << "1";
    });

    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Cancel),&QPushButton::clicked,[=]{

        qDebug() << "2";
    });
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
        // 创建JSON对象
        QJsonObject jsonObject;
        jsonObject["name"] = "张三";
        QJsonDocument jsonDocument(jsonObject);
        QFile file(file_path.c_str());
        if (file.open(QIODevice::WriteOnly)) {
            file.write(jsonDocument.toJson());
            file.close();
            qDebug() << "JSON文件已成功创建并保存。";
        }
        else {
            qDebug() << "无法创建或保存JSON文件。";
        }
        return;
    }

    // 打开JSON文件
    QFile file(file_path.c_str());
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开JSON文件。";
        return;
    }

    // 读取JSON数据
    QByteArray jsonData = file.readAll();
    file.close();

    // 解析JSON数据
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    if (jsonDocument.isNull()) {
        qDebug() << "无法解析JSON数据。";
    }

    // 将JSON数据转换为JSON对象
    QJsonObject jsonObject = jsonDocument.object();

    // 获取JSON数据并进行处理
    QString name = jsonObject["name"].toString();
    int age = jsonObject["age"].toInt();
    QString city = jsonObject["city"].toString();

    qDebug() << "姓名：" << name;
    qDebug() << "年龄：" << age;
    if (jsonObject.contains("city")) {
        qDebug() << "城市：" << city;
    }
    else {
        qDebug() << "2" ;
    }





}




