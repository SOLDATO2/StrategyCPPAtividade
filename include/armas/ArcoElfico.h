//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_ARCOELFICO_H
#define STRATEGYCPP_ARCOELFICO_H


#include "../Arma.h"
#include "../Personagem.h"

class ArcoElfico : public Arma {
public:
    ArcoElfico() : Arma("Arco Elfico", 12, 15, TipoArma::Arco) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override {
        return a.getDestreza() >= 8;
    }

    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* area) override {
        if (!atacante.podeUsar(getTipo()) || !atendeRequisitos(atacante)) { std::cout << "  >> Nao atende.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int total = 0;
        int danoAlvo = aplicarCriticoSeOcorrer(getDanoBase());
        total += alvo.receberDano(danoAlvo);

        if (area) {
            for (auto* inimigo : *area) if (inimigo && inimigo->estaVivo()) {
                int danoAoE = aplicarCriticoSeOcorrer(getDanoBase());
                inimigo->receberDano(danoAoE);
            }
            std::cout << "  >> Chuva de Flechas atingiu a area.\n";
        }
        return total;
    }
};


#endif //STRATEGYCPP_ARCOELFICO_H