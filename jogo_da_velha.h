#include <QMessageBox>
#include <QList>
#include <QListWidgetItem>
#include "client.h"
#include <QString>

#define PosMax 8

class jogo_da_velha : public QObject
{

    Q_OBJECT

private:
    int Mode_Game;
    char z;
    QString tabuleiro;
	char vencedor;
	int jogador_X,jogador_O,empate;
    Client *client;
    QString from;

private slots:
    void receiveMove(const QString &move);


public:
    jogo_da_velha(Client *client,QString from, char player);
    ~jogo_da_velha(void);
    void player(char turn);
	void atualiza_tab(int i);
	char teste_win();
	int verif_jogada(int i);
	void reiniciar(void);
	void Bip_Buzzer(void);
	int estatistica_X(void);
	int status_empate(void);
	int estatistica_O(void);
	void atualiza_vencedor(void);
	char testa_vencedor(void);
    void winner(void);
    int Button_action(int i);
    void update_table(void);
    void close_game();


};
