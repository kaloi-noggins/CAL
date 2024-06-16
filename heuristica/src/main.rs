use std::{
    fs,
    io::{self, BufRead},
};

mod a_star;
mod helper_functions;

use a_star::a_star_search;
use helper_functions::{get_input_coord, pretty_print_map, pretty_print_path};

fn main() {
    let map_path = "data/map01.txt";
    println!("{:?}", map_path);

    let f = fs::File::open(map_path).expect("Couldn't open file");
    let reader = io::BufReader::new(f);

    let mut map: Vec<Vec<i32>> = Vec::new();
    for line in reader.lines() {
        let line = line.expect("Couldn't read line");
        let row: Vec<i32> = line
            .chars()
            .filter_map(|c| c.to_digit(10).map(|d| d as i32))
            .collect();
        map.push(row);
    }

    let row_count: i32 = map.len() as i32;
    let col_count: i32 = map[0].len() as i32;

    println!("Mapa lido:");
    pretty_print_map(&map);
    println!("Dimensão do mapa: {}x{}", row_count, col_count);

    println!("Entre com as coordenadas da origem (ex: 0,0): ");
    let orig = get_input_coord();

    println!(
        "Entre com as coordenadas do destino (ex: {},{}): ",
        row_count - 1,
        col_count - 1
    );
    let des = get_input_coord();

    // dbg!(orig);
    // dbg!(dest);

    match a_star_search(orig, des, &map) {
        Ok(path) => {
            pretty_print_path(&path);
            for (i, j) in path {
                map[i as usize][j as usize] = 2;
            }
            println!("Mapa com caminho: ");
            pretty_print_map(&map);
        }
        Err(e) => {
            println!("{e}");
        }
    }
}
