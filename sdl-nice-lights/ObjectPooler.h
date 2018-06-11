#pragma once
#include <vector>
#include <assert.h>
#include <utility>

/*

Vector wrapper for fast iteration of active objects

*/

template <typename T>
class ObjectPooler
{
public:
	ObjectPooler(int s, bool expand = false) {
		size = s;
		active = 0;
		shouldExpand = expand;
		pool = std::vector<T>();

		for (int i = 0; i < size; i++) {
			pool.push_back(T());
		}
	}

	~ObjectPooler() {

	}

	// retourne un nouvel élément
	int create() {
		if (active == size && shouldExpand) {
			size *= 2;
			pool.resize(size);
		} 

		activate(active);
		return active - 1;
	}

	T& getNew() {
		return get(create());
	}

	T& get(int index) {

		assert(index < size);

		return pool[index];
	}

	T& operator[](int i) {
		return get(i);
	}

	const int& activeTotal() const {
		return active;
	}

	void activate(int index) {

		if (index >= size) // trop grand
			return;
		if (index < active) // déjà actif
			return;

		/*T temp = m_pool[m_active];
		m_pool[m_active] = m_pool[index];
		m_pool[index] = temp;*/

		std::swap(pool[active], pool[index]);

		active++;
	}

	void swap(size_t pos1, size_t pos2) {
		std:swap(pool[pos1], pool[pos2]);
	}

	void deactivate(int index) {
		if (index >= size) // trop grand
			return;
		if (index >= active) // déjà inactif
			return;

		active--;

		pool[index] = pool[active];
		pool[active] = m_default;
	}

private:
	bool shouldExpand;
	int size;
	int active;
	std::vector<T> pool;
};