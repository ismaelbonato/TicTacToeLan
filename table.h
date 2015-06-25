#ifndef TABLE_H
#define TABLE_H

#include <QPushButton>
#include "jogo_da_velha.h"
#include "client.h"
#include <QList>
#include <QMainWindow>

#include "ui_load.h"
#include "ui_table.h"

class Client;
class load;

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0,Client *client =0,QString from = "",char player = 0);
    ~table();
    void change_O();
    void showwinner(char Win);
    void restart_tictactoe();
    void Update_table(char *table);
    int  show_X_winner(void);
    int  show_O_winner(void);
    int  show_Draw(void);
    void Print_X(int pos);
    void Print_O(int pos);
    void disable_table(void);
    void enable_table();


    //sigleton
    static table * getInstance(){
        return instance;
    }

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();


private:
    Ui::table *ui;
    //Client *client;
    jogo_da_velha * jogo;

    static table * instance;
    QPushButton *Button_vect[10];
};

#endif // TABLE_H
