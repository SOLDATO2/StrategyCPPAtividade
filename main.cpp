#include <iostream>
#include "include/Utils.h"
#include "include/enums/Classe.h"
#include "include/enums/TipoArma.h"
#include "include/Personagem.h"
#include "include/Batalha.h"
// Armas
#include "include/armas/EspadaLonga.h"
#include "include/armas/ArcoElfico.h"
#include "include/armas/CajadoArcano.h"
#include "include/armas/MachadoGuerra.h"
#include "include/armas/AdagaSombria.h"
#include "include/armas/LaminaSagrada.h"

int main() {
    Utils::seed();

    //Personagens
    Personagem* guerreiro = new Personagem("Thorgar", Classe::Guerreiro, 15, 8, 5, 120, 50);
    Personagem* arqueiro  = new Personagem("Elandra", Classe::Arqueiro,   8, 15, 7,  90, 80);
    Personagem* mago      = new Personagem("Aramil",  Classe::Mago,       5,  7, 18,  70,150);
    Personagem* paladino  = new Personagem("Sir Alden", Classe::Paladino,12,10,12, 110,100); // hibrido

    //Armas
    Arma* espada   = new EspadaLonga();
    Arma* arco     = new ArcoElfico();
    Arma* cajado   = new CajadoArcano();
    Arma* machado  = new MachadoGuerra();
    Arma* adaga    = new AdagaSombria();
    Arma* sagrada  = new LaminaSagrada(); // extensao

    // Loadouts iniciais
    guerreiro->setArma(espada);
    arqueiro->setArma(arco);
    mago->setArma(cajado);
    paladino->setArma(sagrada);

    // vantagem furtiva para mostrar efeito da adaga
    arqueiro->surpreenderProximoAtaque = true;

    // Batalha 2x2
    Batalha b;
    b.adicionarA(guerreiro);
    b.adicionarA(arqueiro);
    b.adicionarB(mago);
    b.adicionarB(paladino);

    b.rodar();

    // arqueiro troca para Adaga, troca de strategy

    std::cout << "\n== Troca de arma/Strategy em runtime ==\n";
    // Reset leve (apenas vida/mana para reutilizar instancias)
    // Para simplicidade, destruimos e recriamos:
    delete guerreiro; delete arqueiro; delete mago; delete paladino;
    guerreiro = new Personagem("Thorgar", Classe::Guerreiro, 15, 8, 5, 120, 50);
    arqueiro  = new Personagem("Elandra", Classe::Arqueiro,   8, 15, 7,  90, 80);
    mago      = new Personagem("Aramil",  Classe::Mago,       5,  7, 18,  70,150);
    paladino  = new Personagem("Sir Alden", Classe::Paladino,12,10,12, 110,100);

    guerreiro->setArma(machado); // agora stun
    arqueiro->setArma(arco);
    mago->setArma(cajado);
    paladino->setArma(sagrada);

    // Turno 1 manual
    std::vector<Personagem*> area;
    std::cout << "\n-- Turno 1 --\n";
    guerreiro->atacar(*mago);
    if (paladino->estaVivo()) area.push_back(paladino);
    arqueiro->atacar(*mago, &area); // Arco em area
    if (paladino->estaVivo()) paladino->atacar(*guerreiro);
    if (mago->estaVivo()) mago->atacar(*arqueiro);
    guerreiro->processarEfeitosDeTurno();
    arqueiro->processarEfeitosDeTurno();
    mago->processarEfeitosDeTurno();
    paladino->processarEfeitosDeTurno();

    // Turno 2: troca Strategy do arqueiro
    std::cout << "\n-- Turno 2 (troca Arco->Adaga) --\n";
    arqueiro->setArma(adaga);
    arqueiro->surpreenderProximoAtaque = true;
    if (mago->estaVivo()) guerreiro->atacar(*mago);
    if (paladino->estaVivo()) arqueiro->atacar(*paladino);
    if (paladino->estaVivo()) paladino->atacar(*guerreiro);
    if (mago->estaVivo()) mago->atacar(*arqueiro);
    guerreiro->processarEfeitosDeTurno();
    arqueiro->processarEfeitosDeTurno();
    mago->processarEfeitosDeTurno();
    paladino->processarEfeitosDeTurno();

    // limpeza
    delete espada; delete arco; delete cajado; delete machado; delete adaga; delete sagrada;
    delete guerreiro; delete arqueiro; delete mago; delete paladino;
    return 0;
}
