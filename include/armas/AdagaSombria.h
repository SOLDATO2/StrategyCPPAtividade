//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_ADAGASOMBRIA_H
#define STRATEGYCPP_ADAGASOMBRIA_H


#include "../Arma.h"
#include "../Personagem.h"

class AdagaSombria : public Arma {
public:
    AdagaSombria() : Arma("Adaga Sombria", 10, 10, TipoArma::Adaga) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override {
        return a.getDestreza() >= 12;
    }

    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* /*area*/) override {
        if (!atacante.podeUsar(getTipo()) || !atendeRequisitos(atacante)) { std::cout << "  >> Não atende.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int base = getDanoBase();
        bool desprevenido = atacante.surpreenderProximoAtaque || alvo.estaAtordoado();
        if (desprevenido) {
            base *= 3;
            atacante.surpreenderProximoAtaque = false;
            std::cout << "  >> Ataque Furtivo! Dano triplo.\n";
        }
        int dano = aplicarCriticoSeOcorrer(base);
        return alvo.receberDano(dano);
    }
};


#endif //STRATEGYCPP_ADAGASOMBRIA_H