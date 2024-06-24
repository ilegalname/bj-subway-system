#include "newwindow.h"
#include "ui_newwindow.h"
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
#include <cmath>
#include <QMessageBox>
#include <sstream>
#include <QDebug>

using namespace std;
const double EARTH_RADIUS = 6371000.0; // 地球半径（单位：米）
const double pi = M_PI;

class Station {
public:
    string name;
    string line;
    double longtitude, latitude;
    int number;
    int ifchange;

    Station(int num, string n, string l, float i, float j, int change) : number(num),name(n), line(l), longtitude(i), latitude(j) , ifchange(change) {}
};

class Edge {
public:
    Station* start;
    Station* end;
    int weight;
    Edge(Station* s, Station* e, int w) : start(s), end(e), weight(w) {}
    int counttime() {
        if (start->line == "1号线")
            return weight / 567;
        else if (start->line == "2号线")
            return weight / 525;
        else if (start->line == "4号线")
            return weight / 590;
        else if (start->line == "5号线")
            return weight / 533;
        else if (start->line == "6号线")
            return weight / 622;
        else if (start->line == "8号线")
            return weight / 573;
        else if (start->line == "9号线")
            return weight / 523;
        else if (start->line == "10号线")
            return weight / 548;
        else if (start->line == "13号线")
            return weight / 708;
    }
};

class Line {
public:
    int red, blue, green;
    string name;
    Line(string n, int r, int g, int b) :name(n), red(r), green(g), blue(b){}
};

extern vector<Station*> stations;
extern vector<Edge*> edges;
extern vector<Line*> lines;

double deg2rad(double deg);
double calculateDistance(double lat1, double lng1, double lat2, double lng2);


newwindow::newwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newwindow)
{
    ui->setupUi(this);
}

newwindow::~newwindow()
{
    delete ui;
}

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

static string qstr2str(const QString str_1)
{
    string str;
    str = str_1.toLocal8Bit().constData();
    return str;
}

void newwindow::on_pushButton_clicked()
{
    int current_num=0;
    int count=0;
    std::vector<Station*> reccordStation;
    //reccordStation.clear();
    ifstream stationfile("station.txt",ios::in);
    string num2,name2,line2,lont2,lat2,change2;
    while (stationfile>>num2>>name2>>line2>>lont2>>lat2>>change2){
        int n,c;
        double lo,la;
        istringstream ss(num2);
        ss>>n;
        istringstream sslon(lont2);
        sslon>>lo;
        istringstream ssla(lat2);
        ssla>>la;
        istringstream ssc(change2);
        ssc>>c;
        Station* station = new Station(n,name2,line2,lo,la,c);
        reccordStation.push_back(station);
    }
    istringstream ss(num2);
    ss>>current_num;
    cout<<num2<<endl;
    stationfile.close();
    cout << current_num << endl;

    if(!(ui->lineEdit_5->text().isEmpty()||ui->lineEdit_6->text().isEmpty()||ui->lineEdit_7->text().isEmpty())){
        QString stationname = ui->lineEdit_5->text();
        string name = qstr2str(stationname);
        QString linename = ui->comboBox->currentText();
        string linee = qstr2str(linename);
        QString latitude = ui->lineEdit_6->text();
        double lat = latitude.toDouble();
        QString longtitude = ui->lineEdit_7->text();
        double longt = longtitude.toDouble();
        string num1,name1,line1,lont1,lat1,change1;
        QString neighbor1n = ui->comboBox_2->currentText();
        string neighbor1 = qstr2str(neighbor1n);
        QString neighbor2n = ui->comboBox_3->currentText();
        string neighbor2 = qstr2str(neighbor2n);
        QString distance1 = ui->lineEdit_4->text();
        string d1 = qstr2str(distance1);
        QString distance2 = ui->lineEdit_2->text();
        string d2 = qstr2str(distance2);

        ifstream stationfile2("station.txt",ios::in);
        while (stationfile2>>num1>>name1>>line1>>lat>>longt>>change1){
            if(name1==name){
                QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("该站点已存在，请重新输入"));
                break;
            }
            else{
                count++;
            }
        }
        stationfile2.close();
        int nei1,nei2;
        double nei1la,nei1lo,nei2la,nei2lo;

        cout<<"latitude"<<lat<<endl;
        cout<<"longtitude"<<longt<<endl;

        for(int i=0;i<reccordStation.size();i++){
            if(reccordStation[i]->name==neighbor1){
                nei1=reccordStation[i]->number;
                nei1la=reccordStation[i]->latitude;
                nei1lo=reccordStation[i]->longtitude;
            }
            else if(reccordStation[i]->name==neighbor2){
                nei2=reccordStation[i]->number;
                nei2la=reccordStation[i]->latitude;
                nei2lo=reccordStation[i]->longtitude;
            }
        }

        double dd1=calculateDistance(nei1la,nei1lo,lat,longt);
        double dd2=calculateDistance(nei2la,nei2lo,lat,longt);

        cout<<"距离1"<<" "<<dd1<<endl;
        cout<<"距离2"<<" "<<dd2<<endl;

        cout<<current_num<<" "<<count<<endl;
        if(count==current_num+1){
            cout<<"i am here"<<endl;
            fstream inputstation;
            inputstation.open("station.txt",ios::app);
            inputstation << current_num+1 << "\t" << name << "\t" <<linee<<"\t"<< longt<<"\t"<<lat<<"\t"<<0<<endl;
            inputstation.close();
            fstream editDdge;
            editDdge.open("edge.txt",ios::app);
            if(neighbor1!="无"){
                editDdge<<nei1<<"\t"<<current_num+1<<"\t"<<d1<<endl;
            }
            if(neighbor2!="无"){
                editDdge<<nei2<<"\t"<<current_num+1<<"\t"<<d2<<endl;
            }
            editDdge.close();
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("成功添加站点"));

        }
    }
    else{
        QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("站点信息不完整，请重新输入"));
    }
}

void newwindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex() == 0){ //判断选择的为第0项
          ui->comboBox_2->clear();                 //清除ComboBox中的内容
          ui->comboBox_3->clear();
          ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="1号线"){
                  QString outputname;
                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }

      }else if(ui->comboBox->currentIndex() == 1){
          ui->comboBox_2->clear();
          ui->comboBox_3->clear();
          cout<<"变成二号线"<<endl;
          ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
          cout<<"89uu"<<endl;
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="2号线"){
                  QString outputname;

                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }
      }else if(ui->comboBox->currentIndex() == 2){
          ui->comboBox_2->clear();
          ui->comboBox_3->clear();
          ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="4号线"){
                  QString outputname;
                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }
      }else if(ui->comboBox->currentIndex() == 3){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="5号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 4){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="6号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 5){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="8号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 6){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="9号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 7){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="10号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 8){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("无"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("无"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="13号线"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }
}

double deg2rad(double deg) {
    return deg * pi / 180.0;
}

double calculateDistance(double lat1, double lng1, double lat2, double lng2) {
    // 将经纬度从度转换为弧度
    lat1 = deg2rad(lat1);
    lng1 = deg2rad(lng1);
    lat2 = deg2rad(lat2);
    lng2 = deg2rad(lng2);

    // 计算经纬度差值
    double a = lat1 - lat2;
    double b = lng1 - lng2;

    // Haversine 公式计算距离
    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(b / 2), 2)));

    // 将距离转换为千米
    s = s * EARTH_RADIUS;

    return s;
}
