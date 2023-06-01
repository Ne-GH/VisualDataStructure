#include "Log.h"
#include "ui_Log.h"

#include <format>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <QTextEdit>

using std::string;

Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
    setWindowTitle("日志");
    ui->log_edit->setReadOnly(true);
    _flog.open("./log.txt",std::ios::in | std::ios::out | std::ios::trunc);
}

Log::~Log() {
    delete ui;
}


static string GetData(){
    using namespace::std::chrono;
    return std::format("{0:%x} {0:%T} ",current_zone()->to_local(system_clock::now())).substr(0,17);
}

void Log::AddLog(string message,string log_type) {
    string log = GetData() + log_type + " : " + message;
    ui->log_edit->append(log.c_str());

    _flog << log + "\n";
    _flog.flush();
}


void Log::Hide() {
    hide();
}

// TODO：高亮问题基本解决，但是无法高亮"[]"
static void HighLight_(QTextEdit *text_edit,const string& search_word,HighLightType highlight_type) {

    QTextDocument *document = text_edit->document();
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    switch (highlight_type) {
        case HighLightType::Wring :
            color_format.setForeground(Qt::black);   //字体颜色

            color_format.setBackground(Qt::yellow);  //背景颜色
            break;

        case HighLightType::Error :
            color_format.setForeground(Qt::black);   //字体颜色
            color_format.setBackground(Qt::red);  //背景颜色
            break;

        default:
            break;
    }
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_word.c_str(), highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull()) {
            if (!found)
                found = true;
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();

    return;
}
void HighLight(QTextEdit *text_edit){
    HighLight_(text_edit,"Wring",HighLightType::Wring);
    HighLight_(text_edit,"Error",HighLightType::Error);

    return;
}

void Log::AddErrorLog(std::string error_message) {
    AddLog(std::move(error_message),"[Error]");
}
void Log::AddWringLog(std::string wring_message) {
    AddLog(std::move(wring_message),"[Wring]");
}


void Log::Show() {
    show();
    activateWindow();
    HighLight(ui->log_edit);
}
// 重写虚函数resizeEvent
// 作用：使得日志窗口大小改变的时候，QTextEdit大小一起改变，始终铺满窗口
void Log::resizeEvent(QResizeEvent *event) {
    auto window_width = QWidget::width();
    auto window_height = QWidget::height();
    ui->log_edit->setFixedSize(window_width,window_height);
}

