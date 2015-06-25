#include <QMessageBox>
#include <QList>
#include <QListWidgetItem>
#include "client.h"

#define PosMax 8

class jogo_da_velha
{
private:
    int Mode_Game;
	int z;
	char *tabuleiro;
	char vencedor;
	int jogador_X,jogador_O,empate;
    Client *client;
    QString form;
    /////////////////////////////////////////////////




    /////////////////////////////////////////////////

public:
    jogo_da_velha(Client *client,QString from);
    ~jogo_da_velha(void);
	void mudar_jogador();
	void atualiza_tab(int i);
	int verif_jogador();
	char teste_win();
	int verif_jogada(int i);
	void reiniciar(void);
	void Bip_Buzzer(void);
	int estatistica_X(void);
	int status_empate(void);
	int estatistica_O(void);
	void atualiza_vencedor(void);
	char testa_vencedor(void);
	void zera_vencedor(void);
    void winner(void);
    void restart(void);
    int Button_action(int i);
    void update_table(void);
    void update_modegame();

};
