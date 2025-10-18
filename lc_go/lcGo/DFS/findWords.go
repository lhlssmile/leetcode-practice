package main

import "fmt"

type TrieNode struct {
	children [26]*TrieNode
	word     string
}

func (t *TrieNode) Insert(word string) {
	node := t
	for _, ch := range word {
		idx := ch - 'a'
		if node.children[idx] == nil {
			node.children[idx] = &TrieNode{}
		}
		node = node.children[idx]
	}
	node.word = word
}

func findWords(board [][]byte, words []string) []string {
	root := &TrieNode{}
	for _, w := range words {
		root.Insert(w)
	}

	m, n := len(board), len(board[0])
	dirs := [][]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}}
	var ans []string

	var dfs func(r, c int, node *TrieNode)
	dfs = func(r, c int, node *TrieNode) {
		ch := board[r][c]
		if ch == '#' || node.children[ch-'a'] == nil {
			return
		}
		node = node.children[ch-'a']
		if node.word != "" {
			ans = append(ans, node.word)
			node.word = "" // 避免重复加入
		}

		board[r][c] = '#'
		for _, d := range dirs {
			nr, nc := r+d[0], c+d[1]
			if nr >= 0 && nr < m && nc >= 0 && nc < n {
				dfs(nr, nc, node)
			}
		}
		board[r][c] = ch
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			dfs(i, j, root)
		}
	}

	return ans
}

func main() {
	board := [][]byte{
		{'o', 'a', 'a', 'n'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'k', 'r'},
		{'i', 'f', 'l', 'v'},
	}
	words := []string{"oath", "pea", "eat", "rain"}
	fmt.Println(findWords(board, words)) // 输出: [oath eat]
}
