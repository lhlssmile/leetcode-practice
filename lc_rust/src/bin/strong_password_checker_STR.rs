struct Solution;

impl Solution {
    pub fn strong_password_checker(password: String) -> bool {
        if password.len() < 8 {return false}
        let mut mask = 0;
        let special = "!@#$%^&*()-+";
        let mut has_lower = false;
        let mut has_upper = false;
        let mut has_digit = false;
        let mut has_special = false;
        let chars :Vec<char> = password.chars().collect();
        for i in 0..chars.len() {
            let c = chars[i];
            if i > 0 && c == chars[i - 1] {
                return false;
            }
            if c.is_ascii_lowercase() {
                has_lower = true;
            } else if c.is_ascii_uppercase() {
                has_upper = true;
            } else if c.is_ascii_digit() {
                has_digit = true;
            } else if special.contains(c) {
                has_special = true;
            }
        }

        has_lower && has_upper && has_digit && has_special
    }
}

fn main() {

}