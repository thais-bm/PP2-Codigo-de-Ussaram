#include <cctype>
#include <cstdlib>
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
  bool end();
  void next();
  void reset();
  bool getCurrentItem(T &item);
  int getCurrentPosition() const;
  void seekToPosition(int pos);
  ListNavigator(Node<T> *current);
};

template <typename T> ListNavigator<T>::ListNavigator(Node<T> *current) {
  this->current = current;
  this->start = current;
}

template <typename T> bool ListNavigator<T>::end() {
  return current == nullptr;
}

template <typename T> void ListNavigator<T>::next() { current = current->next; }

template <typename T> void ListNavigator<T>::reset() { current = start; }

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
// Funcao responsavel por remover os espacos em branco do inicio e do fim de uma
// string
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

bool isIantecoFunctionCall(const string &line) {
  return line.size() == 1 && isupper(line[0]);
}

// Funcao responsavel por detectar o fim de uma funcao
bool isEndFunction(const string& line) {
    return (line.find("FIM DE FUNCAO") != string::npos);
}


// Funcao responsavel por executar o codigo Azuri
// Ta bugada e nao sei como consertar

void ExecutorAzuri(List<string> codeList) {
  ListNavigator<string> nav = codeList.getListNavigator();
  Queue<string> msg(List<string>{});
  Stack<string> functionStack(List<string>{});

  // Procura a funcao principal (Z :)
  cout << "Executando funcao principal..." << endl;
  string line;
  while (!nav.end()) {
    nav.getCurrentItem(line);
    line = trim(line);
    if (isMainFunction(line)) {
      line.pop_back(); // Remove o ':'
      line = trim(line); // Remove espacos em branco
      functionStack.push(line); // Empilha a funcao principal
      cout << "Funcao principal encontrada: " << line << endl;
      break;
    }
    nav.next();
  }


  // Executa as funcoes que estao na pilha
  while (!functionStack.empty()) {
    string currentFunction = functionStack.top();// Pega a funcao atual (topo da pilha)
    nav.reset(); // Volta para o inicio do codigo
    cout << "Funcao atual: " << currentFunction << endl;

    // Procura a funcao atual
    while (!nav.end()) {
      nav.getCurrentItem(line);
      line = trim(line);
      if (isIantecoFunction(line)) {
        line.pop_back(); // Remove o ':'
        line = trim(line); // Remover espaco em branco
        if ( line == currentFunction) {
          cout << "Funcao: " << line << endl;
          break;
        }
      }

      nav.next(); // Pular para prox linha
    }

    // Executa os comandos da funcao atual ou empilha a proxima,
    // ACHEI O ERRO
    // ta, quando ele comeca a desempilhar, ele ta executando a funcao anterior DO INICIO, ao inves de onde parou
    // Como arruma? Vou pensar depois
    while (!nav.end()) {
      nav.getCurrentItem(line);
      line = trim(line);

      // Aqui pode ser o culpado do loop
      if (isEndFunction(line)){
        functionStack.pop(); // Desempilha a funcao atual
        break;
      }

      if (isIantecoFunctionCall(line)) {
        cout << "Funcao: " << line << "empilhada" << endl;
        functionStack.push(line);
        currentFunction = functionStack.top();
        break;
      }
      else if (line.find("DESENFILEIRA") != string::npos) {
        cout << "Desenfileirando" << endl;
        msg.dequeue();
      }
      else if (line.find("ENFILEIRA") != string::npos) {
        cout << "Enfileirando: " << line.substr(10) << endl;
        msg.enqueue(line.substr(10)); // Remove o "ENFILEIRA "
      }

      nav.next();
    }

  }

  // Imprime o resultado
  std::cout << "Resultado: ";
  while (!msg.empty()) {
    cout << msg.front() << " ";
    msg.dequeue();
  }
  cout << endl;
}

int main() {
  List<string> codeList;
  string line;

  while (getline(cin, line) && line != "~") {
    if (line.find_first_not_of(" \t\r\n") == std::string::npos || line.empty() || line.empty()) {
      codeList.insertBack("FIM DE FUNCAO");
    }
    else {
      codeList.insertBack(line);
    }

  }

  // Problemas do codigo:

  // while (!codeList.empty()) {
  //   cout << codeList.getItemFront() << endl;
  //   codeList.removeFront();
  // }

  ExecutorAzuri(codeList);

  return 0;

  /*
          /| _ ╱|、
         ( •̀ㅅ •́  )
       ＿ノ ヽ ノ＼＿
      /　`/ ⌒Ｙ⌒ Ｙ　 \
     ( 　(三ヽ人　 /　 　|
    |　ﾉ⌒＼ ￣￣ヽ　 ノ
    ヽ＿＿＿＞､＿＿／
          ｜( 王 ﾉ〈
         /ﾐ`ー―彡\
        |       ╯|
        |   /\   |
        |  /  \  |
        | /    \ |

  */
}

/*
Codigo de teste

C :
ENFILEIRA T
ENFILEIRA A
ENFILEIRA Q

A :
ENFILEIRA A
C
DESENFILEIRA
DESENFILEIRA
ENFILEIRA U

B :
ENFILEIRA A
ENFILEIRA T
DESENFILEIRA
A

Z :
ENFILEIRA X
ENFILEIRA Q
B
ENFILEIRA E
DESENFILEIRA

~

OUTPUT: ATAQUE
*/
