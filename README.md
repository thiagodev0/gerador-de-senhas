**🔐 Gerador de Senhas em C++**

Este utilitário de terminal gera senhas seguras e personalizadas, permitindo escolher letras maiúsculas, minúsculas, números e símbolos. Oferece modo **interativo** e uso via **linha de comando**.

---

## 🚀 Como Compilar

Certifique-se de ter um compilador C++11 (ou superior). No terminal, execute:

```bash
g++ -std=c++11 -o gerador_senha gerador_senha.cpp
```

Isso produzirá o executável `gerador_senha`.

---

## ✅ Modo Interativo

Basta executar sem argumentos:

```bash
./gerador_senha
```

Você verá perguntas passo a passo:

```
Tamanho da senha (padrão 8):
Quer minúsculas (s/n)?
Quer maiúsculas (s/n)?
Quer números (s/n)?
Quer símbolos (s/n)?
```

Ao final, a senha é exibida e salva em `senhas.txt`.

---

## ⚙️ Uso por Linha de Comando

É possível gerar direto sem interação:

```bash
./gerador_senha [opções]
```

| Opção          | Descrição                       |
| -------------- | ------------------------------- |
| `--interativo` | Força o modo interativo         |
| `-l N`         | Define comprimento da senha (N) |
| `--minusc`     | Incluir letras minúsculas       |
| `--maiusc`     | Incluir letras maiúsculas       |
| `--numeros`    | Incluir números                 |
| `--simbolos`   | Incluir símbolos especiais      |

### Exemplo

```bash
./gerador_senha --maiusc --numeros -l 12
# Saída:
# Senha gerada: Q8V6A9XZ17RW
```

---

## 📁 Arquivo de Saída

Todas as senhas são salvas (append) em:

```
senhas.txt
```

Cada nova senha é adicionada em uma linha separada.

---

## 💡 Por que usar?

* **Leve e simples**: sem dependências externas
* **Portátil**: roda em Windows, Linux e macOS
* **Interativo**: ideal para iniciantes
* **Em português**: mensagens claras e diretas

---

## 📌 Requisitos

* Compilador compatível com C++11+: `g++`, `clang++`, MSVC etc.

---

Desfrute de senhas fortes e práticas sem complicações! 😊