#include "log.h"
#include "ui_log.h"


#include <iostream>
#include <sstream>
#include <iomanip>

using std::cout,std::endl;
using std::string;


Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
    setWindowTitle("日志");
    ui->log_edit->setReadOnly(true);
}

Log::~Log() {
    delete ui;
}


static string GetData(){
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time),"%Y/%m/%d %X");
    string ret = ss.str();
//    ret.erase(std::remove(ret.begin(),ret.end(),'\n'),ret.end());
    return ret;
}
void Log::AddLog(string message,string log_type) {
    string log = GetData() + log_type + " : " + message + "\n";
    logs += log;
    ui->log_edit->setText(logs.c_str());
    return;
}


void Log::Hide() {
    hide();
}

std::string Log::GetLogString() {
    return logs;
}

static void HighLight_(QTextEdit *text_edit,string word,HighLightType highlight_type) {
    QTextDocument *document = text_edit->document();
    QTextCursor cursor(document);
    QTextCharFormat format;
    switch (highlight_type) {

        case HighLightType::Wring:

            format.setBackground(Qt::yellow);
            break;
        case HighLightType::Error:
            format.setBackground(Qt::red);
            break;
        default:
            break;
    }
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document->find(word.c_str(), cursor);
        if (!cursor.isNull()) {
            cursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
            cursor.mergeCharFormat(format);
        }
    }

}
void HighLight(QTextEdit *text_edit){
    // TODO : 高亮未能正常显示
    QString search_text = "Wring";
    if (search_text.trimmed().isEmpty())
    {
        return;
    }
    else
    {
        QTextDocument *document = text_edit->document();
        bool found = false;
        QTextCursor highlight_cursor(document);
        QTextCursor cursor(document);
        //开始
        cursor.beginEditBlock();
        QTextCharFormat color_format(highlight_cursor.charFormat());
        color_format.setForeground(Qt::red);   //字体颜色
        color_format.setBackground(Qt::blue);  //背景颜色
        while (!highlight_cursor.isNull() && !highlight_cursor.atEnd())
        {
            //查找指定的文本，匹配整个单词
            highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
            if (!highlight_cursor.isNull())
            {
                if (!found)
                    found = true;
                highlight_cursor.mergeCharFormat(color_format);
            }
        }
        cursor.endEditBlock();
    }
//    HighLight_(text_edit,"[Wring]",HighLightType::Wring);
//    HighLight_(text_edit,"[Error]",HighLightType::Error);
//    QTextDocument *doc = text_edit->document();
//    QTextCursor highlight_cursor(doc);
//    QTextCharFormat plainFormat = highlight_cursor.charFormat();
//    QTextCharFormat colorFormat = plainFormat;
//    colorFormat.setForeground(Qt::red);
//
//    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
//        highlight_cursor = doc->find("Wring", highlight_cursor);
//        if (!highlight_cursor.isNull()) {
//            highlight_cursor.mergeCharFormat(colorFormat);
//        }
//    }
    return;
}

void Log::AddErrorLog(std::string error_message) {
    AddLog(error_message,"[Error]");
}
void Log::AddWringLog(std::string wring_message) {
    AddLog(wring_message,"[Wring]");
}


void Log::Show() {
    show();
    activateWindow();
    HighLight(ui->log_edit);
}

