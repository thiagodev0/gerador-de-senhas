#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <map>
#include <clocale>

using namespace std;

class Senha
{
public:
    Senha()
        : tamanho_(8)
    {
        opcoes_["minusc"] = false;
        opcoes_["maiusc"] = false;
        opcoes_["numeros"] = false;
        opcoes_["simbolos"] = false;
    }

    void definirTamanho(int t)
    {
        tamanho_ = (t > 0 ? t : 8);
    }

    void ativar(const string& tipo)
    {
        if (caracteres_.count(tipo))
            opcoes_[tipo] = true;
    }

    string criar()
    {
        string pool;
        for (auto& [tipo, on] : opcoes_)
            if (on)
                pool += caracteres_.at(tipo);

        if (pool.empty())
            throw invalid_argument("Selecione ao menos um tipo de caractere.");

        unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 gerador(seed);
        uniform_int_distribution<> dist(0, pool.size() - 1);

        string s;
        s.reserve(tamanho_);
        for (int i = 0; i < tamanho_; ++i)
            s += pool[dist(gerador)];

        shuffle(s.begin(), s.end(), gerador);
        return s;
    }

    void salvar(const string& s, const string& arquivo = "senhas.txt")
    {
        ofstream f(arquivo, ios::app);
        if (!f) cerr << "Não consegui abrir " << arquivo << '\n';
        else f << s << '\n';
    }

private:
    int tamanho_;
    map<string, bool> opcoes_;
    const map<string, string> caracteres_ = {
        {"minusc", "abcdefghijklmnopqrstuvwxyz"},
        {"maiusc", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"numeros", "0123456789"},
        {"simbolos", "!@#$%&*()_+-=[]{};:,.<>?"}
    };
};

bool simOuNao(const string& perg)
{
    char r;
    cout << perg << " (s/n)? ";
    cin >> r;
    return tolower(r) == 's';
}

void interativo()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    cout << "\n*** Modo Interativo ***\n";
    do
    {
        Senha s;
        int t;
        cout << "Tamanho da senha (padrão 8): "; cin >> t;
        s.definirTamanho(t);

        if (simOuNao("Quer minúsculas")) s.ativar("minusc");
        if (simOuNao("Quer maiúsculas")) s.ativar("maiusc");
        if (simOuNao("Quer números"))    s.ativar("numeros");
        if (simOuNao("Quer símbolos"))   s.ativar("simbolos");

        try
        {
            auto senha = s.criar();
            cout << "Senha: [ " << senha << " ]" << endl;
            s.salvar(senha);
            cout << "(Guardei em senhas.txt)" << endl;
        }
        catch (exception& e)
        {
            cerr << "Ops: " << e.what() << endl;
        }
    }
    while (simOuNao("Outra senha"));
}

void ajuda()
{
    cout << "\nUso: gerador_senha [opções]\n";
    cout << "  --interativo   Modo interativo\n";
    cout << "  -l N           Define tamanho N\n";
    cout << "  --minusc       Minúsculas\n";
    cout << "  --maiusc       Maiúsculas\n";
    cout << "  --numeros      Números\n";
    cout << "  --simbolos     Símbolos\n";
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    if (argc == 1)
    {
        interativo();
        return 0;
    }

    Senha s;
    bool inter = false;
    int tam = 8;
    map<string, bool> opts = {
        {"minusc", false}, {"maiusc", false},
        {"numeros", false}, {"simbolos", false}
    };

    for (int i = 1; i < argc; ++i)
    {
        string a = argv[i];
        if (a == "--interativo") { inter = true; break; }
        if (a == "-l" && i+1<argc)    tam = stoi(argv[++i]);
        if (opts.count(a.substr(2)))    opts[a.substr(2)] = true;
    }

    s.definirTamanho(tam);
    for (auto& [k, v] : opts) if (v) s.ativar(k);

    if (inter)
        interativo();
    else
    {
        try
        {
            auto senha = s.criar();
            cout << "Senha gerada: " << senha << endl;
            s.salvar(senha);
        }
        catch (exception& e)
        {
            cerr << "Erro: " << e.what() << endl;
            return 1;
        }
    }
    return 0;
}