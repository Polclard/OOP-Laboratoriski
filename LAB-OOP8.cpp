#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    //дополнително барање 1
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char * boja_="", int gustina_ = 0)
    {
        strcpy(this->boja, boja_);
        gustina = gustina_;
    }

    Forma(const Forma & that)
    {
        strcpy(this->boja, that.boja);
        gustina = that.gustina;
    }

};

class Topka : public Forma, public Igrachka
{
private:
    int radius;
public:
    Topka(char * boja_="", int gustina_ = 0, int radius_=0) : Forma(boja_, gustina_)
    {
        this->radius = radius_;
    }

    float getMasa() override
    {
        return getVolumen() * (float)gustina;
    }

    float getVolumen() override
    {
        return (double)4/3 * 3.14 * (radius*radius*radius);
    }

    float getPlostina() override
    {
        return 4 * 3.14 * radius * radius;
    }

    ~Topka(){}
};

class Kocka : public Forma, public Igrachka
{
private:
    int visina;
    int sirina;
    int dlabocina;
public:
    Kocka(char * boja_="", int gustina_ = 0, int visina_=0, int sirina_=0, int dlabocina_=0) : Forma(boja_, gustina_)
    {
        this->visina = visina_;
        this->sirina = sirina_;
        this->dlabocina = dlabocina_;
    }

    float getMasa() override
    {
        return getVolumen() * (double)gustina;
    }

    float getPlostina() override
    {
        return (2 * sirina * dlabocina) + (2 * sirina * visina) + (2 * dlabocina * visina);
    }

    float getVolumen() override
    {
        return (double)sirina * (double)dlabocina * (double)visina;
    }

    ~Kocka()
    {}
};

bool daliEPogolema(Igrachka ** niza, int n, Kocka & pet)
{
    double vkupnaMasa = 0.0;
    for(int i = 0; i < n; i++)
    {
        vkupnaMasa += niza[i]->getMasa();
    }
    if(vkupnaMasa > pet.getMasa())
        return true;
    return false;
}

void apsolutnaRazlika(Igrachka ** niza, int n, Kocka & pet)
{
    Igrachka * maksimalnaIgracka = niza[0];
    for(int i = 0; i < n; i++)
    {
        if(maksimalnaIgracka->getVolumen() < niza[i]->getVolumen())
        {
            maksimalnaIgracka = niza[i];
        }
    }

    double finalResult = abs(maksimalnaIgracka->getVolumen() - pet.getVolumen());
    cout << "Razlikata e: " << finalResult << endl;
}

void najmalaApsolutnaRazlika(Igrachka ** niza, int n, Kocka & pet)
{
    Igrachka * minimalnaIgracka = niza[0];
    for(int i = 0; i < n; i++)
    {
        if(minimalnaIgracka->getPlostina() > niza[i]->getPlostina())
        {
            minimalnaIgracka = niza[i];
        }
    }

    double finalResult = abs(minimalnaIgracka->getPlostina() - pet.getPlostina());
    cout << "Razlikata e: " << finalResult << endl;
}

int main(){
    int n;
    cin >> n;
    Igrachka ** kupche = new Igrachka * [n];

    //vnesi informacii za kupche
    for(int i = 0; i < n; i++)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            char boja1[100];
            int gustina;
            int radius;
            cin >> boja1 >> gustina >> radius;
            kupche[i] = new Topka(boja1, gustina, radius);
        }
        else if(type == 2)
        {
            char boja[100];
            int gustina;
            int d;
            int s;
            int v;
            cin >> boja >> gustina >> v >> s >> d;
            kupche[i] = new Kocka(boja, gustina, v, s, d);
        }
    }

    //vnesi informacii za igrachkata na Petra
    char bojaP[100];
    int gustinaP;
    int vP;
    int sP;
    int dP;
    cin >> bojaP >> gustinaP >> vP >> sP >> dP;
    Kocka kockaNaPetra(bojaP, gustinaP, vP, sP, dP);

    //baranje 1
    if(daliEPogolema(kupche, n, kockaNaPetra))
    {
        cout << "DA" << endl;
    }
    else
    {
        cout << "NE" << endl;
    }

    //baranje 2
    apsolutnaRazlika(kupche, n, kockaNaPetra);

    //дополнително барање 2
    najmalaApsolutnaRazlika(kupche, n, kockaNaPetra);

    return 0;
}