# sg-HexGrid
基于opencv绘制的六边形网格元胞自动机
##细胞自动机
细胞自动机（cellular automata）是为模拟包括自组织结构在内的复杂现象提供的一个强有力的方法，也称为元胞自动机（Cellular Automaton）。细胞自动机模型的基本思想是：自然界里许多复杂结构和过程，归根到底只是由大量基本组成单元的简单相互作用所引起。细胞自动机主要研究由小的计算机或部件，按邻域连接方式连接成较大的、并行工作的计算机或部件的理论模型。它分为固定值型、周期型、混沌型以及复杂型。
##生命游戏（Game of Life）
生命游戏是由3条规则构成的二维元胞自动机(2D Cellular Automata), 它在1970年被英国的数学家约翰·何顿·康威发明, 很多好奇的计算机爱好者都写过这个程序并让这些人造生物繁殖在自己的计算机上。
#如果一个生命，其周围的同类生命太少，会因为得不到帮助而死亡；如果太多，则会因为得不到足够的生命资源而死亡。 ——英国数学家约翰·康威
生命游戏事实上并不是通常意义上的”游戏”, 它没有游戏玩家各方之间的竞争, 也谈不上输赢，可以把它归类为“仿真游戏”。事实上，也是因为它模拟和显示的图象，看起来颇似生命的出生和繁衍过程而得名为“生命”。游戏在一个类似于围棋棋盘一样的，可以无限延伸的二维方格网中进行。例如，设想每个方格中都可放置一个生命细胞，生命细胞只有两种状态：“生”或“死”。图中，用黑色的方格表示该细胞为“生”, 空格表示该细胞为“死” 。游戏开始时, 每个细胞可以随机地（或给定地）被设定为“生”或“死”之一的某个状态, 然后，再根据某种规则（生存定律）计算下一代每个细胞的状态：
我们可以规定如下的‘生存定律’：
1． 每个细胞的状态由该细胞及周围八个细胞上一次的状态所决定；
2. 如果一个细胞周围有3个细胞为生，则该细胞为生，即该细胞若原先为死，则转为生，若原先为生，则保持不变；
3. 如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；
4. 在其它情况下，该细胞为死，即该细胞若原先为生，则转为死，若原先为死，则保持不变
以上是都是基于方形网格的自动机。
##Hex Grid
均匀、对称、和谐与美，本人觉得方形不够完美，因为方形的结构不够均匀（很容易理解，到侧方的距离和到对角的距离是不等的），所以本人开发了这个基于六边形网格的元胞自动机程序。
