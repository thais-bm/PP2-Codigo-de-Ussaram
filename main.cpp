#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

/////Class Node/////
template <typename T> class Node {
private:
  T item;

public:
  Node<T> *next;
  Node<T> *prev;
  T getItem();
  Node();
  Node(T item);
};

template <typename T> Node<T>::Node() {
  next = nullptr;
  prev = nullptr;
}

template <typename T> Node<T>::Node(T item) {
  this->item = item;
  next = nullptr;
  prev = nullptr;
}

template <typename T> T Node<T>::getItem() { return item; }

// Early declaration
template <typename T> class ListNavigator;

////Class List/////
template <typename T> class List {
private:
  Node<T> *pHead;
  Node<T> *pBack;
  int numItems;
  void succ(Node<T> *&p);
  void pred(Node<T> *&p);

public:
  void insertFront(T item);
  void insertBack(T item);
  void removeFront();
  void removeBack();
  T getItemFront();
  T getItemBack();
  ListNavigator<T> getListNavigator() const;
  int size();
  bool empty();
  List();
};

template <typename T> List<T>::List() {
  pHead = new Node<T>();
  pBack = pHead;
  pHead->next = nullptr;
  numItems = 0;
}

template <typename T> void List<T>::succ(Node<T> *&p) { p = p->next; }

template <typename T> void List<T>::pred(Node<T> *&p) {
  Node<T> *q = pHead;
  while (q->next != p) {
    succ(q);
  }
  p = q;
}

template <typename T> void List<T>::insertFront(T item) {
  Node<T> *pNew = new Node<T>(item);
  pNew->next = pHead->next;
  pHead->next = pNew;

  if (pBack == pHead) {
    pBack = pNew;
  }
  numItems++;
}

template <typename T> void List<T>::insertBack(T item) {
  Node<T> *pNew = new Node<T>(item);
  pBack->next = pNew;
  pBack = pNew;

  numItems++;
}

template <typename T> void List<T>::removeFront() {
  if (empty()) {
    return;
  }
  Node<T> *temp = pHead->next;
  pHead->next = temp->next;

  if (pBack == temp) {
    pBack = pHead;
  }
  delete temp;
  numItems--;
}

template <typename T> void List<T>::removeBack() {
  if (empty()) {
    return;
  }

  Node<T> *temp = pBack;
  pred(pBack);
  pBack->next = nullptr;

  delete temp;

  if (pHead == pBack) {
    pHead = pBack;
  }
  numItems--;
}

template <typename T> T List<T>::getItemFront() {
  if (empty()) {
    return T();
  }
  return pHead->next->getItem();
}

template <typename T> T List<T>::getItemBack() {
  if (empty()) {
    return T();
  }

  return pBack->getItem();
}

template <typename T> ListNavigator<T> List<T>::getListNavigator() const {
  return ListNavigator<T>(pHead->next);
}

template <typename T> int List<T>::size() { return numItems; }

template <typename T> bool List<T>::empty() { return pBack == pHead; }

/////Class ListNavigator/////
template <typename T> class ListNavigator {
private:
  Node<T> *current;
  Node<T> *start;
  int currentPosition;

public:
  ListNavigator(Node<T> *current);
  bool end();
  void next();
  void reset();
  bool getCurrentItem(T &item);
  int getCurrentPosition() const;
  void seekToPosition(int pos);
};

template <typename T> ListNavigator<T>::ListNavigator(Node<T> *current){
  this->current = current;
  this->start = current;
  this->currentPosition = 0;
}

template <typename T> bool ListNavigator<T>::end() {
  return current == nullptr;

}

template <typename T> void ListNavigator<T>::next() {
  current = current->next;
  currentPosition++;
}

template <typename T> void ListNavigator<T>::reset() {
  current = start;
  currentPosition = 0;
}

template <typename T> bool ListNavigator<T>::getCurrentItem(T &item) {
  if (current == nullptr) {
    return false;
  }
  item = current->getItem();
  return true;
}

template <typename T> int ListNavigator<T>::getCurrentPosition() const {
  return currentPosition;
}

template <typename T> void ListNavigator<T>::seekToPosition(int pos) {
  reset();
  for (int i = 0; i < pos && !end(); i++) {
    next();
  }
}

/////Class Queue/////
template <typename T> class Queue {
private:
  List<T> list;

public:
  void enqueue(T item);
  void dequeue();
  T front();
  int size();
  bool empty();
  Queue(List<T>);
};

template <typename T> Queue<T>::Queue(List<T> list) { this->list = list; }

template <typename T> void Queue<T>::enqueue(T item) { list.insertBack(item); }

template <typename T> void Queue<T>::dequeue() {
  if (empty()) {
    return;
  }
  list.removeFront();
}

template <typename T> T Queue<T>::front() {
  if (empty()) {
    return T();
  }
  return list.getItemFront();
}

template <typename T> int Queue<T>::size() { return list.size(); }

template <typename T> bool Queue<T>::empty() { return list.empty(); }

/////Class Stack/////
template <typename T> class Stack {
private:
  List<T> list;

public:
  void push(T item);
  void pop();
  T top();
  int size();
  bool empty();
  Stack(List<T>);
};

template <typename T> Stack<T>::Stack(List<T> list) { this->list = list; }

template <typename T> void Stack<T>::push(T item) { list.insertFront(item); }

template <typename T> void Stack<T>::pop() {
  if (empty()) {
    return;
  }
  list.removeFront();
}

template <typename T> T Stack<T>::top() {
  if (empty()) {
    return T();
  }
  return list.getItemFront();
}

template <typename T> int Stack<T>::size() { return list.size(); }

template <typename T> bool Stack<T>::empty() { return list.empty(); }

//// Funcoes Relacionadas a Atividade comecam aqui ////
// Funcao responsavel por remover os espacos em branco do inicio e do fim de uma string
string trim(const string &str) {
  int start = 0;
  int end = str.length() - 1;

  while (start <= end && isspace(str[start])) {
    start++;
  }
  while (end >= start && isspace(str[end])) {
    end--;
  }
  return str.substr(start, end - start + 1);
}

// Funcao responsavel por detectar funcao principal (Z)
bool isMainFunction(const string& line) { return (line == "Z :"); }

// Funcao responsavel por detectar funcao Ianteco
bool isIantecoFunction(const string& line) {
  return (line.find(" :") != string::npos);
}

// Funcao responsavel por detectar chamada de funcao Ianteco
bool isIantecoFunctionCall(const string &line) {
  return line.size() == 1 && isupper(line[0]);
}

// Funcao responsavel por detectar o fim de uma funcao
bool isEndFunction(const string& line) {
    return (line.find("FIM DE FUNCAO") != string::npos);
}

// Funcao responsavel por imprimir as mensagens
void printMsg(Queue<string> msg) {
  std::cout << "Resultado: ";
  while (!msg.empty()) {
    std::cout << msg.front() << " ";
    msg.dequeue();
  }
  std::cout << endl;
}

// Funcao responsavel por executar o codigo Azuri
// Structura para armazenar o contexto da funcao
struct FunctionContext {
  string functionName; // Nome da funcao
  int position; // Onde a funcao comeca
  int returnPosition; // Onde retornar apos chamada de funcao
};

void ExecutorAzuri(List<string> codeList) {
  ListNavigator<string> nav = codeList.getListNavigator(); // Navegador da lista
  Queue<string> msg(List<string>{}); // Fila para armazenar mensagens
  Stack<FunctionContext> functionStack(List<FunctionContext>{}); // Pilha para armazenar o contexto das funcoes

  // Inicializa a pilha com a funcao principal
  string line;

  // Variaveis para controle de fluxo de retorno
  bool shouldReturn = false;
  int pendingReturn = -1;

  // Passo 1: Encontrar a funcao principal (Z :)
  while (!nav.end()) {
    nav.getCurrentItem(line);
    line = trim(line);

    if (isMainFunction(line)) {
      line.pop_back(); // Remove ':'
      line = trim(line);

      FunctionContext Zmain;
      Zmain.functionName = line;
      Zmain.position = nav.getCurrentPosition() + 1; // posicao da funcao no CodeList
      Zmain.returnPosition = -1; // nao tem retorno
      functionStack.push(Zmain);

      std::cout << "Funcao principal encontrada: " << line << endl;
      break;
    }
    nav.next();
  }

  // Passo 2: Executar as funcoes empilhadas
  while (!functionStack.empty()) {
    if (shouldReturn) {
      nav.seekToPosition(pendingReturn); // Volta para a linha apos chamada
      shouldReturn = false;
    } else {
      nav.seekToPosition(functionStack.top().position); // Navega para a posicao da funcao
    }
    std::cout << "Executando funcao: " << functionStack.top().functionName << endl;

    while (!nav.end()) {
      nav.getCurrentItem(line);
      line = trim(line);

      // Comandos da linguagem
      if (line.find("DESENFILEIRA") != string::npos) {
        if (!msg.empty()) {
          msg.dequeue();
          std::cout << "Desenfileirando" << endl;
        }
      }
      else if (line.find("ENFILEIRA") != string::npos) {
        string content = line.substr(10); // depois de "ENFILEIRA "
        msg.enqueue(content);
        std::cout << "Enfileirando: " << content << endl;
      }

      // Fim da funcao
      if (isEndFunction(line)) {
        if (functionStack.top().returnPosition != -1) {
          pendingReturn = functionStack.top().returnPosition; // Volta para a linha apos chamada
          shouldReturn = true; // Indica que deve retornar
          functionStack.pop(); // Remove a funcao atual da pilha
          break;

        } else {
          functionStack.pop(); // Remove a funcao
          break;
        }
      }

      // Chamada de outra funcao
      if (isIantecoFunctionCall(line)) {
        FunctionContext newContext;
        newContext.functionName = trim(line);
        newContext.returnPosition = nav.getCurrentPosition() + 1;

        // Buscar posicao da funcao chamada
        ListNavigator<string> search = codeList.getListNavigator();
        string searchLine;

        while (!search.end()) {
          search.getCurrentItem(searchLine);
          searchLine = trim(searchLine);
          if (isIantecoFunction(searchLine)) {
            string function = trim(searchLine);
            function.pop_back(); // remove ':'
            function = trim(function);
            if (function == newContext.functionName) {
              newContext.position = search.getCurrentPosition() + 1;
              break;
            }
          }
          search.next();
        }

        std::cout << "Chamando funcao: " << newContext.functionName << endl;
        std::cout << "Retornando para: " << newContext.returnPosition << endl;
        std::cout << "Posicao da funcao chamada: " << newContext.position << endl;

        functionStack.push(newContext); // Empilha a nova funcao
        break; // Pausa execucao atual para tratar nova funcao
      }

      nav.next();
    }
  }

  // Passo 3: Imprimir mensagens
  printMsg(msg);
  std::cout << endl;
  std::cout << "Fim do programa" << endl;
}

// Implementando Tabela e funcao hash

// Criando a classe dicionario

struct DictEntry {
    string ianteco;
    string azuri;
    DictEntry* proximo;

    DictEntry(std::string i, std::string a) : ianteco(i), azuri(a), proximo(nullptr) {}
};


// Tabela Hash

template <typename T> class HashTable {
private:
    DictEntry** tabela;
    size_t tamanho;

    // Funcao Hash //
    size_t hash(const std::string& key, size_t m) {
      size_t valor_hash = 0;
      size_t n = key.length();

      for (size_t i = 0; i < n; ++i) {
          size_t potencia = 1;

          for (size_t j = 0; j < n - i - 1; ++j) {
              potencia *= 128;
          }

          valor_hash += key[i] * potencia;
          valor_hash %= m;
      }

      return valor_hash;
  }


public:
    HashTable(size_t m) {
        tamanho = m;
        tabela = new DictEntry*[tamanho];
        for (size_t i = 0; i < tamanho; ++i) {
            tabela[i] = nullptr;
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < tamanho; ++i) {
            DictEntry* atual = tabela[i];
            while (atual != nullptr) {
                DictEntry* temp = atual;
                atual = atual->proximo;
                delete temp;
            }
        }
        delete[] tabela;
    }

    void insert(const std::string& chave, const DictEntry& entrada) {
        size_t indice = hash(chave, tamanho);
        DictEntry* novo = new DictEntry(entrada.ianteco, entrada.azuri);
        novo->proximo = tabela[indice];
        tabela[indice] = novo;
    }

    std::string search(const std::string& chave) {
        size_t indice = hash(chave, tamanho);
        DictEntry* atual = tabela[indice];
        while (atual != nullptr) {
            if (atual->ianteco == chave) return atual->azuri;
            atual = atual->proximo;
        }
        return ""; // nao encontrado
    }

    bool empty() const {
      for (int i = 0; i < 11; ++i) {
          if (tabela[i] != nullptr) {
              return false;
          }
      }
      return true;
  }
};

// Tradutor de Ianteco-Azuri

List<string> traduzirIanteco(HashTable<string>& dict, List<string>& iantecoLines) {
    ListNavigator<string> nav = iantecoLines.getListNavigator();
    List<string> codigoAzuri;
    string linha;

    while (!nav.end()) {
        nav.getCurrentItem(linha);
        linha = trim(linha);

        if (linha.empty() || linha == "~") {
            codigoAzuri.insertBack("FIM DE FUNCAO");
            nav.next();
            continue;
        }

        // Caso 1: Definicao de funcao (ex: :.:---:)
        if (linha.back() == ':' && linha.find("------") == string::npos) {
            string nomeFunc = "";
            for (size_t i = 0; i + 2 < linha.length(); i += 3) {
                string simbolo = linha.substr(i, 3);
                string traduzido = dict.search(simbolo);
                if (!traduzido.empty() && traduzido != " ") {
                    nomeFunc += traduzido;
                }
            }
            // Remove o ':' final se existir
            if (!nomeFunc.empty() && nomeFunc.back() == ':') {
                nomeFunc.pop_back();
            }
            codigoAzuri.insertBack(nomeFunc + " :");
        }
        // Caso 2: Linha de comando (ex: ------:...:|.:)
        else if (linha.find("------:") == 0) {
            string conteudo = linha.substr(7);
            string parametro = "";
            
            for (size_t i = 0; i + 2 < conteudo.length(); i += 3) {
                string simbolo = conteudo.substr(i, 3);
                string traduzido = dict.search(simbolo);
                if (!traduzido.empty() && traduzido != " ") {
                    parametro += traduzido;
                }
            }
            
            if (parametro.empty()) {
                codigoAzuri.insertBack("DESENFILEIRA");
            } else {
                codigoAzuri.insertBack("ENFILEIRA " + parametro);
            }
        }
        // Caso 3: Chamada de funcao (ex: :.:)
        else {
            string chamada = "";
            for (size_t i = 0; i + 2 < linha.length(); i += 3) {
                string simbolo = linha.substr(i, 3);
                string traduzido = dict.search(simbolo);
                if (!traduzido.empty() && traduzido != " ") {
                    chamada += traduzido;
                }
            }
            if (!chamada.empty()) {
                codigoAzuri.insertBack(chamada);
            }
        }

        nav.next();
    }

    return codigoAzuri;
}

int main() {
  HashTable<string> dict(11);
  List<string> codeList;
  string line;

  DictEntry entradas[] = {
        {":::", "A"}, {".::", "B"}, {":.:", "C"}, {"::.", "D"},
        {":..", "E"}, {".:.", "F"}, {"..:", "G"}, {"...", "H"},
        {"|::", "I"}, {":|:", "J"}, {"::|", "K"}, {"|.:", "L"}, 
        {".|:", "M"}, {".:|", "N"}, {"|:.", "O"}, {":|.", "P"},
        {":.|", "Q"}, {"|..", "R"}, {".|.", "S"}, {"..|", "T"},
        {".||", "U"}, {"|.|", "V"}, {"||.", "W"}, {"-.-", "X"}, 
        {".--", "Y"}, {"--.", "Z"}, {"---", " "}, {"~", "~"}, {" ", " "},
    };

  for (const auto& entrada : entradas) {
    dict.insert(entrada.ianteco, entrada);
  }

  while (getline(cin, line) && line != "~") {
    if (line.find_first_not_of(" \t\r\n") == std::string::npos || line.empty() || line.empty()) {
      codeList.insertBack("FIM DE FUNCAO");
    }
    else {
      codeList.insertBack(line);
    }

  }

  List<string> codeAzuri = traduzirIanteco(dict, codeList);

  // Print da traducao pra entender bugs
  cout << "\n=== CODIGO TRADUZIDO ===\n";
  ListNavigator<string> nav = codeAzuri.getListNavigator();
  string translatedLine;
  while (nav.getCurrentItem(translatedLine)) {
    cout << translatedLine << endl;
    nav.next();
  }
  cout << "=======================\n\n";

  ExecutorAzuri(codeAzuri);

  return 0;
    
}