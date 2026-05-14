#ifndef MAPPA_HPP
#define MAPPA_HPP
class Mappa {
public:
    // Ritorna vero se siamo dentro il rettangolo 40x20 (Slide 20)
    bool isVuoto(int y, int x) {
        return (y > 0 && y < 19 && x > 0 && x < 39);
    }
    bool isRed(int y, int x) { return false; } // Per ora niente fuoco
};
#endif
