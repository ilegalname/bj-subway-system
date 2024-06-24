#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>

namespace Ui {
class newwindow;
}

class newwindow : public QWidget
{
    Q_OBJECT

public:
    explicit newwindow(QWidget *parent = nullptr);
    ~newwindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::newwindow *ui;
};

#endif // NEWWINDOW_H
