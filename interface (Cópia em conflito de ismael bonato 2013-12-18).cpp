#include "interface.h"
#include "ui_interface.h"
#include "table.h"

#include <QMessageBox>
#include <QtWidgets>

interface * interface::instance = 0;

interface::interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface)
{
    ui->setupUi(this);
    interface::instance = this;


    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->textEdit->setReadOnly(true);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(&client, SIGNAL(newMessage(QString,QString)),
            this, SLOT(appendMessage(QString,QString)));
    connect(&client, SIGNAL(newParticipant(QString)),
            this, SLOT(newParticipant(QString)));
    connect(&client, SIGNAL(participantLeft(QString)),
            this, SLOT(participantLeft(QString)));
    connect(&client, SIGNAL(newGame(QString,QString)),
            this, SLOT(orderGame(QString,QString)));
    connect(&client, SIGNAL(newGameAnswer(QString,QString)),
            this, SLOT(orderGameanswer(QString,QString)));



    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
    /////////////////////////////////////////////////////

}

interface::~interface()
{
    delete _table[0];
    delete ui;
}

void interface::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = ui->textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void interface::returnPressed()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = ui->textEdit->textColor();
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        ui->textEdit->setTextColor(color);
    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    ui->lineEdit->clear();
}

void interface::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = ui->textEdit->textColor();
    ui->textEdit->setTextColor(Qt::gray);
    ui->textEdit->append(tr("* %1 has joined").arg(nick));
    ui->textEdit->setTextColor(color);
    ui->listWidget->addItem(nick);
}

void interface::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = ui->listWidget->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = ui->textEdit->textColor();
    ui->textEdit->setTextColor(Qt::gray);
    ui->textEdit->append(tr("* %1 has left").arg(nick));
    ui->textEdit->setTextColor(color);
}

void interface::showInformation()
{
    if (ui->listWidget->count() == 1) {
        QMessageBox::information(this, tr("Chat"),
                                 tr("Launch several instances of this "
                                    "program on your local network and "
                                    "start chatting!"));
    }
}

void interface::on_radiobuttonGameMode_clicked()
{
    if(ui->radiobuttonGameMode->isChecked()) ui->GameButton->setText("conect");
    else ui->GameButton->setText("Start");
}

void interface::on_GameButton_clicked()
{

    if(!ui->listWidget->selectedItems().isEmpty())
    {
       client.orderofplay(ui->listWidget->currentItem()->text());
    }
    else
        QMessageBox::information(this, tr("<h1>Warning<h1>"),
                                 tr("select a player for conect"),QMessageBox::Ok );
}

int interface::orderGame(const QString &from, const QString &message)
{

    if (from.isEmpty())
        return 0;

    int ret = QMessageBox::information(this, tr("Order Of Game"),tr("tópa?"), QMessageBox::No | QMessageBox::Yes );
    client.orderofgameanswer(from,ret);
    if(ret == QMessageBox::Yes)
    {
        newgame(from);
    }
    return 0;

}

void interface::newgame(const QString &from)
{
    _table[0] = new table(this,&client,from);
    _table[0]->show();

}

int interface::orderGameanswer(const QString &from, const QString &answer)
{

    if(answer.toInt()==(QMessageBox::Yes))
        newgame(from);

    return 0;
}
