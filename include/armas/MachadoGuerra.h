//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_MACHADOGUERRA_H
#define STRATEGYCPP_MACHADOGUERRA_H


#include "../Arma.h"
#include "../StatusEffect.h"
#include "../Personagem.h"

class MachadoGuerra : public Arma {
public:
    MachadoGuerra() : Arma("Machado de Guerra", 18, 5, TipoArma::Machado) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override {
        return a.getForca() >= 15;
    }

    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* /*area*/) override {
        if (!atacante.podeUsar(getTipo()) || !atendeRequisitos(atacante)) { std::cout << "  >> Nao atende.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int dano = aplicarCriticoSeOcorrer(getDanoBase());
        int aplicado = alvo.receberDano(dano);
        if (Utils::chance(25)) {
            alvo.adicionarEfeito(new Atordoado());
            std::cout << "  >> Golpe Esmagador! Atordoado.\n";
        }
        return aplicado;
    }
};


#endif //STRATEGYCPP_MACHADOGUERRA_H