#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;



// a) algorytm Johnsona- 2,3 maszynowy
// b) przepływ zupełny(1,2 maszynowy)
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

    void savesimplyforinstant(int numberofproces1, int timeofproces1, int numberofmachines1) {
        numberofproces = numberofproces1;
        tp = timeofproces1;
        numberofmachines = numberofmachines1;
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
    void saveNumbermachines(int i)
    {
        numberofmachines=i;
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

    int tabhelpque[]={0,0,0};
    int tmp = 0;
    int tmp3 = 0;
    int help=0;
    int tim1=0,tim2=0;
    vector<Job> virtual3;

    for(int i=0;i<tab.size();i++)
    {
        virtual3.push_back(tab[i]);
        virtual3.push_back(tab1[i]);

    }
    sort(virtual3.begin(), virtual3.end());
    while (tmp != numberallprocess*2) {
        int w1=0;
        int w2=0;

        if (virtual3[tmp].returnNumberofmachines() == 1) {
            for (int i = 0; i < numberallprocess*2; i++) {
                if (tabhelpque[i] == virtual3[tmp].returnNumberofprocess()) {
                    w1 = 1;
                }
            }
            if (w1 ==0 ) {
                tabhelpque[help] = virtual3[tmp].returnNumberofprocess();
                help++;
            }
        } else {
            for (int i = 0; i < numberallprocess*2; i++) {
                if (tabhelpque[i] == virtual3[tmp].returnNumberofprocess()) {
                    w2 = 1;
                }
            }
            if (w2 == 0) {
                ++tmp3;
                tabhelpque[numberallprocess - tmp3] = virtual3[tmp].returnNumberofprocess();
            }
        }
        tmp++;
    }
    cout << "Kolejnosc zadan ustalona przez algorytm to: " << endl;
    for (int i = 0; i < numberallprocess; i++) {
        cout << tabhelpque[i] << ";";
    }
    cout << "           " << endl;
    for (int i = 0; i < numberallprocess; i++) {
        int tmphelp1 = 0, tmphelp2 = 0, tmphelp3 = 0;
        while (tabhelpque[i] != tab[tmphelp1].returnNumberofprocess()) {
            tmphelp1++;
        }
        tim1 = tim1 + tab[tmphelp1].returnTimeofallprocess();
        while (tabhelpque[i] != tab1[tmphelp2].returnNumberofprocess()) {
            tmphelp2++;
        }
        if (i != 0 && tab[tmphelp1].returnTimeofallprocess() > tab1[tmphelp2].returnTimeofallprocess() &&
            tim1 > tim2) {
            int value;
            value = tab[tmphelp1].returnTimeofallprocess() - tab1[tmphelp2].returnTimeofallprocess();
            tim2 = tim2 + value;
        }
        tim2 = tim2 + tab1[tmphelp2].returnTimeofallprocess();
        if (i == 0) {
            tim2 = tim2 + tim1;
        }
    }
    cout << "Całkowity czas realizacji zadania to: " << tim2 << endl;
    return tim2;

}

void JohnsonAlgorith3machines(vector<Job> tab1, vector<Job> tab2, vector<Job> tab3, int numberofprocess) {
    vector<Job> virtual1, virtual2, virtual3;
    Job example;
    int tmp = 0;
    int tmp3 = 0;
    int tabque[]={0,0,0,0};
    int tim1 = 0, tim2 = 0, tim3 = 0, help = 0;
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
    sort(virtual2.begin(), virtual2.end());
    for (int i = 0; i < virtual1.size() ; i++) {
        virtual1[i].saveNumbermachines(1);
        virtual3.push_back(virtual1[i]);


    }
    for(int i=0;i<virtual2.size();i++)
    {
        virtual2[i].saveNumbermachines(2);
        virtual3.push_back(virtual2[i]);

    }
    sort(virtual3.begin(), virtual3.end());
    while (tmp != 8) {
        int w1=0;
        int w2=0;

        if (virtual3[tmp].returnNumberofmachines() == 1) {
            for (int i = 0; i < 8; i++) {
                if (tabque[i] == virtual3[tmp].returnNumberofprocess()) {
                    w1 = 1;
                }
            }
            if (w1 ==0 ) {
                tabque[help] = virtual3[tmp].returnNumberofprocess();
                help++;
            }
        } else {
            for (int i = 0; i < 8; i++) {
                if (tabque[i] == virtual3[tmp].returnNumberofprocess()) {
                    w2 = 1;
                }
            }
            if (w2 == 0) {
                ++tmp3;
                tabque[numberofprocess - tmp3] = virtual3[tmp].returnNumberofprocess();
            }
        }
        tmp++;
    }

        cout << "Kolejny procesy do wykoniania to: " << endl;
        for (int i = 0; i < numberofprocess; i++) {
            cout << tabque[i] << ";";
        }
        cout << endl;
        for (int i = 0; i < numberofprocess; i++) {
            int tmphelp1 = 0, tmphelp2 = 0, tmphelp3 = 0;
            while (tabque[i] != tab1[tmphelp1].returnNumberofprocess()) {
                tmphelp1++;
            }
            tim1 = tim1 + tab1[tmphelp1].returnTimeofallprocess();
            while (tabque[i] != tab2[tmphelp2].returnNumberofprocess()) {
                tmphelp2++;
            }
            if (i != 0 && tab1[tmphelp1].returnTimeofallprocess() > tab2[tmphelp2].returnTimeofallprocess() &&
                tim1 > tim2) {
                int value;
                value = tab1[tmphelp1].returnTimeofallprocess() - tab2[tmphelp2].returnTimeofallprocess();
                tim2 = tim2 + value;
            }
            tim2 = tim2 + tab2[tmphelp2].returnTimeofallprocess();
            while (tabque[i] != tab3[tmphelp3].returnNumberofprocess()) {
                tmphelp3++;
            }
            if (i != 0 && tab2[tmphelp2].returnTimeofallprocess() > tab3[tmphelp3].returnTimeofallprocess() &&
                tim2 > tim3) {
                int value;
                value = tab2[tmphelp2].returnTimeofallprocess() - tab3[tmphelp3].returnTimeofallprocess();
                tim3 = tim3 + value;
            }
            tim3 = tim3 + tab3[tmphelp3].returnTimeofallprocess();
            if (i == 0) {
                tim2 = tim2 + tim1;
                tim3 = tim2 + tim3;
            }

        }

        cout << "Całkowity czas realizacji zadania to: " << tim3 << endl;


    }

    ostream &operator<<(ostream &out, Job &first) {
        out << "Numer wykonanego procesu to: " << first.numberofproces << ", " << "czas wykonania rj to: " << first.rj
            << endl;
        return out;
    }

    int main() {
        int n, p1[100], p2[100], p3[100];
        ifstream data("data.txt");
        data >> n;
        for (int i = 0; i < n; i++) {
            data >> p1[i] >> p2[i] >> p3[i];
        }
        data.close();
        cout << " DATA " << n << endl;


        /************Koniec drugiej części************/


      Job fife;
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
      do
      {
          completeOverview2machines(tab1, tab2, decision);
      }while (next_permutation(tab1.begin(), tab1.end()));


        /****************Koniec drugiej części*******************/
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
        tmp = JohnsonAlgorithm2machines(tab, tab1, decision2);
        cout << "Całkowity czas pracy maszyn to (MAKESPAN): " << tmp << endl;
        */
/************Koniec trzeciej części************/
  /*      Job fife;
        vector<Job> tab1, tab2, tab3;
        int tmp = 1;

        for (int i = 0; i < n; i++) {
            int t = 1;
            fife.savesimplyforinstant(tmp, p1[i], t);
            tab1.push_back(fife);
            tmp++;
        }
        tmp = 1;
        for (int i = 0; i < n; i++) {
            int t = 2;
            fife.savesimplyforinstant(tmp, p2[i], t);
            tab2.push_back(fife);
            tmp++;
        }
        tmp = 1;
        for (int i = 0; i < n; i++) {
            int t = 3;
            fife.savesimplyforinstant(tmp, p3[i], t);
            tab3.push_back(fife);
            tmp++;
        }
        JohnsonAlgorith3machines(tab1, tab2, tab3, n);
        */
        return 0;


    }
