/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/08/18 23:15
*******************************************************************************/


#include <QDesktopServices>
#include "AboutDialog.h"
#include "ui_AboutDialog.h"


AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);

    setWindowTitle("关于");
    ui->image_label->setScaledContents(true);
    ui->image_label->setPixmap(QPixmap(":/Resource/About.png"));
    ui->image_label->setMaximumSize(80,80);

    ui->textBrowser->setText(
            (std::string("") +
            "<center>" +
            "<h2>VisualStructure" + "<br>" +
            "当前版本为: v" + VERSION + "</h2>" +
            "支持的数据结构有:" + "<br>" +
            "数组" + "<br>" +
            "栈" + "<br>" +
            "队列" + "<br>" +
            "链表" + "<br>" +
            "平衡树" + "<br>" +

            "<br>" +
            "支持的排序有:" + "<br>" +
            "冒泡排序" + "<br>" +
            "std::sort排序" + "<br>" +
            "选择排序" + "<br>" +
            "插入排序" + "<br>" +
            "快速排序" + "<br>" +
            "归并排序" + "<br>" +

            "<br>" +
            "项目地址为: " + "<a href=\"https://github.com/Ne-GH/VisualDataStructure\">" + "GitHub地址" + "</a><br>" +
            "作者: " + "<a href=\"https://github.com/Ne-GH\">" + "Ne-GH" + "</a>" +
            "</center>"
            ).c_str());
    connect(ui->textBrowser, &QTextBrowser::anchorClicked, this, [=](const QUrl url) {
        QDesktopServices::openUrl(url);
    });
    resize(400,300);
}

AboutDialog::~AboutDialog() {
    delete ui;
}
