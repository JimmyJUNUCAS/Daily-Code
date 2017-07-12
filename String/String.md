String 
===
[1 String ADT:](https://github.com/JimmyJUNUCAS/Daily-Code/blob/master/String/String.md#string-adt)

[2 String Match:](https://github.com/JimmyJUNUCAS/Daily-Code/blob/master/String/String.md#string-match)

	* 2.1 KMP 
	* 2.2 BM (BC + GS) 
	* 2.3 KR 

String ADT:
---
|  接口  | 功能 | 备注 |
|---------: | :--------| :--------:|
| length()  |查询串长度 | 长度 |
| charAt(i) |返回第i个字符 |查询|
|substr(i,k)|返回第i个字符起长度为k的子串 |查询|
| prefix(k) |返回长度为k的前缀 |查询|
| suffix(k) |返回长度为k的后缀 |查询|
| equal(T)  |判断T是否与当前字符串相等 |判等|
| concat(T) |将T串接在当前字符串之后 |拼接|
| indexOf(P)|若P是当前字符串的子串，则返回该子串的起始位置；否则返回-1 |匹配|

String Match:
---
### 2.1 KMP<br>

### 2.2 BM<br>
整体思路：KMP关注成功的匹配，而失败在整体思路来看，显得更重要。<br>
失败决定了此次循环是否结束。（判定相等与判定不等->差距很大）<br>
同时越靠后的失败其价值更高，因为有其存在省略了接下来的比对 <br>
综上所述，BC/GS选择了 从右向左 检索的方式来取代 KMP 算法 从左向右 的检索方式。

#### BC: Bad Char
将失配的字符定义为坏字符<br>
当定位此轮循环失配之后，模式符应该继续移动，移动到模式符中与此坏字符匹配为止。
此时存在三种情况：<br>
>1 多个匹配，选择最右字符，最右字符在当前失配字符左侧，移动至坏字符<br>
>2 多个匹配，选择最右字符，最右字符在当前失配字符右侧，移动一个字符<br>
>3 无匹配，将整个字符串移过此坏字符<br>

针对此三种情况构造 模式串 对应的BC表，通过构造BC表完成此算法最主要部分
``` C++
int* buildBC ( char* P ) { //构造Bad Charactor Shift表：O(m + 256)
   int* bc = new int[256]; //BC表，与字符表等长
   for ( size_t j = 0; j < 256; j ++ ) bc[j] = -1; //初始化：首先假设所有字符均未在P中出现
   for ( size_t m = strlen ( P ), j = 0; j < m; j ++ ) //自左向右扫描模式串P
      bc[ P[j] ] = j; //将字符P[j]的BC项更新为j（单调递增）——画家算法
   /*DSA*/printBC ( bc );
   return bc;
}
```
=======
#### GS: Good String
将失配后已经匹配过的后缀称为好后缀，希望将好后缀能够再次对齐。<br>
将好后缀再次对齐可以节省大量的试错时间。充分利用了已经匹配的经验。<br>
构建好后缀表的思路是，在模式串前缀中寻找与好后缀匹配的子串。<br>
可以分为两种情况：
>1 找到的匹配串小于好后缀的长度。<br>
>2 找到的匹配串大于好后缀的长度。<br>

构建好后缀通过两个步骤，1 是构建最大匹配后缀长度表。 2 是构建好后缀位移量表<br>

---
1 构建最大匹配后缀长度表
``` C++
int* buildSS ( char* P ) { //构造最大匹配后缀长度表：O(m)
   int m = strlen ( P ); int* ss = new int[m]; //Suffix Size表
   ss[m - 1]  =  m; //对最后一个字符而言，与之匹配的最长后缀就是整个P串
// 以下，从倒数第二个字符起自右向左扫描P，依次计算出ss[]其余各项
   for ( int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j -- )
      if ( ( lo < j ) && ( ss[m - hi + j - 1] <= j - lo ) ) //情况一
         ss[j] =  ss[m - hi + j - 1]; //直接利用此前已计算出的ss[]
      else { //情况二
         hi = j; lo = __min ( lo, hi );
         while ( ( 0 <= lo ) && ( P[lo] == P[m - hi + lo - 1] ) ) //二重循环？
            lo--; //逐个对比处于(lo, hi]前端的字符
         ss[j] = hi - lo;
      }
   /*DSA*/printf ( "-- ss[] Table -------\n" );
   /*DSA*/for ( int i = 0; i < m; i ++ ) printf ( "%4d", i ); printf ( "\n" );
   /*DSA*/printString ( P ); printf ( "\n" );
   /*DSA*/for ( int i = 0; i < m; i ++ ) printf ( "%4d", ss[i] ); printf ( "\n\n" );
   return ss;
}
```
---
2 构建好后缀位移量表
``` C++
int* buildGS ( char* P ) { //构造好后缀位移量表：O(m)
   int* ss = buildSS ( P ); //Suffix Size table
   size_t m = strlen ( P ); int* gs = new int[m]; //Good Suffix shift table
   for ( size_t j = 0; j < m; j ++ ) gs[j] = m; //初始化
   for ( size_t i = 0, j = m - 1; j < UINT_MAX; j -- ) //逆向逐一扫描各字符P[j]
      if ( j + 1 == ss[j] ) //若P[0, j] = P[m - j - 1, m)，则
         while ( i < m - j - 1 ) //对于P[m - j - 1]左侧的每个字符P[i]而言（二重循环？）
            gs[i++] = m - j - 1; //m - j - 1都是gs[i]的一种选择
   for ( size_t j = 0; j < m - 1; j ++ ) //画家算法：正向扫描P[]各字符，gs[j]不断递减，直至最小
      gs[m - ss[j] - 1] = m - j - 1; //m - j - 1必是其gs[m - ss[j] - 1]值的一种选择
   /*DSA*/printGS ( P, gs );
   delete [] ss;   return gs;
}
```
---
算法整体为：
``` C++
int match ( char* P, char* T ) { //Boyer-Morre算法（完全版，兼顾Bad Character与Good Suffix）
   int* bc = buildBC ( P ); int* gs = buildGS ( P ); //构造BC表和GS表
   size_t i = 0; //模式串相对于文本串的起始位置（初始时与文本串左对齐）
   while ( strlen ( T ) >= i + strlen ( P ) ) { //不断右移（距离可能不止一个字符）模式串
      int j = strlen ( P ) - 1; //从模式串最末尾的字符开始
      while ( P[j] == T[i + j] ) //自右向左比对
         if ( 0 > --j ) break; /*DSA*/showProgress ( T, P, i, j ); printf ( "\n" ); getchar();
      if ( 0 > j ) //若极大匹配后缀 == 整个模式串（说明已经完全匹配）
         break; //返回匹配位置
      else //否则，适当地移动模式串
         i += __max ( gs[j], j - bc[ T[i + j] ] ); //位移量根据BC表和GS表选择大者
   }
   delete [] gs; delete [] bc; //销毁GS表和BC表
   return i;
}
```

---
### 2.3 KR<br>
整体思路：将一切字符串均看做是整数，所以字符串的匹配转化成整数的匹配过程。<br>
通过散列技术完成字符串与整数的匹配。同时通过指纹快速更新来完成快速匹配的过程。
