String 
===
[1 String ADT:](https://github.com/JimmyJUNUCAS/Daily-Code/blob/master/String/String.md#string-adt)

[2 String Match:](https://github.com/JimmyJUNUCAS/Daily-Code/blob/master/String/String.md#string-match)

	* 2.1 KMP 
	* 2.2 BC + GS 
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
### KMP<br>

### BC+GS<br>
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
<<<<<<< HEAD
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
>>>>>>> origin/master

#### BC: Bad Char
