# Registrador Ambiental con Arduino para Pruebas de Aislamiento

Este proyecto universitario fue desarrollado para monitorear y registrar condiciones ambientales (temperatura y humedad) utilizando una placa Arduino y diversos sensores. El objetivo principal era recopilar datos a lo largo del tiempo para poder comparar la capacidad de aislamiento térmico de un nuevo material frente a materiales aislantes convencionales.

El sistema lee datos de múltiples sensores de temperatura (DS18B20) y un sensor combinado de temperatura y humedad (SHT21), obtiene la fecha y hora actual de un módulo de reloj en tiempo real (RTC DS1307) y muestra la información seleccionada en una pantalla LCD I2C. La selección de qué sensor mostrar en la pantalla se controla mediante comandos enviados a través del puerto serie.

**Nota:** La funcionalidad descrita originalmente incluía el registro de los datos (temperatura, humedad, fecha y hora) en un archivo CSV dentro de una tarjeta SD. El código proporcionado en este repositorio se centra en la lectura de los sensores, el RTC y la visualización en LCD controlada por comandos seriales. La implementación del guardado en la tarjeta SD sería un paso adicional necesario para completar la funcionalidad de *datalogging* descrita.

## Componentes de Hardware Utilizados

* Placa Arduino (Uno, Nano, o similar)
* 2 x Sensores de Temperatura Digitales DS18B20 (conectados al bus OneWire)
* 1 x Sensor de Temperatura y Humedad SHT21 (conectado vía I2C)
* 1 x Módulo de Reloj en Tiempo Real (RTC) DS1307 (conectado vía I2C)
* 1 x Pantalla LCD 16x2 con interfaz I2C (Dirección común: 0x27 o 0x3F)
* Resistencia pull-up de 4.7kΩ para el bus OneWire (entre el pin de datos y 5V)
* Cables de conexión (Jumpers)
* (Opcional/Previsto) Módulo lector de tarjetas MicroSD con interfaz SPI

## Librerías de Arduino Requeridas

Asegúrate de tener instaladas las siguientes librerías en tu IDE de Arduino:

* `OneWire` (Normalmente incluida con el IDE o fácil de instalar)
* `DallasTemperature` by Miles Burton and others
* `TimerOne` (Aunque incluida, su uso específico no es evidente en el bucle principal del código provisto)
* `Wire` (Incluida con el IDE de Arduino para comunicación I2C)
* `RTClib` by Adafruit (Para el DS1307)
* `SHT21` by Tilen Majerle or similar (Asegúrate de que sea compatible con I2C)
* `LiquidCrystal_I2C` by Frank de Brabander or similar

## Conexiones (Ejemplo Básico)

* **Bus I2C (SDA, SCL):** Conecta los pines SDA y SCL del Arduino a los pines correspondientes del módulo RTC DS1307, el sensor SHT21 y la pantalla LCD I2C. En Arduino Uno/Nano suelen ser A4 (SDA) y A5 (SCL).
* **Bus OneWire (DS18B20):** Conecta el pin de datos de ambos sensores DS18B20 al pin digital 5 del Arduino. Conecta la resistencia de 4.7kΩ entre este pin (D5) y el pin de 5V. Asegúrate de alimentar correctamente los sensores (VCC y GND).
* **Alimentación:** Conecta VCC y GND de todos los módulos a los pines 5V/3.3V (según requiera cada módulo) y GND del Arduino respectivamente.

**Importante:** Las direcciones I2C (LCD: `0x27`) y las direcciones únicas de los sensores DS18B20 (`sensorAddress1`, `sensorAddress2`) están definidas en el código. Verifica que coincidan con tu hardware o ajústalas según sea necesario. Puedes usar un script "I2C Scanner" para encontrar la dirección de tus dispositivos I2C y modificar el código si encuentras las direcciones de los DS18B20 usando un ejemplo de la librería DallasTemperature.

## Funcionamiento

1.  Carga el código (`Registrador_Ambiental.ino` o el nombre que elijas) en tu placa Arduino.
2.  Abre el Monitor Serie del IDE de Arduino (configurado a 9600 baudios).
3.  Envía un número a través del Monitor Serie para seleccionar qué información mostrar en la pantalla LCD:
    * `1`: Muestra la temperatura leída por el primer sensor DS18B20 (`Sensor A`).
    * `2`: Muestra la temperatura leída por el segundo sensor DS18B20 (`Sensor B`).
    * `3`: Muestra la fecha y hora actual obtenida del módulo RTC (`Clock`).
    * `4`: Muestra la temperatura y humedad leídas por el sensor SHT21 (`SHT 21`).
4.  La pantalla LCD se actualizará para mostrar la información correspondiente al comando enviado.

## Pasos Futuros / Mejoras

* **Implementar el registro en Tarjeta SD:** Añadir el código necesario utilizando las librerías `<SPI.h>` y `<SD.h>` para inicializar la tarjeta SD y guardar periódicamente las lecturas de los sensores y la hora/fecha en un archivo CSV.
* **Ajustar el RTC:** Incluir una forma (quizás mediante comandos seriales o al inicio) para ajustar la hora del módulo RTC si no está correcta.
* **Interfaz de Usuario:** Mejorar la interacción, quizás usando botones en lugar de comandos seriales.
* **Gestión de Errores:** Añadir comprobaciones para detectar si los sensores o módulos no responden correctamente.

---