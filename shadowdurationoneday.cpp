//Простое вычисление количество тени в секундах(ГСО)
#include "shadowdurationoneday.h"
#include "ui_shadowdurationoneday.h"
#include "onedaygso.h"
#include <exception>

ShadowDurationOneDay::ShadowDurationOneDay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowDurationOneDay)
{
    ui->setupUi(this);
}

ShadowDurationOneDay::~ShadowDurationOneDay()
{
    delete ui;
}
//--------------------------------------------------------------
//Универсальная система проверки нововведенных блоков кода. Для проверки подставить закомментированный блок try в
//в новые блоки кода, пронумеровать их в std::cerr и запустить компиляцию программы.
//Блок проверяет исключения, которые могут вызвать неправильный результат в скомпилированной программе!
///class MyException : public std::exception {
///private:
///    std::string message;
///public:
///    MyException(const std::string& msg) :message(msg) {}

///    virtual const char* what() const throw() {
///        return message.c_str();
///    }
///    virtual ~MyException() throw() {}
///};

////try {
//    //код
////}
////catch (const MyException& e) {
////    std::cerr << "В блоке № ошибка. Проверьте этот блок" << e.what() << std::endl;
////}
//--------------------------------------------------------------


void ShadowDurationOneDay::on_pushButton_clicked()
{
    QDate date = ui->dateEdit->date();
    OneDayGSO oneDayGSO = OneDayGSO();
    double result = oneDayGSO.CountShadowDuration(date);
    if (result == -1) ui->label_4->setText("В этот день тень отсутвует");
    else ui->label_4->setText(QString::number(result) + " секунд");
}
