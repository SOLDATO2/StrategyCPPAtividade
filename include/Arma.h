//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_ARMA_H
#define STRATEGYCPP_ARMA_H


#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "Utils.h"
#include "enums/TipoArma.h"

class Personagem; // forward declaration

class Arma {
protected:
    std::string nome;
    int danoBase;
    int custoMana;
    TipoArma tipo;
public:
    Arma(const std::string& n, int dano, int custo, TipoArma t)
        : nome(n), danoBase(dano), custoMana(custo), tipo(t) {}
    virtual ~Arma() = default;

    const std::string& getNome() const { return nome; }
    int  getDanoBase() const { return danoBase; }
    int  getCustoMana() const { return custoMana; }
    TipoArma getTipo() const { return tipo; }

    virtual bool atendeRequisitos(const Personagem& atacante) const = 0;
    virtual int  atacar(Personagem& atacante, Personagem& alvo,
                        std::vector<Personagem*>* areaTargets) = 0;

    static int aplicarCriticoSeOcorrer(int base) {
        if (Utils::chance(10)) {
            std::cout << "  >> **Critico!**\n";
            return (int)std::round(base * 1.5);
        }
        return base;
    }
};


#endif //STRATEGYCPP_ARMA_H