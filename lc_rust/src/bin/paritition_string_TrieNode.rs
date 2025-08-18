use std::rc::Rc;
use std::cell::RefCell;

struct TrieNode {
    son: [Option<Rc<RefCell<TrieNode>>>; 26],
}

impl TrieNode {
    fn new() -> Self {
        TrieNode { son: Default::default() }
    }
}

fn partition_string(s: &str) -> Vec<String> {
    let mut ans = vec![];
    let root = Rc::new(RefCell::new(TrieNode::new()));
    let mut curr = Rc::clone(&root);
    let mut left = 0;

    for (i, ch) in s.chars().enumerate() {
        let idx = (ch as u8 - b'a') as usize;

        // 这里分开借用
        let has_child = curr.borrow().son[idx].is_some();
        if !has_child {
            // 新段
            curr.borrow_mut().son[idx] = Some(Rc::new(RefCell::new(TrieNode::new())));
            ans.push(s[left..=i].to_string());
            left = i + 1;
            curr = Rc::clone(&root); // 重置
        } else {
            let next = Rc::clone(curr.borrow().son[idx].as_ref().unwrap());
            curr = next;
        }
    }

    ans
}

fn main() {
    let s = "abbccccd";
    let res = partition_string(s);
    println!("{:?}", res);
}
