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
const double EARTH_RADIUS = 6371000.0; // ����뾶����λ���ף�
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
        if (start->line == "1����")
            return weight / 567;
        else if (start->line == "2����")
            return weight / 525;
        else if (start->line == "4����")
            return weight / 590;
        else if (start->line == "5����")
            return weight / 533;
        else if (start->line == "6����")
            return weight / 622;
        else if (start->line == "8����")
            return weight / 573;
        else if (start->line == "9����")
            return weight / 523;
        else if (start->line == "10����")
            return weight / 548;
        else if (start->line == "13����")
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
                QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��վ���Ѵ��ڣ�����������"));
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

        cout<<"����1"<<" "<<dd1<<endl;
        cout<<"����2"<<" "<<dd2<<endl;

        cout<<current_num<<" "<<count<<endl;
        if(count==current_num+1){
            cout<<"i am here"<<endl;
            fstream inputstation;
            inputstation.open("station.txt",ios::app);
            inputstation << current_num+1 << "\t" << name << "\t" <<linee<<"\t"<< longt<<"\t"<<lat<<"\t"<<0<<endl;
            inputstation.close();
            fstream editDdge;
            editDdge.open("edge.txt",ios::app);
            if(neighbor1!="��"){
                editDdge<<nei1<<"\t"<<current_num+1<<"\t"<<d1<<endl;
            }
            if(neighbor2!="��"){
                editDdge<<nei2<<"\t"<<current_num+1<<"\t"<<d2<<endl;
            }
            editDdge.close();
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�ɹ����վ��"));

        }
    }
    else{
        QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("վ����Ϣ������������������"));
    }
}

void newwindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex() == 0){ //�ж�ѡ���Ϊ��0��
          ui->comboBox_2->clear();                 //���ComboBox�е�����
          ui->comboBox_3->clear();
          ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="1����"){
                  QString outputname;
                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }

      }else if(ui->comboBox->currentIndex() == 1){
          ui->comboBox_2->clear();
          ui->comboBox_3->clear();
          cout<<"��ɶ�����"<<endl;
          ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
          cout<<"89uu"<<endl;
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="2����"){
                  QString outputname;

                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }
      }else if(ui->comboBox->currentIndex() == 2){
          ui->comboBox_2->clear();
          ui->comboBox_3->clear();
          ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
          ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
          for(int i=0;i<stations.size();i++){
              if(stations[i]->line=="4����"){
                  QString outputname;
                  outputname=str2qstr(stations[i]->name);
                  ui->comboBox_2->addItem(outputname);
                  ui->comboBox_3->addItem(outputname);
              }
          }
      }else if(ui->comboBox->currentIndex() == 3){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="5����"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 4){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="6����"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 5){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="8����"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 6){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="9����"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 7){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="10����"){
                QString outputname;
                outputname=str2qstr(stations[i]->name);
                ui->comboBox_2->addItem(outputname);
                ui->comboBox_3->addItem(outputname);
            }
        }
     }else if(ui->comboBox->currentIndex() == 8){
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        ui->comboBox_2->addItem(QString::fromLocal8Bit("��"));
        ui->comboBox_3->addItem(QString::fromLocal8Bit("��"));
        for(int i=0;i<stations.size();i++){
            if(stations[i]->line=="13����"){
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
    // ����γ�ȴӶ�ת��Ϊ����
    lat1 = deg2rad(lat1);
    lng1 = deg2rad(lng1);
    lat2 = deg2rad(lat2);
    lng2 = deg2rad(lng2);

    // ���㾭γ�Ȳ�ֵ
    double a = lat1 - lat2;
    double b = lng1 - lng2;

    // Haversine ��ʽ�������
    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(b / 2), 2)));

    // ������ת��Ϊǧ��
    s = s * EARTH_RADIUS;

    return s;
}
