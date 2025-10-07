//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_ESPADALONGA_H
#define STRATEGYCPP_ESPADALONGA_H


#include "../Arma.h"
#include "../StatusEffect.h"
#include "../Personagem.h"

class EspadaLonga : public Arma {
public:
    EspadaLonga() : Arma("Espada Longa", 15, 0, TipoArma::Espada) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override { return a.getForca() >= 10; }
    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* /*area*/) override {
        if (!atacante.podeUsar(getTipo())) { std::cout << "  >> Sem proficiência.\n"; return 0; }
        if (!atendeRequisitos(atacante)) { std::cout << "  >> Requisito não atendido.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int dano = aplicarCriticoSeOcorrer(getDanoBase());
        int aplicado = alvo.receberDano(dano);
        if (Utils::chance(30)) alvo.adicionarEfeito(new Sangramento());
        return aplicado;
    }
};


#endif //STRATEGYCPP_ESPADALONGA_H