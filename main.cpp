#include "Player.h"
#include "Board.h"
#include <iostream>
#include <vector>

// Funkcje pomocnicze
void cleenScreen() {
#ifdef _WIN32
    system("cls"); // Wyczyść ekran na Windows
#else
    system("clear"); 
#endif
}

void pauseBetweenTours() {
    std::cout << "Nacisnij Enter, aby przekazac ture przeciwnikowi...";
    std::cin.ignore(); // Oczekiwanie na Enter
    std::cin.get();    // Kolejne oczekiwanie, gdy jest buforowane wejście
}

// Funkcja ustawiania statków dla gracza
void setShipsForPlayer(Player& player) {
    std::cout << player.name << " - ustaw swoje statki.\n";
    player.board.showBoard(false); 
    player.setShipsManually();
    cleenScreen();
}

// Funkcja obsługi tury gracza
bool serveTour(Player& activePlayer, Player& opponent, int& tour) {
    std::cout << activePlayer.name << " - Twoja tura!\n";
    activePlayer.board.showBoard(false);

    int x, y;
    bool correct = false;
    while (!correct) {
        std::cout << "Podaj wspolrzedne do strzalu (x y): ";
        std::cin >> x >> y;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            correct = true;
            if (activePlayer.shootToOpponent(x, y)) {
                if (opponent.ifAllSunk()) {
                    std::cout << "Gratulacje! " << activePlayer.name << " wygral!\n";
                    return true; // Koniec gry
                } else {
                    std::cout << "Masz kolejna ture!\n";
                }
            } else {
                tour = (tour == 1) ? 2 : 1;
                pauseBetweenTours();
                cleenScreen();
            }
        } else {
            std::cout << "Niepoprawne wspolrzędne! Wprowadz liczby od 0 do 9.\n";
        }
    }

    return false; // Gra trwa dalej
}

// Funkcja pojedynczej rozgrywki
bool game(int& player1Wins, int& player2Wins) {
    Player player1("Gracz 1");
    Player player2("Gracz 2");

    // Ustawienie statków
    setShipsForPlayer(player1);
    setShipsForPlayer(player2);

    int tour = 1; // 1 dla Gracza 1, 2 dla Gracza 2
    bool ifEnd = false;

    while (!ifEnd) {
        Player& activePlayer = (tour == 1) ? player1 : player2;
        Player& opponent = (tour == 1) ? player2 : player1;

        ifEnd = serveTour(activePlayer, opponent, tour);
    }

    if (tour == 1) {
        player1Wins++;
    } else {
        player2Wins++;
    }

    std::cout << "Czy chcesz zagrac ponownie? (T/N): ";
    char choice;
    std::cin >> choice;
    return !(choice == 'N' || choice == 'n'); // Zwraca true, jeśli gracz chce kontynuować
}

// Funkcja główna
int main() {
    int firstPlayerWins = 0;
    int secondPlayerWins = 0;
    bool playAgain = true;

    while (playAgain) {
        playAgain = game(firstPlayerWins, secondPlayerWins);
        std::cout << "Wyniki:\n";
        std::cout << "Gracz 1: " << firstPlayerWins << " wygranych\n";
        std::cout << "Gracz 2: " << secondPlayerWins << " wygranych\n";
    }

    std::cout << "Dziekujemy za gre!" << std::endl;
    return 0;
}
