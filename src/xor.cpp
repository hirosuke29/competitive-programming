/*
 　**0からxまでのXOR和**
 　XORは結合法則と交換法則が成立
 　XORの和は差と同じ
 　a^a=0なのでa^x=bとなるxは両辺a^をとってx=a^bとなる
*/

template <class T>
T getxor(T x) {
    if (x % 2) {
        if (((x + 1) / 2) % 2)
            return 1;
        else
            return 0;
    }
    else
        return getxor(x + 1) ^ (x + 1);
}