#ifndef LIFESKETCH_H
#define LIFESKETCH_H
template<uint32_t key_len> struct LifeSketch_CM {
	int win, m, k;
	double clean;
	long long sum = 0;
	long long a[HASHMAX][COLMAX];
	uint64_t lst = -1;
	double ratio;
	int pointer = 0;
	BOBHash32 **hash;

	LifeSketch_CM(int _m, int _win, int _k, double _clean) : m(_m), win(_win), k(_k), clean(_clean) {
		rep2 (i, 0, k) {
			rep2 (j, 0, m) {
                a[i][j] = 0;
            }
		}
		double tmp = pow( 1.0-2.0/(double(win)+1.0),m/clean);
		ratio = 1.0-tmp;
		// ratio = pow( 1.0-2.0/(double(win)+1.0),m/clean);
		hash = new BOBHash32*[HASHMAX];
		rep2 (i, 0, k) hash[i] = new BOBHash32(uint8_t(rd() % MAX_PRIME32));
	}

	void insert(uint32_t key, uint64_t clock) {
		if (clock != lst) {
			if(clean>=1) {
				int tmp = clean;
				while(tmp--) {
					rep2 (i, 0, k) {
						int dre = a[i][pointer]*ratio;
						a[i][pointer] -= dre;
						// a[i][pointer]*=ratio;
					}
					pointer = (pointer + 1) % m;
				}
			}else {
				int tmp = 1/clean;

				if((clock % tmp)==0) {
					rep2 (i, 0, k) {
						a[i][pointer] -= a[i][pointer]*ratio;
						// a[i][pointer]*=ratio;
					}
					pointer = (pointer + 1) % m;
				}
			}
		}
		int hashid[k];
		rep2 (i, 0, k) hashid[i] = hash[i]->run((char *)&key, key_len) % m;
		rep2 (i, 0, k) {
			// int pos = hash[i]->run((char *)&key, key_len) % m;
			a[i][hashid[i]] += win;
		}


		lst = clock;
	}

	double query(uint32_t key) {
		int hashid[k];

		rep2 (i, 0, k) hashid[i] = hash[i]->run((char *)&key, key_len) % m;
  //       long long ans = 1e7;
		// rep2 (i, 0, k) {
		// 	long long pre = (a[i][hashid[i]] << 1)/(win+1);
		// 	ans = min(pre, ans );
		// 	// ans = min(a[i][hashid[i]], ans );
  //
		// }
		// return ans;

		long long ans = 1LL << 62 ;
		rep2 (i, 0, k) {
			ans = min(a[i][hashid[i]], ans );
			// ans = min(a[i][hashid[i]], ans );

		}
		return (ans<< 1)/(win+1);
	}
};

#endif //LIFESKETCH_H
