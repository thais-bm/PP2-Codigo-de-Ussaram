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

// Structura para armazenar o contexto da funcao
struct FunctionContext {
  string functionName; // Nome da funcao
  int position; // Onde a funcao comeca
  int returnPosition; // Onde retornar após chamada de função
};

void ExecutorAzuri(List<string> codeList) {
  ListNavigator<string> nav = codeList.getListNavigator(); // Navegador da lista
  Queue<string> msg(List<string>{}); // Fila para armazenar mensagens
  Stack<FunctionContext> functionStack(List<FunctionContext>{}); // Pilha para armazenar o contexto das funcoes

  // Inicializa a pilha com a funcao principal
  FunctionContext Zmain; //Mantendo a funcao main
  string line;

  // Passo 1: Encontrar a funcao principal (Z :)
  while (!nav.end()) {
    nav.getCurrentItem(line);
    line = trim(line);

    if (isMainFunction(line)) {
      line.pop_back(); // Remove ':'
      line = trim(line);

      Zmain.functionName = line;
      Zmain.position = nav.getCurrentPosition() + 1; // posicao da funcao no CodeList
      Zmain.returnPosition = -1; // nao tem retorno
      functionStack.push(Zmain);

      std::cout << "Funcao principal encontrada: " << line << endl;
      break;
    }
    nav.next();
  }

  // Passo 2: Executar as funções empilhadas
  while (!functionStack.empty()) {
    FunctionContext currentFunction = functionStack.top(); // Pega o contexto da funcao atual
    functionStack.pop(); // Remove a função atual da pilha
    
    nav.seekToPosition(currentFunction.position); // Navega para a posicao da funcao
    std::cout << "Executando funcao: " << currentFunction.functionName << endl; // DEBUG

    while (!nav.end()) {
      nav.getCurrentItem(line);
      line = trim(line);

      // Fim da função
      if (isEndFunction(line)) {

        if (currentFunction.returnPosition != -1) {
          ListNavigator<string> search = codeList.getListNavigator();
          string searchLine;

          FunctionContext retorno;
          int func_pos = currentFunction.returnPosition - 1;
          search.seekToPosition(func_pos);
          search.getCurrentItem(searchLine);
          searchLine = trim(searchLine);

          retorno.functionName = searchLine;
          retorno.position = currentFunction.returnPosition;

          // Agora olhamos o topo atual da pilha (a função que chamou esta), se existir
          if (!functionStack.empty()) {
            retorno.returnPosition = functionStack.top().returnPosition;
            std::cout << "Retornando para: " << retorno.returnPosition << endl;
          } else {
            retorno.returnPosition = -1; // Voltou para o fim da main
          }

          functionStack.push(retorno);
          std::cout << "Fim de Funcao: " << currentFunction.functionName << endl;
        }
    break;
  }


      // Chamada de outra função
      if (isIantecoFunctionCall(line)) {
        FunctionContext newContext;
        newContext.functionName = trim(line);
        newContext.returnPosition = nav.getCurrentPosition() + 1;

        // Buscar posição da função chamada
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

        functionStack.push(newContext); // Chamada da nova função
        break; // Pausa execução atual
      }

      // Comandos da linguagem
      else if (line.find("DESENFILEIRA") != string::npos) {
        if (!msg.empty()) {
          msg.dequeue();
          std::cout << "Desenfileirando" << endl;
        } else {
          std::cout << "Fila vazia ao tentar desenfileirar" << endl;
        }
      }
      else if (line.find("ENFILEIRA") != string::npos) {
        string content = line.substr(10); // depois de "ENFILEIRA "
        msg.enqueue(content);
        std::cout << "Enfileirando: " << content << endl;
      }

      nav.next();
    }


  }

  
  // Imprimir resultado final
  std::cout << "Resultado: ";
  while (!msg.empty()) {
    std::cout << msg.front() << " ";
    msg.dequeue();
  }
  std::cout << endl;
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
