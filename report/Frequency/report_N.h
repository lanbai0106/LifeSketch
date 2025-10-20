#ifndef REPORT_N_H
#include "../../sketch/CM/LifeSketch.h"
#define REPORT_N_H

const int NUM = 3;
map<uint32_t, int> truth_frequency;
pair<uint32_t,uint64_t> strrep[MAX_INSERT_PACKAGE];

vector<double> lsaae_list;
vector<double> lsare_list;

void clear() {
    truth_frequency.clear();
    for (int i = 0; i < MAX_INSERT_PACKAGE; ++i) {
        strrep[i] = {0, 0};
    }
}
void print_result(vector<double> aae_list, vector<double> are_list) {
    cout << "aae: ";
    for(int i = 0;i < 5; i++) {
        cout << aae_list[i] << " " ;
    }
    cout << endl;
    cout << "are: ";
    for(int i = 0;i < 5; i++) {
        cout << are_list[i] << " ";
    }

    cout << endl;
}
void print_results() {
    cout << "LS: \n";
    print_result(lsaae_list,lsare_list);
}
void report_N(vector<uint32_t> pac_list, vector<uint64_t> timestamp) {
    int left = 0, right = 5;
    int N_lsit[6] = {100000,500000,1000000,5000000,10000000};
    int memory = 128 ; memory*=(1024*8);
    int k = 2, d = 4;
    bool ifHSS = 0, ifLS = 1, ifMS = 0, ifSHE = 0, ifSS = 0, ifUCS = 0;

    for(int i = left;i < right;i++) {
        cout << i << " = i" << endl;
        clear();
        int WIN = N_lsit[i];
        double hssaae = 0, lsaae = 0, msaae = 0, sheaae = 0, ucsaae = 0,ssaae = 0;
        double hssare = 0, lsare = 0, msare = 0, sheare = 0, ucsare = 0,ssare = 0;
        double sum_wucha = 0;
        int cnt = 0, pkt = 0, h = 0, t = 0;

        // LS
        int m = memory / (k *42);
        double clean = 0.1;
        auto ls = new LifeSketch_CM<4>(m,WIN,k,clean);

        while (cnt < 100 * (NUM-1)) {
            uint32_t tuple = pac_list[pkt];

            while (h != t && strrep[h].se + WIN <= timestamp[pkt]) {
                truth_frequency[strrep[h].fi] -= 1;
                h++;
            }
            truth_frequency[tuple] += 1;
            strrep[t++] = mp(tuple, timestamp[pkt]);
            if(ifLS) {
                ls->insert(pac_list[pkt], timestamp[pkt]);
                if ((timestamp[pkt] - timestamp[0]) >= WIN && (timestamp[pkt] / (WIN/100)) != (timestamp[pkt-1] / (WIN/100))) {
                    cnt++;
                    int mapsize = 0;
                    double sum_aae = 0, sum_are = 0;
                    for (auto &it: truth_frequency) if (it.se) {
                        mapsize++;
                        double  pre = ls->query(it.fi);
                        sum_aae += abs(it.se - pre);
                        sum_are += abs(it.se - pre)/it.se;
                    }
                    sum_wucha += mapsize;
                    lsaae += sum_aae;
                    lsare += sum_are;
                }
            }

            pkt++;
            if(pkt == MAX_INSERT_PACKAGE )break;
        }
        lsaae_list.push_back(lsaae/sum_wucha);
        lsare_list.push_back(lsare/sum_wucha);
    }

    print_results();
}

#endif //REPORT_N_H
