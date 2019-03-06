#include <iostream>

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

// Zadanie do wykonania na laboratorium z przedmiotu SPD
// Grupa: Sebastian Kamraj 235273, Tomasz Dybowski ......

// c) algorytm Johnosa- 2,3 maszynowy
// d) przepływ zupełny(2,3 maszynowy)
class Job {
private:
    int numberofproces = 0;
    int numberofmachines = 0;
    int rj = 0; //Czas przygotowania
    int pj = 0; //Czas wykonania
    int qj = 0; //Czas dostarczen
    int tp = 0; //Czas procesu (rj+pj)

public:
    void saveParameters() {
        cout << "Podaj kolejno numerprocesu, maszyne, czas:przygotowania,wykonania,dostarczenia." << endl;
        cin >> numberofproces;
        cin >> numberofmachines;
        cin >> rj;
        cin >> pj;
        cin >> qj;
        tp = rj + pj;
    }

    void savesimply(int numberofproces1, int numberofmachines1) {
        int a;
        cout << "Podaj dlugosc: " << endl;
        numberofproces = numberofproces1;
        numberofmachines = numberofmachines1;
        cin >> a;
        tp = a;
    }

    int returnTimeofallprocess() {

        return tp;
    }

    int returnNumberofprocess() {
        return numberofproces;
    }

    int returnRj() {
        return rj;
    }

    int returnPj() {
        return pj;
    }

    void saveproces(
            int numberofprocess
    ) {
        numberofproces = numberofprocess;
    }

    void savetimeofproces(int timeofproces) {
        tp = timeofproces;

    }

    int returnNumberofmachines() {
        return numberofmachines;
    }

    bool operator<(const Job &first) const {
        return (tp < first.tp);
    }


    friend ostream &operator<<(ostream &out, Job &first);

};

//Pierwsza funkcja dla wariantu jedno maszynowego
int completeOverviewSimply(Job first, Job second, int zeroParametr) {
    static int timeofallprocescomplete = 0;
    int tmp = 0;
    tmp = first.returnTimeofallprocess();
    if (zeroParametr == 1) {
        timeofallprocescomplete = 0;
    }
    if (tmp >= second.returnRj()) {
        tmp = tmp + second.returnPj();
        timeofallprocescomplete = timeofallprocescomplete + tmp;
    } else {
        int tmp1;
        tmp1 = second.returnRj() - first.returnTimeofallprocess();
        timeofallprocescomplete = timeofallprocescomplete + tmp1;
    }
    return timeofallprocescomplete;
}

int completeOverview2machines(vector<Job> tab, vector<Job> tab1, int numberallprocess) {
    int tim1machine = 0;
    int tim2machine = 0;
    int tmp = 0;
    for (int i = 0; i < numberallprocess; i++) {
        tim1machine = tim1machine + tab[i].returnTimeofallprocess();
        tmp = 0;
        while (tab[i].returnNumberofprocess() != tab1[tmp].returnNumberofprocess()) {
            tmp++;
        }

        if (i != 0 && tim1machine <= tim2machine) {
            tim2machine = tim2machine + tab1[tmp].returnTimeofallprocess();
        } else if (i != 0 && tim1machine > tim2machine) {
            tim2machine = tim2machine + (tim1machine - tim2machine);
            tim2machine = tim2machine + tab1[tmp].returnTimeofallprocess();

        }
        if (i == 0) {
            tim2machine = tab[i].returnTimeofallprocess() + tab1[tmp].returnTimeofallprocess();
        }


    }
    for (int i = 0; i < numberallprocess; i++) {
        cout << "Kolejka procesow: " << tab[i].returnNumberofprocess() << ";";
    }
    cout << "Całkowity czas zadania to: " << tim2machine << endl;

}

int JohnsonAlgorithm2machines(vector<Job> tab, vector<Job> tab1, int numberallprocess) {

    static int endtime = 0;
    int tabhelptime[numberallprocess];
    int tabhelpque[numberallprocess];
    int tabelnumbermachines[numberallprocess];
    int tmp = 0;
    int tmp2 = 0;
    int tmp3 = 0;
    int tmp4 = 0;


    sort(tab.begin(), tab.end());
    while (tmp3 != numberallprocess) {
        tmp4 = 0;
        while (tab[tmp3].returnNumberofprocess() != tab1[tmp4].returnNumberofprocess()) {
            tmp4++;
        }
        if (tab[tmp3].returnTimeofallprocess() <= tab1[tmp4].returnTimeofallprocess()) {

            tabhelptime[tmp] = tab[tmp3].returnTimeofallprocess();
            tabhelpque[tmp] = tab[tmp3].returnNumberofprocess();
            tabelnumbermachines[tmp] = tab[tmp3].returnNumberofmachines();


            tmp++;
        } else {
            ++tmp2;
            tabhelptime[numberallprocess - tmp2] = tab1[tmp4].returnTimeofallprocess();
            tabhelpque[numberallprocess - tmp2] = tab1[tmp4].returnNumberofprocess();
            tabelnumbermachines[numberallprocess - tmp2] = tab1[tmp4].returnNumberofmachines();


        }

        tmp3++;
    }
    cout << "Kolejnosc zadan ustalona przez algorytm to: " << endl;
    for (int i = 0; i < numberallprocess; i++) {
        cout << tabhelpque[i] << ";";
    }
    cout << "           " << endl;
    for (int i = 0; i < numberallprocess; i++) {
        int tmp = 0;
        while (tabhelpque[i] != tab1[tmp].returnNumberofprocess()) {
            tmp++;
        }
        endtime = endtime + tab1[tmp].returnTimeofallprocess();
        tmp = 0;
        while (tabhelpque[i] != tab[tmp].returnNumberofprocess()) {
            tmp++;
        }
        endtime = endtime + tab[tmp].returnTimeofallprocess();
    }

    return endtime;


}

void JohnsonAlgorith3machines(vector<Job> tab1, vector<Job> tab2, vector<Job> tab3, int numberofprocess) {
    vector<Job> virtual1, virtual2;
    Job example;
    int tmp = 0;
    int tmp3 = 0;
    int tabque[numberofprocess];
    int totalmakespan = 0;
    int tim1 = 0, tim2 = 0, tim3 = 0;
    for (int i = 0; i < numberofprocess; i++) {
        example.saveproces(tab1[i].returnNumberofprocess());
        example.savetimeofproces(tab1[i].returnTimeofallprocess() + tab2[i].returnTimeofallprocess());
        virtual1.push_back(example);
    }
    for (int i = 0; i < numberofprocess; i++) {
        example.saveproces(tab2[i].returnNumberofprocess());
        example.savetimeofproces(tab2[i].returnTimeofallprocess() + tab3[i].returnTimeofallprocess());
        virtual2.push_back(example);
    }
    sort(virtual1.begin(), virtual1.end());
    while (tmp != numberofprocess) {
        int tmp2 = 0;
        while (virtual1[tmp].returnNumberofprocess() != virtual2[tmp2].returnNumberofprocess()) {
            tmp2++;
        }
        if (virtual1[tmp].returnTimeofallprocess() <= virtual2[tmp2].returnTimeofallprocess()) {
            tabque[tmp] = virtual1[tmp].returnNumberofprocess();
        } else {
            ++tmp3;
            tabque[numberofprocess - tmp3] = virtual2[tmp2].returnNumberofprocess();
        }
        tmp++;

    }
    for (int i = 0; i < numberofprocess; i++) {
        cout << "Kolejne procesy do wykonania to: " << tabque[i] << ";";
    }
    for (int i = 0; i < numberofprocess; i++) {
        int tmp = 0;
        while (tabque[i] != tab1[tmp].returnNumberofprocess()) {
            tmp++;
        }
        tim1 = tab1[tmp].returnTimeofallprocess();
        tmp = 0;
        while (tabque[i] != tab2[tmp].returnNumberofprocess()) {
            tmp++;
            totalmakespan = totalmakespan + tab2[tmp].returnTimeofallprocess();

        }
        tim2 = tab2[tmp].returnTimeofallprocess();
        tmp = 0;
        while (tabque[i] != tab3[tmp].returnNumberofprocess()) {
            tmp++;
        }
        tim3 = tab3[tmp].returnTimeofallprocess();
        if (i == 0) {
            totalmakespan = tim1 + tim2 + tim3;
        }
        if (i = !0 && tim1 < tim2) {
            totalmakespan = totalmakespan + (tim2 - tim1);
            totalmakespan = tim1 + tim2;
        }
        if (i = !0 && tim2 < tim3) {
            totalmakespan = totalmakespan + (tim3 - tim2);
            totalmakespan = tim2 + tim3;
        }

    }
    cout << "Całkowity czas realizacji zadania to: " << totalmakespan << endl;


}

ostream &operator<<(ostream &out, Job &first) {
    out << "Numer wykonanego procesu to: " << first.numberofproces << ", " << "czas wykonania rj to: " << first.rj
        << endl;
    return out;
}

int main() {

    /****************Koniec pierwszej części*******************/
    // Teraz wariant dla 2 maszynowego problemu
/*
    Job fourth;
    vector<Job> tab;
    vector<Job> tab1;
    vector<Job>::iterator it2;
    int decision2;
    cout << "Podaj liczbe elementow dla maszyny1: " << endl;
    cin >> decision2;
    for (int i = 1; i < decision2 + 1; i++) {
        int t = 1;
        fourth.savesimply(i, t);
        tab.push_back(fourth);
    }
    cout << "Podaj liczbe elementow dla maszyny2: " << endl;
    for (int i = 1; i < decision2 + 1; i++) {
        int t = 2;
        fourth.savesimply(i, t);
        tab1.push_back(fourth);
    }
    int tmp;
    tmp = JohnsonAlgorithm(tab, tab1, decision2);
    cout << "Całkowity czas pracy maszyn to (MAKESPAN): " << tmp << endl;
  */
    /************Koniec drugiej części************/
    Job fife;
    vector<Job> tab1, tab2, tab3;
    int decision;
    cout << "Podaj liczbe procesow" << endl;
    cin >> decision;
    for (int i = 1; i < decision + 1; i++) {
        int t = 1;
        fife.savesimply(i, t);
        tab1.push_back(fife);
    }
    for (int i = 1; i < decision + 1; i++) {
        int t = 2;
        fife.savesimply(i, t);
        tab2.push_back(fife);
    }
    for (int i = 1; i < decision + 1; i++) {
        int t = 3;
        fife.savesimply(i, t);
        tab3.push_back(fife);
    }
    JohnsonAlgorith3machines(tab1, tab2, tab3, decision);

    /***************Koniec trzeciej części***********/
    /* Job fife;
     vector<Job> tab1, tab2;
     int decision;
     cout << "Podaj liczbe procesow" << endl;
     cin >> decision;
     for (int i = 1; i < decision + 1; i++) {
         int t = 1;
         fife.savesimply(i, t);
         tab1.push_back(fife);
     }
     for (int i = 1; i < decision + 1; i++) {
         int t = 2;
         fife.savesimply(i, t);
         tab2.push_back(fife);
     }
     //while (next_permutation(tab1.begin(), tab2.end()));
   //  {
         completeOverview2machines(tab1, tab2, decision);
    // }
     */
    return 0;

}
