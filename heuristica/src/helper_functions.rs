use std::io;

pub fn pretty_print_map(map: &Vec<Vec<i32>>) {
    for line in map {
        for cell in line {
            if *cell == 1 {
                print!("#");
            }
            if *cell == 0 {
                print!(" ");
            }
            if *cell == 2 {
                print!("*");
            }
        }
        print!("\n");
    }
}

pub fn pretty_print_path(path:&Vec<(i32,i32)>) {
    let path_len = path.len();
    let mut count:usize = 0;
    println!("Caminho encontrado!");
    for (i,j) in path {
        count+=1;
        if count != path_len{
            print!("({i},{j})->");
        }else{
            print!("({i},{j})");
        }
    }
    print!("\n");
}

// Le 2 inteiros separados por virgula e os processa para uma tupla
pub fn get_input_coord() -> (i32, i32) {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Erro lendo a entrada!");

    let split_input: Vec<&str> = input.split(',').collect();

    // dbg!(&split_input);

    let first: i32 = split_input[0].trim().parse().expect("Erro de conversão");
    let second: i32 = split_input[1].trim().parse().expect("Erro de conversão");

    return (first, second);
}