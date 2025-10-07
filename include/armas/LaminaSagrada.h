//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_LAMINASAGRADA_H
#define STRATEGYCPP_LAMINASAGRADA_H


#include "../Arma.h"
#include "../Personagem.h"

class LaminaSagrada : public Arma {
public:
    LaminaSagrada() : Arma("Lamina Sagrada", 14, 10, TipoArma::Sagrada) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override {
        return (a.getForca() >= 10 || a.getInteligencia() >= 10);
    }
    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* /*area*/) override {
        if (!atacante.podeUsar(getTipo()) || !atendeRequisitos(atacante)) { std::cout << "  >> Nao atende.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int dano = aplicarCriticoSeOcorrer(getDanoBase());
        int aplicado = alvo.receberDano(dano);
        if (Utils::chance(20)) {
            atacante.curar(10);
            bool limpou = atacante.removerUmDebuff();
            std::cout << "  >> Luz Curativa: +" << 10 << " HP" << (limpou ? " e purificacao!\n" : "!\n");
        }
        return aplicado;
    }
};


#endif //STRATEGYCPP_LAMINASAGRADA_H