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
            if (maze[i][j] == 2)
            {
                cout << ".";
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
bool solveMaze(int maze[N][N], coord current, vector<coord> &path)
{
    // mapa com as celulas já visitadas
    map<coord, bool> visited_map;
    // pilha com as celulas a serem visitadas
    stack<coord> to_visit;

    // começando de (0,0)
    to_visit.push(current);

    // enquanto houverem celulas a serem visitadas
    while (!to_visit.empty())
    {
        // pega coordnada do topo da pilha
        coord current_coord = to_visit.top();
        to_visit.pop();

        // desempacota a tupla
        int i = get<0>(current_coord);
        int j = get<1>(current_coord);

        // checa se está no final
        if (i == N - 1 && j == N - 1)
        {
            path.push_back(current_coord);
            // marca os 
            for (const auto &p : path)
            {
                int x = get<0>(p);
                int y = get<1>(p);
                maze[x][y] = 2; // Mark the path as 2
            }
            return true; // Stop when a solution is found
        }

        // checa se posição valida e não visitada.
        // se não for, pula para a proxima iteração sem executar o que está abaixo deste if
        if (!isValid(i, j) || maze[i][j] == 1 || visited_map[current_coord])
            continue;
       
        // marca posição se 
        visited_map[current_coord] = true;
        path.push_back(current_coord);

        // empilha os vizinhos para visita-los,
        // comçando com o imediatamente abaixo 
        to_visit.push(make_tuple(i + 1, j));
        to_visit.push(make_tuple(i, j + 1));
        to_visit.push(make_tuple(i, j - 1));
        to_visit.push(make_tuple(i - 1, j));
    }

    // se pilha vazia sem retorno, não há solução
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

    // vetor com o caminho percorrido
    vector<coord> path;

    // chama a função iterativa de resolução do labirinto
    if (solveMaze(maze, make_tuple(0, 0), path))
    {
        cout << "Labirinto resolvido" << endl;
        printMaze(maze);
    }
    else
    {
        cout << "Não há solução" << endl;
    }

    return 0;
}
