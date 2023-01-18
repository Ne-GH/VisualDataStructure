#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <string>
#include <chrono>

namespace Ui {
    class Log;
}
enum class HighLightType{
    None,Wring,Error
};
class Log : public QDialog {
    Q_OBJECT

public:
    explicit Log(QWidget *parent = nullptr);
    ~Log();

    void AddLog(std::string,std::string log_type = "");
    void AddErrorLog(std::string);
    void AddWringLog(std::string);
    void Show();
    void Hide();
    std::string GetLogString();

private:
    Ui::Log *ui;
    std::string logs;

};

#endif // LOG_H
