//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_BATALHA_H
#define STRATEGYCPP_BATALHA_H


#include <vector>
#include <algorithm>
#include <iostream>
#include "Personagem.h"
#include "enums/Classe.h"
#include "enums/TipoArma.h"

class Batalha {
private:
    std::vector<Personagem*> equipeA;
    std::vector<Personagem*> equipeB;
    int turno;
public:
    Batalha() : turno(1) {}

    void adicionarA(Personagem* p) { equipeA.push_back(p); }
    void adicionarB(Personagem* p) { equipeB.push_back(p); }

    static bool timeVivo(const std::vector<Personagem*>& time) {
        for (auto* p : time) if (p->estaVivo()) return true;
        return false;
    }

    bool estaNoTimeA(Personagem* p) const {
        return std::find(equipeA.begin(), equipeA.end(), p) != equipeA.end();
    }

    std::vector<Personagem*> vivosDoOutroTime(Personagem* atacante) {
        std::vector<Personagem*> result;
        const auto& alvoTime = estaNoTimeA(atacante) ? equipeB : equipeA;
        for (auto* p : alvoTime) if (p->estaVivo()) result.push_back(p);
        return result;
    }

    void processarFimDoTurno() {
        for (auto* p : equipeA) if (p->estaVivo()) p->processarEfeitosDeTurno();
        for (auto* p : equipeB) if (p->estaVivo()) p->processarEfeitosDeTurno();
        turno++;
    }

    void rodadaTime(std::vector<Personagem*>& timeAtacante) {
        for (auto* p : timeAtacante) {
            if (!p->estaVivo()) continue;
            auto alvos = vivosDoOutroTime(p);
            if (alvos.empty()) break;
            Personagem* alvo = alvos.front();

            std::vector<Personagem*> area;
            if (p->getArma() && p->getArma()->getTipo() == TipoArma::Arco) {
                for (size_t i = 1; i < alvos.size(); ++i) area.push_back(alvos[i]);
                p->atacar(*alvo, &area);
            } else {
                p->atacar(*alvo, nullptr);
            }
        }
    }

    void rodar() {
        std::cout << "=== BATALHA INICIO ===\n\n";
        while (timeVivo(equipeA) && timeVivo(equipeB)) {
            std::cout << "----- Novo Turno -----\n";
            rodadaTime(equipeA);
            if (!timeVivo(equipeA) || !timeVivo(equipeB)) break;
            rodadaTime(equipeB);
            processarFimDoTurno();
            std::cout << "\n";
        }
        std::cout << "=== BATALHA FIM ===\n";
        bool aVenceu = timeVivo(equipeA);
        bool bVenceu = timeVivo(equipeB);
        if (aVenceu && !bVenceu) std::cout << "Time A venceu!\n";
        else if (!aVenceu && bVenceu) std::cout << "Time B venceu!\n";
        else std::cout << "Empate tecnico.\n";
    }
};


#endif //STRATEGYCPP_BATALHA_H