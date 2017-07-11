String 
===
String ADT:

String Match:
> KMP <br>
> BC + GS <br>
> KR <br>

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
