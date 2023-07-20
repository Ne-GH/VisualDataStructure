/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/19 00:28
*******************************************************************************/
#include "Setting.h"
#include "ui_Setting.h"

#include <QColorDialog>
#include <QPushButton>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
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
                auto p = QColorDialog::getColor(Qt::red, ui->setting_widget, "选择颜色");
                qDebug() << p;
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
 * 使用Lua加载配置文件
*******************************************************************************/
void Setting::LoadSettingFile() {
    lua_State *l = luaL_newstate();
    if (l == nullptr) {
        return;
    }

    int bret = luaL_loadfile(l, "./.config.lua");
    if (bret) {
        qDebug() << "加载配置文件失败";
        return;
    }

    bret = lua_pcall(l, 0, 0, 0);
    if (bret) {
        qDebug() << "pcall 失败";
        return;
    }

// 获取并保存默认颜色值
    const char* DefaultColor = nullptr;
    lua_getglobal(l, "Color");
    lua_getfield(l, -1, "default");
    DefaultColor = lua_tostring(l, -1);
    lua_pop(l, 1); // 弹出栈顶元素，现在栈为空

// 修改 "default" 字段的值为 "#ff0000"
    lua_getglobal(l, "Color");
    lua_pushstring(l, "#ff0000");
    lua_setfield(l, -2, "default");

// 获取并保存新的默认颜色值
    const char* NewDefaultColor = nullptr;
    lua_getglobal(l, "Color");
    lua_getfield(l, -1, "default");
    NewDefaultColor = lua_tostring(l, -1);
    lua_pop(l, 1); // 弹出栈顶元素，现在栈为空

// 输出结果
    qDebug() << "Original Default Color: " << DefaultColor;
    qDebug() << "New Default Color: " << NewDefaultColor;

// 关闭 Lua 状态
    lua_close(l);

}




