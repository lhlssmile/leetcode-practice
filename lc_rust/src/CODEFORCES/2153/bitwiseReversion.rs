use std::io::{self, Read};

fn ok(x: i32, y: i32, z: i32) -> bool {
    for i in 0..30 {
        let (xi, yi, zi) = ((x >> i) & 1, (y >> i) & 1, (z >> i) & 1);
        if xi + yi + zi == 2 {
            return false;
        }
    }
    true
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let x: i32 = it.next().unwrap().parse().unwrap();
        let y: i32 = it.next().unwrap().parse().unwrap();
        let z: i32 = it.next().unwrap().parse().unwrap();
        if ok(x, y, z) {
            println!("YES")
        } else {
            println!("NO")
        }
    }
}
