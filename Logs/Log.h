#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <string>
#include <memory>
#include <fstream>


namespace Ui {
    class Log;
}
enum class HighLightType{
    None,Wring,Error
};
class Log : public QDialog {
    Q_OBJECT

    explicit Log(QWidget *parent = nullptr);
    Log(const Log&) = default;
    Log& operator = (const Log&) = default;
    std::fstream _flog;
private slots:
    void resizeEvent(QResizeEvent *event);
public:
    ~Log();

    void AddLog(std::string,std::string log_type = "");
    void AddErrorLog(std::string);
    void AddWringLog(std::string);
    void Show();
    void Hide();
    std::string GetLogString();

    static Log &GetInstance() {
        static std::unique_ptr<Log> instance(new Log) ;
        return *instance;
    }
private:
    Ui::Log *ui;
    std::string logs;

};

#define LOG Log::GetInstance()
#endif // LOG_H
