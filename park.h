#ifndef PARK_H
#define PARK_H

#include <QWidget>

namespace Ui {
class park;
}

class park : public QWidget
{
    Q_OBJECT

public:
    explicit park(QWidget *parent = nullptr);
    ~park();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::park *ui;

};

#endif // PARK_H
