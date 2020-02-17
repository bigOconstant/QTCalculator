#include "calculator.h"
#include "ui_calculator.h"

double calcVal= 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number((calcVal)));
    QPushButton *numButtons[10];
    for(int i = 0; i <10; ++i){
        QString buttName = "Button"+ QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumPressed()));
    }

    connect(ui->Add,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals,SIGNAL(released()),this,
            SLOT(EqualButton()));

    connect(ui->ChangeSign,SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));
    connect(ui->MemAdd,SIGNAL(released()),this,
            SLOT(MemoryButtonPressed()));
    connect(ui->MemGet,SIGNAL(released()),this,
            SLOT(RetrieveMemory()));

    connect(ui->Clear,SIGNAL(released()),this,SLOT(clearScrean()));
connect(ui->MemClear,SIGNAL(released()),this,SLOT(deleteMemory()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble()== 0)||(displayVal.toDouble()== 0.0)){
        ui->Display->setText(butval);
    }else{
        QString newVal = displayVal + butval;
        double dblNewBal = newVal.toDouble();
        QString outputhere = QString::number(dblNewBal,'g',16);
        ui->Display->setText(outputhere);
    }

}
void Calculator::clearScrean(){
    ui->Display->setText("");
}

void Calculator::deleteMemory(){
    this->memorybuttonvalue = 0;
}
void Calculator::MathButtonPressed(){
    divTrigger = false;
    addTrigger = false;
    multTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal,"*",Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }else if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else{
        subTrigger = true;
    }

    ui->Display->setText("");

}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }else {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    //Verify it is a number;
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplay = displayVal.toDouble();
        dblDisplay *= -1;
        ui->Display->setText(QString::number(dblDisplay,'g',16));
    }

}


void Calculator::MemoryButtonPressed(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        this->memorybuttonvalue = displayVal.toDouble();
    }
}
void Calculator::RetrieveMemory(){
    QString outputhere = QString::number(this->memorybuttonvalue,'g',16);
    ui->Display->setText(outputhere);
}
