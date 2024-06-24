#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newwindow.h"
#include "paywindow.h"
#include "park.h"
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

using namespace std;
using std::to_string;

extern string desti;
extern string current;

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

class Path {
public:
    Station* start_station;
    Station* end_station;
    int distance;
    int transfer;
    std::vector<Station*> stations_visited;
    int price;
    int time;

    int Price() {
        if (distance < 6000)
            price = 3;
        else if (distance < 12000)
            price = 4;
        else if (distance < 22000) {
            price = 5;
        }
        else if(distance<32000)
            price = 6;
        else {
            price = 6 + (distance - 32000) / 20000;
        }
        return price;
    }

    Path(Station* start, Station* end, int dist, int trans, std::vector<Station*>& visited,int time)
        : start_station(start), end_station(end), distance(dist), transfer(trans), stations_visited(visited), time(time) {}
};

vector<Station*> stations;
vector<Edge*> edges;
vector<Line*> lines;
const int INF = INT_MAX;
vector<vector<int>> G(250, vector<int>(250, INF)); //�ȳ�ʼ����ȫ��ΪINT_MAX
vector<vector<int>> T(250, vector<int>(250, INF));

using namespace std;

Path* dijkstra(Station* start, Station* end);
Path* searchleastchange(Station* start, Station* end);
Path* dijkstra2(string now, string destination, int ifstartchange , int ifendchange);
Path* searchleastchange2(string now, string destination, int ifstartchange , int ifendchange);
string qstr2str(const QString qstr);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    stations.clear();
    edges.clear();
    lines.clear();
        int num = 15;
        char name[10] = " ", line[10] = " ", longtitude[15], latitude[15], number[5], ifchange[5];
        double lon, la;
        int nn, change;
        char start[5] = " ", end[5] = " ", weight[10];
        int begin, last, w;

        ifstream stationfile("station.txt");
        if (!stationfile.is_open()) {
            cout << "can not open this file" << endl;
        }
        string linee;
        while (getline(stationfile, linee)) {
            // ʹ�� stringstream �ָ�����
            istringstream ss(linee);
            string number, name, line, latitude, longitude, ifchange;

            getline(ss, number, '\t');
            getline(ss, name, '\t');
            getline(ss, line, '\t');
            getline(ss, latitude, '\t');
            getline(ss, longitude, '\t');
            getline(ss, ifchange, '\t');

            // ת��Ϊ���ʵ�����
            int num = stoi(number);
            double lat = stod(latitude);
            double lon = stod(longitude);
        int change = stoi(ifchange);
        // ���� Station ���󲢴洢
        Station* station = new Station(num, name, line, lon, lat, change);
        stations.push_back(station);
        }
        stationfile.close();

        cout<<"i am here! I finished station"<<endl;

        cout << "1����";
        cout<<stations.size()<<endl;
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "") {
                    cout << stations[i]->name << "1����";
                }
            }
            cout << endl;
            cout << "2����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "2����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "4����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "4����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "5����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "5����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "6����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "6����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "8����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "8����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "9����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "9����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "10����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "10����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;
            cout << "13����";
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i]->line == "13����") {
                    cout << stations[i]->name << " ";
                }
            }
            cout << endl;

        ifstream edgefile("edge.txt");
        if (!edgefile.is_open()) {
            cout << "Failed to open file." << endl;
        }
        while (!edgefile.eof()) {
            edgefile.getline(start, num, '\t');
            edgefile.getline(end, num, '\t');
            edgefile.getline(weight, num, '\n');
            begin = atoi(start);
            last = atoi(end);
            w = atoi(weight);
            Station* s = nullptr;
            Station* e = nullptr;

            for (int i = 0; i < stations.size(); ++i) {
                if (stations[i]->number == begin) {
                    s = stations[i];
                }
                if (stations[i]->number == last) {
                    e = stations[i];
                }
            }

            if (s != nullptr && e != nullptr) {
                Edge* edge = new Edge(s, e, w);
                edges.push_back(edge);
            }
        }
        edgefile.close();

        cout<<"i am here! I finished edge"<<endl;

        for (int k = 0; k < edges.size(); k++) {                  //�����������ھ���
            int i = edges[k]->start->number;
            int j = edges[k]->end->number;
            G[i][j] = edges[k]->weight;
            G[j][i] = edges[k]->weight;
        }
        for (int i = 0; i < stations.size(); i++) {
            for (int j = 0; j < stations.size(); j++) {
                if (stations[i]->name == stations[j]->name) {
                    G[i][j] = 0;
                    G[j][i] = 0;
                }
            }
        }
        for (int k = 0; k < edges.size(); k++) {                  //����ʱ�����ھ���
            int i = edges[k]->start->number;
            int j = edges[k]->end->number;
            T[i][j] = edges[k]->counttime();
            T[j][i] = edges[k]->counttime();
        }
        for (int i = 0; i < stations.size(); i++) {
            for (int j = 0; j < stations.size(); j++) {
                if (stations[i]->name == stations[j]->name) {
                    if (stations[i]->number == stations[j]->number) {
                        T[i][j] = 0;
                        T[j][i] = 0;
                    }
                    else
                        T[i][j] = T[j][i] = 6;
                }
            }
        }

        ifstream linefile ("line.txt");
        char linename[10] = " ", red[5] = " ", green[5] = " ", blue[5] = " ";
        int r, g, b;

        if (!linefile.is_open()) {
            cout << "can not open this file" << endl;
        }
        while (!linefile.eof()) {
            string n;
            for (int i = 0; i < 10; i++) {
                name[i] = ' ';
            }
            linefile.getline(linename, num, ' ');
            linefile.getline(red, num, ' ');
            linefile.getline(green, num, ' ');
            linefile.getline(blue, num, '\n');
            r = atoi(red);
            g = atoi(green);
            b = atoi(blue);
            for (int i = 0; i < strlen(linename); i++) {
                if (linename[i] != '\t') {
                    n += linename[i];
                }
            }
            Line* line = new Line(n,r,g,b);
            lines.push_back(line);
        }
        linefile.close();

        for (int i = 0; i < lines.size(); i++) {
                cout << lines[i]->name << " " << lines[i]->red << " " << lines[i]->green << " " << lines[i]->blue << endl;
            }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    string now, destination;
        Path* path1 = nullptr;

        QString startstation = ui->lineEdit->text();
        string begin = qstr2str(startstation);

        QString endstation = ui->lineEdit_2->text();
        string end = qstr2str(endstation);

        cout<<"pushbuttonstart"<<begin<<endl;
        cout<<"pushbuttonend"<<end<<endl;

        int ifstartchange = -1;
        int ifendchange = -1;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == begin) {
                ifstartchange = stations[i]->ifchange;
            }
            if (stations[i]->name == end) {
                    ifendchange = stations[i]->ifchange;
                }
            }

        if(ifstartchange==-1){
            QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ڸ���㣬����������"));
        }
        else{
            if(ifendchange==-1){
                QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ڸ��յ㣬����������"));
            }
            else{
                path1 = dijkstra2(begin,end,ifstartchange,ifendchange);

                cout << "���·��Ϊ��";
                    for (int i = path1->stations_visited.size() - 1; i > 0; i--) {
                        cout << path1->stations_visited[i]->line << " " << path1->stations_visited[i]->name << "->";
                    }
                    cout << path1->stations_visited[0]->line << path1->stations_visited[0]->name << endl << "ȫ��Ϊ��" << path1->distance << "��" << endl << "���˴���Ϊ��" << path1->transfer << endl << "Ʊ��Ϊ" << path1->Price() << "Ԫ" << endl;
                    cout << " һ����" << path1->stations_visited.size() << "վ" << endl;
                    cout << "��ʱ��Ϊ��" << path1->time << "����" << endl;

                    QString qtr=QString::fromLocal8Bit("���·��Ϊ");
                    ui->textBrowser->insertPlainText(qtr +='\n');
                    Path* path3 = dijkstra2(begin,end,ifstartchange,ifendchange);
                    string output;
                    cout << "���ٻ���վ·��Ϊ��";
                    cout<<"����"<<endl;
                    int j=0;
                    for (j = path3->stations_visited.size() - 1; j>0; j--) {
                            //cout << path3->stations_visited[j]->line << " " << path3->stations_visited[j]->name << "->";
                            if(j==0)
                                break;
                            cout<<j<<endl;
                            string l1=path3->stations_visited[j]->line;
                            ui->textBrowser->insertPlainText(QString::fromLocal8Bit(l1.data()));
                            string sta = path3->stations_visited[j]->name;
                            ui->textBrowser->insertPlainText(QString::fromLocal8Bit(sta.data()));
                            string arrow = "->";
                            ui->textBrowser->insertPlainText(QString::fromLocal8Bit(arrow.data()));
                    }
                    cout << path3->stations_visited[0]->line << " " << path3->stations_visited[0]->name << endl << "ȫ��Ϊ��" << path3->distance << "��" << endl << "���˴���Ϊ��" << path3->transfer << endl << "Ʊ��Ϊ" << path3->Price() << "Ԫ" << endl;

                    string sta2 = path3->stations_visited[0]->name;
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(sta2.data())+='\n');

                    string strr="ȫ��";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(strr.data()));
                    string numm = std::to_string(path3->distance);
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(numm.data()));
                    string str5="��";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str5.data())+='\n');

                    string str1="һ����";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str1.data()));
                    string num = std::to_string(path3->stations_visited.size());
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num.data()));
                    string str2="վ";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str2.data())+='\n');

                    string str3="��ʱ��Ϊ";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str3.data()));
                    string num2 = std::to_string(path3->time);
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num2.data()));
                    string str4="����";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str4.data())+='\n');

                    string str6="��֧��";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str6.data()));
                    string num3 = std::to_string(path3->price);
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num3.data()));
                    string str7="Ԫ";
                    ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str7.data())+='\n');

            }
        }


}

Path* dijkstra(Station* start, Station* end) {
    int INF = INT_MAX;
    int num = end->number;
    int change = 0;
    int t = 0;
    vector<Station*> visited;
    vector<int> distance(250, INF);
    set<pair<int, int>> pq;
    vector<int> front(250, -1);
    distance[start->number] = 0;
    pq.insert({ 0, start->number });
    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (int v = 0; v < 250; ++v) {
            if (G[u][v] != INF) {
                int alt = distance[u] + G[u][v];
                if (alt < distance[v]) {
                    distance[v] = alt;
                    pq.insert({ distance[v], v });
                    front[v] = u;
                }
            }
        }
    }
    while (num != start->number) {
        for (int j = 0; j < stations.size(); j++) {
            if (stations[j]->number == num) {
                Station* station = new Station(stations[j]->number, stations[j]->name, stations[j]->line, stations[j]->longtitude, stations[j]->latitude, stations[j]->ifchange);
                visited.push_back(station);
                if (stations[j]->name==stations[front[j]]->name&& stations[j]->number != stations[front[j]]->number && front[j] != start->number && j != end->number)
                    change++;
            }
        }
        t += T[num][front[num]];
        num = front[num];
    }
    Station* station = new Station(start->number, start->name, start->line, start->longtitude, start->latitude, start->ifchange);
    visited.push_back(station);
    Path* path = new Path(start, end, distance[end->number], change, visited,t);
    return path;
}

Path* dijkstra2(string now, string destination, int ifstartchange , int ifendchange) {


    cout<<"startchange="<<ifstartchange<<endl;
    cout<<"endchange="<<ifendchange<<endl;



    if (ifstartchange == 0 && ifendchange == 0) {
        Station* start = nullptr;
        Station* end = nullptr;
        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        Path* path = nullptr;
        path = dijkstra(start, end);
        return path;
    }

    else if (ifstartchange == 1 && ifendchange == 0) {

        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;
            }
        }

        Path* path = nullptr;
        Path* path2 = nullptr;
        path = dijkstra(start, end);
        path2 = dijkstra(start2, end);

        if (path->time < path2->time) {
            return path;
        }
        else {
            return path2;
        }
    }

    else if (ifstartchange == 0 && ifendchange == 1) {
        Station* start = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;
            }
        }

        Path* path = nullptr;
        Path* path2 = nullptr;
        path = dijkstra(start, end);
        path2 = dijkstra(start, end2);

        if (path->time < path2->time) {
            return path;
        }
        else {
            return path2;
        }

        cout<<"i am out"<<endl;
    }

    else if (ifstartchange == 1 && ifendchange == 1) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;
            }
        }
        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        path1 = dijkstra(start, end);
        path2 = dijkstra(start2, end);
        path3 = dijkstra(start, end);
        path4 = dijkstra(start2, end2);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime = min(leasttime1, leasttime2);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else
            return path4;

    }

    else if (ifstartchange == 2 && ifendchange == 0) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* start3 = nullptr;
        Station* end = nullptr;
        int j = 0,num=0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start2 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        num = j+1;
        for (j = num; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start3 = stations[j];
                break;
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        path1 = dijkstra(start, end);
        path2 = dijkstra(start2, end);
        path3 = dijkstra(start3, end);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime = min(path3->time, leasttime1);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else
            return path3;
    }

    else if (ifstartchange == 0 && ifendchange == 2) {
        Station* start = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        Station* end3 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end2 = stations[j];
                break;
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end3 = stations[j];
                break;
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        path1 = dijkstra(start, end);
        path2 = dijkstra(start, end2);
        path3 = dijkstra(start, end3);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime = min(path3->time, leasttime1);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else
            return path3;
    }

    else if (ifstartchange == 1 && ifendchange == 2) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        Station* end3 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end2 = stations[j];
                break;
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end3 = stations[j];
                break;
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        Path* path5 = nullptr;
        Path* path6 = nullptr;
        path1 = dijkstra(start, end);
        path2 = dijkstra(start, end2);
        path3 = dijkstra(start, end3);
        path4 = dijkstra(start2, end);
        path5 = dijkstra(start2, end2);
        path6 = dijkstra(start2, end3);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime3 = min(path5->time, path6->time);
        int leasttime4 = min(leasttime1, leasttime2);
        int leasttime = min(leasttime3, leasttime4);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else if (leasttime == path4->time)
            return path4;
        else if (leasttime == path5->time)
            return path5;
        else
            return path6;
    }

    else if (ifstartchange == 2 && ifendchange == 1) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* start3 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start2 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start3 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        Path* path5 = nullptr;
        Path* path6 = nullptr;
        path1 = dijkstra(start, end);
        path2 = dijkstra(start, end2);
        path3 = dijkstra(start2, end);
        path4 = dijkstra(start2, end2);
        path5 = dijkstra(start3, end);
        path6 = dijkstra(start3, end2);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime3 = min(path5->time, path6->time);
        int leasttime4 = min(leasttime1, leasttime2);
        int leasttime = min(leasttime3, leasttime4);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else if (leasttime == path4->time)
            return path4;
        else if (leasttime == path5->time)
            return path5;
        else
            return path6;
    }

    else
        return nullptr;
}

Path* searchleastchange(Station* start, Station* end) {
    int INF = INT_MAX;
    int i = 0;
    int num = end->number;
    int change = 0;
    int alter=0;
    int dist = 0;
    int t=0;
    vector<Station*> visited;
    vector<int> changetime(250, INF);     //���ڼ�¼ÿ���㵽�����Ļ��˴�������ʼ��Ϊ������
    set<pair<int, int>> pq;     //���ȶ��У����յ�һ��int�Ĵ�С˳�����ţ���һ��Ϊ�������Ļ��˴������ڶ���Ϊվ����
    vector<int> front(250, -1);    //�����洢ǰ�̽ڵ�����
    changetime[start->number] = 0;
    pq.insert({ 0, start->number });
    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (int v = 0; v < 250; ++v) {
            if (G[u][v] != INF) {
                if (stations[u]->name == stations[v]->name && stations[u]->number != stations[v]->number&&u!=start->number&&v!=end->number) {
                    alter = changetime[u] + 1;
                }
                else
                    alter = changetime[u];
                if (alter < changetime[v]) {
                    changetime[v] = alter;
                    pq.insert({ changetime[v], v });
                    front[v] = u;
                }
            }
        }
    }
    while (num != start->number) {
        for (int j = 0; j < stations.size(); j++) {
            if (stations[j]->number == num) {
                Station* station = new Station(stations[j]->number, stations[j]->name, stations[j]->line, stations[j]->longtitude, stations[j]->latitude, stations[j]->ifchange);
                visited.push_back(station);
                if (stations[j]->ifchange == 1)
                    change++;
                i++;
            }
        }
        dist += G[num][front[num]];
        t += T[num][front[num]];
        num = front[num];
    }

    Station* station = new Station(start->number, start->name, start->line, start->longtitude, start->latitude, start->ifchange);
    visited.push_back(station);

    Path* path = new Path(start, end, dist, changetime[end->number], visited,t);
    return path;
}

Path* searchleastchange2(string now, string destination, int ifstartchange , int ifendchange) {
    if (ifstartchange == 0 && ifendchange == 0) {         //�����ǻ���վ
        Station* start = nullptr;
        Station* end = nullptr;
        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        Path* path = nullptr;
        path = searchleastchange(start, end);
        return path;
    }

    else if (ifstartchange == 1 && ifendchange == 0) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path = nullptr;
        Path* path2 = nullptr;
        path = searchleastchange(start, end);
        path2 = searchleastchange(start2, end);

        if (path->time < path2->time) {
            return path;
        }
        else {
            return path2;
        }
    }

    else if (ifstartchange == 0 && ifendchange == 1) {
        Station* start = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }

        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path = nullptr;
        Path* path2 = nullptr;
        path = searchleastchange(start, end);
        path2 = searchleastchange(start, end2);

        if (path->time < path2->time) {
            cout << "return path1" << endl;
            return path;
        }
        else {
            cout << "return path2" << endl;
            return path2;
        }
    }

    else if (ifstartchange == 1 && ifendchange == 1) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        path1 = searchleastchange(start, end);
        for (int j = path1->stations_visited.size() - 1; j > 0; j--) {
            cout << path1->stations_visited[j]->line << " " << path1->stations_visited[j]->name << "->";
        }
        cout << path1->stations_visited[0]->line << " " << path1->stations_visited[0]->name << endl;
        path2 = searchleastchange(start2, end);
        for (int j = path2->stations_visited.size() - 1; j > 0; j--) {
            cout << path2->stations_visited[j]->line << " " << path2->stations_visited[j]->name << "->";
        }
        cout << path2->stations_visited[0]->line << " " << path2->stations_visited[0]->name << endl;
        path3 = searchleastchange(start, end);
        for (int j = path3->stations_visited.size() - 1; j > 0; j--) {
            cout << path3->stations_visited[j]->line << " " << path3->stations_visited[j]->name << "->";
        }
        cout << path3->stations_visited[0]->line << " " << path3->stations_visited[0]->name << endl;
        path4 = searchleastchange(start2, end2);
        for (int j = path4->stations_visited.size() - 1; j > 0; j--) {
            cout << path4->stations_visited[j]->line << " " << path4->stations_visited[j]->name << "->";
        }
        cout << path4->stations_visited[0]->line << " " << path4->stations_visited[0]->name << endl;

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime = min(leasttime1, leasttime2);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else
            return path4;

    }

    else if (ifstartchange == 2 && ifendchange == 0) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* start3 = nullptr;
        Station* end = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start2 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        num = j + 1;
        for (j = num; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start3 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        path1 = searchleastchange(start, end);
        path2 = searchleastchange(start2, end);
        path3 = searchleastchange(start3, end);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime = min(path3->time, leasttime1);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else
            return path3;
    }

    else if (ifstartchange == 0 && ifendchange == 2) {
        Station* start = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        Station* end3 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
                cout << "�ҵ�һ������" << start->line << start->name << endl;
            }
            if (stations[i]->name == destination) {
                end = stations[i];
                cout << "�ҵ�һ���յ���" << end->line << end->name << endl;
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end2 = stations[j];
                cout << "�ҵ������յ���" << end2->line << end2->name << endl;
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end3 = stations[j];
                cout << "�ҵ������յ���" << end3->line << end3->name << endl;
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        path1 = searchleastchange(start, end);
        path2 = searchleastchange(start, end2);
        path3 = searchleastchange(start, end3);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime = min(path3->time, leasttime1);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else
            return path3;
    }

    else if (ifstartchange == 1 && ifendchange == 2) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        Station* end3 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == now) {
                start2 = stations[i];
                break;
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end2 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == destination) {
                end3 = stations[j];
                break;  // һ���ҵ� start2 ��ֹͣѭ��
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        Path* path5 = nullptr;
        Path* path6 = nullptr;
        path1 = searchleastchange(start, end);
        path2 = searchleastchange(start, end2);
        path3 = searchleastchange(start, end3);
        path4 = searchleastchange(start2, end);
        path5 = searchleastchange(start2, end2);
        path6 = searchleastchange(start2, end3);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime3 = min(path5->time, path6->time);
        int leasttime4 = min(leasttime1, leasttime2);
        int leasttime = min(leasttime3, leasttime4);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else if (leasttime == path4->time)
            return path4;
        else if (leasttime == path5->time)
            return path5;
        else
            return path6;
    }

    else if (ifstartchange == 2 && ifendchange == 1) {
        Station* start = nullptr;
        Station* start2 = nullptr;
        Station* start3 = nullptr;
        Station* end = nullptr;
        Station* end2 = nullptr;
        int j = 0, num = 0;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == now) {
                start = stations[i];
            }
            if (stations[i]->name == destination) {
                end = stations[i];
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            if (stations[i]->name == destination) {
                end2 = stations[i];
                break;
            }
        }
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start2 = stations[j];
                break;
            }
        }
        num = j + 1;
        for (j = 0; j < stations.size() - 1; j++) {
            if (stations[j]->name == now) {
                start3 = stations[j];
                break;
            }
        }

        Path* path1 = nullptr;
        Path* path2 = nullptr;
        Path* path3 = nullptr;
        Path* path4 = nullptr;
        Path* path5 = nullptr;
        Path* path6 = nullptr;
        path1 = searchleastchange(start, end);
        path2 = searchleastchange(start, end2);
        path3 = searchleastchange(start2, end);
        path4 = searchleastchange(start2, end2);
        path5 = searchleastchange(start3, end);
        path6 = searchleastchange(start3, end2);

        int leasttime1 = min(path1->time, path2->time);
        int leasttime2 = min(path3->time, path4->time);
        int leasttime3 = min(path5->time, path6->time);
        int leasttime4 = min(leasttime1, leasttime2);
        int leasttime = min(leasttime3, leasttime4);
        if (leasttime == path1->time)
            return path1;
        else if (leasttime == path2->time)
            return path2;
        else if (leasttime == path3->time)
            return path3;
        else if (leasttime == path4->time)
            return path4;
        else if (leasttime == path5->time)
            return path5;
        else
            return path6;
    }

    else
        return nullptr;
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void MainWindow::on_pushButton_3_clicked()
{
    cout<<"i am here"<<endl;
    newwindow *configWindow = new newwindow;
    configWindow->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textBrowser->clear();
    string now, destination;
        int time1;

        QString startstation = ui->lineEdit->text();
        string begin = qstr2str(startstation);

        QString endstation = ui->lineEdit_2->text();
        string end = qstr2str(endstation);

        cout<<"pushbuttonstart"<<begin<<endl;
        cout<<"pushbuttonend"<<end<<endl;

        int ifstartchange = -1;
        int ifendchange = -1;

        for (int i = 0; i < stations.size(); i++) {
            if (stations[i]->name == begin) {
                ifstartchange = stations[i]->ifchange;
            }
            if (stations[i]->name == end) {
                    ifendchange = stations[i]->ifchange;
                }
            }

        if(ifstartchange==-1){
            QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ڸ���㣬����������"));
        }
        else{
            if(ifendchange==-1){
                QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ڸ��յ㣬����������"));
            }
            else{
                QString qtr=QString::fromLocal8Bit("���ٻ���·��Ϊ");
                ui->textBrowser->insertPlainText(qtr +='\n');
                Path* path3 = nullptr;
                string output;
                path3 = searchleastchange2(begin,end,ifstartchange,ifendchange);
                cout << "���ٻ���վ·��Ϊ��";
                cout<<"����"<<endl;
                int j=0;
                for (j = path3->stations_visited.size() - 1; j>0; j--) {
                        //cout << path3->stations_visited[j]->line << " " << path3->stations_visited[j]->name << "->";
                        if(j==0)
                            break;
                        cout<<j<<endl;
                        string l1=path3->stations_visited[j]->line;
                        ui->textBrowser->insertPlainText(QString::fromLocal8Bit(l1.data()));
                        string sta = path3->stations_visited[j]->name;
                        ui->textBrowser->insertPlainText(QString::fromLocal8Bit(sta.data()));
                        string arrow = "->";
                        ui->textBrowser->insertPlainText(QString::fromLocal8Bit(arrow.data()));
                }
                cout << path3->stations_visited[0]->line << " " << path3->stations_visited[0]->name << endl << "ȫ��Ϊ��" << path3->distance << "��" << endl << "���˴���Ϊ��" << path3->transfer << endl << "Ʊ��Ϊ" << path3->Price() << "Ԫ" << endl;

                string sta2 = path3->stations_visited[0]->name;
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(sta2.data())+='\n');

                string strr="ȫ��";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(strr.data()));
                string numm = std::to_string(path3->distance);
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(numm.data()));
                string str5="��";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str5.data())+='\n');

                string str1="һ����";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str1.data()));
                string num = std::to_string(path3->stations_visited.size());
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num.data()));
                string str2="վ";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str2.data())+='\n');

                string str3="��ʱ��Ϊ";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str3.data()));
                string num2 = std::to_string(path3->time);
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num2.data()));
                string str4="����";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str4.data())+='\n');

                string str6="��֧��";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str6.data()));
                string num3 = std::to_string(path3->price);
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(num3.data()));
                string str7="Ԫ";
                ui->textBrowser->insertPlainText(QString::fromLocal8Bit(str7.data())+='\n');

                cout << " һ����" << path3->stations_visited.size() << "վ" << endl;
                cout << "��ʱ��Ϊ��" << path3->time << "����" << endl;
            }
        }

}

void MainWindow::on_pushButton_5_clicked()
{
    paywindow *buyWindow = new paywindow;
    buyWindow->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    park *parkwindow = new park;
    parkwindow ->show();

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(QString::fromLocal8Bit(current.data()));
    ui->lineEdit_2->setText(QString::fromLocal8Bit(desti.data()));
}
