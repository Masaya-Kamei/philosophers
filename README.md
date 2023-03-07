# 42 philosophers

## 概要

[食事する哲学者の問題](https://ja.wikipedia.org/wiki/%E9%A3%9F%E4%BA%8B%E3%81%99%E3%82%8B%E5%93%B2%E5%AD%A6%E8%80%85%E3%81%AE%E5%95%8F%E9%A1%8C)を題材にした並列処理に関する問題
- 哲学者の位置により右手か左手を優先する解法で実装
- `philo`: マルチスレッドで、ミューテックスによる排他制御
- `philo_bonus`: マルチプロセスで、セマフォによる排他制御

## キーワード

`C`,`マルチスレッド`,`マルチプロセス`,`ミューテックス`,`セマフォ`,`デッドロック`
