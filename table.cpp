#include "table.h"


table * table::instance = 0;

table::table(QWidget *parent,Client *client,QString from,char player) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);


    jogo = new jogo_da_velha(client,from,player);

    table::instance = this;

    Button_vect[0]=ui->pushButton_1;
    Button_vect[1]=ui->pushButton_2;
    Button_vect[2]=ui->pushButton_3;
    Button_vect[3]=ui->pushButton_4;
    Button_vect[4]=ui->pushButton_5;
    Button_vect[5]=ui->pushButton_6;
    Button_vect[6]=ui->pushButton_7;
    Button_vect[7]=ui->pushButton_8;
    Button_vect[8]=ui->pushButton_9;


}

table::~table()
{
   delete jogo;
    delete ui;
}
void table::disable_table()
{
    ui->centralwidget->setEnabled(false);


    
}
void table::enable_table()
{
    ui->centralwidget->setEnabled(true);

}


void table::on_pushButton_1_clicked()
{
    jogo->Button_action(0);
}

void table::on_pushButton_2_clicked()
{
    jogo->Button_action(1);
}

void table::on_pushButton_3_clicked()
{
    jogo->Button_action(2);
}

void table::on_pushButton_4_clicked()
{
    jogo->Button_action(3);
}

void table::on_pushButton_5_clicked()
{
    jogo->Button_action(4);
}

void table::on_pushButton_6_clicked()
{
    jogo->Button_action(5);
}
void table::on_pushButton_7_clicked()
{
    jogo->Button_action(6);
}
void table::on_pushButton_8_clicked()
{
    jogo->Button_action(7);
}
void table::on_pushButton_9_clicked()
{
    jogo->Button_action(8);
}
int table::show_X_winner(void)
{
    return QMessageBox::information(this, tr("Vencedor"),tr("jogador X ganhou\n"), QMessageBox::Ok );
}
int table::show_O_winner(void)
{
    return QMessageBox::information(this, tr("Vencedor"),tr("jogador O ganhou\n"),QMessageBox::Ok );
}
int table::show_Draw(void)
{
    return QMessageBox::information(this, tr("Empate"),tr("Deu velha\n"), QMessageBox::Ok );

}
void table::restart_tictactoe()
{
    ui->pushButton_1->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_2->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_3->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_4->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_5->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_6->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_7->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_8->setStyleSheet("border-image: url(NULL);");
    ui->pushButton_9->setStyleSheet("border-image: url(NULL);");
}

void table::Print_X(int pos)
{
    Button_vect[pos]->setStyleSheet("border-image: url(:/imagens/marcaX.png);");
}

void table::Print_O(int pos)
{
    Button_vect[pos]->setStyleSheet("border-image: url(:/imagens/marcaO.png);");
}
