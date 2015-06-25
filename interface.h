#ifndef INTERFACE_H
#define INTERFACE_H
#include <QPushButton>
#include <QMainWindow>
#include "table.h"

#include "ui_interface.h"
#include "client.h"

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    ~interface();


public slots:
////////////////////////////////////////////////////
///
/// classe chat
///
////////////////////////////////////////////////////

    void appendMessage(const QString &from, const QString &message);
    int orderGame(const QString &from, const QString &message);

///////////////////////////////////////////////////

private slots:


////////////////////////////////////////////////////
///
/// classe chat
///
////////////////////////////////////////////////////
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void showInformation();
/////////////////////////////////////////////////////
    void on_radiobuttonGameMode_clicked();

    void on_GameButton_clicked();
    void newgame(const QString &from,char player);
    int orderGameanswer(const QString &from, const QString &answer);


private:
    Ui::interface *ui;
    table * _table[10];
    static interface * instance;
    QPushButton *Button_vect[10];

////////////////////////////////////////////////////
///
/// classe chat
///
////////////////////////////////////////////////////
    Client client;
    QString myNickName;
    QTextTableFormat tableFormat;

/////////////////////////////////////////////////////
};

#endif // INTERFACE_H
