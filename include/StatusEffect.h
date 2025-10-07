//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_STATUSEFFECT_H
#define STRATEGYCPP_STATUSEFFECT_H


#include <string>
#include <iostream>


class Personagem;

class StatusEffect {
protected:
    std::string nome;
    int turnosRestantes;
public:
    StatusEffect(const std::string& n, int t) : nome(n), turnosRestantes(t) {}
    virtual ~StatusEffect() = default;

    const std::string& getNome() const {
        return nome;
    }

    int getTurnosRestantes() const {
        return turnosRestantes;
    }

    // Interface
    virtual int  danoPorTurno() const = 0;     // 0 se não causar dano periódico
    virtual bool eAtordoamento() const {
        return false;
    }

    // avança 1 turno; retorna true se o efeito expirou
    bool tick() {
        turnosRestantes--;
        return (turnosRestantes <= 0);
    }
};

// ----- Efeitos concretos -----

class Sangramento : public StatusEffect {
    int dpt;
public:
    Sangramento(int dano=5, int turnos=3)
        : StatusEffect("Sangramento", turnos), dpt(dano) {}
    int danoPorTurno() const override { return dpt; }
};

class Queimadura : public StatusEffect {
    int dpt;
public:
    Queimadura(int dano=10, int turnos=2)
        : StatusEffect("Queimadura", turnos), dpt(dano) {}
    int danoPorTurno() const override { return dpt; }
};

class Atordoado : public StatusEffect {
public:
    Atordoado(int turnos=1) : StatusEffect("Atordoado", turnos) {}
    int  danoPorTurno() const override { return 0; }
    bool eAtordoamento() const override { return true; }
};

#endif //STRATEGYCPP_STATUSEFFECT_H