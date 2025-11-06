use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::io::{self, Read};

macro_rules! read {
    ($it:ident => $t:ty) => {
        $it.next().unwrap().parse::<$t>().unwrap()
    };
}
macro_rules! multi_read {
    ($it:ident => $($t:ty),+) => {
        ($(read!($it => $t)),+)
    };
}

#[derive(Clone, Copy)]
struct Pair {
    op: usize,
    x: usize,
}

fn process_queries(c: usize, connections: &[(usize, usize)], queries: &[Pair]) -> Vec<i32> {
    // 图
    let mut graph = vec![Vec::new(); c + 1];
    for &(u, v) in connections {
        graph[u].push(v);
        graph[v].push(u);
    }

    // belongs[x] = 所属连通分量编号
    let mut belongs = vec![usize::MAX; c + 1];

    // 每个连通分量一个最小堆
    let mut heaps: Vec<BinaryHeap<Reverse<usize>>> = Vec::new();

    // DFS 找分量
    fn dfs(
        x: usize,
        comp_id: usize,
        graph: &Vec<Vec<usize>>,
        belongs: &mut Vec<usize>,
        buf: &mut Vec<usize>,
    ) {
        belongs[x] = comp_id;
        buf.push(x);
        for &y in &graph[x] {
            if belongs[y] == usize::MAX {
                dfs(y, comp_id, graph, belongs, buf);
            }
        }
    }

    // 构建所有连通分量
    for i in 1..=c {
        if belongs[i] != usize::MAX {
            continue;
        }
        let comp_id = heaps.len();
        let mut buf = Vec::new();
        dfs(i, comp_id, &graph, &mut belongs, &mut buf);

        let mut heap = BinaryHeap::new();
        for &x in &buf {
            heap.push(Reverse(x)); // Reverse -> 最小堆
        }
        heaps.push(heap);
    }

    // 离线标记
    let mut offline = vec![false; c + 1];

    // 处理查询
    let mut ans = Vec::new();

    for q in queries {
        let (op, x) = (q.op, q.x);

        if op == 2 {
            offline[x] = true;
            continue;
        }

        if !offline[x] {
            ans.push(x as i32);
            continue;
        }

        let cid = belongs[x];
        let heap = &mut heaps[cid];

        while let Some(&Reverse(top)) = heap.peek() {
            if offline[top] {
                heap.pop();
            } else {
                ans.push(top as i32);
                break;
            }
        }

        if heap.is_empty() {
            ans.push(-1);
        }
    }
    ans
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let c = read!(it => usize);
    let n = read!(it => usize);
    let q = read!(it => usize);

    let mut connections = Vec::new();
    for _ in 0..n {
        let (u, v) = multi_read!(it => usize, usize);
        connections.push((u, v));
    }

    let mut queries = Vec::new();
    for _ in 0..q {
        let (op, x) = multi_read!(it => usize, usize);
        queries.push(Pair { op, x });
    }

    let ans = process_queries(c, &connections, &queries);

    for (i, v) in ans.iter().enumerate() {
        if i > 0 {
            print!(" ");
        }
        print!("{}", v);
    }
    println!();
}
