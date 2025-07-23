#Projeto Ray Tracing - Estrutura Esférica em Camadas

Este projeto é uma cena desenvolvida com base no livro/projeto *Ray Tracing in One Weekend*, com modificações próprias para gerar uma estrutura visual composta por esferas representando elementos da natureza  organizadas em camadas concêntricas.

## 🌀 Descrição da Cena

A cena contém três camadas de esferas:

- **Camada Externa**: 5 esferas maiores dispostas em círculo, representando os 5 elementos.
- **Camada Intermediária**: 10 esferas menores entre as pontas da estrela, com materiais variados.
- **Camada Interna**: 6 esferas ainda menores no centro, formando o topo da torre.
- **Centro**: Uma esfera metálica brilhante simbolizando energia cósmica.
- **Terreno**: Plano escuro suave para contrastar com os materiais da torre.

A câmera foi posicionada e configurada para capturar a estrutura como uma torre vertical com boa profundidade e iluminação.

## 🔧 Como Compilar

Para compilar o projeto com `g++`:

```bash
g++ -std=c++17 -o raytracer src/InOneWeekend/*.cc

Depois, execute com:

./raytracer ou ./program

A imagem renderizada será salva automaticamente (dependendo da implementação da função render) como image.ppm. Você pode converter esse arquivo para PNG com:

convert image.ppm imagem.png  # Requer ImageMagick

🖼️ Resultado

Aqui está o resultado da renderização:
![Renderização da Torre Estelar](/home/joao-vitor/Documentos/Projeto02_PG_RayTracing/raytracing_in_one_weekend/src/InOneWeekend

👨‍💻 Autores

    Projeto baseado em Peter Shirley

    Modificações e estrutura da cena por:

        João Vitor Seiji Sato Calvaro

        Gustavo Andreas

        Bruna Scarpelli

        Nícolas Benitez

🪪 Licença

Este projeto segue a licença CC0 Public Domain Dedication.
