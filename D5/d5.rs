use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    let file = File::open("input.txt").unwrap();
    let reader = BufReader::new(file);

    let mut max: u32 = 0;
    let mut ids: [bool; 1024] = [false; 1024];

    for line in reader.lines() {
        let line = line.unwrap();

        let row_bi = &line[0..7].replace("F", "0")
            .replace("B", "1");
        let row = u32::from_str_radix(row_bi, 2).unwrap();

        let col_bi = &line[7..10].replace("L", "0")
            .replace("R", "1");
        let col = u32::from_str_radix(col_bi, 2).unwrap();

        let id: u32 = row * 8 + col;
        ids[id as usize] = true;
        
        if id > max {
            max = id;
        }
    }

    println!("max = {}", max);

    for i in 1..1023 {
        if !ids[i] && ids[i-1] && ids[i+1] {
            println!("missing = {}", i);
            break;
        }
    }
}
