#include "FSMEnemigo.hpp"
#include "../Func_aux.hpp"
#include "../Estructuras.hpp"
#include <iostream>
#include <cmath>


// Implementación de EstadoEnemigoIDLE
EstadoEnemigoIDLE::EstadoEnemigoIDLE() {
    // Inicializar variables del estado IDLE
     frames_actual_ani=0;
    frames_maxim_ani=3;
    contador = 0;
    current_tiempo = 0.0;
    idle_tiempo = 3.0;  // 10 segundos de tiempo de espera
    strestado = "IDLE";
}

FSMEnemigo* EstadoEnemigoIDLE::input_handle(Enemigo& en, KeyOyente& keys, MouseOyente& mouse) {
    // No hay transiciones en el estado IDLE
    return nullptr;
}

void EstadoEnemigoIDLE::on_entrar(Enemigo& en) {
    // Reiniciar contador y tiempo al entrar al estado IDLE
     frames_actual_ani=0;
    frames_maxim_ani=3;
    contador = 0;
    current_tiempo = Tiempo::get_tiempo();
}

void EstadoEnemigoIDLE::on_salir(Enemigo& en) {
    // No se realiza ninguna acción al salir del estado IDLE
}

void EstadoEnemigoIDLE::on_update(Enemigo& en, double dt) {
    // Incrementar el contador y comprobar si ha pasado el tiempo de espera
    contador++;
    double elapsed_tiempo = Tiempo::get_tiempo() - current_tiempo;
    if (elapsed_tiempo > idle_tiempo) {
        // El tiempo de espera ha excedido, transicionar al estado de transición
        en.set_estado(new EstadoEnemigoTransicion());
    }
}


// Implementación de EstadoEnemigoTransicion
EstadoEnemigoTransicion::EstadoEnemigoTransicion() {
    // Inicializar variables del estado de transición
    check = {0, 0};
    ant_check = {0, 0};
    centro = {0, 0};
    distancia = 10.0;
     frames_actual =0;
    frames_maximo = 45;
    frames_actual_ani=0;
    frames_maxim_ani=5;
    strestado = "TRANSICION";
}

FSMEnemigo* EstadoEnemigoTransicion::input_handle(Enemigo& en, KeyOyente& keys, MouseOyente& mouse) {
    // No hay transiciones en el estado de transición
    /*if(frames_actual>frames_maximo)
    {
        if(distancia<10)
        {
            return new EstadoEnemigoAttack(*en.get_obj_lock());
        }
        return new EstadoEnemigoTransicion();
    }*/

    return NULL;
}

void EstadoEnemigoTransicion::on_entrar(Enemigo& en) {
    // Calcular el centro y la distancia al objeto a seguir
    Objeto* objeto_seguir = en.get_obj_lock();
    if (objeto_seguir) {
        centro = objeto_seguir->get_posicion_mundo();

        int diferenciaX = centro.x - en.get_posicion_mundo().x;
        int diferenciaY = centro.y - en.get_posicion_mundo().y;
        distancia = std::sqrt(diferenciaX * diferenciaX + diferenciaY * diferenciaY);
    }
        //frames para sprite
    /* en.en_transicion = 1;

    vel = en.velocidad;
    pos_inicial = en.get_posicion_mundo();//(0,0) 

    //seguro decir que este estado siempre entra en lock object
    // no es necesario comprobar que lock object no es nulo
    pos_final = en.get_obj_lock()->get_posicion_mundo(); //o.x,o.y
    
    //convertir en posicion relativo a las coordenads camara
  

    //la diferencia es la cantidad de pixeles que se mueve
    ant_check={0,0};
    //distancia=0.f;

    //checkar la distancia es pequeña para ajustar los frames
    distancia = std::sqrt(std::pow(centro.x-(pos_final.x),2)+std::pow(centro.y-(pos_final.y),2));
    //std::cout<<"Distancia > "<<distancia<<"\n";
    float lim = en.get_obj_lock()->get_avatar()->get_vertices()[3].x - en.get_obj_lock()->get_avatar()->get_vertices()[0].x;
    if(distancia<lim)
    {
        //std::cout<<"LIM "<<lim<<"\n";
        frames_maximo = 10;
    }*/
     frames_actual_ani=0;
    frames_maxim_ani=5;
}

void EstadoEnemigoTransicion::on_salir(Enemigo& en) {
    // No se realiza ninguna acción al salir del estado de transición
    en.en_transicion = 0;
}

void EstadoEnemigoTransicion::on_update(Enemigo& en, double dt) {

      /* if(frames_actual>frames_maximo)
        return;

    float t = frames_actual/(float)frames_maximo;
    check= LERP(pos_inicial,pos_final,t);
    //la diferencia es cuantos pixeles avanza por frame
    ant_check.x = check.x-ant_check.x;
    ant_check.y = check.y-ant_check.y;

    Coordenadas objpos = en.get_obj_lock()->get_posicion_mundo();

    distancia = std::sqrt(std::pow(centro.x-objpos.x,2)+std::pow(centro.y-objpos.y,2));
    //std::cout<<"Distancia > "<<distancia<<"\n";

    en.set_posicion_mundo(ant_check);
    frames_actual++;
    //DEBUGLINEA(check,pos_final)
    //DEBUGCOOR(ant_check);

    //guardamos la posición anterior
    ant_check = check;*/


    
   /*Objeto* objeto_seguir = en.get_obj_lock();
    if (objeto_seguir) {
        ant_check = check;
        check = objeto_seguir->get_posicion_mundo();

        // Calcular la interpolación lineal entre las posiciones anteriores y actuales
        Coordenadas t;
        
        t.x = ant_check.x + dt * (check.x - ant_check.x);
        t.y = ant_check.y + dt * (check.y - ant_check.y);
        en.set_posicion_mundo(t);

        // Verificar si se ha alcanzado la posición del objeto a seguir
         int diferenciaX = centro.x - en.get_posicion_mundo().x;
        int diferenciaY = centro.y - en.get_posicion_mundo().y;
        double new_distancia = std::sqrt(diferenciaX * diferenciaX + diferenciaY * diferenciaY);
        if (new_distancia <= distancia) {
            // Se ha alcanzado la posición del objeto, transicionar al estado de ataque
            en.set_estado(new EstadoEnemigoAttack(*en.get_obj_lock()));
        }
    }*/
    en.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}
Coordenadas EstadoEnemigoTransicion::normalizar_vector(const Coordenadas& vector)
{
    
    Coordenadas temp = {0, 0};
    int diferenciaX = vector.x - temp.x;
    int diferenciaY = vector.y - temp.y;
    double longitud = std::sqrt(diferenciaX * diferenciaX + diferenciaY * diferenciaY);
    // Verificar si la longitud es cero para evitar división por cero
    if (longitud == 0.0)
        return vector;
    Coordenadas c={static_cast<int>(vector.x / longitud), static_cast<int>(vector.y / longitud)};
    return c;
}

// Implementación de EstadoEnemigoAttack
EstadoEnemigoAttack::EstadoEnemigoAttack(Objeto& objlock) : obj(&objlock), locked(false) {
    // Inicializar variables del estado de ataque
    centro = {0, 0};
    strestado = "ATTACK";
    obj = &objlock;
     frames_actual_ani=0;
    frames_maxim_ani=5;
}

FSMEnemigo* EstadoEnemigoAttack::input_handle(Enemigo& en, KeyOyente& keys, MouseOyente& mouse) {
    // No hay transiciones en el estado de ataque
    return nullptr;
}

void EstadoEnemigoAttack::on_entrar(Enemigo& en) {
    // Guardar la posición del objeto a seguir y establecer la bandera de bloqueo en verdadero
    if (obj) {
        centro = obj->get_posicion_mundo();
        en.lock = true;
           frames_actual_ani=0;
    frames_maxim_ani=5;
    }
}

void EstadoEnemigoAttack::on_salir(Enemigo& en) {
    // No se realiza ninguna acción al salir del estado de ataque
}

void EstadoEnemigoAttack::on_update(Enemigo& en, double dt) {
    // Verificar si el objeto a seguir sigue existiendo
    if (obj && en.lock) {
        // Realizar acciones de ataque al objeto
        // Restar HP al objeto, por ejemplo:
        float vida=obj->get_hp();
        obj->set_hp(vida-en.get_ataque());
        // Verificar si el objeto ha sido derrotado
        if (obj->get_hp() <= 0.0) {
            // El objeto ha sido derrotado, transicionar al estado IDLE después de 10 segundos
            printf("El objeto ha sido derrotado\n");
        }
        en.set_estado(new EstadoEnemigoIDLE());
        //en.get_estado()->on_entrar(en);  // Reiniciar el estado IDLE
    } 
        en.get_sprite()->play_frame(2,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}
