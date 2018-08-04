#ifndef LENGTH_HPP
#define LENGTH_HPP

struct Length {
    static Length from_au(double val_au);
    static Length from_angstrom(double val_angst);
    operator double() const;
    Length();
private:
    explicit Length(double val_au);
    double val_au;
};

inline Length::Length() :
val_au(0.0){
}

inline Length::Length(double val_au) :
val_au(val_au) {
}

inline Length Length::from_au(double val_au) {
    return Length(val_au);
}

inline Length Length::from_angstrom(double val_angst) {
    return Length(val_angst / 0.53);
}

inline Length::operator double() const {
    return val_au;
}

#endif
