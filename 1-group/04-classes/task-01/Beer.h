#ifndef WEEK04_BEER_H
#define WEEK04_BEER_H


class Beer {
private:
    char brand[128];
    unsigned volume;
public:
    Beer();
    Beer(const char*, const unsigned&);
    const char* getBrand() const;
    unsigned getVolume() const;
    void setBrand(const char*);
    void setVolume(const unsigned&);
    void add(Beer&, unsigned);
    bool check(const char*);
};


#endif //WEEK04_BEER_H
