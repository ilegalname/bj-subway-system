#include "park.h"
#include "ui_park.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <set>
#include <tuple>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QString>
#include <string.h>
using namespace std;

string desti;
string current;

park::park(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::park)
{
    ui->setupUi(this);
}

park::~park()
{
    delete ui;
}

void park::on_pushButton_5_clicked()
{
    desti="����ƥ�˹�԰";
    cout<<desti<<endl;
}

void park::on_pushButton_6_clicked()
{
    desti="�찲�Ŷ�";
    cout<<desti<<endl;
}

void park::on_pushButton_clicked()
{
    desti="�찲�Ŷ�";
    cout<<desti<<endl;
}

void park::on_pushButton_3_clicked()
{
    desti="Բ��԰";
    cout<<desti<<endl;
}

void park::on_pushButton_4_clicked()
{
    desti="������";
    cout<<desti<<endl;
}

void park::on_pushButton_2_clicked()
{
    desti="�������";
    cout<<desti<<endl;
}

void park::on_pushButton_7_clicked()
{
    desti="�����ͬ";
    cout<<desti<<endl;
}

void park::on_pushButton_8_clicked()
{
    desti="����԰";
    cout<<desti<<endl;
}

void park::on_pushButton_9_clicked()
{
    desti="������";
    cout<<desti<<endl;
}

void park::on_pushButton_10_clicked()
{
    QString startstation = ui->lineEdit->text();
    QByteArray cdata = startstation.toLocal8Bit();
    current = string(cdata);
}
