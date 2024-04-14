#include <bits/stdc++.h>

// tamanho do labirinto
#define N 61

using namespace std;

/* coordenada do labirinto */
typedef tuple<int, int> coord;

/*Checa se uma coordenada é valida*/
bool isValid(int i, int j)
{
    if (i >= 0 && i < N && j >= 0 && j < N)
    {
        return true;
    }
    return false;
}

/*Recebe um labirinto e o imprime*/
void printMaze(int maze[N][N])
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (maze[i][j] == 0)
            {
                cout << " ";
            }
            if (maze[i][j] == 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }
}

/*Carrega o labirinto a partir de uma arquivo*/
void loadMaze(int maze[N][N], string path)
{
    ifstream file(path);
    string str;

    int i = 0;
    while (getline(file, str))
    {
        for (size_t j = 0; j < N; j++)
        {
            // ASCII de 0 é 48 então é necessário subtrair 48 para se ter o número correto
            maze[i][j] = str[j] - 48;
        }
        i++;
    }
}

/* Função que resolve o labirinto a partir da posição 0 0 */
bool solveMaze(int maze[N][N], coord currrent)
{

    /* Lista de coordenadas do map que levam até o final do labirinto*/
    vector<coord> path;
    /* Mapa de coordenadas já visitadas*/
    map<coord, bool> visited_map;
    /* Pilha dos pontos a serem visitados*/
    stack<coord> to_visit;

    // inicialização do mapa de coordenadas visitadas
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (maze[i][j] != 1)
            {
                visited_map[make_tuple(i, j)] = false;
            }
        }
    }

    // insere o inicio do labirinto na pilha de coordenadas a serem visitadas
    to_visit.push(make_tuple(0, 0));

    // executa uma busca em profundidade no labirinto até encontrar a saída
    while (!to_visit.empty())
    {
        coord current_coord = to_visit.top();
        to_visit.pop();

        if (!visited_map.count(current_coord))
        {
            cout << "(" << get<0>(current_coord) << "," << get<1>(current_coord) << ")" << endl;
            int i = get<0>(current_coord);
            int j = get<1>(current_coord);
            
            if (isValid(i-1,j))
            {
                to_visit.push(make_tuple(i-1,j));
            }
            if (isValid(i,j-1))
            {
                to_visit.push(make_tuple(i,j-1));
            }
            if (isValid(i+1,j))
            {
                to_visit.push(make_tuple(i+1,j));
            }
            if (isValid(i,j+1))
            {
                to_visit.push(make_tuple(i,j+1));
            }
            
        }
    }

    return false;
}

int main()
{
    /*Labirinto de tamanho N*N com paredes
    representadas por 1 e caminhos possíveis
    representados por 0*/
    int maze[N][N];

    loadMaze(maze, "../lab.txt");

    printMaze(maze);

    if (solveMaze(maze, make_tuple(0, 0)))
    {
        cout << "Labirinto resolvido" << endl;
    }
    else
    {
        cout << "Não há solução" << endl;
    }
    return 0;
}