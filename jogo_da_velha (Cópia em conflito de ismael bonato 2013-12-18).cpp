#include "table.h"

jogo_da_velha::jogo_da_velha(Client *client,QString from)
{

    this->client = client;

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
	
	z=0;
	vencedor=0;

}

jogo_da_velha::~jogo_da_velha(void)
{

}

void jogo_da_velha::mudar_jogador()
{
	z=~z;
}

void jogo_da_velha::atualiza_tab(int i)
{
	if(z==0) tabuleiro[i]='O';
	else tabuleiro[i]='X';
    update_table();
}

int jogo_da_velha::verif_jogador()
{
	return(z);
}

char jogo_da_velha::teste_win()
{
     if(z==0)
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
    }
    else if(z!=0)
    {
		if(tabuleiro[0]=='X'&& tabuleiro[1]=='X' && tabuleiro[2]=='X') vencedor='X';
		else if(tabuleiro[3]=='X'&& tabuleiro[4]=='X' && tabuleiro[5]=='X') vencedor='X';
		else if(tabuleiro[6]=='X'&& tabuleiro[7]=='X' && tabuleiro[8]=='X') vencedor='X';

		else if(tabuleiro[0]=='X'&& tabuleiro[3]=='X' && tabuleiro[6]=='X')vencedor='X';
		else if(tabuleiro[1]=='X'&& tabuleiro[4]=='X' && tabuleiro[7]=='X') vencedor='X';
		else if(tabuleiro[2]=='X'&& tabuleiro[5]=='X' && tabuleiro[8]=='X') vencedor='X';

		else if(tabuleiro[0]=='X'&& tabuleiro[4]=='X' && tabuleiro[8]=='X') vencedor='X';
		else if(tabuleiro[6]=='X'&& tabuleiro[4]=='X' && tabuleiro[2]=='X') vencedor='X';
		else if(tabuleiro[0]!=' ' && tabuleiro[1]!=' ' &&tabuleiro[2]!=' ' && tabuleiro[3]!=' '&& tabuleiro[4]!=' ' && tabuleiro[5]!=' ' && tabuleiro[6]!=' '&& tabuleiro[6]!=' ' && tabuleiro[7]!=' ') vencedor='e';
    }
	
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
           winner();
           //client->sendmove(tabuleiro,from);


       }
    return(0);
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

void jogo_da_velha::reiniciar(void)
{
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

    z=0;
    zera_vencedor();

    table::getInstance()->restart_tictactoe();
}

char jogo_da_velha::testa_vencedor(void)
{
	return vencedor;
}

void jogo_da_velha::zera_vencedor(void)
{
	vencedor=0;
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

    if( option == QMessageBox::No) table::getInstance()->close();
    else if(option == QMessageBox::Yes) reiniciar();
}

void jogo_da_velha::restart()
{

}

void jogo_da_velha::update_modegame()
{

}
