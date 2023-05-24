# Restauración del firmware original

En este documento se detallan los pasos para restaurar el firmware original en la consola.

Dentro de esta carpeta se hallan los siguientes elementos:

- *esptool*. Herramienta proporcionada por el fabricante para el manejo de binarios.
- *Firmware*. Firmware original de la consola, que incluye el Tetris.
- *flashEsp32.bat*. Fichero que se utiliza para flashear el firmware.

***

## Requisitos

La ejecución del script que flashea el binario requiere tener instalado [Python 3](https://www.python.org/downloads/). Antes de intentar instalar Python, se recomienda seguir los siguientes pasos para instalar el firmware por si ya hay una versión instalada.

***

## Instrucciones

El script *flashEso32.bat* ejecuta una aplicación y le pasa como parámetros los cuatro binarios que es necesario transferir al microcontrolador.

Un parámetro adicional es el puerto "COM" por el que está conectada la consola. Antes de ejecuctar el script es **IMPRESCINDIBLE** editar  el script con un editor de texto y poner el puerto COM correcto.

Para determinar cuál es el puerto "COM" de la consola, hay que abrir el administrador de dispositivos, ir a la lista de puertos COM y encender la consola. Deberá aparecer un un puerto nuevo, tal y como se ve en la siguiente imagen:

<p align="center">
  <img src="../images/comport.png" height="40">
</p>

Una vez puesto el puerto "COM" correcto, "COM4" en el ejemplo se debe guardar cambios y hacer doble clic sobre el fichero "*flashEsp32.bat*".

Como ya se ha indicado en el fichero "*README.md*", es necesario mantener pulsado el botón rojo (B) durante la grabación de los binarios.