# Smart-Orchard
ESP32-based smart and autonomous orchard.


Link para la bitácora que lleva registro del desarrollo del proyecto
https://docs.google.com/document/d/1KFSiqcFTqIYzIrPB1Agh6pknZBYJP58AOWJd3PyHZ9o/edit?usp=sharing  


Huerta en tiempo real que mide:
- Intensidad de luz con módulo KY 018 y la registra
- Temperatura y humedad del aire con el módulo DHT22
- Humedad del suelo con el módulo e higrómetro Y 69

El sistema activará desde el main dos actuadores por relay:
 - Bomba de agua que se activará durante 1 segundo debido a su gran caudal
 - Ventilador (motor DC con hélice) que se activará para disminuir la temperatura



![PINOUT](https://github.com/Vaddak/Smart-Orchard/assets/62626110/a1f2607c-b4fe-4bd2-9fa9-5aa3a64460b3)
