cmake_minimum_required(VERSION 4.0)
project(StrategyCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(StrategyCPP main.cpp
        include/enums/Classe.h
        include/enums/TipoArma.h
        include/Utils.h
        include/Arma.h
        include/StatusEffect.h
        include/Personagem.h
        include/armas/EspadaLonga.h
        include/armas/ArcoElfico.h
        include/armas/CajadoArcano.h
        include/armas/MachadoGuerra.h
        include/armas/AdagaSombria.h
        include/armas/LaminaSagrada.h
        include/Batalha.h
)
