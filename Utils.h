#pragma once
#include "stdafx.h"

class Utils {
    public:
        template <class T>
            static T* vectorToArray(vector<T*>& v) {
                T* array = new T[v.size()];

                for(unsigned int i = 0; i < v.size(); i++) {
                    array[i] = *v[i];
                }

                return array;
            }

        template <class T>
            static vector <T> arrayToVector(T* array, int size) {
                vector <T> v;
                v.reserve(size);

                for(int i=0; i<size; i++) {
                    v.push_back(array[i]);
                }

                return v;
            }

        static float distance(vec2 a, vec2 b) {
            return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
        }

        static void printPlayersArray(Player* array, int size) {
		for (int i = 0; i < size; i++) {
			cout << array[i].id << ", " << array[i].isHurt << "\n";
		}
	}
};
