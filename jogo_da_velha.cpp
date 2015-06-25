#include "table.h"

jogo_da_velha::jogo_da_velha(Client *client,QString from,char player)
{

    this->client = client;
    this->from = from;

    connect(this->client, SIGNAL(receiveMove(QString)),
              this, SLOT(receiveMove(QString)));

    tabuleiro = new char[10];

	tabuleiro[0]=' ';
	tabuleiro[1]=' ';
	tabuleiro[2]=' ';
	tabuleiro[3]=' ';
	tabuleiro[4]=' ';
	tabuleiro[5]=' ';
	tabuleiro[6]=' ';
	tabuleiro[7]=' ';
	tabuleiro[8]=' ';
	tabuleiro[9]='\0';

	jogador_X=0;
	jogador_O=0;
	empate=0;
	
	vencedor=0;
    this->player(player);

}
jogo_da_velha::~jogo_da_velha(void)
{
}

void jogo_da_velha::player(char turn)
{
//	z=~z;
    z=turn;
}
void jogo_da_velha::atualiza_tab(int i)
{
    tabuleiro[i]=z;
    update_table();
}

char jogo_da_velha::teste_win()
{

		if(tabuleiro[0]=='O'&& tabuleiro[1]=='O' && tabuleiro[2]=='O') vencedor='O';
		else if(tabuleiro[3]=='O'&& tabuleiro[4]=='O' && tabuleiro[5]=='O')vencedor='O';
		else if(tabuleiro[6]=='O'&& tabuleiro[7]=='O' && tabuleiro[8]=='O') vencedor='O';

		else if(tabuleiro[0]=='O'&& tabuleiro[3]=='O' && tabuleiro[6]=='O') vencedor='O';
		else if(tabuleiro[1]=='O'&& tabuleiro[4]=='O' && tabuleiro[7]=='O') vencedor='O';
        else if(tabuleiro[2]=='O'&& tabuleiro[5]=='O' && tabuleiro[8]=='O') vencedor='O';

		else if(tabuleiro[0]=='O'&& tabuleiro[4]=='O' && tabuleiro[8]=='O') vencedor='O';
		else if(tabuleiro[6]=='O'&& tabuleiro[4]=='O' && tabuleiro[2]=='O') vencedor='O';
		else if(tabuleiro[0]!=' ' && tabuleiro[1]!=' ' &&tabuleiro[2]!=' ' && tabuleiro[3]!=' '&& tabuleiro[4]!=' ' && tabuleiro[5]!=' ' && tabuleiro[6]!=' '&& tabuleiro[6]!=' ' && tabuleiro[7]!=' ') vencedor='e';


		if(tabuleiro[0]=='X'&& tabuleiro[1]=='X' && tabuleiro[2]=='X') vencedor='X';
		else if(tabuleiro[3]=='X'&& tabuleiro[4]=='X' && tabuleiro[5]=='X') vencedor='X';
		else if(tabuleiro[6]=='X'&& tabuleiro[7]=='X' && tabuleiro[8]=='X') vencedor='X';

		else if(tabuleiro[0]=='X'&& tabuleiro[3]=='X' && tabuleiro[6]=='X')vencedor='X';
		else if(tabuleiro[1]=='X'&& tabuleiro[4]=='X' && tabuleiro[7]=='X') vencedor='X';
		else if(tabuleiro[2]=='X'&& tabuleiro[5]=='X' && tabuleiro[8]=='X') vencedor='X';

		else if(tabuleiro[0]=='X'&& tabuleiro[4]=='X' && tabuleiro[8]=='X') vencedor='X';
		else if(tabuleiro[6]=='X'&& tabuleiro[4]=='X' && tabuleiro[2]=='X') vencedor='X';
		else if(tabuleiro[0]!=' ' && tabuleiro[1]!=' ' &&tabuleiro[2]!=' ' && tabuleiro[3]!=' '&& tabuleiro[4]!=' ' && tabuleiro[5]!=' ' && tabuleiro[6]!=' '&& tabuleiro[6]!=' ' && tabuleiro[7]!=' ') vencedor='e';

	
	return vencedor;
}

int jogo_da_velha::verif_jogada(int pos)
{
    if(tabuleiro[pos]==' ') return 1;
	else return 0;
}

int jogo_da_velha::Button_action(int pos)
{
    if(verif_jogada(pos) && testa_vencedor()==0)
       {

           atualiza_tab(pos);

            client->sendmove(tabuleiro,from);
            winner();
            table::getInstance()->disable_table();
       }
    return(0);
}
void jogo_da_velha::receiveMove(const QString &move)
{
    testa_vencedor();
    tabuleiro=move;
    update_table();
    winner();
    table::getInstance()->enable_table();
}

void jogo_da_velha::update_table(void)
{
    int pos;
    for(pos=0 ; pos<=PosMax ;pos++ )
    {

        if(tabuleiro[pos]=='X') table::getInstance()->Print_X(pos);
        else if(tabuleiro[pos]=='O') table::getInstance()->Print_O(pos);
                // imprime o nada.
    }
}

char jogo_da_velha::testa_vencedor(void)
{
	return vencedor;
}

void jogo_da_velha::Bip_Buzzer(void) /*SystemSounds::Beep->Play()*/
{
// sounds
}

int jogo_da_velha::estatistica_X(void)
{
	return(jogador_X);
}

int jogo_da_velha::estatistica_O(void)
{
	return(jogador_O);
}

int jogo_da_velha::status_empate(void)
{
	return(empate);
}

void jogo_da_velha::atualiza_vencedor(void)
{
	if(vencedor=='X') jogador_X++;
	if(vencedor=='O') jogador_O++;
	if(vencedor=='e') empate++;
}

void jogo_da_velha::winner(void)
{
    char ret;
    int option;

    ret=teste_win();
    atualiza_vencedor();

    if(ret=='X')  option=table::getInstance()->show_X_winner();
    else if(ret=='O')  option=table::getInstance()->show_O_winner();
    else if(ret=='e')  option=table::getInstance()->show_Draw();

    if( option == QMessageBox::Ok) close_game();
}
void jogo_da_velha::close_game()
{
    table::getInstance()->close();
}
