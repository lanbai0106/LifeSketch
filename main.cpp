#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <time.h>
#include <random>
#include "tool/inc.h"
#include "tool/loadData.h"
#include "report/Frequency/report_N.h"
using namespace std;

int main()
{
    DataLoader data_loader = DataLoader("ca19"); Object obj = data_loader.get_object();
    vector<uint32_t> pac_list  = obj.pac_list; vector<uint64_t> timestamp = obj.timestamp;
    report_N(pac_list, timestamp);
    return 0;
}
