# Trabajos Programación de Microcontroladores

_Nicolás Hasbún A._

Colección de trabajos prácticos realizados en el contexto de la Carrera de Especialización de Sistemas Embebidos del Laboratorio de Sistemas Embebidos de la Universidad de Buenos Aires.

Los proyectos base utilizados se han extraído del [repositorio del profesor Patricio Bos](https://github.com/patriciobos/PdM_workspace). Se requiere una placa de desarrollo **Nucleo F429ZI** y el IDE **STM32Cube** para ejecutarlos.



## Carpetas

Proyectos para importar en STM32Cube IDE:

* **p2_non_blocking_delay (Práctica 2):** Consiste en la implementación y prueba con LEDs de **delays no bloqueantes**.
* **p3_modularization (Práctica 3):** Ejemplo de modularización de funciones en C utilizando **delays no bloqueantes como ejemplo** para crear los archivos **API_delay.h y API_delay.c**.
* **p4_debouncing (Práctica 4.1):** Ejemplo de aplicación de técnica de anti-rebote (debouncer). Se utiliza el **botón USER** y los LEDs 1 y 2 de la placa para ejemplificar la detección.
* **p4_debouncing_modularization (Práctica 4.2):** Modularización de técnica de anti-rebote en los archivos **API_debouncer.h y API_debouncer.c**. Se utiliza el **botón USER** para ejemplificar cambiando el periodo de parpadeo del LED2.
* **p5_uart (Práctica 5):** Modularización de comunicación serial en los archivos **API_uart.h y API_uart.c**. Se reporta por este medio el estado **FALLING** o **RAISING** de la máquina de estados finita que maneja el anti-rebote del **botón USER**.
* **tp_mag_states (Trabajo Final):** Prototipo de Brújula Digital. Comunicación con magnetómetro y retroalimentación respecto al estado de la comunicación, estado de calibración por medio de LEDs y UART. Accionamiento de calibración de brújula por pulsación larga de botón de usuario.
