#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <string>


namespace Ui {
    class Log;
}
enum class HighLightType{
    None,Wring,Error
};
class Log : public QDialog {
    Q_OBJECT

private slots:
    void resizeEvent(QResizeEvent *event);
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
