# Jogo Sobrevivência (Nome Provisório)

Um roguelike de sobrevivência contra hordas de inimigos, inspirado em clássicos modernos como *Vampire Survivors* e *The Binding of Isaac*. O objetivo é sobreviver o maior tempo possível enquanto coleta power-ups para melhorar seus atributos e se tornar mais forte.
![Start](https://github.com/user-attachments/assets/b03bdd61-f7ca-4c49-99bf-2ac1bb65eabb)

## Funcionalidades Planejadas
*   **Ação Frenética:** Enfrente ondas infinitas de inimigos que testarão seus reflexos.
*   **Progressão de Atributos:** Melhore seu personagem com atributos como:
    *   Vida (Health)
    *   Velocidade de Disparo (Fire Rate)
    *   Dano
    *   Velocidade de Movimento
    *   Entre outros
*   **Power-ups:** Mate inimigos para ganhar XP e fazer as escolhas.
*   **Controles Simples:** Fácil de aprender, difícil de dominar.

## Tecnologias Utilizadas
*   **Linguagem:** C++
*   **Bibliotecas Gráficas e Multimídia:**
    *   **SDL2:** Para criação de janelas, renderização e gerenciamento de eventos.
    *   **SDL2_image:** Para carregar texturas e sprites (PNG, JPG, etc.).
    *   **SDL2_ttf:** Para renderizar texto e fontes TrueType.
*   **Gerenciador de Pacotes:** [vcpkg](https://github.com/microsoft/vcpkg) para gerenciar as dependências.
![Inicio](https://github.com/user-attachments/assets/268c6db9-6995-42b8-b60a-d9dcd69dc197)

## Como Compilar e Executar

Este projeto foi desenvolvido usando o Visual Studio 2022. A maneira mais fácil de compilar é usando o gerenciador de pacotes `vcpkg`.

### Pré-requisitos
1.  **Visual Studio 2022** com a carga de trabalho "Desenvolvimento para desktop com C++".
2.  **Git**.
3.  **vcpkg**.



https://github.com/user-attachments/assets/3dfcc539-e0ee-4600-a44e-f27a6aa23815




### Passos para Compilação
1.  **Configure o vcpkg:**
    *   Clone o repositório do vcpkg e execute o script de inicialização.
    ```bash
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.bat
    ```
    *   Integre o vcpkg com o seu ambiente de usuário do Visual Studio (só precisa fazer isso uma vez).
    ```bash
    ./vcpkg integrate install
    ```

2.  **Instale as Dependências:**
    *   Use o vcpkg para instalar as bibliotecas necessárias para a arquitetura de 64 bits.
    ```bash
    ./vcpkg install sdl2:x64-windows sdl2-image:x64-windows sdl2-ttf:x64-windows
    ```

3.  **Clone e Compile o Projeto:**
    *   Clone este repositório.
    ```bash
    git clone https://github.com/LincolnNotAbraham/jogo.git # Substitua pelo URL correto se for diferente
    cd jogo
    ```
    *   Abra o arquivo da solução (`.sln`) no Visual Studio.
    *   Certifique-se de que a plataforma da solução está definida como **x64**.
    *   Compile o projeto (Build > Build Solution ou `Ctrl+Shift+B`).

## Como Jogar
*   **Movimentação:** `W`, `A`, `S`, `D`
*   **Atirar:** Setas

  ![Game Over](https://github.com/user-attachments/assets/78032283-01b7-4513-bbb9-f21002164eec)

---
