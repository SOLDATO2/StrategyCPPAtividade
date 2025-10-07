//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_CAJADOARCANO_H
#define STRATEGYCPP_CAJADOARCANO_H


#include "../Arma.h"
#include "../StatusEffect.h"
#include "../Personagem.h"

class CajadoArcano : public Arma {
public:
    CajadoArcano() : Arma("Cajado Arcano", 8, 25, TipoArma::Cajado) {}

    [[nodiscard]]
    bool atendeRequisitos(const Personagem& a) const override {
        return a.getInteligencia() >= 12;
    }

    int atacar(Personagem& atacante, Personagem& alvo, std::vector<Personagem*>* /*area*/) override {
        if (!atacante.podeUsar(getTipo()) || !atendeRequisitos(atacante)) { std::cout << "  >> Não atende.\n"; return 0; }
        if (!atacante.gastarMana(getCustoMana())) { std::cout << "  >> Mana insuficiente.\n"; return 0; }

        int dano = aplicarCriticoSeOcorrer(getDanoBase());
        int aplicado = alvo.receberDano(dano);
        alvo.adicionarEfeito(new Queimadura());
        std::cout << "  >> Bola de Fogo aplicada.\n";
        return aplicado;
    }
};


#endif //STRATEGYCPP_CAJADOARCANO_H