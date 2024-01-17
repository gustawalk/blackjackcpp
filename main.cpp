#include <iostream>
#include <string>
#include <cctype>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

//funcoes do jogo
void game_result(int winner);
void bet_game();
void start_game();
int calc_result();
int generate_cards(int qtd_cartas);
void draw_game();
void lose_game(int loser);

//funcoes pequenas

void clear(){system("clear || cls");}
void sleep(int segundos){this_thread::sleep_for(chrono::seconds(segundos));}
// variaveis dos jogadores

string nome_player_um, nome_player_dois;
int dinheiro_base = 500;
int dinheiro_player_um = dinheiro_base, dinheiro_player_dois = dinheiro_base;
bool blow_player_um = false, blow_player_dois = false;
int pontos_player_um = 0, pontos_player_dois = 0;
int bet_player_um, bet_player_dois, bet_total, bet_min = 50;

int rodada = 1;

int main(){
    srand(time(0));
    char start;
    cout << "Mini-game de duas pessoas baseado em apostas, o primeiro que ficar sem dinheiro, perde!" << endl;
    cout << "Deseja começar? Y/n " << endl;
    cin >> start;
    start = tolower(start);

    if(start == 'y'){
        clear();
        start_game();
    }else if(start == 'n'){
        cout << "ta fazendo oq aqui entao maluco";
    }else{
        cout << "voce só pode ser burro ne no minimo";
    }
    return 0;
}

void start_game(){
    cout << "Digite o nome do primeiro jogador: ";
    cin >> nome_player_um;
    clear();
    cout << "Digite o nome do segundo jogador: ";
    cin >> nome_player_dois;
    clear();
    cout << nome_player_um << " e " << nome_player_dois << " ambos começam com R$" << dinheiro_base << flush;
    sleep(2);
    clear();
    bet_game();
}

void bet_game(){
    bet_player_um = 0;
    bet_player_dois = 0;

    bool valid_bet;
    // bet player 1
    do{
        valid_bet = false;

        cout << nome_player_um << " quanto deseja apostar? (R$" << dinheiro_player_um << ") - Min(R$50)" << endl << "R$";
        if(dinheiro_player_um > bet_min){
            if(cin >> bet_player_um){
                valid_bet = true;
            }else{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }else{
            cout << dinheiro_player_um;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            bet_player_um = dinheiro_player_um;
        }

        clear();
    }while(bet_player_um > dinheiro_player_um || bet_player_um <= 0 || bet_player_um < 50 || !valid_bet);

    dinheiro_player_um -= bet_player_um;

    // bet player 2
    do{
        valid_bet = false;
        cout << nome_player_dois << " quanto deseja apostar? (R$" << dinheiro_player_dois << ") - Min(R$50)" << endl << "R$";
        if(dinheiro_player_dois > bet_min){
            if(cin >> bet_player_dois){
                valid_bet = true;
            }else{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }else{
            cout << dinheiro_player_dois;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            bet_player_dois = dinheiro_player_dois;
        }
        clear();
    }while(bet_player_dois > dinheiro_player_dois || bet_player_dois <= 0 || bet_player_dois < 50 || !valid_bet);

    dinheiro_player_dois -= bet_player_dois;



    bet_total = bet_player_um + bet_player_dois;

    cout << "A aposta total está em R$" << bet_total << flush;
    sleep(2);
    clear();
    draw_game();
}

void draw_game(){

    cout << "Rodada " << rodada << " - Valendo R$" << bet_total << endl << endl;

    int qtd_cartas;
    int turno = 1;
    string escolha = "hit";

    while(escolha == "hit" && turno == 1 && !blow_player_um){   

        cout << nome_player_um << ", quantas cartas você deseja? ";
        cin >> qtd_cartas;

        pontos_player_um += generate_cards(qtd_cartas);

        if(pontos_player_um <= 21){
            cout << endl << nome_player_um << ", você tem " << pontos_player_um;
            if(pontos_player_um > 1){
                cout << " pontos";
            }else{
                cout << " ponto";
            }
            cout << ", o que deseja fazer? hit/stop" << endl;
            cin >> escolha;
        }else{
            cout << "Você estourou seu burro ganancioso judeu!!!" << flush;
            sleep(2);
            blow_player_um = true;
        }
    }

    clear();

    cout << "Rodada " << rodada << " - Valendo R$" << bet_total << endl << endl;

    turno = 2;
    escolha = "hit";
    qtd_cartas = 0;

    while(escolha == "hit" && turno == 2 && !blow_player_dois){

        cout << nome_player_dois << ", quantas cartas você deseja? ";
        cin >> qtd_cartas;

        pontos_player_dois += generate_cards(qtd_cartas);

        if(pontos_player_dois <= 21){
            cout << endl << nome_player_dois << ", você tem " << pontos_player_dois;
            if(pontos_player_dois > 1){
                cout << " pontos";
            }else{
                cout << " ponto";
            }
            cout << ", o que deseja fazer? hit/stop" << endl;
            cin >> escolha;
        }else{
            cout << "Burro pra caralho hein amigo" << flush;
            sleep(2);
            blow_player_dois = true;
        }
    }
    clear();
    cout << "Calculando jogo..." << flush;
    sleep(2);
    clear();
    game_result(calc_result());
}

int calc_result(){
    
    if(!blow_player_um && !blow_player_dois){
        if(pontos_player_um > pontos_player_dois){ //se pontos do p1 for maior, p1 ganha
            return 1;
        }else if(pontos_player_um < pontos_player_dois){ //se pontos do p2 for maior, p2 ganha
            return 2;
        }else{
            return 3; //se pontos forem iguais, empate
        }
    }else if(!blow_player_um && blow_player_dois){ //se p1 nao estourou e p2 estourou, p1 ganha
        return 1;
    }else if(blow_player_um && !blow_player_dois){ //se p1 estourou e p2 nao estourou, p2 ganha
        return 2;
    }else{
        return 3;  //se ambos estouraram, empate
    }
}

void game_result(int winner){
    clear();
    switch(winner){
        case 1:{
            cout << nome_player_um << ", parabéns, você ganhou!!";
            dinheiro_player_um += bet_total;
        }break;
        case 2:{
            cout << nome_player_dois << ", parabéns, você ganhou!!";
            dinheiro_player_dois += bet_total;
        }break;
        case 3:{
            cout << "Parece que deu empate, dois ruim fudido";
        }break;
        default:{
            cout << "Algo deu errado :(";
        }
    }

    if(dinheiro_player_um > 0 && dinheiro_player_dois > 0){
        cout << endl << endl << "Dinheiro atual disponivel: " << endl;
        cout << nome_player_um << ": " << dinheiro_player_um << endl;
        cout << nome_player_dois << ": " << dinheiro_player_dois << endl << flush;
        sleep(3);
        rodada++;
        bet_game();
    }else{
        cout << "Temos um vencedor!!" << flush;
        sleep(2);
        clear();
        if(dinheiro_player_um <= 0){
            lose_game(1);
        }else if(dinheiro_player_dois <= 0){
            lose_game(2);
        }
    }
}

void lose_game(int loser){
    char escolha;
    switch (loser){
        case 1:{
            cout << nome_player_um << " voce perdeu seu bosta lixo merdaa";
        }break;
        case 2:{
            cout << nome_player_dois << " o " << nome_player_um << " pisou na sua bola seu bosta";
        }break;
        default:{
            cout << "algo deu merda foi mal";
        }
    }

    cout << endl << endl << "Deseja jogar novamente? Y/n" << endl;
    cin >> escolha;
    escolha = tolower(escolha);

    if(escolha == 'y'){
        dinheiro_base = 500;
        dinheiro_player_um = dinheiro_base;
        dinheiro_player_dois = dinheiro_base;
        blow_player_um = false;
        blow_player_dois = false;
        pontos_player_um = 0;
        pontos_player_dois = 0;

        main();
    }else{
        cout << "fodase entao seu bosta";
    }
}

int generate_cards(int qtd){
    int soma = 0;
    
    vector<int> cartas;

    for(int i = 0; i < qtd; i++){

        int valor = rand() % 13 + 1;

        if(valor == 1){
            cout << "----------" << endl;
            cout << "| " << "A" << "      |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|      " << "A" <<" |" << endl;
            cout << "----------" << endl;
        }
        else if(valor < 10){
            cout << "----------" << endl;
            cout << "| " << valor << "      |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|      " << valor <<" |" << endl;
            cout << "----------" << endl;
        }else if(valor == 10){
            cout << "----------" << endl;
            cout << "| " << valor << "     |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|     " << valor <<" |" << endl;
            cout << "----------" << endl;
        }else if(valor == 11){
            cout << "----------" << endl;
            cout << "| " << "J" << "      |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|      " << "J" <<" |" << endl;
            cout << "----------" << endl;
        }else if(valor == 12){
            cout << "----------" << endl;
            cout << "| " << "Q" << "      |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|        |" << endl;
            cout << "|      " << "Q" <<" |" << endl;
            cout << "----------" << endl;
        }else if(valor == 13){
            cout << "----------" << endl;
            cout << "| " << "K" << "      |"<< endl;
            cout << "|        |" << endl;
            cout << "|        |" <<  endl;
            cout << "|        |" << endl;
            cout << "|      " << "K" <<" |" << endl;
            cout << "----------" << endl;
        }

        cartas.push_back(valor);

        size_t qtd_cartas = cartas.size();

        if(qtd_cartas == 2){
            if((cartas[0] == 1 || cartas[1] == 1) && (cartas[0] > 10 || cartas[1] > 10)){
                return 21;
            }
        }

        if(valor > 10){
            valor = 10;
        }
        soma += valor;
    }

    return soma;
}