//
// Created by sQuAde on 10/7/2025.
//
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "enums/Classe.h"
#include "enums/TipoArma.h"
#include "Utils.h"
#include "Arma.h"
#include "StatusEffect.h"

class Personagem {
private:
    std::string nome;
    Classe classe;
    int forca, destreza, inteligencia;
    int vidaMax, vida;
    int manaMax, mana;
    Arma* arma;
    std::vector<StatusEffect*> efeitos;

public:
    // usado pela Adaga Sombria (ataque furtivo)
    bool surpreenderProximoAtaque;

    Personagem(const std::string& n, Classe c, int f, int d, int i, int v, int m)
        : nome(n), classe(c), forca(f), destreza(d), inteligencia(i),
          vidaMax(v), vida(v), manaMax(m), mana(m), arma(nullptr),
          surpreenderProximoAtaque(false) {}

    ~Personagem() {
        for (auto* e : efeitos) delete e;
        efeitos.clear();
    }

    // ---------- Getters ----------
    [[nodiscard]] const std::string& getNome() const { return nome; }
    [[nodiscard]] Classe getClasse() const { return classe; }
    [[nodiscard]] int getForca() const { return forca; }
    [[nodiscard]] int getDestreza() const { return destreza; }
    [[nodiscard]] int getInteligencia() const { return inteligencia; }
    [[nodiscard]] int getVida() const { return vida; }
    [[nodiscard]] int getMana() const { return mana; }
    [[nodiscard]] int getVidaMax() const { return vidaMax; }
    [[nodiscard]] int getManaMax() const { return manaMax; }

    // ---------- Utilitários ----------
    void curar(int qtd) { vida = std::min(vida + qtd, vidaMax); }
    void ganharMana(int qtd) { mana = std::min(mana + qtd, manaMax); }

    [[nodiscard]] bool estaVivo() const { return vida > 0; }

    [[nodiscard]] bool estaAtordoado() const {
        for (auto* e : efeitos) if (e->eAtordoamento()) return true;
        return false;
    }

    void setArma(Arma* a) { arma = a; }
    [[nodiscard]] Arma* getArma() const { return arma; }

    void adicionarEfeito(StatusEffect* e) {
        if (!e) return;
        std::cout << "  >> " << nome << " recebe efeito: " << e->getNome() << "\n";
        efeitos.push_back(e);
    }

    [[nodiscard]] bool tentarEsquivar() const {
        if (classe == Classe::Arqueiro) {
            if (Utils::chance(25)) return true;
        }
        return false;
    }

    int receberDano(int danoBase) {
        if (!estaVivo()) return 0;

        // Esquiva do Arqueiro
        if (tentarEsquivar()) {
            std::cout << "  >> " << nome << " esquivou!\n";
            return 0;
        }

        int dano = danoBase;
        // Passivas defensivas
        if (classe == Classe::Guerreiro)      dano = (int)std::round(dano * 0.8); // -20%
        else if (classe == Classe::Paladino)  dano = (int)std::round(dano * 0.9); // -10%

        dano = std::max(0, dano);
        vida = std::max(0, vida - dano);
        std::cout << "  >> " << nome << " recebe " << dano
                  << " de dano (HP " << vida << "/" << vidaMax << ")\n";
        return dano;
    }

    bool gastarMana(int custo) {
        if (mana < custo) return false;
        mana -= custo;
        return true;
    }

    [[nodiscard]] bool podeUsar(TipoArma t) const {
        switch (classe) {
            case Classe::Guerreiro: return (t == TipoArma::Espada || t == TipoArma::Machado || t == TipoArma::Sagrada);
            case Classe::Arqueiro:  return (t == TipoArma::Arco   || t == TipoArma::Adaga);
            case Classe::Mago:      return (t == TipoArma::Cajado || t == TipoArma::Adaga || t == TipoArma::Sagrada);
            case Classe::Paladino:  return (t == TipoArma::Espada || t == TipoArma::Sagrada || t == TipoArma::Machado);
        }
        return false;
    }

    // ---------- Núcleo "Java-like": Personagem processa os efeitos ----------
    void processarEfeitosDeTurno() {
        std::vector<StatusEffect*> vivos;
        vivos.reserve(efeitos.size());

        for (auto* e : efeitos) {
            if (!e) continue;

            // dano periódico (se houver)
            const int dpt = e->danoPorTurno();
            if (dpt > 0) {
                std::cout << "  >> (" << e->getNome() << ") dano " << dpt
                          << " em " << nome << "\n";
                receberDano(dpt);
            }

            // avança o efeito; se expirou, descarta
            const bool expirou = e->tick();
            if (expirou) {
                std::cout << "  >> Efeito expirou em " << nome << ": "
                          << e->getNome() << "\n";
                delete e;
            } else {
                vivos.push_back(e);
            }
        }
        efeitos.swap(vivos);

        // passivas por turno
        if (classe == Classe::Mago) {
            ganharMana(10);
            std::cout << "  >> Regeneração de mana (Mago) em " << nome
                      << ": +10 (" << mana << ")\n";
        } else if (classe == Classe::Paladino) {
            ganharMana(5);
            std::cout << "  >> Regeneração de mana (Paladino) em " << nome
                      << ": +5 (" << mana << ")\n";
        }
    }

    bool removerUmDebuff() {
        for (size_t i = 0; i < efeitos.size(); ++i) {
            if (!efeitos[i]->eAtordoamento()) {
                std::cout << "  >> " << nome << " teve " << efeitos[i]->getNome()
                          << " removido!\n";
                delete efeitos[i];
                efeitos.erase(efeitos.begin() + (int)i);
                return true;
            }
        }
        return false;
    }

    // ---------- Strategy: delega o ataque para a Arma equipada ----------
    void atacar(Personagem& alvo, std::vector<Personagem*>* area = nullptr) {
        if (!estaVivo())    { std::cout << "  >> " << nome << " está fora de combate.\n"; return; }
        if (estaAtordoado()){ std::cout << "  >> " << nome << " está atordoado e perde o turno.\n"; return; }
        if (!arma)          { std::cout << "  >> " << nome << " está sem arma equipada.\n"; return; }

        std::cout << nome << " ataca com " << arma->getNome()
                  << " em " << alvo.getNome() << "\n";
        arma->atacar(*this, alvo, area);
    }
};
