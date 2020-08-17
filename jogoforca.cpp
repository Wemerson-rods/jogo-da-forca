#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

string secretWord;
map<char, bool> kickHit;
vector<char> kickError;

void openGame()
{
    cout << "**************************" << endl;
    cout << "*      Jogo da Forca     *" << endl;
    cout << "**************************" << endl;
    cout << endl;
}
// Ler palavras do arquivo
vector<string> readFile()
{
    int numberWord;
    vector<string> wordFile;
    ifstream file;
    
    file.open("palavras.txt");
    if(file.is_open())
    {
        file >> numberWord;
        
        for(int i = 0; i < numberWord; i++)
        {
            string s;
            file >> s;
            wordFile.push_back(s);
        }
        file.close();
        
        return wordFile;
    }
    else
    {
        cout << "Não foi possível acessar o arquivo de palavras!" << endl;
        exit(0);
    }
}
// Escrever em um arquivo
void writeFile(vector<string> wordFile)
{
    ofstream file;
    
    file.open("palavras.txt");
    
    if(file.is_open())
    {
        file << wordFile.size() << endl;
        
        for(string word : wordFile)
        {
            file << word << endl;
        }
        
        file.close();
    }
    else
    {
        cout << "Não foi possível acessar o arquivo de palavras!" << endl;
        exit(0);
    }
}
// Selecionar uma palavra do arquivo
void selectWord()
{
    vector<string> wordFile = readFile();
    srand(time(NULL));
    int index = rand() % wordFile.size();
    
    secretWord = wordFile[index];
}
// Adicionar novas palavras
void addWord()
{
    string newWorld;
    vector<string> wordFile = readFile(); 
    
    cout << "Qual a nova palavra? ";
    cin >> newWorld;
    
    wordFile.push_back(newWorld);
    
    writeFile(wordFile);
}
// Encontrar letra
bool findLetter(char letter)
{
    for(char c : secretWord)
    {
        if(c == letter)
        {
            return true;
        }
    }
    return false;
}
// Receber uma letra chutada pelo usuário
void kickLetter()
{
    char kick;
    
    cout << "\nChute uma letra: ";
    cin >> kick;
    if (findLetter(kick))
    {
        kickHit[kick] = true;
    }
    else
    {
        kickError.push_back(kick);
    }
}
// Imprimir letras erradas
void printError()
{
    cout << "Letras erradas: ";
    for(char c : kickError)
    {
        cout << c << " ";
    }
    cout << endl;
}
// Desenhar a forca
void drawHangman()
{
    printError();
    
    for(char c : secretWord)
    {
        if(kickHit[c])
        {
            cout << c << " ";
        }
        else
        {
            cout <<"_ ";
        }
    }
    cout << endl;
}
// Verificar se ganhou o Jogo
bool win()
{
    for(char c : secretWord)
    {
        if(!kickHit[c])
        {
            return false;
        }
    }
    return true;
}
// Verificar se perdeu o Jogo
bool lose()
{
    return (kickError.size() >= 5); 
}

int main()
{
    openGame();
    selectWord();
    drawHangman();
    
    do
    {
        kickLetter();
        drawHangman();
        
    }while(!win() && !lose());
    
    if(win())
    {
        cout << "\nParabéns, você ganhou!" << endl;
        
        char want;
        cout << "Você deseja adicionar uma nova palavra no jogo? (S/N) ";
        cin >> want;
    
        if(want == 'S')
        {
            addWord();
        }
    }
    else
    {
        cout << "\nPuxa, você foi enforcado!" << endl;
        cout << "A palavra era ** " << secretWord << " **" << endl;
    }
    return 0;
}
