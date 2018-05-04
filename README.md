# Quintuple-Go (NCTU intro to AI 2018)
An MCTS implementation of connect-5 (a.k.a gobang). The map different from normal 19*19 board. It is in a shape of hexagon.
Please read the `PR2.pdf` to know the details.

Our report is `PR2_Group7_report.pdf`(Tradisional Chinese). Please read it if interested.

# Random Notes here
OS: Arch linux, compiler: clang++ 6.0.0

- 有 Makefile 可以使用，手動 compile 需要 -O3 ，不然趕不及在 5s 內 simulate 足夠的數字
- 這個作業在期中考週結束的當下才開始寫的，6 天內能寫完我覺得還蠻神奇的，雖然還是沒趕上原始 deadline，但是只扣 5 分的話我覺得還可以接受。
- 在最後 debug 的時候，還把 simulation 用的 heuristic 拿來跟自己對戰，幸好有成功獲勝
- 再處理 thread 之間的 sync 也下了許多功夫，畢竟都寫成了 multithreaded program。
- 因為地圖的關係，我還刻了整個地圖的 map，每個點，六個方向都有正確的位置
