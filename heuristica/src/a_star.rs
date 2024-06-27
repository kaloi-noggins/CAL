use std::cmp::Ordering;

#[derive(Debug, Clone)]
struct Cell {
    row_index: i32,
    col_index: i32,
    f: f64,
    g: f64,
    h: f64,
    parent_coord: Option<(i32, i32)>,
}

// Método construtor para a celula
impl Cell {
    fn new(
        row_index: i32,
        col_index: i32,
        f: f64,
        g: f64,
        h: f64,
        parent_coord: Option<(i32, i32)>,
    ) -> Cell {
        Cell {
            row_index,
            col_index,
            f,
            g,
            h,
            parent_coord,
        }
    }
}

// Implementação de Ord, PartialOrd e PartialEq para poder ordenar células
// baseado no valor da função de custo f
impl PartialOrd for Cell {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        self.f.partial_cmp(&other.f)
    }
}

impl Ord for Cell {
    fn cmp(&self, other: &Self) -> Ordering {
        self.partial_cmp(other).unwrap_or(Ordering::Equal)
    }
}

impl PartialEq for Cell {
    fn eq(&self, other: &Self) -> bool {
        self.f == other.f
    }
}

impl Eq for Cell {}

fn find_cell(cells: &Vec<Cell>, row_index: i32, col_index: i32) -> Option<&Cell> {
    cells
        .iter()
        .find(|&cell| cell.row_index == row_index && cell.col_index == col_index)
}

//======= Funções relacionadas ao A*

// Distancia euclidiana entre a e b como heuristica
fn heuristic(a: (i32, i32), b: (i32, i32)) -> f64 {
    let a0 = a.0 as f64;
    let a1 = a.1 as f64;
    let b0 = b.0 as f64;
    let b1 = b.1 as f64;

    ((a0 - b0).powf(2.0) + (a1 - b1).powf(2.0)).sqrt()
}

// Checa se a posição está dentro do mapa
fn is_valid(pos: (i32, i32), row_count: i32, col_count: i32) -> bool {
    pos.0 >= 0 && pos.0 < row_count && pos.1 >= 0 && pos.1 < col_count
}

// Checa se a posição informada está bloqueada (1 é tratado como digito)
fn is_blocked(pos: (i32, i32), map: &Vec<Vec<i32>>) -> bool {
    if map[pos.0 as usize][pos.1 as usize] == 1 {
        return true;
    } else {
        return false;
    }
}

// Recebe a celula destino e a lista de celulas visitadas, e constroi o caminho
// da origem até a celula destino
fn build_path(current_node: Cell, closed_list: &Vec<Cell>) -> Vec<(i32, i32)> {
    let mut current_node = current_node;
    // Declara o vetor com o caminho
    let mut path: Vec<(i32, i32)> = Vec::new();
    // Insere o destino no caminho
    path.push((current_node.row_index, current_node.col_index));

    while let Some(parent) = current_node.parent_coord {
        path.push((parent.0, parent.1));
        match find_cell(&closed_list, parent.0, parent.1) {
            Some(cell) => current_node = cell.clone(),
            None => break,
        }
    }

    // Inverte o caminho para ir da origem ao destino
    path.reverse();
    path
}

// Recebe a celula atual e o mapa, e para cada uma das 4 direções, checa se
// é uma posição valida e se não está bloqueada, retornando um vetor de novas
// coordenadas para serem inseridos na lista aberta
fn get_neighbors(current_cell: &Cell, map: &Vec<Vec<i32>>) -> Vec<(i32, i32)> {
    // Direções para procura
    let directions: Vec<(i32, i32)> = vec![(0, 1), (1, 0), (0, -1), (-1, 0)];
    // Lista de coodernads a serem exploradas
    let mut neighbors: Vec<(i32, i32)> = Vec::new();

    for (delta_row, delta_col) in directions {
        let pos = (
            current_cell.row_index + delta_row,
            current_cell.col_index + delta_col,
        );
        let row_count: i32 = map.len() as i32;
        let col_count: i32 = map[0].len() as i32;
        if is_valid(pos, row_count, col_count) && !is_blocked(pos, map) {
            neighbors.push(pos);
        }
    }

    neighbors
}

// Busca em mapa nxn, sendo 0 celula caminhavel, 1 parede
pub fn a_star_search(
    orig: (i32, i32),
    des: (i32, i32),
    map: &Vec<Vec<i32>>,
) -> Result<Vec<(i32, i32)>, &str> {
    // Tamanho do map
    let row_count: i32 = map.len() as i32;
    let col_count: i32 = map[0].len() as i32;

    // Listas aberta e fechada
    let mut open_list: Vec<Cell> = Vec::new();
    let mut closed_list: Vec<Cell> = Vec::new();

    // Se orig ou des estiverem fora do mapa ou estiverem bloqueados
    if !is_valid(orig, row_count, col_count)
        || !is_valid(des, row_count, col_count)
        || is_blocked(orig, map)
        || is_blocked(des, map)
    {
        return Err("Coordenadas para busca são invalidas");
    }

    // Constroi a primeira célula visitada e a insere na lista aberta
    let starting_cell = Cell::new(orig.0, orig.1, 0.0, 0.0, 0.0, None);
    open_list.push(starting_cell);

    // Enquanto houverem celulas a serem exploradas no mapa
    while let Some(current_cell) = open_list.pop() {
        // Se a celula atual for o destino
        if current_cell.row_index == des.0 && current_cell.col_index == des.1 {
            // Array com as coordenadas econtradas
            let path: Vec<(i32, i32)> = build_path(current_cell, &closed_list);
            // se tudo ocorreu bem, retorna o caminho encontrado
            return Ok(path);
        }

        for neighbor in get_neighbors(&current_cell, map) {
            if closed_list
                .iter()
                .any(|cell| cell.row_index == neighbor.0 && cell.col_index == neighbor.1)
            {
                continue;
            }

            let tentative_g = current_cell.g + 1.0;
            let existing_neighbor = open_list
                .iter_mut()
                .find(|cell| cell.row_index == neighbor.0 && cell.col_index == neighbor.1);

            if let Some(neighbor_cell) = existing_neighbor {
                if tentative_g < neighbor_cell.g {
                    neighbor_cell.g = tentative_g;
                    neighbor_cell.f = neighbor_cell.g + neighbor_cell.h;
                    neighbor_cell.parent_coord =
                        Some((current_cell.row_index, current_cell.col_index));
                }
            } else {
                let h = heuristic(neighbor, des);
                let new_cell = Cell::new(
                    neighbor.0,
                    neighbor.1,
                    tentative_g + h,
                    tentative_g,
                    h,
                    Some((current_cell.row_index, current_cell.col_index)),
                );
                open_list.push(new_cell);
            }
        }

        open_list.sort_by(|a, b| b.partial_cmp(a).unwrap_or(Ordering::Equal));
        closed_list.push(current_cell);
    }

    // Se percorreu todos os nós e não achou nenhum caminho
    // então não há caminho entre orig e dest
    Err("Nenhum camiho encontrado")
}
